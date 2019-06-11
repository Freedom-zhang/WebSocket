/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QLineEdit *input;
    QPushButton *send;
    QPlainTextEdit *output;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(400, 300);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        input = new QLineEdit(Dialog);
        input->setObjectName(QStringLiteral("input"));

        gridLayout->addWidget(input, 1, 0, 1, 1);

        send = new QPushButton(Dialog);
        send->setObjectName(QStringLiteral("send"));

        gridLayout->addWidget(send, 1, 1, 1, 1);

        output = new QPlainTextEdit(Dialog);
        output->setObjectName(QStringLiteral("output"));
        output->setReadOnly(true);
        output->setPlainText(QStringLiteral("Initializing WebChannel..."));
        output->setBackgroundVisible(false);

        gridLayout->addWidget(output, 0, 0, 1, 2);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        input->setPlaceholderText(QApplication::translate("Dialog", "Message Contents", 0));
        send->setText(QApplication::translate("Dialog", "Send", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
