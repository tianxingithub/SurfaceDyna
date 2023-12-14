/********************************************************************************
** Form generated from reading UI file 'SettingDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingDialogClass
{
public:
    QPushButton *btnFrameName;
    QLabel *label_3;
    QLineEdit *editFrameName;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *editDynaPath;
    QLineEdit *editTsPath;
    QPushButton *btnTs;
    QPushButton *btnDyna;
    QPushButton *btnClose;

    void setupUi(QDialog *SettingDialogClass)
    {
        if (SettingDialogClass->objectName().isEmpty())
            SettingDialogClass->setObjectName(QString::fromUtf8("SettingDialogClass"));
        SettingDialogClass->resize(690, 291);
        btnFrameName = new QPushButton(SettingDialogClass);
        btnFrameName->setObjectName(QString::fromUtf8("btnFrameName"));
        btnFrameName->setGeometry(QRect(550, 130, 101, 31));
        QFont font;
        font.setPointSize(11);
        btnFrameName->setFont(font);
        label_3 = new QLabel(SettingDialogClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 130, 116, 23));
        label_3->setFont(font);
        editFrameName = new QLineEdit(SettingDialogClass);
        editFrameName->setObjectName(QString::fromUtf8("editFrameName"));
        editFrameName->setGeometry(QRect(180, 130, 351, 31));
        label = new QLabel(SettingDialogClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 30, 116, 23));
        label->setFont(font);
        label_2 = new QLabel(SettingDialogClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 80, 116, 23));
        label_2->setFont(font);
        editDynaPath = new QLineEdit(SettingDialogClass);
        editDynaPath->setObjectName(QString::fromUtf8("editDynaPath"));
        editDynaPath->setGeometry(QRect(180, 80, 351, 31));
        editTsPath = new QLineEdit(SettingDialogClass);
        editTsPath->setObjectName(QString::fromUtf8("editTsPath"));
        editTsPath->setGeometry(QRect(180, 30, 351, 31));
        btnTs = new QPushButton(SettingDialogClass);
        btnTs->setObjectName(QString::fromUtf8("btnTs"));
        btnTs->setGeometry(QRect(550, 30, 101, 31));
        btnTs->setFont(font);
        btnDyna = new QPushButton(SettingDialogClass);
        btnDyna->setObjectName(QString::fromUtf8("btnDyna"));
        btnDyna->setGeometry(QRect(550, 80, 101, 31));
        btnDyna->setFont(font);
        btnClose = new QPushButton(SettingDialogClass);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(550, 240, 101, 31));
        btnClose->setFont(font);

        retranslateUi(SettingDialogClass);

        QMetaObject::connectSlotsByName(SettingDialogClass);
    } // setupUi

    void retranslateUi(QDialog *SettingDialogClass)
    {
        SettingDialogClass->setWindowTitle(QApplication::translate("SettingDialogClass", "\351\205\215\347\275\256\346\226\207\344\273\266\350\267\257\345\276\204", nullptr));
        btnFrameName->setText(QApplication::translate("SettingDialogClass", "\347\241\256\345\256\232", nullptr));
        label_3->setText(QApplication::translate("SettingDialogClass", "\347\252\227\344\275\223\345\220\215\345\255\227", nullptr));
        label->setText(QApplication::translate("SettingDialogClass", "\347\277\273\350\257\221\346\226\207\344\273\266\350\267\257\345\276\204", nullptr));
        label_2->setText(QApplication::translate("SettingDialogClass", "Manager\347\250\213\345\272\217\350\267\257\345\276\204", nullptr));
        btnTs->setText(QApplication::translate("SettingDialogClass", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        btnDyna->setText(QApplication::translate("SettingDialogClass", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        btnClose->setText(QApplication::translate("SettingDialogClass", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingDialogClass: public Ui_SettingDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
