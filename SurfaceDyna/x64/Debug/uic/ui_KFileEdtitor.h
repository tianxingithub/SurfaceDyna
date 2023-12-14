/********************************************************************************
** Form generated from reading UI file 'KFileEdtitor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KFILEEDTITOR_H
#define UI_KFILEEDTITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KFileEdtitorClass
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *menuDemo;
    QAction *actionSetting;
    QAction *actionDyna;
    QAction *actionOpenDyna;
    QAction *actionDynaClose;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QSplitter *splitter;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menuManager;

    void setupUi(QMainWindow *KFileEdtitorClass)
    {
        if (KFileEdtitorClass->objectName().isEmpty())
            KFileEdtitorClass->setObjectName(QString::fromUtf8("KFileEdtitorClass"));
        KFileEdtitorClass->resize(603, 372);
        actionOpen = new QAction(KFileEdtitorClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(KFileEdtitorClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        menuDemo = new QAction(KFileEdtitorClass);
        menuDemo->setObjectName(QString::fromUtf8("menuDemo"));
        actionSetting = new QAction(KFileEdtitorClass);
        actionSetting->setObjectName(QString::fromUtf8("actionSetting"));
        actionDyna = new QAction(KFileEdtitorClass);
        actionDyna->setObjectName(QString::fromUtf8("actionDyna"));
        actionOpenDyna = new QAction(KFileEdtitorClass);
        actionOpenDyna->setObjectName(QString::fromUtf8("actionOpenDyna"));
        actionDynaClose = new QAction(KFileEdtitorClass);
        actionDynaClose->setObjectName(QString::fromUtf8("actionDynaClose"));
        centralWidget = new QWidget(KFileEdtitorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(9, 9, 9, 9);
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        verticalLayoutWidget = new QWidget(splitter);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        splitter->addWidget(verticalLayoutWidget);
        horizontalLayoutWidget = new QWidget(splitter);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        splitter->addWidget(horizontalLayoutWidget);

        verticalLayout_2->addWidget(splitter);

        KFileEdtitorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(KFileEdtitorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 603, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menuManager = new QMenu(menuBar);
        menuManager->setObjectName(QString::fromUtf8("menuManager"));
        KFileEdtitorClass->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menuManager->menuAction());
        menu->addAction(actionOpen);
        menu->addAction(actionSave);
        menu_2->addAction(actionSetting);
        menuManager->addAction(actionOpenDyna);
        menuManager->addAction(actionDynaClose);

        retranslateUi(KFileEdtitorClass);

        QMetaObject::connectSlotsByName(KFileEdtitorClass);
    } // setupUi

    void retranslateUi(QMainWindow *KFileEdtitorClass)
    {
        KFileEdtitorClass->setWindowTitle(QApplication::translate("KFileEdtitorClass", "\346\277\200\345\217\221\344\273\277\347\234\237\350\275\257\344\273\266", nullptr));
        actionOpen->setText(QApplication::translate("KFileEdtitorClass", "\346\211\223\345\274\200", nullptr));
        actionSave->setText(QApplication::translate("KFileEdtitorClass", "\345\257\274\345\207\272", nullptr));
        menuDemo->setText(QApplication::translate("KFileEdtitorClass", "Demo", nullptr));
        actionSetting->setText(QApplication::translate("KFileEdtitorClass", "\350\267\257\345\276\204\351\200\211\346\213\251", nullptr));
        actionDyna->setText(QApplication::translate("KFileEdtitorClass", "manager", nullptr));
        actionOpenDyna->setText(QApplication::translate("KFileEdtitorClass", "Open", nullptr));
        actionDynaClose->setText(QApplication::translate("KFileEdtitorClass", "close", nullptr));
        menu->setTitle(QApplication::translate("KFileEdtitorClass", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QApplication::translate("KFileEdtitorClass", "\351\205\215\347\275\256\344\277\241\346\201\257", nullptr));
        menuManager->setTitle(QApplication::translate("KFileEdtitorClass", "Manager", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KFileEdtitorClass: public Ui_KFileEdtitorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KFILEEDTITOR_H
