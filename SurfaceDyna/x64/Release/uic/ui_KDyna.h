/********************************************************************************
** Form generated from reading UI file 'KDyna.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KDYNA_H
#define UI_KDYNA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KDynaClass
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;

    void setupUi(QWidget *KDynaClass)
    {
        if (KDynaClass->objectName().isEmpty())
            KDynaClass->setObjectName(QString::fromUtf8("KDynaClass"));
        KDynaClass->resize(654, 422);
        verticalLayout = new QVBoxLayout(KDynaClass);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(KDynaClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(KDynaClass);

        QMetaObject::connectSlotsByName(KDynaClass);
    } // setupUi

    void retranslateUi(QWidget *KDynaClass)
    {
        KDynaClass->setWindowTitle(QApplication::translate("KDynaClass", "\346\277\200\345\217\221\344\273\277\347\234\237\350\275\257\344\273\266\347\240\224\345\217\221\346\224\257\346\222\221\346\234\215\345\212\241\345\271\263\345\217\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("KDynaClass", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("KDynaClass", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KDynaClass: public Ui_KDynaClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KDYNA_H
