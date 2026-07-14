#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QJsonObject>
#include <QWidget>

class QComboBox;
class QLabel;
class QLineEdit;
class QListWidget;
class QPushButton;

class RegisterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWidget(QWidget *parent = nullptr);

    bool validate(QString *message) const;
    QJsonObject requestPayload() const;

    void setBusy(bool busy);
    void clearStatus();
    void showError(const QString &message);
    void showRegistered();

signals:
    void registerRequested(const QJsonObject &payload);
    void loginRequested();
    void registeredActionRequested();

private:
    void buildUi();
    void refreshRoleFields();
    QString studentClassName() const;
    QStringList selectedTeacherClasses() const;

    QLineEdit *usernameEdit;
    QLineEdit *nameEdit;
    QLineEdit *phoneEdit;
    QLineEdit *studentNoEdit;
    QLineEdit *passwordEdit;
    QLineEdit *confirmPasswordEdit;
    QComboBox *roleCombo;
    QComboBox *studentMajorCombo;
    QComboBox *studentClassCombo;
    QListWidget *teacherClassList;
    QComboBox *subjectCombo;
    QLabel *roleHintLabel;
    QWidget *contactFields;
    QWidget *studentFields;
    QWidget *teacherFields;
    QPushButton *registerButton;
    QPushButton *loginButton;
    QLabel *messageLabel;
    QPushButton *statusButton;
};

#endif // REGISTERWIDGET_H
