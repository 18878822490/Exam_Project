#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QUrl>
#include <QString>

class AppConfig
{
public:
    static QString apiBaseUrl();
    static QUrl apiUrl(const QString &path = QString());
    static QString configFilePath();

private:
    static QString normalizedApiBaseUrl(QString value);
};

#endif // APPCONFIG_H
