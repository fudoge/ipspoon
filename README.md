# 🥄 ipspoon

**Lightweight DNS resolver - Not a dig, just a scoop.**

ipspoon is a simple CLI utility for quick DNS lookups, supporting both IPv4 and IPv6 lookup.

## Setup
```bash
sudo ./setup.sh
```
GNU Compiler Collection(GCC) is required.

## Uninstall
```bash
sudo ./uninstall.sh
```

## Usage
```bash
ipspoon --version         # Version lookup
ipspoon -h <hostname>     # Forward lookup (hostname → IPs)
ipspoon -4 <IPv4>         # Reverse lookup (IPv4 → hostname)
ipspoon -6 <IPv6>         # Reverse lookup (IPv6 → hostname)

```
