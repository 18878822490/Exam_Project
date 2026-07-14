#include "ReportGenerator.h"

#include <QDate>
#include <QtGlobal>
#include <algorithm>

QVariantList ReportGenerator::loadScoreData(const QString &className, const QString &examName) const
{
    const QStringList names = {
        QStringLiteral("石晓虹"), QStringLiteral("张思远"), QStringLiteral("李雨涵"), QStringLiteral("王一鸣"),
        QStringLiteral("陈嘉宁"), QStringLiteral("赵若溪"), QStringLiteral("刘子墨"), QStringLiteral("周明轩"),
        QStringLiteral("孙亦辰"), QStringLiteral("吴佳怡"), QStringLiteral("郑云帆"), QStringLiteral("高梓萱"),
        QStringLiteral("马天宇"), QStringLiteral("何清越"), QStringLiteral("罗星然"), QStringLiteral("许安琪"),
        QStringLiteral("宋景行"), QStringLiteral("林芷若"), QStringLiteral("唐书宁"), QStringLiteral("韩知远"),
        QStringLiteral("梁思齐"), QStringLiteral("叶知秋"), QStringLiteral("顾清扬"), QStringLiteral("方若安")
    };

    const uint seed = qHash(className + examName + QStringLiteral("print"));
    QVariantList scores;
    for (int i = 0; i < names.size(); ++i) {
        const double offset = ((seed / (i + 5)) % 27) - 10;
        const double score = qBound(45.0, 73.0 + offset + (i % 6) * 3.2, 99.0);
        scores.append(QVariantMap{
            {QStringLiteral("studentNo"), QStringLiteral("S%1%2").arg(seed % 100, 2, 10, QLatin1Char('0')).arg(i + 1, 3, 10, QLatin1Char('0'))},
            {QStringLiteral("name"), names.at(i)},
            {QStringLiteral("score"), score}
        });
    }

    std::sort(scores.begin(), scores.end(), [](const QVariant &left, const QVariant &right) {
        return left.toMap().value(QStringLiteral("score")).toDouble()
                > right.toMap().value(QStringLiteral("score")).toDouble();
    });
    return scores;
}

QVariantMap ReportGenerator::generateReport(const QString &className,
                                            const QString &examName,
                                            const QString &reportType) const
{
    const QVariantList scores = loadScoreData(className, examName);
    return QVariantMap{
        {QStringLiteral("title"), QStringLiteral("智考星成绩报告")},
        {QStringLiteral("className"), className},
        {QStringLiteral("examName"), examName},
        {QStringLiteral("reportType"), reportType},
        {QStringLiteral("date"), QDate::currentDate().toString(QStringLiteral("yyyy-MM-dd"))},
        {QStringLiteral("scores"), scores},
        {QStringLiteral("stats"), statisticsForScores(scores)}
    };
}

QVariantMap ReportGenerator::statisticsForScores(const QVariantList &scores) const
{
    if (scores.isEmpty()) {
        return {
            {QStringLiteral("average"), 0},
            {QStringLiteral("highest"), 0},
            {QStringLiteral("lowest"), 0}
        };
    }

    double sum = 0;
    double highest = 0;
    double lowest = 100;
    for (const QVariant &value : scores) {
        const double score = value.toMap().value(QStringLiteral("score")).toDouble();
        sum += score;
        highest = qMax(highest, score);
        lowest = qMin(lowest, score);
    }
    return {
        {QStringLiteral("average"), sum / scores.size()},
        {QStringLiteral("highest"), highest},
        {QStringLiteral("lowest"), lowest}
    };
}
