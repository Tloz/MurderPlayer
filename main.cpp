#include <QDebug>
#include <QLocale>
#include <QString>
#include <QMessageBox>
#include <QTranslator>
#include <QApplication>
#include <QLibraryInfo>

#include "GUI/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /* Translation stuff */
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    QTranslator translator2;
    translator2.load(QString("MurderPlayer_") + locale);
    app.installTranslator(&translator);
    app.installTranslator(&translator2);
    /* end */

    MainWindow *gw = new MainWindow();
    gw->show();

    return app.exec();
}
