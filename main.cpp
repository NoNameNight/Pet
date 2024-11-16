#include "widget.h"

#include "ResourcesManager.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Pet_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    try
    {
        ResourcesManager::instance()->load();
    }
    catch (const QString id)
    {
        char err_msg[512] = { 0 };
        sprintf_s(err_msg, ("无法加载: %s"), id.toStdString().c_str());
        QMessageBox msg_box;
        msg_box.setText("Resources Load Error");
        msg_box.setInformativeText(err_msg);
        msg_box.setStandardButtons(QMessageBox::Ok);
        msg_box.setDefaultButton(QMessageBox::Ok);
        int ret = msg_box.exec();
        return -1;
    }


    Widget w;
    w.show();
    return a.exec();
}
