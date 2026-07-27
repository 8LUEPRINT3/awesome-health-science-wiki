"""
IOC Enricher Tool
Queries VirusTotal, AbuseIPDB, and Shodan to enrich threat indicators.
"""
import os
import re
import requests
import json

VT_KEY       = os.getenv("VIRUSTOTAL_API_KEY", "")
ABUSEIPDB_KEY= os.getenv("ABUSEIPDB_API_KEY", "")
SHODAN_KEY   = os.getenv("SHODAN_API_KEY", "")

TIMEOUT = 10

def detect_ioc_type(ioc: str) -> str:
    ioc = ioc.strip()
    if re.match(r'^[\da-fA-F]{32}$', ioc):   return "hash_md5"
    if re.match(r'^[\da-fA-F]{40}$', ioc):   return "hash_sha1"
    if re.match(r'^[\da-fA-F]{64}$', ioc):   return "hash_sha256"
    if re.match(r'^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$', ioc): return "ip"
    if re.match(r'^https?://', ioc):          return "url"
    if re.match(r'^[a-zA-Z0-9\-\.]+\.[a-zA-Z]{2,}$', ioc): return "domain"
    return "unknown"

def enrich_ioc(ioc: str, ioc_type: str = "auto") -> str:
    ioc = ioc.strip()
    if ioc_type == "auto":
        ioc_type = detect_ioc_type(ioc)

    results = [f"IOC ENRICHMENT REPORT\n{'='*40}",
               f"IOC:  {ioc}",
               f"Type: {ioc_type}\n"]

    # VirusTotal
    if VT_KEY:
        vt = _query_virustotal(ioc, ioc_type)
        results.append("VIRUSTOTAL:\n" + vt)
    else:
        results.append("VIRUSTOTAL: [API key not set — add VIRUSTOTAL_API_KEY to .env]")

    # AbuseIPDB (IPs only)
    if ioc_type == "ip":
        if ABUSEIPDB_KEY:
            abuse = _query_abuseipdb(ioc)
            results.append("\nABUSEIPDB:\n" + abuse)
        else:
            results.append("\nABUSEIPDB: [API key not set — add ABUSEIPDB_API_KEY to .env]")

        # Shodan (IPs only)
        if SHODAN_KEY:
            shodan = _query_shodan(ioc)
            results.append("\nSHODAN:\n" + shodan)
        else:
            results.append("\nSHODAN: [API key not set — add SHODAN_API_KEY to .env]")

    # Free WHOIS/DNS for domains
    if ioc_type in ("domain", "ip"):
        whois = _query_whois_free(ioc)
        results.append("\nWHOIS/DNS:\n" + whois)

    return '\n'.join(results)

def _query_virustotal(ioc, ioc_type):
    try:
        if "hash" in ioc_type:
            url = f"https://www.virustotal.com/api/v3/files/{ioc}"
        elif ioc_type == "ip":
            url = f"https://www.virustotal.com/api/v3/ip_addresses/{ioc}"
        elif ioc_type == "domain":
            url = f"https://www.virustotal.com/api/v3/domains/{ioc}"
        elif ioc_type == "url":
            import base64
            url_id = base64.urlsafe_b64encode(ioc.encode()).decode().strip("=")
            url = f"https://www.virustotal.com/api/v3/urls/{url_id}"
        else:
            return "  Unsupported IOC type for VT lookup"

        r = requests.get(url, headers={"x-apikey": VT_KEY}, timeout=TIMEOUT)
        if r.status_code == 404:
            return "  Not found in VirusTotal"
        if r.status_code == 401:
            return "  Invalid API key"
        if not r.ok:
            return f"  HTTP {r.status_code}"

        data = r.json().get("data", {}).get("attributes", {})
        stats = data.get("last_analysis_stats", {})
        mal   = stats.get("malicious", 0)
        sus   = stats.get("suspicious", 0)
        total = sum(stats.values()) if stats else 0
        reputation = data.get("reputation", "N/A")

        verdict = "🔴 MALICIOUS" if mal >= 3 else "🟡 SUSPICIOUS" if (mal > 0 or sus > 0) else "🟢 CLEAN"
        out = [f"  Verdict:    {verdict}"]
        out.append(f"  Detections: {mal} malicious, {sus} suspicious / {total} engines")
        out.append(f"  Reputation: {reputation}")

        # Last seen / tags
        tags = data.get("tags", [])
        if tags:
            out.append(f"  Tags:       {', '.join(tags[:6])}")

        categories = data.get("categories", {})
        if categories:
            cats = list(set(categories.values()))[:3]
            out.append(f"  Categories: {', '.join(cats)}")

        return '\n'.join(out)

    except requests.RequestException as e:
        return f"  Request failed: {e}"
    except Exception as e:
        return f"  Error: {e}"

def _query_abuseipdb(ip):
    try:
        r = requests.get(
            "https://api.abuseipdb.com/api/v2/check",
            headers={"Key": ABUSEIPDB_KEY, "Accept": "application/json"},
            params={"ipAddress": ip, "maxAgeInDays": 90, "verbose": True},
            timeout=TIMEOUT
        )
        if not r.ok:
            return f"  HTTP {r.status_code}"

        d = r.json().get("data", {})
        score   = d.get("abuseConfidenceScore", 0)
        country = d.get("countryCode", "?")
        isp     = d.get("isp", "?")
        reports = d.get("totalReports", 0)
        usage   = d.get("usageType", "?")
        tor     = d.get("isTor", False)

        verdict = "🔴 HIGH RISK" if score >= 75 else "🟡 MEDIUM" if score >= 25 else "🟢 LOW RISK"
        out = [
            f"  Verdict:     {verdict} (score: {score}/100)",
            f"  Country:     {country}",
            f"  ISP:         {isp}",
            f"  Usage Type:  {usage}",
            f"  Reports:     {reports} (last 90 days)",
            f"  Tor Exit:    {'Yes ⚠' if tor else 'No'}",
        ]

        # Show recent report categories
        reports_list = d.get("reports", [])[:3]
        if reports_list:
            out.append("  Recent Categories:")
            for rep in reports_list:
                cats = rep.get("categories", [])
                out.append(f"    • {', '.join(str(c) for c in cats)}")

        return '\n'.join(out)

    except Exception as e:
        return f"  Error: {e}"

def _query_shodan(ip):
    try:
        r = requests.get(
            f"https://api.shodan.io/shodan/host/{ip}",
            params={"key": SHODAN_KEY},
            timeout=TIMEOUT
        )
        if r.status_code == 404:
            return "  Not found in Shodan"
        if not r.ok:
            return f"  HTTP {r.status_code}"

        d = r.json()
        org    = d.get("org", "?")
        os_    = d.get("os", "?")
        ports  = d.get("ports", [])
        vulns  = list(d.get("vulns", {}).keys())
        hostnames = d.get("hostnames", [])

        out = [
            f"  Org:       {org}",
            f"  OS:        {os_}",
            f"  Ports:     {', '.join(str(p) for p in ports[:15])}",
            f"  Hostnames: {', '.join(hostnames[:5]) or 'None'}",
        ]
        if vulns:
            out.append(f"  ⚠ CVEs:   {', '.join(vulns[:8])}")

        return '\n'.join(out)

    except Exception as e:
        return f"  Error: {e}"

def _query_whois_free(ioc):
    """Free DNS/WHOIS via public APIs (no key needed)"""
    try:
        # Use ip-api.com for IPs (free, no key)
        if re.match(r'^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$', ioc):
            r = requests.get(f"http://ip-api.com/json/{ioc}?fields=status,country,regionName,city,org,as,isp,proxy,hosting,mobile", timeout=TIMEOUT)
            d = r.json()
            if d.get("status") == "success":
                return (f"  Country:  {d.get('country','?')} / {d.get('regionName','?')} / {d.get('city','?')}\n"
                        f"  Org:      {d.get('org','?')}\n"
                        f"  ASN:      {d.get('as','?')}\n"
                        f"  ISP:      {d.get('isp','?')}\n"
                        f"  Proxy:    {'Yes ⚠' if d.get('proxy') else 'No'} | "
                        f"Hosting: {'Yes' if d.get('hosting') else 'No'}")
        else:
            # DNS lookup for domains via Google DNS-over-HTTPS
            r = requests.get(
                f"https://dns.google/resolve",
                params={"name": ioc, "type": "A"},
                timeout=TIMEOUT
            )
            d = r.json()
            answers = d.get("Answer", [])
            if answers:
                ips = [a["data"] for a in answers if a.get("type") == 1]
                return f"  A Records: {', '.join(ips[:5])}"
            return "  No DNS A records found"
    except Exception as e:
        return f"  Error: {e}"
