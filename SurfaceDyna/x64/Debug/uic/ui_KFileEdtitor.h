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
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolButton>
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
    QHBoxLayout *horizontalLayout_2;
    QToolButton *btnOpen;
    QToolButton *btnSave;
    QToolButton *btnSetting;
    QToolButton *btnOpenDyna;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSplitter *splitter;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_4;

    void setupUi(QMainWindow *KFileEdtitorClass)
    {
        if (KFileEdtitorClass->objectName().isEmpty())
            KFileEdtitorClass->setObjectName(QString::fromUtf8("KFileEdtitorClass"));
        KFileEdtitorClass->resize(843, 494);
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
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnOpen = new QToolButton(centralWidget);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));
        btnOpen->setMinimumSize(QSize(0, 0));
        btnOpen->setStyleSheet(QString::fromUtf8("border:0;\n"
"margin:3;\n"
"padding:0"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../Icon/open-kdyna.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnOpen->setIcon(icon);

        horizontalLayout_2->addWidget(btnOpen);

        btnSave = new QToolButton(centralWidget);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setMinimumSize(QSize(0, 0));
        btnSave->setStyleSheet(QString::fromUtf8("border:0;\n"
"margin:3;\n"
"padding:0"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../../Icon/export-kdyna.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSave->setIcon(icon1);

        horizontalLayout_2->addWidget(btnSave);

        btnSetting = new QToolButton(centralWidget);
        btnSetting->setObjectName(QString::fromUtf8("btnSetting"));
        btnSetting->setMinimumSize(QSize(0, 0));
        btnSetting->setStyleSheet(QString::fromUtf8("border:0;\n"
"margin:3;\n"
"padding:0"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../../../Icon/setting-kdyna.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSetting->setIcon(icon2);

        horizontalLayout_2->addWidget(btnSetting);

        btnOpenDyna = new QToolButton(centralWidget);
        btnOpenDyna->setObjectName(QString::fromUtf8("btnOpenDyna"));
        btnOpenDyna->setMinimumSize(QSize(0, 0));
        btnOpenDyna->setStyleSheet(QString::fromUtf8("border:0;\n"
"margin:3px;\n"
"padding:0"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../../Icon/dyna.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnOpenDyna->setIcon(icon3);

        horizontalLayout_2->addWidget(btnOpenDyna);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        verticalLayoutWidget = new QWidget(splitter);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        splitter->addWidget(verticalLayoutWidget);
        horizontalLayoutWidget_3 = new QWidget(splitter);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        splitter->addWidget(horizontalLayoutWidget_3);

        horizontalLayout_3->addWidget(splitter);


        verticalLayout_2->addLayout(horizontalLayout_3);

        KFileEdtitorClass->setCentralWidget(centralWidget);

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
        btnOpen->setText(QString());
        btnSave->setText(QString());
        btnSetting->setText(QString());
        btnOpenDyna->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class KFileEdtitorClass: public Ui_KFileEdtitorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KFILEEDTITOR_H
