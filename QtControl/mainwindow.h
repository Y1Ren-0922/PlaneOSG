#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qstring.h>
#include<winsock2.h>
#include <Ws2tcpip.h>  //InetNtop 和InetPton 声明的文件
#pragma comment(lib, "ws2_32.lib")

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString jsonName;

public slots:
    void getJsonFileName(const QString& text);
    void ourConnect();

protected:
	void init();

private:
    Ui::MainWindow *ui;
	SOCKET sclient;
};

#endif // MAINWINDOW_H
