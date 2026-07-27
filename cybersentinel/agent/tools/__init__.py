from .log_analyzer import analyze_logs
from .ioc_enricher import enrich_ioc
from .pcap_analyzer import analyze_pcap
from .rule_writer import write_detection_rule
from .playbook_gen import incident_playbook
from .scanner import run_scan
import json

# Tool schemas for Groq function calling
TOOLS = [
    {
        "type": "function",
        "function": {
            "name": "analyze_logs",
            "description": "Analyze log data (auth.log, syslog, Windows Event logs, nginx, etc.) for security threats, anomalies, and suspicious patterns.",
            "parameters": {
                "type": "object",
                "properties": {
                    "log_text": {"type": "string", "description": "Raw log content to analyze"},
                    "log_type": {"type": "string", "description": "Type of log: auth, syslog, windows_event, nginx, apache, firewall, generic", "default": "generic"}
                },
                "required": ["log_text"]
            }
        }
    },
    {
        "type": "function",
        "function": {
            "name": "enrich_ioc",
            "description": "Enrich an Indicator of Compromise (IOC) — IP address, domain, file hash, or URL — using threat intelligence sources.",
            "parameters": {
                "type": "object",
                "properties": {
                    "ioc": {"type": "string", "description": "The IOC to look up (IP, domain, MD5/SHA256 hash, or URL)"},
                    "ioc_type": {"type": "string", "description": "Type: ip, domain, hash, url", "default": "auto"}
                },
                "required": ["ioc"]
            }
        }
    },
    {
        "type": "function",
        "function": {
            "name": "analyze_pcap",
            "description": "Analyze a PCAP file for suspicious network activity, C2 beacons, data exfiltration, port scans, and other threats.",
            "parameters": {
                "type": "object",
                "properties": {
                    "pcap_path": {"type": "string", "description": "Path to the .pcap or .pcapng file"},
                    "focus": {"type": "string", "description": "Focus area: c2, exfil, scan, all", "default": "all"}
                },
                "required": ["pcap_path"]
            }
        }
    },
    {
        "type": "function",
        "function": {
            "name": "write_detection_rule",
            "description": "Write a detection rule in Sigma, YARA, or Snort/Suricata format based on threat behavior description.",
            "parameters": {
                "type": "object",
                "properties": {
                    "behavior": {"type": "string", "description": "Description of the threat behavior to detect"},
                    "rule_format": {"type": "string", "description": "Format: sigma, yara, snort, suricata", "default": "sigma"},
                    "context": {"type": "string", "description": "Additional context like IOCs, affected systems, etc.", "default": ""}
                },
                "required": ["behavior", "rule_format"]
            }
        }
    },
    {
        "type": "function",
        "function": {
            "name": "incident_playbook",
            "description": "Generate a step-by-step incident response playbook for a given incident type.",
            "parameters": {
                "type": "object",
                "properties": {
                    "incident_type": {"type": "string", "description": "Type of incident: ransomware, phishing, data_breach, c2, insider_threat, ddos, etc."},
                    "environment": {"type": "string", "description": "Environment details: cloud provider, OS, network size", "default": ""},
                    "severity": {"type": "string", "description": "Severity: low, medium, high, critical", "default": "high"}
                },
                "required": ["incident_type"]
            }
        }
    },
    {
        "type": "function",
        "function": {
            "name": "run_scan",
            "description": "Run network reconnaissance tools (nmap, whois, dig) against a target.",
            "parameters": {
                "type": "object",
                "properties": {
                    "target": {"type": "string", "description": "Target IP, domain, or CIDR range"},
                    "scan_type": {"type": "string", "description": "Type: nmap_quick, nmap_full, nmap_vuln, whois, dns", "default": "nmap_quick"}
                },
                "required": ["target"]
            }
        }
    }
]

def execute_tool(name: str, args: dict) -> str:
    try:
        if name == "analyze_logs":
            return analyze_logs(**args)
        elif name == "enrich_ioc":
            return enrich_ioc(**args)
        elif name == "analyze_pcap":
            return analyze_pcap(**args)
        elif name == "write_detection_rule":
            return write_detection_rule(**args)
        elif name == "incident_playbook":
            return incident_playbook(**args)
        elif name == "run_scan":
            return run_scan(**args)
        else:
            return f"Unknown tool: {name}"
    except Exception as e:
        return f"Tool error ({name}): {str(e)}"
