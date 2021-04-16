/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QComboBox *jsonComboBox;
    QPushButton *jsonBtn;
    QPushButton *keyBoardBtn;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QLineEdit *lineEdit_2;
    QLabel *label_5;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(900, 500);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        jsonComboBox = new QComboBox(centralWidget);
        jsonComboBox->setObjectName(QStringLiteral("jsonComboBox"));
        jsonComboBox->setGeometry(QRect(50, 60, 161, 41));
        jsonBtn = new QPushButton(centralWidget);
        jsonBtn->setObjectName(QStringLiteral("jsonBtn"));
        jsonBtn->setGeometry(QRect(240, 70, 61, 31));
        keyBoardBtn = new QPushButton(centralWidget);
        keyBoardBtn->setObjectName(QStringLiteral("keyBoardBtn"));
        keyBoardBtn->setGeometry(QRect(440, 70, 61, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 10, 151, 31));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(12);
        label->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(440, 10, 151, 31));
        label_2->setFont(font);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(60, 150, 101, 31));
        label_3->setFont(font);
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(190, 150, 151, 31));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(60, 240, 101, 31));
        label_4->setFont(font);
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(190, 240, 151, 31));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(80, 280, 81, 18));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 900, 30));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        jsonComboBox->clear();
        jsonComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Looping", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Roll", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Trudeln", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Split-S", Q_NULLPTR)
         << QApplication::translate("MainWindow", "InverLooping", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Rollenkehre", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Immelmann_Turn", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Turn", Q_NULLPTR)
        );
        jsonComboBox->setCurrentText(QApplication::translate("MainWindow", "Looping", Q_NULLPTR));
        jsonBtn->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", Q_NULLPTR));
        keyBoardBtn->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "json\346\226\207\344\273\266\346\216\247\345\210\266", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\351\224\256\347\233\230\346\216\247\345\210\266", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\347\233\256\346\240\207\345\234\260\345\235\200", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\345\217\202\346\225\260\350\216\267\345\217\226", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\345\276\205\346\211\251\345\261\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
