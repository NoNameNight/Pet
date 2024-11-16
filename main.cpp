#include "widget.h"

#include "ResourcesManager.h"
#include "CharacterManager.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QIcon>

void initMenu(QMenu& menu)
{
    QAction* move_act = menu.addAction("move");
    QObject::connect(move_act, &QAction::triggered,
        [](){
            Character* pet = CharacterManager::instance()->getPet();
            pet->switchState("move");
        }
    );

    QAction* skill2_act = menu.addAction("skill2");
    QObject::connect(skill2_act, &QAction::triggered,
        [](){
            Character* pet = CharacterManager::instance()->getPet();
            pet->switchState("skill_2_begin");
        }
    );

    QAction* sit_act = menu.addAction("sit");
    QObject::connect(sit_act, &QAction::triggered,
        [](){
            Character* pet = CharacterManager::instance()->getPet();
            pet->switchState("sit");
        }
    );

    QAction* sleep_act = menu.addAction("sleep");
    QObject::connect(sleep_act, &QAction::triggered,
        [](){
            Character* pet = CharacterManager::instance()->getPet();
            pet->switchState("sleep");
        }
    );

    QAction* relax_act = menu.addAction("relax");
    QObject::connect(relax_act, &QAction::triggered,
        [](){
            Character* pet = CharacterManager::instance()->getPet();
            pet->switchState("relax");
        }
    );

    QAction* idle_act = menu.addAction("idle");
    QObject::connect(idle_act, &QAction::triggered,
        [](){
            Character* pet = CharacterManager::instance()->getPet();
            pet->switchState("idle");
        }
    );


    QAction* interact_act = menu.addAction("interact");
    QObject::connect(interact_act, &QAction::triggered,
        [](){
            Character* pet = CharacterManager::instance()->getPet();
            pet->switchState("interact");
        }
    );

    QAction* close_act = menu.addAction("close");
    QObject::connect(close_act, &QAction::triggered,
        [](){
            QApplication::quit();
        }
    );
}


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

    QMenu menu;
    initMenu(menu);
    w.setMenu(&menu);

    QIcon icon = QIcon("resources/ico.ico");
    QSystemTrayIcon sysTray(icon, &w);
    sysTray.setContextMenu(&menu);

    sysTray.show();
    w.show();
    return a.exec();
}
