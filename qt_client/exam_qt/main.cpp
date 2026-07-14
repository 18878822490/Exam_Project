#include "LoginWindow.h"

#include <QApplication>
#include <QFile>
#include <QIcon>
#include <QIODevice>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    qputenv("QT_ENABLE_HIGHDPI_SCALING", "0");
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "0");
    qputenv("QT_SCREEN_SCALE_FACTORS", "1");

    QApplication a(argc, argv);
    QApplication::setStyle("Fusion");
    QApplication::setWindowIcon(QIcon(QStringLiteral(":/assets/brand-logo-mark.png")));

    QFile styleFile(QStringLiteral(":/style.qss"));
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        a.setStyleSheet(QString::fromUtf8(styleFile.readAll()));
    }

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "exam_qt_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    LoginWindow w;
    w.show();
    return a.exec();
}
