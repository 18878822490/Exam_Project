#include "LoginWindow.h"

#include "AppConfig.h"
#include "LoginWidget.h"
#include "RegisterWidget.h"
#include "AdminMainWindow.h"
#include "StudentMainWindow.h"
#include "TeacherMainWindow.h"

#include <QAbstractItemView>
#include <QApplication>
#include <QComboBox>
#include <QEventLoop>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QMetaObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPainter>
#include <QPainterPath>
#include <QPalette>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QQmlContext>
#include <QQuickItem>
#include <QQuickWidget>
#include <QResizeEvent>
#include <QScreen>
#include <QSizePolicy>
#include <QTimer>
#include <QUrl>
#include <QVariant>
#include <QVBoxLayout>

namespace {
class AppBackgroundWidget : public QWidget
{
public:
    explicit AppBackgroundWidget(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setAttribute(Qt::WA_StyledBackground, true);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QWidget::paintEvent(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QLinearGradient wash(rect().topLeft(), rect().bottomRight());
        wash.setColorAt(0.0, QColor(244, 249, 255));
        wash.setColorAt(0.48, QColor(236, 247, 255));
        wash.setColorAt(1.0, QColor(248, 251, 255));
        painter.fillRect(rect(), wash);

        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(52, 199, 190, 52));
        painter.drawEllipse(QRectF(width() * 0.02, -height() * 0.20, width() * 0.52, height() * 0.54));

        painter.setBrush(QColor(42, 116, 222, 38));
        painter.drawEllipse(QRectF(width() * 0.63, height() * 0.54, width() * 0.46, height() * 0.50));

        painter.setBrush(QColor(255, 255, 255, 110));
        painter.drawEllipse(QRectF(width() * 0.72, height() * 0.08, 180, 180));
    }
};

class LogoGlyph : public QLabel
{
public:
    explicit LogoGlyph(QWidget *parent = nullptr)
        : QLabel(parent)
        , source(QStringLiteral(":/assets/brand-logo-mark.png"))
    {
        setFixedSize(42, 42);
        setAlignment(Qt::AlignCenter);
        updatePixmap();
    }

protected:
    void resizeEvent(QResizeEvent *event) override
    {
        QLabel::resizeEvent(event);
        updatePixmap();
    }

private:
    void updatePixmap()
    {
        const QPixmap pixmap(source);
        if (!pixmap.isNull()) {
            setPixmap(pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }

    const QString source;
};

QWidget *createBrandLockup(const QString &title, const QString &subtitle, bool centered)
{
    auto *container = new QWidget;
    auto *layout = new QVBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(6);
    layout->setAlignment(centered ? Qt::AlignCenter : Qt::AlignLeft);

    auto *row = new QHBoxLayout;
    row->setContentsMargins(0, 0, 0, 0);
    row->setSpacing(10);
    row->setAlignment(centered ? Qt::AlignCenter : Qt::AlignLeft);

    auto *titleLabel = new QLabel(title);
    titleLabel->setObjectName(QStringLiteral("BrandTitle"));

    row->addWidget(new LogoGlyph);
    row->addWidget(titleLabel);
    layout->addLayout(row);

    if (!subtitle.isEmpty()) {
        auto *sub = new QLabel(subtitle);
        sub->setObjectName(QStringLiteral("BrandSubtitle"));
        sub->setAlignment(centered ? Qt::AlignCenter : Qt::AlignLeft);
        layout->addWidget(sub);
    }

    return container;
}

QFrame *createFeaturePill(const QString &title, const QString &text, bool active)
{
    auto *pill = new QFrame;
    pill->setObjectName(QStringLiteral("FeaturePill"));
    pill->setProperty("active", active);
    pill->setCursor(Qt::PointingHandCursor);

    auto *layout = new QVBoxLayout(pill);
    layout->setContentsMargins(16, 12, 16, 12);
    layout->setSpacing(3);

    auto *titleLabel = new QLabel(title);
    titleLabel->setObjectName(QStringLiteral("FeatureTitle"));
    auto *textLabel = new QLabel(text);
    textLabel->setObjectName(QStringLiteral("FeatureText"));
    textLabel->setWordWrap(true);

    layout->addWidget(titleLabel);
    layout->addWidget(textLabel);
    return pill;
}

class BrandingPanel : public QWidget
{
public:
    explicit BrandingPanel(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setObjectName(QStringLiteral("BrandPanel"));
        setAttribute(Qt::WA_StyledBackground, true);

        auto *layout = new QVBoxLayout(this);
        layout->setContentsMargins(36, 34, 36, 34);
        layout->setSpacing(18);

        layout->addWidget(createBrandLockup(QStringLiteral("智考星"), QStringLiteral("轻量、清晰、可靠的考试平台"), false));

        auto *headline = new QLabel(QStringLiteral("让考试流程更轻松"));
        headline->setObjectName(QStringLiteral("SideHeadline"));
        headline->setWordWrap(true);
        layout->addWidget(headline);

        auto *intro = new QLabel(QStringLiteral("登录后即可进入对应角色工作台，完成考试、组卷与成绩管理。"));
        intro->setObjectName(QStringLiteral("SideIntro"));
        intro->setWordWrap(true);
        layout->addWidget(intro);

        layout->addSpacing(4);
        layout->addWidget(createFeaturePill(QStringLiteral("智能组卷"), QStringLiteral("题库抽题、规则配置、快速生成试卷"), true));
        layout->addWidget(createFeaturePill(QStringLiteral("在线考试"), QStringLiteral("学生答题、自动交卷、过程清晰可控"), false));
        layout->addWidget(createFeaturePill(QStringLiteral("成绩分析"), QStringLiteral("教师查看分数与班级表现趋势"), false));
        layout->addStretch();
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QWidget::paintEvent(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QLinearGradient panelGradient(rect().topLeft(), rect().bottomRight());
        panelGradient.setColorAt(0, QColor(28, 93, 186));
        panelGradient.setColorAt(0.54, QColor(24, 74, 158));
        panelGradient.setColorAt(1, QColor(19, 58, 130));
        QPainterPath panelPath;
        panelPath.setFillRule(Qt::WindingFill);
        panelPath.addRoundedRect(QRectF(rect()), 26, 26);
        panelPath.addRect(QRectF(width() - 34, 0, 34, height()));
        painter.fillPath(panelPath, panelGradient);

        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(58, 211, 198, 92));
        painter.drawEllipse(QRectF(-74, height() * 0.06, 210, 210));
        painter.setBrush(QColor(255, 255, 255, 30));
        painter.drawEllipse(QRectF(width() - 130, -46, 190, 190));
        painter.setBrush(QColor(255, 255, 255, 18));
        painter.drawRoundedRect(QRectF(60, height() - 164, width() - 120, 84), 24, 24);

        QPainterPath desk;
        desk.addRoundedRect(QRectF(86, height() - 144, width() - 172, 58), 18, 18);
        painter.fillPath(desk, QColor(255, 255, 255, 36));

        painter.setPen(QPen(QColor(255, 255, 255, 80), 2));
        painter.drawLine(QPointF(112, height() - 122), QPointF(width() - 120, height() - 122));
        painter.drawLine(QPointF(132, height() - 104), QPointF(width() - 154, height() - 104));
    }
};

QStringList classOptions()
{
    return {
        QStringLiteral("软工01"),
        QStringLiteral("软工02"),
        QStringLiteral("软工03"),
        QStringLiteral("计科01"),
        QStringLiteral("信网01"),
        QStringLiteral("大数据01班")
    };
}

QStringList majorOptions()
{
    return {
        QStringLiteral("软件工程"),
        QStringLiteral("计算机科学与技术"),
        QStringLiteral("信息网络"),
        QStringLiteral("大数据")
    };
}

QStringList classOptionsForMajor(const QString &major)
{
    if (major == QStringLiteral("软件工程")) {
        return {QStringLiteral("软工01"), QStringLiteral("软工02"), QStringLiteral("软工03")};
    }
    if (major == QStringLiteral("计算机科学与技术")) {
        return {QStringLiteral("计科01")};
    }
    if (major == QStringLiteral("大数据")) {
        return {QStringLiteral("大数据01班")};
    }
    return {QStringLiteral("信网01")};
}

QStringList subjectOptions()
{
    return {
        QStringLiteral("高数"),
        QStringLiteral("Java"),
        QStringLiteral("C++"),
        QStringLiteral("数据结构"),
        QStringLiteral("数据库"),
        QStringLiteral("英语")
    };
}

void addShadow(QWidget *widget, const QColor &color, int blur, int yOffset)
{
    auto *effect = new QGraphicsDropShadowEffect(widget);
    effect->setBlurRadius(blur);
    effect->setOffset(0, yOffset);
    effect->setColor(color);
    widget->setGraphicsEffect(effect);
}

QLabel *fieldLabel(const QString &text)
{
    auto *label = new QLabel(text);
    label->setObjectName(QStringLiteral("FieldLabel"));
    return label;
}

QFrame *createLogoPanel(const QString &subtitle)
{
    auto *logoPanel = new QFrame;
    logoPanel->setObjectName(QStringLiteral("LogoPanel"));
    logoPanel->setFixedHeight(86);
    addShadow(logoPanel, QColor(78, 132, 220, 54), 26, 8);

    auto *layout = new QVBoxLayout(logoPanel);
    layout->setContentsMargins(18, 10, 18, 10);
    layout->setSpacing(4);
    layout->setAlignment(Qt::AlignCenter);

    auto *sub = new QLabel(subtitle);
    sub->setObjectName(QStringLiteral("BrandSubtitle"));
    sub->setAlignment(Qt::AlignCenter);

    layout->addWidget(createBrandLockup(QStringLiteral("智考星"), QString(), true));
    layout->addWidget(sub);
    return logoPanel;
}

QString normalizedRole(const QString &rawRole)
{
    QString role = rawRole.trimmed().toUpper();
    role.replace(QLatin1Char('-'), QLatin1Char('_'));
    role.replace(QLatin1Char(' '), QLatin1Char('_'));

    if (role == QLatin1String("ROLE_ADMIN")
            || role == QLatin1String("SYS_ADMIN")
            || role == QLatin1String("SUPER_ADMIN")
            || role == QLatin1String("ADMINISTRATOR")
            || role.contains(QLatin1String("ADMIN"))
            || rawRole.contains(QStringLiteral("管理员"))) {
        return QStringLiteral("ADMIN");
    }
    if (role == QLatin1String("ROLE_TEACHER")
            || role.contains(QLatin1String("TEACHER"))
            || rawRole.contains(QStringLiteral("教师"))
            || rawRole.contains(QStringLiteral("老师"))) {
        return QStringLiteral("TEACHER");
    }
    return QStringLiteral("STUDENT");
}

QString stringValue(const QJsonObject &object, const QStringList &keys)
{
    for (const QString &key : keys) {
        const QString value = object.value(key).toString().trimmed();
        if (!value.isEmpty()) {
            return value;
        }
    }
    return {};
}

}

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , usernameEdit(nullptr)
    , passwordEdit(nullptr)
    , loginButton(nullptr)
    , registerButton(nullptr)
    , messageLabel(nullptr)
    , statusButton(nullptr)
{
    buildUi();
}

QString LoginWidget::username() const
{
    return usernameEdit->text().trimmed();
}

QString LoginWidget::password() const
{
    return passwordEdit->text();
}

void LoginWidget::setBusy(bool busy)
{
    loginButton->setEnabled(!busy);
    registerButton->setEnabled(!busy);
    loginButton->setText(busy ? QStringLiteral("登录中...") : QStringLiteral("登录"));
}

void LoginWidget::clearStatus()
{
    messageLabel->clear();
    messageLabel->hide();
    statusButton->hide();
}

void LoginWidget::showError(const QString &message)
{
    statusButton->hide();
    messageLabel->setText(message);
    messageLabel->show();
}

void LoginWidget::showSuccess(const QString &message)
{
    messageLabel->hide();
    statusButton->setText(message);
    statusButton->show();
}

void LoginWidget::buildUi()
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(40, 32, 40, 30);
    layout->setSpacing(12);

    layout->addWidget(createLogoPanel(QStringLiteral("现代化考试登录平台")));
    layout->addSpacing(8);

    layout->addWidget(fieldLabel(QStringLiteral("用户名")));
    usernameEdit = new QLineEdit;
    usernameEdit->setObjectName(QStringLiteral("Input"));
    usernameEdit->setPlaceholderText(QStringLiteral("请输入用户名"));
    usernameEdit->setMinimumHeight(48);
    layout->addWidget(usernameEdit);

    layout->addWidget(fieldLabel(QStringLiteral("密码")));
    passwordEdit = new QLineEdit;
    passwordEdit->setObjectName(QStringLiteral("Input"));
    passwordEdit->setPlaceholderText(QStringLiteral("请输入密码"));
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setMinimumHeight(48);
    layout->addWidget(passwordEdit);

    loginButton = new QPushButton(QStringLiteral("登录"));
    loginButton->setObjectName(QStringLiteral("PrimaryButton"));
    loginButton->setCursor(Qt::PointingHandCursor);
    loginButton->setMinimumHeight(50);
    layout->addWidget(loginButton);

    registerButton = new QPushButton(QStringLiteral("创建账号"));
    registerButton->setObjectName(QStringLiteral("TextLink"));
    registerButton->setCursor(Qt::PointingHandCursor);
    registerButton->setFlat(true);
    layout->addWidget(registerButton);

    layout->addStretch();

    messageLabel = new QLabel;
    messageLabel->setObjectName(QStringLiteral("MessageLabel"));
    messageLabel->setAlignment(Qt::AlignCenter);
    messageLabel->setWordWrap(true);
    messageLabel->hide();
    layout->addWidget(messageLabel);

    statusButton = new QPushButton;
    statusButton->setObjectName(QStringLiteral("StatusLink"));
    statusButton->setCursor(Qt::PointingHandCursor);
    statusButton->setFlat(true);
    statusButton->hide();
    layout->addWidget(statusButton);

    connect(loginButton, &QPushButton::clicked, this, [this]() {
        emit loginRequested(username(), password());
    });
    connect(passwordEdit, &QLineEdit::returnPressed, this, [this]() {
        emit loginRequested(username(), password());
    });
    connect(registerButton, &QPushButton::clicked, this, &LoginWidget::registerRequested);
    connect(statusButton, &QPushButton::clicked, this, &LoginWidget::successActionRequested);
}

RegisterWidget::RegisterWidget(QWidget *parent)
    : QWidget(parent)
    , usernameEdit(nullptr)
    , nameEdit(nullptr)
    , phoneEdit(nullptr)
    , studentNoEdit(nullptr)
    , passwordEdit(nullptr)
    , confirmPasswordEdit(nullptr)
    , roleCombo(nullptr)
    , studentMajorCombo(nullptr)
    , studentClassCombo(nullptr)
    , teacherClassList(nullptr)
    , subjectCombo(nullptr)
    , roleHintLabel(nullptr)
    , contactFields(nullptr)
    , studentFields(nullptr)
    , teacherFields(nullptr)
    , registerButton(nullptr)
    , loginButton(nullptr)
    , messageLabel(nullptr)
    , statusButton(nullptr)
{
    buildUi();
}

bool RegisterWidget::validate(QString *message) const
{
    if (usernameEdit->text().trimmed().isEmpty()) {
        *message = QStringLiteral("请输入用户名");
        return false;
    }
    if (nameEdit->text().trimmed().isEmpty()) {
        *message = QStringLiteral("请输入姓名");
        return false;
    }
    if (passwordEdit->text().isEmpty()) {
        *message = QStringLiteral("请输入密码");
        return false;
    }
    if (passwordEdit->text() != confirmPasswordEdit->text()) {
        *message = QStringLiteral("两次输入的密码不一致");
        return false;
    }

    const QString role = roleCombo->currentData().toString();
    if (role != QLatin1String("STUDENT") && phoneEdit->text().trimmed().isEmpty()) {
        *message = role == QLatin1String("TEACHER")
                ? QStringLiteral("请输入教师手机号")
                : QStringLiteral("请输入管理员手机号");
        return false;
    }
    if (role == QLatin1String("STUDENT")) {
        if (studentNoEdit->text().trimmed().isEmpty()) {
            *message = QStringLiteral("请输入学号");
            return false;
        }
        if (studentClassName().trimmed().isEmpty()) {
            *message = QStringLiteral("请选择所在班级");
            return false;
        }
    }
    if (role == QLatin1String("TEACHER")) {
        if (selectedTeacherClasses().isEmpty()) {
            *message = QStringLiteral("请选择管理班级");
            return false;
        }
        if (subjectCombo->currentText().trimmed().isEmpty()) {
            *message = QStringLiteral("请选择所任科目");
            return false;
        }
    }
    return true;
}

QJsonObject RegisterWidget::requestPayload() const
{
    QJsonObject payload;
    const QString role = roleCombo->currentData().toString();

    payload.insert(QStringLiteral("username"), usernameEdit->text().trimmed());
    payload.insert(QStringLiteral("password"), passwordEdit->text());
    payload.insert(QStringLiteral("name"), nameEdit->text().trimmed());
    payload.insert(QStringLiteral("role"), role);

    if (role == QLatin1String("STUDENT")) {
        payload.insert(QStringLiteral("studentNo"), studentNoEdit->text().trimmed());
        payload.insert(QStringLiteral("major"), studentMajorCombo->currentText());
        payload.insert(QStringLiteral("className"), studentClassName());
    } else if (role == QLatin1String("TEACHER")) {
        QJsonArray classes;
        for (const QString &className : selectedTeacherClasses()) {
            classes.append(className);
        }
        payload.insert(QStringLiteral("classNames"), classes);
        payload.insert(QStringLiteral("subject"), subjectCombo->currentText());
        payload.insert(QStringLiteral("phone"), phoneEdit->text().trimmed());
    } else if (role == QLatin1String("ADMIN")) {
        payload.insert(QStringLiteral("phone"), phoneEdit->text().trimmed());
    }

    return payload;
}

void RegisterWidget::setBusy(bool busy)
{
    registerButton->setEnabled(!busy);
    loginButton->setEnabled(!busy);
    registerButton->setText(busy ? QStringLiteral("注册中...") : QStringLiteral("注册"));
}

void RegisterWidget::clearStatus()
{
    messageLabel->clear();
    messageLabel->hide();
    statusButton->hide();
}

void RegisterWidget::showError(const QString &message)
{
    statusButton->hide();
    messageLabel->setText(message);
    messageLabel->show();
}

void RegisterWidget::showRegistered()
{
    messageLabel->hide();
    statusButton->setText(QStringLiteral("✓ 注册完成"));
    statusButton->show();
}

void RegisterWidget::buildUi()
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(36, 24, 36, 24);
    layout->setSpacing(8);

    layout->addWidget(createLogoPanel(QStringLiteral("创建你的考试系统账号")));

    layout->addWidget(fieldLabel(QStringLiteral("登录账号")));
    usernameEdit = new QLineEdit;
    usernameEdit->setObjectName(QStringLiteral("Input"));
    usernameEdit->setPlaceholderText(QStringLiteral("请输入登录账号"));
    usernameEdit->setMinimumHeight(44);
    layout->addWidget(usernameEdit);

    layout->addWidget(fieldLabel(QStringLiteral("姓名")));
    nameEdit = new QLineEdit;
    nameEdit->setObjectName(QStringLiteral("Input"));
    nameEdit->setPlaceholderText(QStringLiteral("请输入真实姓名"));
    nameEdit->setMinimumHeight(44);
    layout->addWidget(nameEdit);

    auto *passwordRow = new QHBoxLayout;
    passwordRow->setSpacing(12);

    auto *passwordColumn = new QVBoxLayout;
    passwordColumn->setSpacing(6);
    passwordColumn->addWidget(fieldLabel(QStringLiteral("密码")));
    passwordEdit = new QLineEdit;
    passwordEdit->setObjectName(QStringLiteral("Input"));
    passwordEdit->setPlaceholderText(QStringLiteral("密码"));
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setMinimumHeight(44);
    passwordColumn->addWidget(passwordEdit);

    auto *confirmColumn = new QVBoxLayout;
    confirmColumn->setSpacing(6);
    confirmColumn->addWidget(fieldLabel(QStringLiteral("确认密码")));
    confirmPasswordEdit = new QLineEdit;
    confirmPasswordEdit->setObjectName(QStringLiteral("Input"));
    confirmPasswordEdit->setPlaceholderText(QStringLiteral("再次输入"));
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    confirmPasswordEdit->setMinimumHeight(44);
    confirmColumn->addWidget(confirmPasswordEdit);

    passwordRow->addLayout(passwordColumn);
    passwordRow->addLayout(confirmColumn);
    layout->addLayout(passwordRow);

    layout->addWidget(fieldLabel(QStringLiteral("身份")));
    roleCombo = new QComboBox;
    roleCombo->setObjectName(QStringLiteral("Input"));
    roleCombo->setMinimumHeight(44);
    roleCombo->addItem(QStringLiteral("学生"), QStringLiteral("STUDENT"));
    roleCombo->addItem(QStringLiteral("教师"), QStringLiteral("TEACHER"));
    roleCombo->addItem(QStringLiteral("管理员"), QStringLiteral("ADMIN"));
    layout->addWidget(roleCombo);

    roleHintLabel = new QLabel;
    roleHintLabel->setObjectName(QStringLiteral("RoleHintLabel"));
    roleHintLabel->setWordWrap(true);
    roleHintLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    roleHintLabel->setMinimumHeight(42);
    layout->addWidget(roleHintLabel);

    contactFields = new QWidget;
    auto *contactLayout = new QVBoxLayout(contactFields);
    contactLayout->setContentsMargins(0, 0, 0, 0);
    contactLayout->setSpacing(6);
    contactLayout->addWidget(fieldLabel(QStringLiteral("手机号")));
    phoneEdit = new QLineEdit;
    phoneEdit->setObjectName(QStringLiteral("Input"));
    phoneEdit->setPlaceholderText(QStringLiteral("教师/管理员必须填写手机号"));
    phoneEdit->setMinimumHeight(44);
    contactLayout->addWidget(phoneEdit);
    layout->addWidget(contactFields);

    studentFields = new QWidget;
    auto *studentLayout = new QVBoxLayout(studentFields);
    studentLayout->setContentsMargins(0, 0, 0, 0);
    studentLayout->setSpacing(6);

    auto *studentClassRow = new QHBoxLayout;
    studentClassRow->setSpacing(12);

    studentLayout->addWidget(fieldLabel(QStringLiteral("学号")));
    studentNoEdit = new QLineEdit;
    studentNoEdit->setObjectName(QStringLiteral("Input"));
    studentNoEdit->setPlaceholderText(QStringLiteral("请输入学号"));
    studentNoEdit->setMinimumHeight(44);
    studentLayout->addWidget(studentNoEdit);

    auto *majorColumn = new QVBoxLayout;
    majorColumn->setSpacing(6);
    majorColumn->addWidget(fieldLabel(QStringLiteral("专业")));
    studentMajorCombo = new QComboBox;
    studentMajorCombo->setObjectName(QStringLiteral("Input"));
    studentMajorCombo->setMinimumHeight(44);
    studentMajorCombo->addItems(majorOptions());
    majorColumn->addWidget(studentMajorCombo);

    auto *classColumn = new QVBoxLayout;
    classColumn->setSpacing(6);
    classColumn->addWidget(fieldLabel(QStringLiteral("班级")));
    studentClassCombo = new QComboBox;
    studentClassCombo->setObjectName(QStringLiteral("Input"));
    studentClassCombo->setMinimumHeight(44);
    studentClassCombo->addItems(classOptionsForMajor(studentMajorCombo->currentText()));
    classColumn->addWidget(studentClassCombo);

    studentClassRow->addLayout(majorColumn);
    studentClassRow->addLayout(classColumn);
    studentLayout->addLayout(studentClassRow);
    layout->addWidget(studentFields);

    teacherFields = new QWidget;
    auto *teacherLayout = new QVBoxLayout(teacherFields);
    teacherLayout->setContentsMargins(0, 0, 0, 0);
    teacherLayout->setSpacing(6);
    teacherLayout->addWidget(fieldLabel(QStringLiteral("管理班级")));
    teacherClassList = new QListWidget;
    teacherClassList->setObjectName(QStringLiteral("ClassList"));
    teacherClassList->setSelectionMode(QAbstractItemView::MultiSelection);
    teacherClassList->setFixedHeight(82);
    teacherClassList->addItems(classOptions());
    teacherLayout->addWidget(teacherClassList);
    teacherLayout->addWidget(fieldLabel(QStringLiteral("所任科目")));
    subjectCombo = new QComboBox;
    subjectCombo->setObjectName(QStringLiteral("Input"));
    subjectCombo->setMinimumHeight(44);
    subjectCombo->addItems(subjectOptions());
    teacherLayout->addWidget(subjectCombo);
    layout->addWidget(teacherFields);

    registerButton = new QPushButton(QStringLiteral("注册"));
    registerButton->setObjectName(QStringLiteral("PrimaryButton"));
    registerButton->setCursor(Qt::PointingHandCursor);
    registerButton->setMinimumHeight(48);
    layout->addWidget(registerButton);

    loginButton = new QPushButton(QStringLiteral("返回登录"));
    loginButton->setObjectName(QStringLiteral("TextLink"));
    loginButton->setCursor(Qt::PointingHandCursor);
    loginButton->setFlat(true);
    layout->addWidget(loginButton);

    layout->addStretch();

    messageLabel = new QLabel;
    messageLabel->setObjectName(QStringLiteral("MessageLabel"));
    messageLabel->setAlignment(Qt::AlignCenter);
    messageLabel->setWordWrap(true);
    messageLabel->hide();
    layout->addWidget(messageLabel);

    statusButton = new QPushButton;
    statusButton->setObjectName(QStringLiteral("StatusLink"));
    statusButton->setCursor(Qt::PointingHandCursor);
    statusButton->setFlat(true);
    statusButton->hide();
    layout->addWidget(statusButton);

    connect(roleCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int) {
        refreshRoleFields();
    });
    connect(studentMajorCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int) {
        studentClassCombo->clear();
        studentClassCombo->addItems(classOptionsForMajor(studentMajorCombo->currentText()));
    });
    connect(registerButton, &QPushButton::clicked, this, [this]() {
        QString message;
        if (!validate(&message)) {
            showError(message);
            return;
        }
        emit registerRequested(requestPayload());
    });
    connect(loginButton, &QPushButton::clicked, this, &RegisterWidget::loginRequested);
    connect(statusButton, &QPushButton::clicked, this, &RegisterWidget::registeredActionRequested);

    refreshRoleFields();
}

void RegisterWidget::refreshRoleFields()
{
    const QString role = roleCombo->currentData().toString();
    contactFields->setVisible(role != QLatin1String("STUDENT"));
    studentFields->setVisible(role == QLatin1String("STUDENT"));
    teacherFields->setVisible(role == QLatin1String("TEACHER"));
    if (role == QLatin1String("STUDENT")) {
        roleHintLabel->setText(QStringLiteral("学生账号需入库：登录账号、密码、姓名、学号、专业、班级。"));
        usernameEdit->setPlaceholderText(QStringLiteral("请输入学生登录账号"));
        nameEdit->setPlaceholderText(QStringLiteral("请输入学生姓名"));
    } else if (role == QLatin1String("TEACHER")) {
        roleHintLabel->setText(QStringLiteral("教师账号需入库：登录账号、密码、姓名、手机号、所任科目，并关联至少一个管理班级。"));
        usernameEdit->setPlaceholderText(QStringLiteral("请输入教师登录账号"));
        nameEdit->setPlaceholderText(QStringLiteral("请输入教师姓名"));
        phoneEdit->setPlaceholderText(QStringLiteral("请输入教师手机号"));
    } else {
        roleHintLabel->setText(QStringLiteral("管理员账号需入库：登录账号、密码、姓名、手机号。"));
        usernameEdit->setPlaceholderText(QStringLiteral("请输入管理员登录账号"));
        nameEdit->setPlaceholderText(QStringLiteral("请输入管理员姓名"));
        phoneEdit->setPlaceholderText(QStringLiteral("请输入管理员手机号"));
    }
    clearStatus();
}

QString RegisterWidget::studentClassName() const
{
    if (studentMajorCombo == nullptr || studentClassCombo == nullptr) {
        return {};
    }
    return studentClassCombo->currentText().trimmed();
}

QStringList RegisterWidget::selectedTeacherClasses() const
{
    QStringList classes;
    for (QListWidgetItem *item : teacherClassList->selectedItems()) {
        classes.append(item->text());
    }
    return classes;
}

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , card(nullptr)
    , brandPanel(nullptr)
    , pageViewport(nullptr)
    , pageTrack(nullptr)
    , loginWidget(nullptr)
    , registerWidget(nullptr)
    , quickWidget(nullptr)
    , network(new QNetworkAccessManager(this))
    , currentPage(Page::Login)
    , animating(false)
    , pendingUserId(0)
    , loginPageHeight(640)
    , registerPageHeight(720)
{
    buildUi();
}

QVariantList LoginWindow::getClassCatalog() const
{
    QNetworkRequest request(AppConfig::apiUrl(QStringLiteral("/users/teacher-classes")));
    request.setTransferTimeout(1500);

    QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkReply *reply = manager.get(request);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    const QByteArray body = reply->readAll();
    const bool ok = reply->error() == QNetworkReply::NoError;
    reply->deleteLater();
    if (!ok) {
        return {};
    }

    const QJsonDocument document = QJsonDocument::fromJson(body);
    if (!document.isObject()) {
        return {};
    }

    const QJsonObject response = document.object();
    if (!response.value(QStringLiteral("success")).toBool()) {
        return {};
    }
    return response.value(QStringLiteral("data")).toArray().toVariantList();
}

void LoginWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (card != nullptr) {
        updatePageGeometry();
    }
}

void LoginWindow::showRegisterPage()
{
    registerWidget->clearStatus();
    slideTo(Page::Register);
}

void LoginWindow::showLoginPage()
{
    loginWidget->clearStatus();
    slideTo(Page::Login);
}

void LoginWindow::submitLogin(const QString &username, const QString &password)
{
    if (username.trimmed().isEmpty() || password.isEmpty()) {
        if (loginWidget != nullptr) {
            loginWidget->showError(QStringLiteral("请输入用户名和密码"));
        } else {
            invokeQml("loginFailed", QStringLiteral("请输入用户名和密码"));
        }
        return;
    }

    QJsonObject payload;
    payload.insert(QStringLiteral("username"), username.trimmed());
    payload.insert(QStringLiteral("password"), password);

    if (loginWidget != nullptr) {
        loginWidget->setBusy(true);
        loginWidget->clearStatus();
    } else {
        invokeQml("setBusy", QStringLiteral("login"), true);
    }
    postJson(QStringLiteral("/login"), payload, [this](const QJsonObject &response) {
        if (!response.value(QStringLiteral("success")).toBool()) {
            const QString message = response.value(QStringLiteral("message")).toString(QStringLiteral("登录失败"));
            if (loginWidget != nullptr) {
                loginWidget->setBusy(false);
                loginWidget->showError(message);
            } else {
                invokeQml("loginFailed", message);
            }
            return;
        }

        const QJsonObject data = response.value(QStringLiteral("data")).toObject();
        pendingRole = stringValue(data, {
            QStringLiteral("role"),
            QStringLiteral("roleName"),
            QStringLiteral("role_name"),
            QStringLiteral("userRole"),
            QStringLiteral("user_role"),
            QStringLiteral("identity"),
            QStringLiteral("type")
        });
        pendingDisplayName = data.value(QStringLiteral("name")).toString();
        pendingSubject = data.value(QStringLiteral("subject")).toString();
        pendingUsername = data.value(QStringLiteral("username")).toString();
        const QString studentNoFromColumn = data.value(QStringLiteral("student_no")).toString().trimmed();
        const QString studentNoFromDto = data.value(QStringLiteral("studentNo")).toString().trimmed();
        pendingStudentNo = studentNoFromColumn.isEmpty() ? studentNoFromDto : studentNoFromColumn;
        if (pendingDisplayName.isEmpty()) {
            pendingDisplayName = pendingUsername;
        }
        pendingClassName = data.value(QStringLiteral("className")).toString(data.value(QStringLiteral("class_name")).toString());
        pendingUserId = data.value(QStringLiteral("teacherId")).toVariant().toLongLong();
        if (pendingUserId <= 0) {
            pendingUserId = data.value(QStringLiteral("studentId")).toVariant().toLongLong();
        }
        if (pendingUserId <= 0) {
            pendingUserId = data.value(QStringLiteral("student_id")).toVariant().toLongLong();
        }
        if (pendingUserId <= 0) {
            pendingUserId = data.value(QStringLiteral("userId")).toVariant().toLongLong();
        }
        if (pendingUserId <= 0) {
            pendingUserId = data.value(QStringLiteral("user_id")).toVariant().toLongLong();
        }
        if (loginWidget != nullptr) {
            loginWidget->setBusy(false);
            loginWidget->showSuccess(QStringLiteral("✓ 登录完成"));
        } else {
            invokeQml("setBusy", QStringLiteral("login"), false);
        }
        openRoleHome();
    });
}

void LoginWindow::submitRegister(const QVariantMap &payload)
{
    if (registerWidget != nullptr) {
        registerWidget->setBusy(true);
        registerWidget->clearStatus();
    } else {
        invokeQml("setBusy", QStringLiteral("register"), true);
    }
    postJson(QStringLiteral("/register"), QJsonObject::fromVariantMap(payload), [this](const QJsonObject &response) {
        if (!response.value(QStringLiteral("success")).toBool()) {
            const QString message = response.value(QStringLiteral("message")).toString(QStringLiteral("注册失败"));
            if (registerWidget != nullptr) {
                registerWidget->setBusy(false);
                registerWidget->showError(message);
            } else {
                invokeQml("registerFailed", message);
            }
            return;
        }

        if (registerWidget != nullptr) {
            registerWidget->setBusy(false);
            registerWidget->showRegistered();
            QTimer::singleShot(900, this, &LoginWindow::showLoginPage);
        } else {
            invokeQml("registerSucceeded");
        }
    });
}

void LoginWindow::openRoleHome()
{
    QMainWindow *home = nullptr;
    const QString role = normalizedRole(pendingRole);

    if (role == QLatin1String("TEACHER")) {
        home = new TeacherMainWindow(pendingUserId, pendingDisplayName, pendingSubject);
    } else if (role == QLatin1String("ADMIN")) {
        home = new AdminMainWindow(pendingDisplayName);
    } else {
        home = new StudentMainWindow(pendingUserId, pendingDisplayName, pendingStudentNo, pendingClassName);
    }

    home->setAttribute(Qt::WA_DeleteOnClose);
    home->show();
    hide();
}

void LoginWindow::buildUi()
{
    setWindowTitle(QStringLiteral("智考星 - 登录"));
    setMinimumSize(1280, 860);

    const QRect available = QGuiApplication::primaryScreen() != nullptr
            ? QGuiApplication::primaryScreen()->availableGeometry()
            : QRect(0, 0, 1080, 780);
    const int initialWidth = qBound(1360, int(available.width() * 0.96), 1760);
    const int initialHeight = qBound(900, int(available.height() * 0.96), 1060);
    resize(initialWidth, initialHeight);
    move(available.center() - rect().center());

    quickWidget = new QQuickWidget(this);
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    quickWidget->rootContext()->setContextProperty(QStringLiteral("loginWindow"), this);
    quickWidget->setSource(QUrl(QStringLiteral("qrc:/qml/LoginView.qml")));
    setCentralWidget(quickWidget);
}

void LoginWindow::playIntroAnimation()
{
    setWindowOpacity(0.0);
    QTimer::singleShot(40, this, [this]() {
        auto *fade = new QPropertyAnimation(this, "windowOpacity", this);
        fade->setDuration(520);
        fade->setStartValue(0.0);
        fade->setEndValue(1.0);
        fade->setEasingCurve(QEasingCurve::OutCubic);
        fade->start(QAbstractAnimation::DeleteWhenStopped);
    });
}

void LoginWindow::slideTo(Page targetPage)
{
    if (animating || targetPage == currentPage) {
        return;
    }

    animating = true;
    const bool movingToRegister = targetPage == Page::Register;
    const int width = pageViewport->width();
    const int height = pageViewport->height();

    QWidget *current = pageFor(currentPage);
    QWidget *next = pageFor(targetPage);

    current->show();
    next->show();
    pageTrack->raise();
    pageTrack->setGeometry(currentPage == Page::Login ? 0 : -width, 0, width * 2, height);
    loginWidget->setGeometry(0, 0, width, height);
    registerWidget->setGeometry(width, 0, width, height);

    auto *slide = new QPropertyAnimation(pageTrack, "pos", this);
    slide->setDuration(320);
    slide->setStartValue(QPoint(currentPage == Page::Login ? 0 : -width, 0));
    slide->setEndValue(QPoint(movingToRegister ? -width : 0, 0));
    slide->setEasingCurve(QEasingCurve::OutCubic);

    connect(slide, &QPropertyAnimation::finished, this, [this, targetPage]() {
        currentPage = targetPage;
        animating = false;
        updatePageGeometry();
    });

    slide->start(QAbstractAnimation::DeleteWhenStopped);
}

void LoginWindow::updatePageGeometry()
{
    const int availableWidth = qMax(860, width() - 64);
    const int availableHeight = qMax(640, height() - 64);
    const int cardWidth = qBound(860, static_cast<int>(width() * 0.90), availableWidth);
    const int cardHeight = qBound(640, static_cast<int>(height() * 0.88), availableHeight);
    const int leftWidth = qBound(390, static_cast<int>(cardWidth * 0.48), static_cast<int>(cardWidth * 0.55));
    const int rightWidth = cardWidth - leftWidth;

    card->setFixedSize(cardWidth, cardHeight);
    if (brandPanel != nullptr) {
        brandPanel->setFixedSize(leftWidth, cardHeight);
    }
    pageViewport->setFixedSize(rightWidth, cardHeight);

    if (!animating) {
        QWidget *current = pageFor(currentPage);
        pageTrack->setGeometry(currentPage == Page::Login ? 0 : -pageViewport->width(), 0, pageViewport->width() * 2, pageViewport->height());
        loginWidget->setGeometry(0, 0, pageViewport->width(), pageViewport->height());
        registerWidget->setGeometry(pageViewport->width(), 0, pageViewport->width(), pageViewport->height());
        current->show();
        current->raise();
    }
}

void LoginWindow::postJson(const QString &path, const QJsonObject &payload, const std::function<void(const QJsonObject &)> &handler)
{
    QNetworkRequest request(AppConfig::apiUrl(QStringLiteral("/auth") + path));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));

    auto *reply = network->post(request, QJsonDocument(payload).toJson(QJsonDocument::Compact));
    connect(reply, &QNetworkReply::finished, this, [reply, handler]() {
        const QByteArray body = reply->readAll();

        if (reply->error() != QNetworkReply::NoError) {
            QJsonObject error;
            error.insert(QStringLiteral("success"), false);
            error.insert(QStringLiteral("message"), QStringLiteral("无法连接后端服务，请确认 Spring Boot 已启动"));
            handler(error);
            reply->deleteLater();
            return;
        }

        const QJsonDocument document = QJsonDocument::fromJson(body);
        if (!document.isObject()) {
            QJsonObject error;
            error.insert(QStringLiteral("success"), false);
            error.insert(QStringLiteral("message"), QStringLiteral("后端返回格式不正确"));
            handler(error);
            reply->deleteLater();
            return;
        }

        handler(document.object());
        reply->deleteLater();
    });
}

void LoginWindow::invokeQml(const char *method)
{
    if (quickWidget == nullptr || quickWidget->rootObject() == nullptr) {
        return;
    }
    QMetaObject::invokeMethod(quickWidget->rootObject(), method);
}

void LoginWindow::invokeQml(const char *method, const QVariant &argument)
{
    if (quickWidget == nullptr || quickWidget->rootObject() == nullptr) {
        return;
    }
    QMetaObject::invokeMethod(
            quickWidget->rootObject(),
            method,
            Q_ARG(QVariant, argument)
    );
}

void LoginWindow::invokeQml(const char *method, const QVariant &first, const QVariant &second)
{
    if (quickWidget == nullptr || quickWidget->rootObject() == nullptr) {
        return;
    }
    QMetaObject::invokeMethod(
            quickWidget->rootObject(),
            method,
            Q_ARG(QVariant, first),
            Q_ARG(QVariant, second)
    );
}

QWidget *LoginWindow::pageFor(Page page) const
{
    return page == Page::Login ? static_cast<QWidget *>(loginWidget) : static_cast<QWidget *>(registerWidget);
}
