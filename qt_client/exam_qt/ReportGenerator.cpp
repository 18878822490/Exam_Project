#include "ReportGenerator.h"

QVariantList ReportGenerator::loadScoreData(const QString &className, const QString &examName) const
{
    Q_UNUSED(className)
    Q_UNUSED(examName)
    return {};
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
        {QStringLiteral("date"), QStringLiteral("--")},
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
