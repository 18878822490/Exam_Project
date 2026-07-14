#include "AppConfig.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QProcessEnvironment>
#include <QSettings>

QString AppConfig::apiBaseUrl()
{
    static const QString cached = [] {
        const QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        const QString envUrl = env.value(QStringLiteral("EXAM_API_BASE_URL")).trimmed();
        if (!envUrl.isEmpty()) {
            return normalizedApiBaseUrl(envUrl);
        }

        const QString appConfig = configFilePath();
        const QString currentConfig = QDir::current().absoluteFilePath(QStringLiteral("exam_qt.ini"));
        for (const QString &path : {appConfig, currentConfig}) {
            if (!QFileInfo::exists(path)) {
                continue;
            }
            QSettings settings(path, QSettings::IniFormat);
            const QString configuredUrl = settings.value(QStringLiteral("network/apiBaseUrl")).toString().trimmed();
            if (!configuredUrl.isEmpty()) {
                return normalizedApiBaseUrl(configuredUrl);
            }
        }

        return QStringLiteral("http://127.0.0.1:8082/api");
    }();
    return cached;
}

QUrl AppConfig::apiUrl(const QString &path)
{
    QString normalizedPath = path.trimmed();
    if (!normalizedPath.isEmpty() && !normalizedPath.startsWith(QLatin1Char('/'))) {
        normalizedPath.prepend(QLatin1Char('/'));
    }
    return QUrl(apiBaseUrl() + normalizedPath);
}

QString AppConfig::configFilePath()
{
    return QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(QStringLiteral("exam_qt.ini"));
}

QString AppConfig::normalizedApiBaseUrl(QString value)
{
    value = value.trimmed();
    while (value.endsWith(QLatin1Char('/'))) {
        value.chop(1);
    }
    if (!value.endsWith(QStringLiteral("/api"), Qt::CaseInsensitive)) {
        value += QStringLiteral("/api");
    }
    return value;
}
