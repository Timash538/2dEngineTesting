/********************************************************************************
** Form generated from reading UI file 'untitlednLyoPo.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UNTITLEDNLYOPO_H
#define UNTITLEDNLYOPO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog : QDialog
{
public:
    QVBoxLayout *verticalLayout;
    QCheckBox *isClient;
    QCheckBox *isServer;
    QLabel *label_2;
    QLineEdit *clientAddress;
    QLabel *label;
    QLineEdit *serverAddress;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(285, 229);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        isClient = new QCheckBox(Dialog);
        isClient->setObjectName(QString::fromUtf8("isClient"));

        verticalLayout->addWidget(isClient);

        isServer = new QCheckBox(Dialog);
        isServer->setObjectName(QString::fromUtf8("isServer"));

        verticalLayout->addWidget(isServer);

        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        clientAddress = new QLineEdit(Dialog);
        clientAddress->setObjectName(QString::fromUtf8("clientAddress"));

        verticalLayout->addWidget(clientAddress);

        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        serverAddress = new QLineEdit(Dialog);
        serverAddress->setObjectName(QString::fromUtf8("serverAddress"));

        verticalLayout->addWidget(serverAddress);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "\320\236\320\272\320\276\321\210\320\272\320\276)", nullptr));
        isClient->setText(QCoreApplication::translate("Dialog", "\320\232\320\273\320\270\320\265\320\275\321\202", nullptr));
        isServer->setText(QCoreApplication::translate("Dialog", "\320\241\320\265\321\200\320\262\320\265\321\200", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "\320\220\320\264\321\200\320\265\321\201 \320\272\320\273\320\270\320\265\320\275\321\202\320\260:", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "\320\220\320\264\321\200\320\265\321\201 \321\201\320\265\321\200\320\262\320\265\321\200\320\260:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UNTITLEDNLYOPO_H
