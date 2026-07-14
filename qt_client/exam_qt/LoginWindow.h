#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QJsonObject>
#include <QMainWindow>
#include <QVariantList>
#include <QVariantMap>

#include <functional>

class QFrame;
class QNetworkAccessManager;
class QQuickWidget;
class QResizeEvent;
class RegisterWidget;
class LoginWidget;
class QWidget;

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    Q_INVOKABLE QVariantList getClassCatalog() const;
    Q_INVOKABLE void submitLogin(const QString &username, const QString &password);
    Q_INVOKABLE void submitRegister(const QVariantMap &payload);
    Q_INVOKABLE void openRoleHome();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void showRegisterPage();
    void showLoginPage();

private:
    enum class Page {
        Login,
        Register
    };

    void buildUi();
    void playIntroAnimation();
    void slideTo(Page targetPage);
    void updatePageGeometry();
    void postJson(const QString &path, const QJsonObject &payload, const std::function<void(const QJsonObject &)> &handler);
    void invokeQml(const char *method);
    void invokeQml(const char *method, const QVariant &argument);
    void invokeQml(const char *method, const QVariant &first, const QVariant &second);
    QWidget *pageFor(Page page) const;

    QFrame *card;
    QWidget *brandPanel;
    QWidget *pageViewport;
    QWidget *pageTrack;
    LoginWidget *loginWidget;
    RegisterWidget *registerWidget;
    QQuickWidget *quickWidget;
    QNetworkAccessManager *network;
    Page currentPage;
    bool animating;
    QString pendingRole;
    QString pendingDisplayName;
    QString pendingSubject;
    QString pendingUsername;
    QString pendingStudentNo;
    QString pendingClassName;
    qint64 pendingUserId;
    const int loginPageHeight;
    const int registerPageHeight;
};

#endif // LOGINWINDOW_H
