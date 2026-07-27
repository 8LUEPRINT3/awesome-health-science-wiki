# TOOLS.md - Local Notes

Skills define _how_ tools work. This file is for _your_ specifics — the stuff that's unique to your setup.

## What Goes Here

Things like:

- Camera names and locations
- SSH hosts and aliases
- Preferred voices for TTS
- Speaker/room names
- Device nicknames
- Anything environment-specific

## Examples

```markdown
### Cameras

- living-room → Main area, 180° wide angle
- front-door → Entrance, motion-triggered

### SSH

- home-server → 192.168.1.100, user: admin

### TTS

- Preferred voice: "Nova" (warm, slightly British)
- Default speaker: Kitchen HomePod
```
## Installed Skills

### ponytail-auditor
**Trigger:** "audit code", "reduce bloat", or "run ponytail"
**Capability:** Scans the codebase to enforce YAGNI (You Aren't Gonna Need It) and reduce output token costs.
**Execution:** Run the wrapper script via the exec tool: `/home/asauce/.openclaw/workspace/scripts/run-ponytail.sh [target_directory]`

## Why Separate?

Skills are shared. Your setup is yours. Keeping them apart means you can update skills without losing your notes, and share skills without leaking your infrastructure.

---

Add whatever helps you do your job. This is your cheat sheet.
