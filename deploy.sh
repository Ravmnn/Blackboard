#!/usr/bin/env bash
set -e

rm AppDir -rf

DESTDIR=$PWD/AppDir meson install -C build_release

linuxdeploy --appdir AppDir --output appimage