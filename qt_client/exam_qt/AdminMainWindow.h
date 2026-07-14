#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QUrlQuery>
#include <QVariant>

class QQuickWidget;

class AdminMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminMainWindow(const QString &adminName = QString(), QWidget *parent = nullptr);

    Q_INVOKABLE QString adminName() const;
    Q_INVOKABLE void minimizeWindow();
    Q_INVOKABLE void toggleMaximizeWindow();
    Q_INVOKABLE void closeWindow();
    Q_INVOKABLE void logout();
    Q_INVOKABLE void startWindowMove();
    Q_INVOKABLE QVariantMap getStudentManagementData() const;
    Q_INVOKABLE QVariantMap getTeacherManagementData() const;
    Q_INVOKABLE QString lastError() const;

private:
    QJsonObject requestJson(const QString &method,
                            const QString &path,
                            const QJsonObject &payload = {},
                            const QUrlQuery &query = {}) const;

    QQuickWidget *view;
    QString fallbackAdminName;
    mutable QString errorMessage;
};

#endif // ADMINMAINWINDOW_H
