$ErrorActionPreference = "Stop"

$root = Resolve-Path (Join-Path $PSScriptRoot "..\..")
$backend = Join-Path $root "backend\Exam_platform"
$jar = Join-Path $backend "target\Exam_platform-0.0.1-SNAPSHOT.jar"
$packageRoot = Join-Path $root "deploy\package\exam-platform"

if (!(Test-Path $jar)) {
    throw "未找到后端 jar：$jar。请先在 backend\Exam_platform 执行 Maven package。"
}

if (Test-Path $packageRoot) {
    Remove-Item $packageRoot -Recurse -Force
}

New-Item -ItemType Directory -Force -Path $packageRoot | Out-Null
Copy-Item $jar (Join-Path $packageRoot "Exam_platform-0.0.1-SNAPSHOT.jar")
Copy-Item (Join-Path $root "deploy\huawei\env.example") (Join-Path $packageRoot ".env.example")
Copy-Item (Join-Path $root "deploy\huawei\start-backend.sh") (Join-Path $packageRoot "start-backend.sh")
Copy-Item (Join-Path $root "deploy\huawei\install-on-ecs.sh") (Join-Path $packageRoot "install-on-ecs.sh")
Copy-Item (Join-Path $root "deploy\huawei\exam-platform.service") (Join-Path $packageRoot "exam-platform.service")
Copy-Item (Join-Path $root "database\mysql_teacher_exam_schema.sql") (Join-Path $packageRoot "mysql_teacher_exam_schema.sql")
Copy-Item (Join-Path $backend "src\main\resources\exam_system_seed_accounts.sql") (Join-Path $packageRoot "exam_system_seed_accounts.sql")

Compress-Archive -Path (Join-Path $packageRoot "*") -DestinationPath (Join-Path $root "deploy\package\exam-platform-huawei.zip") -Force
Write-Host "已生成部署包：$(Join-Path $root 'deploy\package\exam-platform-huawei.zip')"
