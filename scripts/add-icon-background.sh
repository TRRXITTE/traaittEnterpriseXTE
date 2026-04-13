#!/usr/bin/env bash
# add-icon-background.sh
# Composite a #191919 background onto the transparent app.icns so it looks
# correct on macOS Ventura+ (which no longer whitens transparent dock icons).
#
# Requirements (install once):
#   brew install imagemagick
#
# Usage:
#   ./scripts/add-icon-background.sh
#   ./scripts/add-icon-background.sh --input app/app.icns --output app/app.icns

set -euo pipefail

# ── Defaults ──────────────────────────────────────────────────────────────────
REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
INPUT_ICNS="$REPO_ROOT/app/app.icns"
OUTPUT_ICNS="$REPO_ROOT/app/app.icns"
BG_COLOR="#191919"
WORK_DIR="$REPO_ROOT/.iconbuild"
ICONSET_DIR="$WORK_DIR/AppIcon.iconset"

# Parse named arguments
while [[ $# -gt 0 ]]; do
  case $1 in
    --input)  INPUT_ICNS="$2"; shift 2 ;;
    --output) OUTPUT_ICNS="$2"; shift 2 ;;
    *) shift ;;
  esac
done

# ── Dependency check ──────────────────────────────────────────────────────────
if ! command -v magick &>/dev/null && ! command -v convert &>/dev/null; then
  echo "[add-icon-background] ERROR: ImageMagick not found."
  echo "  Install with: brew install imagemagick"
  exit 1
fi

if ! command -v iconutil &>/dev/null; then
  echo "[add-icon-background] ERROR: iconutil not found (macOS-only tool)."
  exit 1
fi

if [[ ! -f "$INPUT_ICNS" ]]; then
  echo "[add-icon-background] ERROR: Input icns not found: $INPUT_ICNS"
  exit 1
fi

echo "[add-icon-background] Adding $BG_COLOR background to $INPUT_ICNS"

# ── Prepare workspace ─────────────────────────────────────────────────────────
rm -rf "$WORK_DIR"
mkdir -p "$ICONSET_DIR"

# Extract largest PNG representation from icns as source
TEMP_PNG="$WORK_DIR/source.png"
sips -s format png "$INPUT_ICNS" --out "$TEMP_PNG" 2>/dev/null || {
  echo "[add-icon-background] ERROR: sips could not extract PNG from $INPUT_ICNS"
  exit 1
}

# ── Composite helper ──────────────────────────────────────────────────────────
composite_at() {
  local SIZE="$1"
  local OUT="$2"
  # ImageMagick v7 uses "magick", v6 uses "convert"
  if command -v magick &>/dev/null; then
    magick -size "${SIZE}x${SIZE}" "xc:${BG_COLOR}" \
      \( "$TEMP_PNG" -resize "${SIZE}x${SIZE}" \) \
      -composite "$OUT"
  else
    convert -size "${SIZE}x${SIZE}" "xc:${BG_COLOR}" \
      \( "$TEMP_PNG" -resize "${SIZE}x${SIZE}" \) \
      -composite "$OUT"
  fi
}

# ── Build iconset (iconutil required sizes) ───────────────────────────────────
composite_at 16   "$ICONSET_DIR/icon_16x16.png"
composite_at 32   "$ICONSET_DIR/icon_16x16@2x.png"
composite_at 32   "$ICONSET_DIR/icon_32x32.png"
composite_at 64   "$ICONSET_DIR/icon_32x32@2x.png"
composite_at 128  "$ICONSET_DIR/icon_128x128.png"
composite_at 256  "$ICONSET_DIR/icon_128x128@2x.png"
composite_at 256  "$ICONSET_DIR/icon_256x256.png"
composite_at 512  "$ICONSET_DIR/icon_256x256@2x.png"
composite_at 512  "$ICONSET_DIR/icon_512x512.png"
composite_at 1024 "$ICONSET_DIR/icon_512x512@2x.png"

# ── Rebuild icns from iconset ─────────────────────────────────────────────────
iconutil -c icns "$ICONSET_DIR" -o "$OUTPUT_ICNS"
echo "[add-icon-background] Written: $OUTPUT_ICNS"

# ── Update resources/icons PNGs ──────────────────────────────────────────────
for SIZE in 16 24 32 48 64 96 128 256 512 1024; do
  DEST="$REPO_ROOT/resources/icons/${SIZE}x${SIZE}.png"
  if [[ -f "$DEST" ]]; then
    composite_at "$SIZE" "$DEST"
    echo "[add-icon-background] Updated $DEST"
  fi
done

# ── Update in-app notification / tray icons ───────────────────────────────────
for TARGET_PNG in \
  "$REPO_ROOT/app/images/icon.png" \
  "$REPO_ROOT/app/images/icon_color_64x64.png"; do
  if [[ -f "$TARGET_PNG" ]]; then
    composite_at 64 "$TARGET_PNG"
    echo "[add-icon-background] Updated $TARGET_PNG"
  fi
done

# ── Cleanup ───────────────────────────────────────────────────────────────────
rm -rf "$WORK_DIR"
echo "[add-icon-background] Done."
