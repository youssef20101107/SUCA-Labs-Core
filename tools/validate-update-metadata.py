#!/usr/bin/env python3
from pathlib import Path
import argparse

REQUIRED = {
    "release_id", "version", "channel", "architecture", "device_profiles",
    "min_version", "payload", "payload_sha256", "signature", "size_bytes",
    "rollout_percent", "health_check_timeout", "previous_slot", "boot_attempt_limit",
    "recovery_action",
}
CHANNELS = {"stable", "beta", "developer", "recovery"}


def parse(path: Path):
    values = {}
    for raw in path.read_text(encoding="utf-8").splitlines():
        line = raw.strip()
        if not line or line.startswith("#") or "=" not in line:
            continue
        key, value = line.split("=", 1)
        values[key.strip()] = value.strip()
    return values


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("metadata", type=Path)
    parser.add_argument("--template", action="store_true")
    args = parser.parse_args()
    values = parse(args.metadata)
    missing = sorted(REQUIRED - values.keys())
    if missing:
        raise SystemExit(f"missing fields: {', '.join(missing)}")
    if values["architecture"] != "aarch64":
        raise SystemExit("only aarch64 is allowed by this release profile")
    if values["channel"] not in CHANNELS:
        raise SystemExit(f"invalid channel: {values['channel']}")
    rollout = int(values["rollout_percent"])
    if not 0 <= rollout <= 100:
        raise SystemExit("rollout_percent must be between 0 and 100")
    if int(values["size_bytes"]) < 0 or int(values["health_check_timeout"]) <= 0:
        raise SystemExit("invalid numeric update metadata")
    if not args.template:
        if len(values["payload_sha256"]) != 64 or values["payload_sha256"].startswith("REPLACE_"):
            raise SystemExit("payload_sha256 must be a real SHA256 before release")
        if values["signature"].startswith("REPLACE_"):
            raise SystemExit("signature must be present before release")
    print(f"PASS {values['release_id']} channel={values['channel']} rollout={rollout}%")


if __name__ == "__main__":
    main()
