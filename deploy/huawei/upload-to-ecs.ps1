param(
    [Parameter(Mandatory = $true)]
    [string]$HostName,

    [string]$User = "root",

    [string]$KeyFile = "",

    [string]$RemoteDir = "/tmp/exam-platform-upload"
)

$ErrorActionPreference = "Stop"

$root = Resolve-Path (Join-Path $PSScriptRoot "..\..")
$package = Join-Path $root "deploy\package\exam-platform-huawei.zip"

if (!(Test-Path $package)) {
    throw "未找到部署包：$package。请先运行 deploy\huawei\package-backend.ps1。"
}

$sshTarget = "$User@$HostName"
$scpArgs = @()
$sshArgs = @()
if ($KeyFile.Trim() -ne "") {
    $scpArgs += @("-i", $KeyFile)
    $sshArgs += @("-i", $KeyFile)
}

& ssh @sshArgs $sshTarget "mkdir -p $RemoteDir"
& scp @scpArgs $package "${sshTarget}:${RemoteDir}/exam-platform-huawei.zip"
& ssh @sshArgs $sshTarget "cd $RemoteDir && rm -rf exam-platform && unzip -o exam-platform-huawei.zip -d exam-platform && cd exam-platform && bash install-on-ecs.sh"

Write-Host "上传完成。下一步登录服务器修改 /opt/exam-platform/.env 后重启服务：systemctl restart exam-platform"
