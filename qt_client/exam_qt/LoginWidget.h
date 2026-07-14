#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);

    QString username() const;
    QString password() const;

    void setBusy(bool busy);
    void clearStatus();
    void showError(const QString &message);
    void showSuccess(const QString &message);

signals:
    void loginRequested(const QString &username, const QString &password);
    void registerRequested();
    void successActionRequested();

private:
    void buildUi();

    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QLabel *messageLabel;
    QPushButton *statusButton;
};

#endif // LOGINWIDGET_H
