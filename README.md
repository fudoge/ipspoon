# 🥄 ipspoon

**Lightweight DNS resolver - Not a dig, just a scoop.**

ipspoon is a simple CLI utility for quick DNS lookups, supporting both IPv4 and IPv6 lookup.

## Setup
```
sudo ./setup.sh
```
requires GNU Compiler Collection(GCC).

## Usage
```bash
ipspoon -h <hostname>     # Forward lookup (hostname → IPs)
ipspoon -4 <IPv4>         # Reverse lookup (IPv4 → hostname)
ipspoon -6 <IPv6>         # Reverse lookup (IPv6 → hostname)

```
