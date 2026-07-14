#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <QVariantList>
#include <QVariantMap>

class ReportGenerator
{
public:
    QVariantList loadScoreData(const QString &className, const QString &examName) const;
    QVariantMap generateReport(const QString &className,
                               const QString &examName,
                               const QString &reportType) const;

private:
    QVariantMap statisticsForScores(const QVariantList &scores) const;
};

#endif // REPORTGENERATOR_H
