# 华为云部署说明

## 需要准备

- 华为云 ECS 公网 IP
- SSH 用户名和密码或密钥
- MySQL 数据库，可用 ECS 本机 MySQL 或华为云 RDS
- 安全组放行后端端口 `8082`

## 后端环境变量

复制 `.env.example` 为 `.env`，按云端数据库改这些值：

```bash
SERVER_PORT=8082
SPRING_PROFILES_ACTIVE=prod
DB_URL=jdbc:mysql://数据库地址:3306/exam_system?useUnicode=true&characterEncoding=utf8&serverTimezone=Asia/Shanghai
DB_USERNAME=数据库用户名
DB_PASSWORD=数据库密码
OPENAI_API_KEY=你的OpenAI密钥
OPENAI_VISION_MODEL=gpt-5.6
```

## 启动

```bash
chmod +x start-backend.sh
./start-backend.sh
```

如果使用 systemd：

```bash
sudo cp exam-platform.service /etc/systemd/system/exam-platform.service
sudo systemctl daemon-reload
sudo systemctl enable exam-platform
sudo systemctl restart exam-platform
sudo systemctl status exam-platform
```

## 从本机上传到 ECS

```powershell
powershell -ExecutionPolicy Bypass -File .\deploy\huawei\upload-to-ecs.ps1 -HostName 你的公网IP -User root
```

如果使用密钥：

```powershell
powershell -ExecutionPolicy Bypass -File .\deploy\huawei\upload-to-ecs.ps1 -HostName 你的公网IP -User root -KeyFile C:\path\to\key.pem
```

## Qt 客户端连接云端

把 `qt_client/exam_qt/exam_qt.ini.example` 复制为程序目录下的 `exam_qt.ini`，把地址改成：

```ini
[network]
apiBaseUrl=http://你的华为云公网IP:8082/api
```

也可以设置环境变量：

```powershell
$env:EXAM_API_BASE_URL="http://你的华为云公网IP:8082/api"
```
