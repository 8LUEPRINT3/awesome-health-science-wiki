"""
Log Analyzer Tool
Parses and pre-processes log files before sending to the LLM for threat analysis.
"""
import re
from collections import Counter
from datetime import datetime

# Suspicious patterns to highlight before LLM analysis
THREAT_PATTERNS = {
    "brute_force":     r"(Failed password|authentication failure|Invalid user|failed login)",
    "privilege_esc":   r"(sudo|su -|privilege|NOPASSWD|wheel)",
    "persistence":     r"(crontab|rc\.local|systemd|\.bashrc|\.profile|autorun)",
    "lateral_move":    r"(ssh|psexec|wmic|schtasks|at\.exe|net use)",
    "exfiltration":    r"(curl|wget|ftp|scp|rsync|base64|nc |ncat|netcat)",
    "c2_beacon":       r"(User-Agent:.*python|curl|wget|powershell.*encoded|/beacon|/check-in)",
    "web_attack":      r"(union.*select|<script|../|etc/passwd|cmd\.exe|\.php\?.*=http)",
    "malware_artifact":r"(\.exe|\.ps1|\.vbs|\.bat|mshta|regsvr32|certutil|bitsadmin)",
}

def analyze_logs(log_text: str, log_type: str = "generic") -> str:
    if not log_text.strip():
        return "Error: No log content provided."

    lines = log_text.strip().split('\n')
    total_lines = len(lines)

    # Pre-analysis: find pattern hits
    hits = {}
    for pattern_name, pattern in THREAT_PATTERNS.items():
        matches = [l for l in lines if re.search(pattern, l, re.IGNORECASE)]
        if matches:
            hits[pattern_name] = matches[:5]  # cap at 5 examples

    # Extract IPs
    ips = re.findall(r'\b(?:\d{1,3}\.){3}\d{1,3}\b', log_text)
    ip_counts = Counter(ips).most_common(10)

    # Extract usernames (common patterns)
    users = re.findall(r'(?:user|for|username)[= ]+(\w+)', log_text, re.IGNORECASE)
    user_counts = Counter(users).most_common(5)

    # Build structured summary for LLM
    summary = f"""LOG ANALYSIS REQUEST
====================
Log Type: {log_type}
Total Lines: {total_lines}

PATTERN MATCHES FOUND:
{_fmt_hits(hits)}

TOP IP ADDRESSES:
{_fmt_counter(ip_counts)}

TOP USERNAMES SEEN:
{_fmt_counter(user_counts)}

RAW LOG SAMPLE (first 80 lines):
{chr(10).join(lines[:80])}

{'[... ' + str(total_lines - 80) + ' more lines truncated ...]' if total_lines > 80 else ''}
"""
    return summary

def _fmt_hits(hits):
    if not hits:
        return "  None detected"
    out = []
    for name, examples in hits.items():
        out.append(f"\n  ⚠ {name.upper().replace('_',' ')} ({len(examples)} matches):")
        for ex in examples[:3]:
            out.append(f"    → {ex.strip()[:120]}")
    return '\n'.join(out)

def _fmt_counter(items):
    if not items:
        return "  None found"
    return '\n'.join(f"  {val}: {count}" for val, count in items)
