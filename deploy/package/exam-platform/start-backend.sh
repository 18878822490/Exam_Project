#!/usr/bin/env bash
set -euo pipefail

APP_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$APP_DIR"

if [ -f "$APP_DIR/.env" ]; then
  set -a
  # shellcheck disable=SC1091
  source "$APP_DIR/.env"
  set +a
fi

JAR_FILE="${JAR_FILE:-Exam_platform-0.0.1-SNAPSHOT.jar}"
exec java -jar "$APP_DIR/$JAR_FILE" --spring.profiles.active="${SPRING_PROFILES_ACTIVE:-prod}"
