#ifndef STUDENTLISTWIDGET_H
#define STUDENTLISTWIDGET_H

#include <QWidget>
#include <QVariantList>

class QLineEdit;
class QListWidget;
class QPushButton;

class StudentListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StudentListWidget(QWidget *parent = nullptr);

    void setStudents(const QVariantList &students);
    void setCurrentStudent(int index);
    void updateStudent(int index, const QVariantMap &student);
    int currentStudent() const;

signals:
    void studentSelected(int index);
    void previousStudentRequested();
    void nextStudentRequested();

private slots:
    void applyFilter(const QString &keyword);

private:
    void rebuildList();
    void refreshSelection();

    QLineEdit *searchEdit;
    QListWidget *listWidget;
    QPushButton *previousButton;
    QPushButton *nextButton;
    QVariantList studentRows;
    int currentIndex;
};

#endif // STUDENTLISTWIDGET_H
