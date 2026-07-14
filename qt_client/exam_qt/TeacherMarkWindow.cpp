#include "TeacherMarkWindow.h"

#include "AnswerPreviewWidget.h"
#include "ExamInfoCard.h"
#include "ScorePanelWidget.h"
#include "StudentListWidget.h"
#include "TeacherDataRepository.h"

#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>
#include <QComboBox>
#include <QDate>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QMap>
#include <QPair>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QSplitter>
#include <QTimer>
#include <QVBoxLayout>

namespace {
void addPanelShadow(QWidget *widget)
{
    auto *shadow = new QGraphicsDropShadowEffect(widget);
    shadow->setBlurRadius(30);
    shadow->setOffset(0, 10);
    shadow->setColor(QColor(29, 49, 86, 24));
    widget->setGraphicsEffect(shadow);
}

QPushButton *windowButton(const QString &text, QWidget *parent = nullptr)
{
    auto *button = new QPushButton(text, parent);
    button->setObjectName(QStringLiteral("MarkWindowButton"));
    button->setCursor(Qt::PointingHandCursor);
    button->setFixedSize(44, 40);
    return button;
}

QPushButton *navButton(const QString &text, int page, int activePage, QWidget *parent = nullptr)
{
    auto *button = new QPushButton(text, parent);
    button->setObjectName(QStringLiteral("MarkNavButton"));
    button->setCursor(Qt::PointingHandCursor);
    button->setProperty("page", page);
    button->setProperty("active", page == activePage);
    button->setMinimumSize(112, 48);
    return button;
}

void slideIn(QWidget *widget, const QPoint &offset, int delayMs)
{
    if (widget == nullptr) {
        return;
    }
    QTimer::singleShot(delayMs, widget, [widget, offset]() {
        const QPoint end = widget->pos();
        auto *animation = new QPropertyAnimation(widget, "pos", widget);
        widget->move(end + offset);
        animation->setDuration(360);
        animation->setStartValue(widget->pos());
        animation->setEndValue(end);
        animation->setEasingCurve(QEasingCurve::OutCubic);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    });
}

QVariantMap question(int number,
                     const QString &section,
                     const QString &type,
                     const QString &text,
                     const QString &studentAnswer,
                     const QString &standardAnswer,
                     double maxScore,
                     double score,
                     bool autoScored,
                     bool graded,
                     const QString &comment = QString())
{
    return QVariantMap{
        {QStringLiteral("number"), number},
        {QStringLiteral("section"), section},
        {QStringLiteral("type"), type},
        {QStringLiteral("question"), text},
        {QStringLiteral("studentAnswer"), studentAnswer},
        {QStringLiteral("standardAnswer"), standardAnswer},
        {QStringLiteral("maxScore"), maxScore},
        {QStringLiteral("score"), score},
        {QStringLiteral("autoScored"), autoScored},
        {QStringLiteral("graded"), graded},
        {QStringLiteral("comment"), comment}
    };
}
}

TeacherMarkWindow::TeacherMarkWindow(QWidget *parent)
    : QWidget(parent)
    , examInfoCard(nullptr)
    , examCombo(nullptr)
    , studentListWidget(nullptr)
    , answerPreviewWidget(nullptr)
    , scorePanelWidget(nullptr)
    , repository(nullptr)
    , currentExamId(0)
    , backendDataLoaded(false)
    , syncingExamCombo(false)
    , currentStudentIndex(0)
    , currentQuestionIndex(4)
{
    setObjectName(QStringLiteral("TeacherMarkWindow"));
    buildUi();
    applyStyle();
    seedMockData();
    refreshAll();
}

void TeacherMarkWindow::setRepository(TeacherDataRepository *dataRepository)
{
    repository = dataRepository;
}

void TeacherMarkWindow::loadExam(int examId)
{
    if (repository != nullptr) {
        loadBackendExam(examId);
        if (backendDataLoaded) {
            refreshAll();
            return;
        }
    }

    seedMockData();
    refreshAll();
}

void TeacherMarkWindow::loadStudents()
{
    if (backendDataLoaded && repository != nullptr && currentExamId > 0) {
        students = repository->getReviewStudents(currentExamId);
        currentStudentIndex = qBound(0, currentStudentIndex, qMax(0, students.size() - 1));
        if (!students.isEmpty()) {
            loadPaperAnswer(currentStudent().value(QStringLiteral("studentNo")).toString());
        }
        refreshAll();
        return;
    }

    refreshAll();
}

void TeacherMarkWindow::loadPaperAnswer(const QString &studentNo)
{
    if (backendDataLoaded && repository != nullptr && currentExamId > 0 && !studentNo.trimmed().isEmpty()) {
        const QVariantList answers = repository->getReviewStudentAnswers(currentExamId, studentNo);
        answersByStudent.insert(studentNo, answers);
    }
    refreshStudent();
}

bool TeacherMarkWindow::saveScore(int questionIndex, double score, const QString &comment)
{
    const QVariantMap student = currentStudent();
    const QString studentNo = student.value(QStringLiteral("studentNo")).toString();
    if (studentNo.isEmpty() || !answersByStudent.contains(studentNo)) {
        return false;
    }

    QVariantList answers = answersByStudent.value(studentNo);
    if (questionIndex < 0 || questionIndex >= answers.size()) {
        return false;
    }

    QVariantMap row = answers.at(questionIndex).toMap();
    if (row.value(QStringLiteral("autoScored")).toBool()) {
        return false;
    }

    const double maxScore = row.value(QStringLiteral("maxScore"), 10).toDouble();
    const double boundedScore = qBound(0.0, score, maxScore);
    const int answerId = row.value(QStringLiteral("answerId"), row.value(QStringLiteral("id"))).toInt();
    if (backendDataLoaded && repository != nullptr && answerId > 0
            && !repository->saveReviewScore(answerId, boundedScore, comment)) {
        return false;
    }

    row.insert(QStringLiteral("score"), boundedScore);
    row.insert(QStringLiteral("comment"), comment);
    row.insert(QStringLiteral("graded"), true);
    row.insert(QStringLiteral("status"), QStringLiteral("已批改"));
    answers[questionIndex] = row;
    answersByStudent[studentNo] = answers;

    QVariantMap updatedStudent = student;
    updatedStudent.insert(QStringLiteral("score"), QString::number(totalScore(answers), 'f', 0));
    updatedStudent.insert(QStringLiteral("status"), isStudentCompleted(answers) ? QStringLiteral("已批改") : QStringLiteral("批改中"));
    students[currentStudentIndex] = updatedStudent;

    studentListWidget->updateStudent(currentStudentIndex, updatedStudent);
    refreshExamInfo();
    refreshStudent();
    scorePanelWidget->showSaveSuccess();
    return true;
}

void TeacherMarkWindow::playEnterAnimation()
{
    QTimer::singleShot(0, this, [this]() {
        slideIn(examInfoCard, QPoint(0, -34), 0);
        slideIn(studentListWidget, QPoint(-46, 0), 80);
        slideIn(answerPreviewWidget, QPoint(0, 34), 130);
        slideIn(scorePanelWidget, QPoint(46, 0), 180);
    });
}

void TeacherMarkWindow::selectStudent(int index)
{
    currentStudentIndex = qBound(0, index, qMax(0, students.size() - 1));
    const QString studentNo = currentStudent().value(QStringLiteral("studentNo")).toString();
    if (backendDataLoaded && repository != nullptr && currentExamId > 0 && !studentNo.isEmpty()
            && !answersByStudent.contains(studentNo)) {
        answersByStudent.insert(studentNo, repository->getReviewStudentAnswers(currentExamId, studentNo));
    }

    const QVariantList answers = currentAnswers();
    currentQuestionIndex = firstTeacherQuestionIndex(answers);
    refreshStudent();
}

void TeacherMarkWindow::selectQuestion(int index)
{
    setCurrentQuestion(index);
}

void TeacherMarkWindow::saveCurrentScore(double score, const QString &comment)
{
    saveScore(currentQuestionIndex, score, comment);
}

void TeacherMarkWindow::submitCurrentQuestion(double score, const QString &comment)
{
    if (saveScore(currentQuestionIndex, score, comment)) {
        goNextQuestion();
    }
}

void TeacherMarkWindow::goPreviousStudent()
{
    if (currentStudentIndex <= 0) {
        return;
    }
    selectStudent(currentStudentIndex - 1);
    studentListWidget->setCurrentStudent(currentStudentIndex);
}

void TeacherMarkWindow::goNextStudent()
{
    if (currentStudentIndex >= students.size() - 1) {
        return;
    }
    selectStudent(currentStudentIndex + 1);
    studentListWidget->setCurrentStudent(currentStudentIndex);
}

void TeacherMarkWindow::goPreviousQuestion()
{
    const int previous = adjacentTeacherQuestionIndex(currentQuestionIndex, -1);
    if (previous >= 0) {
        setCurrentQuestion(previous);
        return;
    }
    goPreviousStudent();
}

void TeacherMarkWindow::goNextQuestion()
{
    const int next = adjacentTeacherQuestionIndex(currentQuestionIndex, 1);
    if (next >= 0) {
        setCurrentQuestion(next);
        return;
    }
    goNextStudent();
}

void TeacherMarkWindow::buildUi()
{
    auto *rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(28, 22, 28, 26);
    rootLayout->setSpacing(20);

    auto *topNav = new QFrame(this);
    topNav->setObjectName(QStringLiteral("MarkTopNav"));
    topNav->setMinimumHeight(96);
    auto *toolbar = new QHBoxLayout(topNav);
    toolbar->setContentsMargins(22, 14, 18, 14);
    toolbar->setSpacing(14);

    auto *brandBox = new QVBoxLayout;
    brandBox->setSpacing(0);
    auto *brand = new QLabel(QStringLiteral("智考星"), topNav);
    brand->setObjectName(QStringLiteral("MarkBrandTitle"));
    auto *subtitle = new QLabel(QStringLiteral("考试系统教师端"), topNav);
    subtitle->setObjectName(QStringLiteral("MarkBrandSubtitle"));
    brandBox->addWidget(brand);
    brandBox->addWidget(subtitle);

    auto *navRow = new QHBoxLayout;
    navRow->setSpacing(10);
    const QList<QPair<QString, int>> pages = {
        {QStringLiteral("教师首页"), 0},
        {QStringLiteral("题库管理"), 1},
        {QStringLiteral("发布考试"), 2},
        {QStringLiteral("批改试卷"), 3},
        {QStringLiteral("成绩分析"), 4},
        {QStringLiteral("个人中心"), 5}
    };
    for (const auto &page : pages) {
        auto *button = navButton(page.first, page.second, 3, topNav);
        navRow->addWidget(button);
        connect(button, &QPushButton::clicked, this, [this, page]() {
            if (page.second != 3) {
                emit pageRequested(page.second);
            }
        });
    }

    examCombo = new QComboBox(this);
    examCombo->setObjectName(QStringLiteral("MarkExamCombo"));
    examCombo->setMinimumSize(300, 48);
    auto *minButton = windowButton(QStringLiteral("-"), this);
    auto *maxButton = windowButton(QStringLiteral("□"), this);
    auto *closeButton = windowButton(QStringLiteral("X"), this);
    closeButton->setProperty("danger", true);

    toolbar->addLayout(brandBox);
    toolbar->addSpacing(10);
    toolbar->addLayout(navRow);
    toolbar->addStretch();
    toolbar->addWidget(examCombo);
    toolbar->addWidget(minButton);
    toolbar->addWidget(maxButton);
    toolbar->addWidget(closeButton);
    rootLayout->addWidget(topNav);

    examInfoCard = new ExamInfoCard(this);
    rootLayout->addWidget(examInfoCard);

    studentListWidget = new StudentListWidget(this);
    answerPreviewWidget = new AnswerPreviewWidget(this);
    scorePanelWidget = new ScorePanelWidget(this);
    studentListWidget->setMinimumWidth(380);
    answerPreviewWidget->setMinimumWidth(520);
    addPanelShadow(studentListWidget);
    addPanelShadow(answerPreviewWidget);
    addPanelShadow(scorePanelWidget);

    auto *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setObjectName(QStringLiteral("MarkSplitter"));
    splitter->setChildrenCollapsible(false);
    splitter->addWidget(studentListWidget);
    splitter->addWidget(answerPreviewWidget);
    splitter->addWidget(scorePanelWidget);
    splitter->setStretchFactor(0, 2);
    splitter->setStretchFactor(1, 3);
    splitter->setStretchFactor(2, 2);
    splitter->setSizes(QList<int>{430, 640, 520});
    rootLayout->addWidget(splitter, 1);

    connect(minButton, &QPushButton::clicked, this, &TeacherMarkWindow::minimizeRequested);
    connect(maxButton, &QPushButton::clicked, this, &TeacherMarkWindow::maximizeRequested);
    connect(closeButton, &QPushButton::clicked, this, &TeacherMarkWindow::closeRequested);
    connect(examCombo, qOverload<int>(&QComboBox::activated), this, [this](int index) {
        if (syncingExamCombo || index < 0) {
            return;
        }
        const int examId = examCombo->itemData(index).toInt();
        if (examId > 0 && examId != currentExamId) {
            loadExam(examId);
        }
    });
    connect(studentListWidget, &StudentListWidget::studentSelected, this, &TeacherMarkWindow::selectStudent);
    connect(studentListWidget, &StudentListWidget::previousStudentRequested, this, &TeacherMarkWindow::goPreviousStudent);
    connect(studentListWidget, &StudentListWidget::nextStudentRequested, this, &TeacherMarkWindow::goNextStudent);
    connect(answerPreviewWidget, &AnswerPreviewWidget::questionSelected, this, &TeacherMarkWindow::selectQuestion);
    connect(scorePanelWidget, &ScorePanelWidget::saveScoreRequested, this, &TeacherMarkWindow::saveCurrentScore);
    connect(scorePanelWidget, &ScorePanelWidget::submitQuestionRequested, this, &TeacherMarkWindow::submitCurrentQuestion);
    connect(scorePanelWidget, &ScorePanelWidget::previousQuestionRequested, this, &TeacherMarkWindow::goPreviousQuestion);
    connect(scorePanelWidget, &ScorePanelWidget::nextQuestionRequested, this, &TeacherMarkWindow::goNextQuestion);
}

void TeacherMarkWindow::applyStyle()
{
    setStyleSheet(QStringLiteral(R"(
        #TeacherMarkWindow {
            background: #eef3fb;
            color: #111827;
            font-family: "Microsoft YaHei", "Segoe UI";
        }
        #MarkTopNav {
            background: #f8fafd;
            border: 1px solid #dbeafe;
            border-radius: 24px;
        }
        #MarkCard, #MarkPanel {
            background: #ffffff;
            border: 1px solid #e5edf6;
            border-radius: 24px;
        }
        #MarkPanel {
            padding: 20px;
        }
        #MarkBrandTitle {
            color: #111827;
            font-size: 34px;
            font-weight: 800;
        }
        #MarkBrandSubtitle {
            color: #64748b;
            font-size: 17px;
            font-weight: 700;
        }
        #MarkNavButton {
            min-height: 48px;
            padding: 0 18px;
            color: #334155;
            background: #ffffff;
            border: 1px solid #dbe7f6;
            border-radius: 18px;
            font-size: 18px;
            font-weight: 800;
        }
        #MarkNavButton:hover {
            color: #2563eb;
            background: #eff6ff;
            border-color: #bfdbfe;
        }
        #MarkNavButton[active="true"] {
            color: #ffffff;
            background: #2563eb;
            border-color: #2563eb;
        }
        #MarkExamTitle {
            color: #111827;
            font-size: 34px;
            font-weight: 800;
        }
        #MarkPanelTitle {
            color: #111827;
            font-size: 27px;
            font-weight: 800;
        }
        #MarkSmallTitle, #MarkProgressText {
            color: #334155;
            font-size: 17px;
            font-weight: 700;
        }
        #MarkMetaText, #MarkStudentNo, #MarkStatTitle, #MarkSectionLabel {
            color: #64748b;
            font-size: 16px;
        }
        #MarkMiniStatCard, #MarkInnerCard, #MarkAnswerBox {
            background: #f8fbff;
            border: 1px solid #e5edf6;
            border-radius: 18px;
        }
        #MarkStatValue {
            font-size: 32px;
            font-weight: 800;
        }
        #MarkProgressBar {
            background: #edf2f8;
            border: none;
            border-radius: 5px;
        }
        #MarkProgressBar::chunk {
            background: #2563eb;
            border-radius: 5px;
        }
        #MarkSearchEdit, #MarkScoreEdit {
            min-height: 48px;
            padding: 0 14px;
            background: #f7f9fd;
            border: 1px solid #dfe7f2;
            border-radius: 14px;
            color: #111827;
            font-size: 17px;
        }
        #MarkExamCombo {
            min-height: 48px;
            padding: 0 14px;
            background: #ffffff;
            border: 1px solid #dbe7f6;
            border-radius: 14px;
            color: #111827;
            font-size: 17px;
            font-weight: 800;
        }
        #MarkExamCombo::drop-down {
            border: none;
            width: 34px;
        }
        #MarkSearchEdit:focus, #MarkScoreEdit:focus {
            background: #ffffff;
            border: 2px solid #2563eb;
        }
        #MarkStudentList {
            background: transparent;
            border: none;
            outline: none;
        }
        #MarkStudentName {
            color: #111827;
            font-size: 20px;
            font-weight: 800;
        }
        #MarkStudentScore {
            color: #2563eb;
            font-size: 21px;
            font-weight: 800;
        }
        #MarkQuestionNumber {
            color: #111827;
            font-size: 21px;
            font-weight: 800;
        }
        #MarkQuestionText, #MarkAnswerText {
            color: #334155;
            font-size: 18px;
            line-height: 1.5;
        }
        #MarkAutoTag, #MarkManualTag, #MarkStatusBadge {
            border-radius: 12px;
            padding: 5px 10px;
            font-size: 15px;
            font-weight: 700;
        }
        #MarkAutoTag {
            color: #16a34a;
            background: #ecfdf3;
        }
        #MarkManualTag {
            color: #f59e0b;
            background: #fff7ed;
        }
        #MarkAutoScoreSummary {
            color: #16a34a;
            background: #ecfdf3;
            border-radius: 16px;
            padding: 8px 14px;
            font-weight: 800;
        }
        #MarkCommentEdit {
            padding: 12px;
            background: #f7f9fd;
            border: 1px solid #dfe7f2;
            border-radius: 16px;
            color: #111827;
            font-size: 17px;
        }
        #MarkCommentEdit:focus {
            background: #ffffff;
            border: 2px solid #2563eb;
        }
        #MarkPrimaryButton, #MarkGhostButton, #MarkQuickButton {
            min-height: 46px;
            border-radius: 14px;
            font-size: 17px;
            font-weight: 800;
            padding: 0 16px;
        }
        #MarkPrimaryButton {
            color: #ffffff;
            background: #2563eb;
            border: 1px solid #2563eb;
        }
        #MarkPrimaryButton:hover {
            background: #1d4ed8;
        }
        #MarkGhostButton, #MarkQuickButton {
            color: #2563eb;
            background: #eff6ff;
            border: 1px solid #bfdbfe;
        }
        #MarkGhostButton:hover, #MarkQuickButton:hover {
            background: #dbeafe;
        }
        #MarkWindowButton {
            color: #334155;
            background: #ffffff;
            border: 1px solid #dbe7f6;
            border-radius: 12px;
            font-size: 17px;
            font-weight: 800;
        }
        #MarkWindowButton:hover {
            background: #eff6ff;
        }
        #MarkWindowButton[danger="true"]:hover {
            color: #ffffff;
            background: #ef4444;
            border-color: #ef4444;
        }
        #MarkSuccessText {
            color: #16a34a;
            font-size: 17px;
            font-weight: 800;
            padding: 8px 12px;
            background: #ecfdf3;
            border-radius: 14px;
        }
        #MarkSplitter::handle {
            background: transparent;
            width: 12px;
        }
        QScrollBar:vertical {
            width: 10px;
            background: transparent;
            margin: 2px;
        }
        QScrollBar::handle:vertical {
            background: #bfd0e5;
            border-radius: 5px;
            min-height: 40px;
        }
        QScrollBar::handle:vertical:hover {
            background: #8fa6c2;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
        }
    )"));
}

void TeacherMarkWindow::seedMockData()
{
    backendDataLoaded = false;
    currentExamId = 1;
    currentStudentIndex = 0;
    currentQuestionIndex = 4;
    answersByStudent.clear();

    reviewExams = QVariantList{
        QVariantMap{{QStringLiteral("id"), 1}, {QStringLiteral("title"), QStringLiteral("Java期末考试")}, {QStringLiteral("course"), QStringLiteral("Java程序设计")}},
        QVariantMap{{QStringLiteral("id"), 2}, {QStringLiteral("title"), QStringLiteral("数据结构阶段测验")}, {QStringLiteral("course"), QStringLiteral("数据结构")}}
    };
    examInfo = QVariantMap{
        {QStringLiteral("title"), QStringLiteral("Java期末考试")},
        {QStringLiteral("course"), QStringLiteral("Java程序设计")},
        {QStringLiteral("date"), QStringLiteral("2026-06-20")},
        {QStringLiteral("totalScore"), 100}
    };
    refreshExamSelector();

    students = QVariantList{
        QVariantMap{{QStringLiteral("name"), QStringLiteral("张三")}, {QStringLiteral("studentNo"), QStringLiteral("SE01001")}, {QStringLiteral("status"), QStringLiteral("待批改")}, {QStringLiteral("score"), QStringLiteral("--")}},
        QVariantMap{{QStringLiteral("name"), QStringLiteral("李思涵")}, {QStringLiteral("studentNo"), QStringLiteral("SE01002")}, {QStringLiteral("status"), QStringLiteral("已批改")}, {QStringLiteral("score"), QStringLiteral("86")}},
        QVariantMap{{QStringLiteral("name"), QStringLiteral("王明")}, {QStringLiteral("studentNo"), QStringLiteral("SE01003")}, {QStringLiteral("status"), QStringLiteral("批改中")}, {QStringLiteral("score"), QStringLiteral("72")}},
        QVariantMap{{QStringLiteral("name"), QStringLiteral("陈雨薇")}, {QStringLiteral("studentNo"), QStringLiteral("SE01004")}, {QStringLiteral("status"), QStringLiteral("待批改")}, {QStringLiteral("score"), QStringLiteral("--")}},
        QVariantMap{{QStringLiteral("name"), QStringLiteral("赵一鸣")}, {QStringLiteral("studentNo"), QStringLiteral("SE01005")}, {QStringLiteral("status"), QStringLiteral("已批改")}, {QStringLiteral("score"), QStringLiteral("91")}}
    };

    const QVariantList baseAnswers{
        question(1, QStringLiteral("第一部分 选择题"), QStringLiteral("单选题"), QStringLiteral("Java中用于创建对象的关键字是？"), QStringLiteral("new"), QStringLiteral("new"), 6, 6, true, true),
        question(2, QStringLiteral("第一部分 选择题"), QStringLiteral("单选题"), QStringLiteral("Java中String类的核心特性是？"), QStringLiteral("不可变"), QStringLiteral("不可变对象"), 6, 6, true, true),
        question(3, QStringLiteral("第一部分 选择题"), QStringLiteral("多选题"), QStringLiteral("下列属于面向对象核心特性的有？"), QStringLiteral("封装、继承、多态"), QStringLiteral("封装、继承、多态"), 8, 8, true, true),
        question(4, QStringLiteral("第一部分 选择题"), QStringLiteral("判断题"), QStringLiteral("接口中可以定义抽象方法。"), QStringLiteral("正确"), QStringLiteral("正确"), 10, 10, true, true),
        question(5, QStringLiteral("第二部分 主观题"), QStringLiteral("简答题"), QStringLiteral("题目：求函数极值，并说明关键步骤。"), QStringLiteral("先求导，令导数为0，判断单调性后得到极值。"), QStringLiteral("求导，解驻点，再结合二阶导数或单调性判断极大值与极小值。"), 10, 0, false, false),
        question(6, QStringLiteral("第二部分 主观题"), QStringLiteral("编程题"), QStringLiteral("编程题：编写一个方法统计数组中偶数的个数。"), QStringLiteral("int countEven(int[] a){ int c=0; for(int n:a){ if(n%2==0)c++; } return c; }"), QStringLiteral("遍历数组，对每个元素取模判断是否为偶数，满足条件则计数加一并返回。"), 20, 0, false, false),
        question(7, QStringLiteral("第二部分 主观题"), QStringLiteral("分析题"), QStringLiteral("说明HashMap查询效率较高的原因。"), QStringLiteral("HashMap用哈希表保存数据，可以通过key快速定位。"), QStringLiteral("HashMap通过哈希函数将key映射到桶，平均情况下可接近O(1)访问，冲突时通过链表或红黑树处理。"), 40, 0, false, false)
    };

    for (const QVariant &value : students) {
        const QVariantMap student = value.toMap();
        QVariantList answers = baseAnswers;
        if (student.value(QStringLiteral("status")).toString() == QStringLiteral("已批改")) {
            for (int i = 0; i < answers.size(); ++i) {
                QVariantMap row = answers.at(i).toMap();
                if (!row.value(QStringLiteral("autoScored")).toBool()) {
                    row.insert(QStringLiteral("score"), qMin(row.value(QStringLiteral("maxScore")).toDouble(), 8.0 + i * 2.0));
                    row.insert(QStringLiteral("graded"), true);
                    row.insert(QStringLiteral("comment"), QStringLiteral("思路清晰，关键点基本完整。"));
                    answers[i] = row;
                }
            }
        } else if (student.value(QStringLiteral("status")).toString() == QStringLiteral("批改中")) {
            QVariantMap row = answers.at(4).toMap();
            row.insert(QStringLiteral("score"), 7);
            row.insert(QStringLiteral("graded"), true);
            row.insert(QStringLiteral("comment"), QStringLiteral("计算过程正确，最后一步存在错误。"));
            answers[4] = row;
        }
        answersByStudent.insert(student.value(QStringLiteral("studentNo")).toString(), answers);
    }
}

void TeacherMarkWindow::loadBackendExam(int examId)
{
    backendDataLoaded = false;
    answersByStudent.clear();

    reviewExams = repository->getReviewExams();
    if (reviewExams.isEmpty()) {
        refreshExamSelector();
        return;
    }

    QVariantMap selectedExam;
    for (const QVariant &value : reviewExams) {
        const QVariantMap exam = value.toMap();
        if (examId > 0 && exam.value(QStringLiteral("id")).toInt() == examId) {
            selectedExam = exam;
            break;
        }
    }
    if (selectedExam.isEmpty()) {
        for (const QVariant &value : reviewExams) {
            const QVariantMap exam = value.toMap();
            if (exam.value(QStringLiteral("pendingAnswerCount")).toInt() > 0
                    || exam.value(QStringLiteral("submittedCount")).toInt() > 0) {
                selectedExam = exam;
                break;
            }
        }
    }
    if (selectedExam.isEmpty()) {
        selectedExam = reviewExams.first().toMap();
    }

    currentExamId = selectedExam.value(QStringLiteral("id")).toInt();
    if (currentExamId <= 0) {
        return;
    }

    examInfo = normalizeExam(selectedExam);
    refreshExamSelector();
    students = repository->getReviewStudents(currentExamId);
    currentStudentIndex = 0;
    currentQuestionIndex = 0;
    backendDataLoaded = true;

    if (!students.isEmpty()) {
        loadPaperAnswer(students.first().toMap().value(QStringLiteral("studentNo")).toString());
    }
}

QVariantMap TeacherMarkWindow::normalizeExam(const QVariantMap &exam) const
{
    QString date = exam.value(QStringLiteral("date")).toString();
    if (date.isEmpty()) {
        date = exam.value(QStringLiteral("startTime"), exam.value(QStringLiteral("start_time"))).toString().left(10);
    }
    if (date.isEmpty()) {
        date = QDate::currentDate().toString(QStringLiteral("yyyy-MM-dd"));
    }

    return QVariantMap{
        {QStringLiteral("title"), exam.value(QStringLiteral("title"), exam.value(QStringLiteral("name"), QStringLiteral("未命名考试")))},
        {QStringLiteral("course"), exam.value(QStringLiteral("course"), exam.value(QStringLiteral("subject"), QStringLiteral("综合")))},
        {QStringLiteral("date"), date},
        {QStringLiteral("totalScore"), exam.value(QStringLiteral("totalScore"), exam.value(QStringLiteral("total_score"), 0))},
        {QStringLiteral("average"), exam.value(QStringLiteral("average"), exam.value(QStringLiteral("averageScore"), 0))}
    };
}

void TeacherMarkWindow::refreshExamSelector()
{
    if (examCombo == nullptr) {
        return;
    }
    syncingExamCombo = true;
    examCombo->clear();
    for (const QVariant &value : reviewExams) {
        const QVariantMap exam = value.toMap();
        const int id = exam.value(QStringLiteral("id")).toInt();
        const QString title = exam.value(QStringLiteral("title"), exam.value(QStringLiteral("name"), QStringLiteral("未命名考试"))).toString();
        const QString subject = exam.value(QStringLiteral("course"), exam.value(QStringLiteral("subject"))).toString();
        const QString label = subject.trimmed().isEmpty() ? title : QStringLiteral("%1 · %2").arg(title, subject);
        examCombo->addItem(label, id);
        if (id == currentExamId) {
            examCombo->setCurrentIndex(examCombo->count() - 1);
        }
    }
    if (examCombo->count() == 0) {
        examCombo->addItem(QStringLiteral("暂无可批改考试"), 0);
    }
    syncingExamCombo = false;
}

void TeacherMarkWindow::refreshAll()
{
    refreshExamInfo();
    studentListWidget->setStudents(students);
    studentListWidget->setCurrentStudent(currentStudentIndex);
    refreshStudent();
}

void TeacherMarkWindow::refreshExamInfo()
{
    int completed = 0;
    double sum = 0;
    int scoreCount = 0;
    for (const QVariant &value : students) {
        const QVariantMap student = value.toMap();
        if (student.value(QStringLiteral("status")).toString() == QStringLiteral("已批改")) {
            completed += 1;
        }
        bool ok = false;
        const double score = student.value(QStringLiteral("score")).toDouble(&ok);
        if (ok) {
            sum += score;
            scoreCount += 1;
        }
    }
    const double fallbackAverage = examInfo.value(QStringLiteral("average"), 0).toDouble();
    const double average = scoreCount > 0 ? sum / scoreCount : fallbackAverage;
    examInfoCard->setExamInfo(examInfo, completed, students.size(), average);
}

void TeacherMarkWindow::refreshStudent()
{
    const QVariantMap student = currentStudent();
    const QVariantList answers = currentAnswers();
    if (answers.isEmpty()) {
        currentQuestionIndex = 0;
    } else if (currentQuestionIndex < 0 || currentQuestionIndex >= answers.size()
               || answers.at(currentQuestionIndex).toMap().value(QStringLiteral("autoScored")).toBool()) {
        currentQuestionIndex = firstTeacherQuestionIndex(answers);
    }
    answerPreviewWidget->setPaperAnswer(student, answers, currentQuestionIndex);
    scorePanelWidget->setQuestion(currentQuestion());
}

QVariantMap TeacherMarkWindow::currentStudent() const
{
    if (currentStudentIndex < 0 || currentStudentIndex >= students.size()) {
        return {};
    }
    return students.at(currentStudentIndex).toMap();
}

QVariantList TeacherMarkWindow::currentAnswers() const
{
    const QString studentNo = currentStudent().value(QStringLiteral("studentNo")).toString();
    return answersByStudent.value(studentNo);
}

QVariantMap TeacherMarkWindow::currentQuestion() const
{
    const QVariantList answers = currentAnswers();
    if (currentQuestionIndex < 0 || currentQuestionIndex >= answers.size()) {
        return {};
    }
    return answers.at(currentQuestionIndex).toMap();
}

void TeacherMarkWindow::setCurrentQuestion(int index)
{
    const QVariantList answers = currentAnswers();
    if (answers.isEmpty()) {
        currentQuestionIndex = 0;
    } else {
        currentQuestionIndex = qBound(0, index, answers.size() - 1);
        if (answers.at(currentQuestionIndex).toMap().value(QStringLiteral("autoScored")).toBool()) {
            currentQuestionIndex = firstTeacherQuestionIndex(answers);
        }
    }
    answerPreviewWidget->setCurrentQuestion(currentQuestionIndex);
    scorePanelWidget->setQuestion(currentQuestion());
}

int TeacherMarkWindow::firstTeacherQuestionIndex(const QVariantList &answers) const
{
    for (int i = 0; i < answers.size(); ++i) {
        const QVariantMap row = answers.at(i).toMap();
        if (!row.value(QStringLiteral("autoScored")).toBool()
                && !row.value(QStringLiteral("graded")).toBool()) {
            return i;
        }
    }
    for (int i = 0; i < answers.size(); ++i) {
        if (!answers.at(i).toMap().value(QStringLiteral("autoScored")).toBool()) {
            return i;
        }
    }
    return answers.isEmpty() ? 0 : -1;
}

int TeacherMarkWindow::adjacentTeacherQuestionIndex(int fromIndex, int direction) const
{
    const QVariantList answers = currentAnswers();
    if (answers.isEmpty() || direction == 0) {
        return -1;
    }
    int index = fromIndex + (direction > 0 ? 1 : -1);
    while (index >= 0 && index < answers.size()) {
        if (!answers.at(index).toMap().value(QStringLiteral("autoScored")).toBool()) {
            return index;
        }
        index += direction > 0 ? 1 : -1;
    }
    return -1;
}

bool TeacherMarkWindow::isStudentCompleted(const QVariantList &answers) const
{
    for (const QVariant &value : answers) {
        const QVariantMap row = value.toMap();
        if (!row.value(QStringLiteral("autoScored")).toBool()
                && !row.value(QStringLiteral("graded")).toBool()) {
            return false;
        }
    }
    return !answers.isEmpty();
}

double TeacherMarkWindow::totalScore(const QVariantList &answers) const
{
    double total = 0;
    for (const QVariant &value : answers) {
        total += value.toMap().value(QStringLiteral("score")).toDouble();
    }
    return total;
}
