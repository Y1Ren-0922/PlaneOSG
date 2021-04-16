#include "ui_mainwindow.h"
#include "mainwindow.h"

#include <iostream>
#include <qstring.h>
#include <qdebug.h>

#include<winsock2.h>
#include <Ws2tcpip.h>  //InetNtop 和InetPton 声明的文件
#pragma comment(lib, "ws2_32.lib")

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	//信号与槽函数绑定
    connect(ui->jsonComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(getJsonFileName(QString)));
    connect(ui->jsonBtn, SIGNAL(clicked(bool)), this, SLOT(ourConnect()));
    connect(ui->keyBoardBtn, SIGNAL(clicked(bool)), this, SLOT(ourConnect()));
	
	//程序运行时就进行连接
	init();
}

MainWindow::~MainWindow()
{
	closesocket(sclient);
	WSACleanup();
    delete ui;
}

//与通信程序进行连接
void MainWindow::init()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		exit(0);
	}


	sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == INVALID_SOCKET)
	{
		cout << "invalid socket!" << endl;
		exit(0);
	}
	sockaddr_in serAddr;
	//PCWSTR src = TEXT("192.168.1.119");
	PCWSTR src = TEXT("127.0.0.1");
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(22222);
	serAddr.sin_addr.S_un.S_addr;
	InetPton(AF_INET, src, &serAddr.sin_addr.S_un.S_addr);
	if (::connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		//连接失败 
		cout << "connect error !" << endl;
		closesocket(sclient);
		exit(0);
	}
}

//文件选择对应的槽函数
void MainWindow::getJsonFileName(const QString& text)
{
    jsonName = text;
}

//通信程序
void MainWindow::ourConnect()
{
    //获取信号源头对象的名称
    QString strObjectSrc = this->sender()->objectName();
	string fileName;
    if("jsonBtn" == strObjectSrc)
    {
        fileName = jsonName.toStdString() + '\n';

    }
    else if("keyBoardBtn" == strObjectSrc)
    {
	   fileName = "keyBoard" + '\n';
    }

	//发送字符串
    const char * sendData;
    sendData = fileName.c_str(); // string转const char*
	send(sclient, sendData, strlen(sendData), 0);

}
