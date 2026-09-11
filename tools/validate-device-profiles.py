#!/usr/bin/env python3
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DEVICE_ROOT = ROOT / "hardware" / "devices"
REQUIRED = {
    "profile_id", "model", "architecture", "soc_family",
    "boot_image_policy", "dtb_required", "support_level",
}
ALLOWED_ARCHITECTURES = {"aarch64", "armhf"}
ALLOWED_LEVELS = {"boot-only", "basic-ui", "usable", "hardware", "daily-driver"}


def parse(path: Path):
    values = {}
    for raw in path.read_text(encoding="utf-8").splitlines():
        line = raw.strip()
        if not line or line.startswith("#") or line.startswith("[") or "=" not in line:
            continue
        key, value = line.split("=", 1)
        values[key.strip()] = value.strip()
    if "level" in values and "support_level" not in values:
        values["support_level"] = values["level"]
    return values


def main():
    profiles = sorted(DEVICE_ROOT.glob("*/device.conf"))
    if not profiles:
        raise SystemExit("no device profiles found")
    for path in profiles:
        values = parse(path)
        missing = sorted(REQUIRED - values.keys())
        if missing:
            raise SystemExit(f"{path}: missing {', '.join(missing)}")
        if values["architecture"] not in ALLOWED_ARCHITECTURES:
            raise SystemExit(f"{path}: unsupported architecture {values['architecture']}")
        if values["boot_image_policy"] != "separate-test-image":
            raise SystemExit(f"{path}: unsafe boot image policy")
        if values["support_level"] not in ALLOWED_LEVELS and not values["support_level"].startswith("basic-ui-until"):
            raise SystemExit(f"{path}: invalid support level {values['support_level']}")
        print(f"PASS {values['profile_id']} {values['model']} level={values['support_level']}")


if __name__ == "__main__":
    main()
