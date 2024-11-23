#include "widget.h"

#include "ResourcesManager.h"
#include "CharacterManager.h"

#include <QSharedMemory>

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QIcon>

#include <QLibrary>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>

// #include "Util.h"

/////////////////////////////////////////////////////////////////////////////////
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

class NNNSharedMemory
{
public:
    NNNSharedMemory(const char* name)
        : m_sharedMemory(name)
    {
        if(m_sharedMemory.attach())
        {
            QMessageBox::warning(nullptr, "Error", "An instance of the application is already running.");
        }
        else
        {
            m_sharedMemory.create(1); // 创建1byte大小的共享内存段
            m_have_create = true;
        }
    }
    ~NNNSharedMemory()
    {
        if(m_have_create)
        {
            m_sharedMemory.detach();
        }
    }

    bool canUse()
    {
        return m_have_create;
    }

private:
    QSharedMemory m_sharedMemory;
    bool m_have_create = false;
};

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

    NNNSharedMemory sharedMemory("20241116CreatePet");  // 设置绑定的共享内存段的key值
    if(!sharedMemory.canUse())
    {
        return -1;
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
