#!/usr/bin/env bash
set -euo pipefail

APP_DIR="/opt/exam-platform"

mkdir -p "$APP_DIR"
cp Exam_platform-0.0.1-SNAPSHOT.jar "$APP_DIR/"
cp start-backend.sh "$APP_DIR/"
cp .env.example "$APP_DIR/.env.example"
cp exam-platform.service /etc/systemd/system/exam-platform.service
chmod +x "$APP_DIR/start-backend.sh"

if [ ! -f "$APP_DIR/.env" ]; then
  cp "$APP_DIR/.env.example" "$APP_DIR/.env"
  echo "已创建 $APP_DIR/.env，请先填写数据库和密钥配置后再启动服务。"
fi

systemctl daemon-reload
systemctl enable exam-platform
echo "安装完成。配置 $APP_DIR/.env 后执行：systemctl restart exam-platform"
