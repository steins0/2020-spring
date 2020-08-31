#include "widget.h"
#include "ui_widget.h"
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QEvent>
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <iostream>
//#include "seekfile.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle(tr("局域网文件传输服务器"));
    /*清空列表文件*/
    if((fp = fopen("./FileList/FILELIST.TXT","w+"))==NULL)
    {
        qDebug()<<"Clear FILELIST.TXT error!";
    }
    fclose(fp);
    server = new Myserver(this);
    server->listen(QHostAddress::Any, 8888);
    closeCommand = 0;

    ui->ClientPB1->setEnabled(false);
    ui->ClientPB2->setEnabled(false);
    ui->ClientPB3->setEnabled(false);
    /*为三个按键安装事件过滤器*/
    ui->ClientPB1->installEventFilter(this);
    ui->ClientPB2->installEventFilter(this);
    ui->ClientPB3->installEventFilter(this);

    ui->LBstate1->setText(tr("断开"));
    ui->LBstate2->setText(tr("断开"));
    ui->LBstate3->setText(tr("断开"));

    connect(ui->pushButton,&QPushButton::clicked,this,&Widget::fileTranferButtonSlot);
    connect(ui->AddFilePB,&QPushButton::clicked,this,&Widget::addFilePBSlot);
    connect(ui->DelFilePB,&QPushButton::clicked,this,&Widget::deleteFileListItem);
    connect(ui->listWidget,&QAbstractItemView::doubleClicked,this,&Widget::doubleClickedItem);
}

Widget::~Widget()
{
    delete ui;
}



bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->ClientPB1)
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
            emit clientDiconnectSignal(1);
            ui->LBDisplayIP1->clear();
            ui->LBstate1->setText(tr("断开"));
            ui->ClientPB1->setEnabled(false);
        }
    }
    else if(watched == ui->ClientPB2)
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
            emit clientDiconnectSignal(2);
            ui->LBDisplayIP2->clear();
            ui->LBstate2->setText(tr("断开"));
            ui->ClientPB2->setEnabled(false);
        }
    }
    else if(watched == ui->ClientPB3)
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
            emit clientDiconnectSignal(3);
            ui->LBDisplayIP3->clear();
            ui->LBstate3->setText(tr("断开"));
            ui->ClientPB3->setEnabled(false);
        }
    }
}

void Widget::closeClientConnectSlot(int ID)
{
    /*判断是哪个客户端断开，并做相应的清除工作*/
    if(ID == 1)
    {
        ui->LBDisplayIP1->clear();
        ui->LBstate1->setText(tr("断开"));
        ui->ClientPB1->setEnabled(false);
    }
    else if(ID == 2)
    {
        ui->LBDisplayIP2->clear();;
        ui->LBstate2->setText(tr("断开"));
        ui->ClientPB2->setEnabled(false);
    }
    else if(ID == 3)
    {
        ui->LBDisplayIP3->clear();
        ui->LBstate3->setText(tr("断开"));
        ui->ClientPB3->setEnabled(false);
    }
}

void Widget::addFilePBSlot()
{
    /*打开目录获得文件目录*/
    dirPath = QFileDialog::getExistingDirectory(this,0,"./");
    QDir dir(dirPath);
#if defined __DEBUG__
    qDebug()<<"Open dir path"<<dirPath;
#endif
    if(dirPath.isEmpty())
        return;
#if defined __DEBUG__
      qDebug()<<"Open directory name is :"<<dir.dirName();
#endif
      this->getSendFileList(dirPath);
    /*获取目录名字，并添加到ListWidget中*/
    ui->listWidget->addItem(dir.dirName());
}
void Widget::getSendFileList(QString path)
{
    QFile filelist("FILELIST.txt");
    QTextStream out(&filelist);
    if(!filelist.open(QFile::WriteOnly|QFile::Text))
    {
        qDebug()<<"write FILELIST.TXT error!"<<endl;
        return;
    }
    QDir dir(path);
    QStringList str;
    str << "*";
    QFileInfoList files = dir.entryInfoList((QStringList)"*",
                                            QDir::Files|QDir::Dirs,QDir::DirsFirst);
    for(int i=0;i<files.count();i++)        //把目录中的文件名写入filelist.txt文件中发送至客户端
    {
        QFileInfo tmpFileInfo = files.at(i);
        QString fileName = tmpFileInfo.fileName();
        if(fileName=="."||fileName=="..")   //过滤掉“.”和“..”目录
            continue;
        if(tmpFileInfo.isFile())
            out << fileName << endl;
        else
            continue;
#ifdef __DEBUG__
        qDebug()<<tmpFileInfo.fileName();
#endif
    filelist.close();
}

void Widget::doubleClickedItem()
{
    /*获得双击项文本*/
    QString str = ui->listWidget->currentItem()->text();
#if defined __DEBUG__
    qDebug()<<"双击项文本内容str为"<<str;
#endif
    QDir dir;
    /*设置路径为添加文件的路径*/
    dir.setPath(dirPath);
    /*切换路径为双击项的路径*/
    dir.cd(str);
    dirPath = dir.absolutePath();
#if defined __DEBUG__
    qDebug()<<"当前文件绝对路径为"<<dirPath;
#endif
    /*更新列表文件内容*/
    this->getSendFileList(dirPath);
    QStringList nameFilters;
    nameFilters << "*";
    QFileInfoList files = dir.entryInfoList(nameFilters,QDir::AllEntries,QDir::DirsFirst);
    ui->listWidget->clear();
    if(str=="..")                       //当返回上一级目录时，只显示目录不显示文件
    {
        for(int i =0 ;i<files.count();i++)
        {
            QFileInfo tmpFileInfo = files.at(i);
            QString fileName = tmpFileInfo.fileName();
            QListWidgetItem *tmp =new QListWidgetItem(fileName);
            if(tmpFileInfo.isDir())         //显示目录
            {
                ui->listWidget->addItem(tmp);
            }
        }
    }
    else
    {
        for(int i =0 ;i<files.count();i++)
        {
            QFileInfo tmpFileInfo = files.at(i);
            QString fileName = tmpFileInfo.fileName();
            QListWidgetItem *tmp =new QListWidgetItem(fileName);
            if(tmpFileInfo.isDir())         //显示目录
            {
                ui->listWidget->addItem(tmp);
            }
            if(tmpFileInfo.isFile())        //显示文件
            {
                ui->listWidget->addItem(tmp);
            }
        }
    }
}

void Widget::fileTranferButtonSlot()
{
    QString fileName = QFileDialog::getOpenFileName(this);
#if defined __DEBUG__
    qDebug()<<"Open file's name is"<<fileName;
#endif
    if(!fileName.isEmpty())
    {
        qDebug()<<"Open file successed!";
    }
    emit sendFileSignal(fileName);
}

void Widget::addClientIPTGUISlot(QString CIP,int ID,int state)
{
    /*判断连接的客户端数量，并根据连接的客户端信息进行界面更新*/
    if((ID == 1)&&(state==QAbstractSocket::ConnectedState))
    {
        ui->LBDisplayIP1->setText(CIP);
        ui->LBstate1->setText(tr("连接"));
        ui->ClientPB1->setEnabled(true);
    }
    else if((ID == 2)&&(state==QAbstractSocket::ConnectedState))
    {
        ui->LBDisplayIP2->setText(CIP);
        ui->LBstate2->setText(tr("连接"));
        ui->ClientPB2->setEnabled(true);
    }
    else if((ID == 3)&&(state==QAbstractSocket::ConnectedState))
    {
        ui->LBDisplayIP3->setText(CIP);
        ui->LBstate3->setText(tr("连接"));
        ui->ClientPB3->setEnabled(true);
    }
}
