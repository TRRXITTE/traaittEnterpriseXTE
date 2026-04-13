#!/usr/bin/env bash
# release.sh — Build, sign, notarize, and publish traaittEnterprise XTE
#
# Usage:
#   ./scripts/release.sh [options]
#
# Options:
#   --arm64        Build macOS Apple Silicon only
#   --x86_64       Build macOS Intel only
#   --windows      Build Windows x86_64
#   --linux        Build Linux x86_64 + ARM64
#   --all          Build all platforms (default)
#   --sign         Code-sign macOS DMG (requires Developer ID cert in Keychain)
#   --notarize     Notarize + staple macOS DMG (implies --sign)
#   --publish      Publish to GitHub Releases via electron-builder
#
# Environment variables (for signing/notarization):
#   SIGNING_IDENTITY   e.g. "Developer ID Application: Christian Benz (MC52ZBYMUT)"
#   APPLE_ID           e.g. traaitt@gmail.com
#   APPLE_TEAM_ID      e.g. MC52ZBYMUT
#   APPLE_APP_PASSWORD app-specific password for notarytool
#
# Examples:
#   ./scripts/release.sh --all --sign --notarize
#   ./scripts/release.sh --arm64 --sign
#   ./scripts/release.sh --all --publish

set -euo pipefail

# ── Defaults ──────────────────────────────────────────────────────────────────
SIGN=false
NOTARIZE=false
PUBLISH=false
BUILD_ARM64=false
BUILD_X86_64=false
BUILD_WINDOWS=false
BUILD_LINUX=false
BUILD_ALL=true

SIGNING_IDENTITY="${SIGNING_IDENTITY:-Developer ID Application: Christian Benz (MC52ZBYMUT)}"
APPLE_TEAM_ID="${APPLE_TEAM_ID:-MC52ZBYMUT}"
APPLE_ID="${APPLE_ID:-}"
APPLE_APP_PASSWORD="${APPLE_APP_PASSWORD:-}"

# ── Parse arguments ───────────────────────────────────────────────────────────
for arg in "$@"; do
  case $arg in
    --arm64)    BUILD_ARM64=true;   BUILD_ALL=false ;;
    --x86_64)   BUILD_X86_64=true;  BUILD_ALL=false ;;
    --windows)  BUILD_WINDOWS=true; BUILD_ALL=false ;;
    --linux)    BUILD_LINUX=true;   BUILD_ALL=false ;;
    --all)      BUILD_ALL=true ;;
    --sign)     SIGN=true ;;
    --notarize) NOTARIZE=true; SIGN=true ;;
    --publish)  PUBLISH=true ;;
    *)          echo "Unknown option: $arg"; exit 1 ;;
  esac
done

if [[ "$BUILD_ALL" == "true" ]]; then
  BUILD_ARM64=true
  BUILD_X86_64=true
  BUILD_WINDOWS=true
  BUILD_LINUX=true
fi

# ── Setup ─────────────────────────────────────────────────────────────────────
REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$REPO_ROOT"

echo ""
echo "══════════════════════════════════════════════"
echo "  traaittEnterprise XTE — Release Build"
echo "══════════════════════════════════════════════"
echo "  arm64:    $BUILD_ARM64"
echo "  x86_64:   $BUILD_X86_64"
echo "  Windows:  $BUILD_WINDOWS"
echo "  Linux:    $BUILD_LINUX"
echo "  Sign:     $SIGN"
echo "  Notarize: $NOTARIZE"
echo "  Publish:  $PUBLISH"
echo "══════════════════════════════════════════════"
echo ""

# ── Install + Build ───────────────────────────────────────────────────────────
echo "==> Installing dependencies..."
yarn install

echo "==> Building renderer + main..."
yarn build

# ── Helper: add icon background ───────────────────────────────────────────────
if [[ -f "./scripts/add-icon-background.sh" ]]; then
  echo "==> Processing icon (adding #191919 background)..."
  bash ./scripts/add-icon-background.sh || echo "  [WARN] Icon processing skipped (ImageMagick not found)"
fi

# ── Helper: sign + notarize a DMG ────────────────────────────────────────────
sign_notarize_dmg() {
  local DMG="$1"

  if [[ "$SIGN" == "true" ]]; then
    echo "  ==> Signing $DMG..."
    codesign --force --options runtime --timestamp \
      --sign "$SIGNING_IDENTITY" "$DMG"
    codesign --verify --verbose "$DMG" 2>&1 | grep -v "^$" || true
  fi

  if [[ "$NOTARIZE" == "true" ]]; then
    if [[ -z "$APPLE_ID" || -z "$APPLE_APP_PASSWORD" ]]; then
      echo "  ERROR: Set APPLE_ID and APPLE_APP_PASSWORD to notarize."
      exit 1
    fi
    echo "  ==> Notarizing $DMG..."
    xcrun notarytool submit "$DMG" \
      --apple-id "$APPLE_ID" \
      --team-id "$APPLE_TEAM_ID" \
      --password "$APPLE_APP_PASSWORD" \
      --wait
    echo "  ==> Stapling $DMG..."
    xcrun stapler staple "$DMG"
  fi

  echo "  ==> Generating SHA256 checksum..."
  shasum -a 256 "$DMG" > "$DMG.sha256"
  echo "  Checksum: $(cat $DMG.sha256)"
}

# ── macOS arm64 (Apple Silicon) ───────────────────────────────────────────────
if [[ "$BUILD_ARM64" == "true" ]]; then
  echo ""
  echo "════ macOS arm64 (Apple Silicon) ════"
  CSC_IDENTITY_AUTO_DISCOVERY=false yarn package-mac-arm64
  DMG=$(ls release/*arm64*.dmg 2>/dev/null | head -1 || true)
  if [[ -n "$DMG" ]]; then
    sign_notarize_dmg "$DMG"
  else
    echo "  [WARN] No arm64 DMG found in release/"
  fi
fi

# ── macOS x86_64 (Intel) ──────────────────────────────────────────────────────
if [[ "$BUILD_X86_64" == "true" ]]; then
  echo ""
  echo "════ macOS x86_64 (Intel) ════"
  CSC_IDENTITY_AUTO_DISCOVERY=false yarn package-mac-x86_64
  DMG=$(ls release/*x64*.dmg release/*x86_64*.dmg 2>/dev/null | head -1 || true)
  if [[ -n "$DMG" ]]; then
    sign_notarize_dmg "$DMG"
  else
    echo "  [WARN] No x86_64 DMG found in release/"
  fi
fi

# ── Windows x86_64 ────────────────────────────────────────────────────────────
if [[ "$BUILD_WINDOWS" == "true" ]]; then
  echo ""
  echo "════ Windows x86_64 ════"
  yarn package-win
fi

# ── Linux x86_64 + ARM64 ─────────────────────────────────────────────────────
if [[ "$BUILD_LINUX" == "true" ]]; then
  echo ""
  echo "════ Linux x86_64 ════"
  yarn package-linux

  echo ""
  echo "════ Linux ARM64 ════"
  yarn package-linux-arm64
fi

# ── Publish ───────────────────────────────────────────────────────────────────
if [[ "$PUBLISH" == "true" ]]; then
  echo ""
  echo "════ Publishing to GitHub Releases ════"
  yarn postinstall && yarn build && electron-builder --publish always
fi

# ── Summary ───────────────────────────────────────────────────────────────────
echo ""
echo "══════════════════════════════════════════════"
echo "  Build complete. Artifacts in ./release/"
echo "══════════════════════════════════════════════"
ls -lh release/*.dmg release/*.exe release/*.AppImage release/*.sha256 2>/dev/null || true
