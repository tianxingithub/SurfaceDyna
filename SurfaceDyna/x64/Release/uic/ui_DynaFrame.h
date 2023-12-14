/********************************************************************************
** Form generated from reading UI file 'DynaFrame.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DYNAFRAME_H
#define UI_DYNAFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DynaFrameClass
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *DynaFrameClass)
    {
        if (DynaFrameClass->objectName().isEmpty())
            DynaFrameClass->setObjectName(QString::fromUtf8("DynaFrameClass"));
        DynaFrameClass->resize(773, 499);
        verticalLayout_2 = new QVBoxLayout(DynaFrameClass);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(DynaFrameClass);

        QMetaObject::connectSlotsByName(DynaFrameClass);
    } // setupUi

    void retranslateUi(QWidget *DynaFrameClass)
    {
        DynaFrameClass->setWindowTitle(QApplication::translate("DynaFrameClass", "Manager", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DynaFrameClass: public Ui_DynaFrameClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DYNAFRAME_H
