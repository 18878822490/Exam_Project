#ifndef TEACHERUIUTILS_H
#define TEACHERUIUTILS_H

#include <QFrame>
#include <QPushButton>
#include <QScrollArea>

namespace TeacherUi {
QFrame *createCard(QWidget *parent = nullptr);
void addShadow(QWidget *widget, int blur = 28, int yOffset = 10);
QPushButton *primaryButton(const QString &text, QWidget *parent = nullptr);
QPushButton *ghostButton(const QString &text, QWidget *parent = nullptr);
QScrollArea *scrollArea(QWidget *content, QWidget *parent = nullptr);
QLabel *sectionTitle(const QString &text, QWidget *parent = nullptr);
QLabel *mutedLabel(const QString &text, QWidget *parent = nullptr);
}

class HoverCard : public QFrame
{
    Q_OBJECT

public:
    explicit HoverCard(QWidget *parent = nullptr);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    bool lifted;
};

#endif // TEACHERUIUTILS_H
