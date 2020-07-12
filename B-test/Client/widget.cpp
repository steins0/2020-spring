#include "widget.h"
#include "ui_widget.h"
#include "debugonoroff.h"
#include "protocolcommand.h"

#include <QTcpSocket>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QTime>
#include <QListWidgetItem>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("局域网文件传输客户端"));
    flag = false;
    SYNFlag = 0;
    DOWNFlag = 0;
    /*文件发送相关初始化*/
    transferData.payloadSize = 640*1024;  //每次发送64kb

    transferData.bytesWritten = 0;
    transferData.bytesToWrite = 0;

    clearVariation();
    FILE *fp;
    if((fp = fopen("FILELIST.txt","w+"))==NULL)
    {
        qDebug()<<"Clear FILELIST.TXT error!";
    }
    fclose(fp);
    tcpSocket = new QTcpSocket();
    ui->ClientConnectPB->setText(tr("连接"));
    ui->DownloadPB->setEnabled(false);
    connect(tcpSocket,&QTcpSocket::readyRead,this,&Widget::receiveFile);
    connect(tcpSocket,&QTcpSocket::bytesWritten,this,&Widget::receiveFile);
    connect(tcpSocket,&QTcpSocket::disconnected,this,&Widget::socketDisconnected);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_ClientConnectPB_clicked()
{
  if(ui->ClientConnectPB->text()==tr("连接"))
  {
       /*断开所有的连接*/
       tcpSocket->abort();
       /*连接服务器*/
       tcpSocket->connectToHost(ui->ClientLineEdit->text(),8888);
       /*等待连接成功*/
       if(!tcpSocket->waitForConnected(30000))
       {
           qDebug()<<"Connection failed!";
           return ;
       }
       flag = true;
       qDebug()<<"Connect successfully!";
       ui->ClientConnectPB->setEnabled(true);
       ui->ClientConnectPB->setText(tr("断开"));
  }
  else
  {
      flag = false;
      /*断开连接*/
      tcpSocket->disconnectFromHost();
      /*修改按键的内容*/
      ui->ClientConnectPB->setText(tr("连接"));
  }
}

void Widget::sendFile(QString path)
{
#if defined __DEBUG__
    qDebug()<<"Socket send file name is"<<path;
#endif
    /*初始化发送字节为0*/
    char buf[4*1024] = {0};

    transferData.bytesWritten = 0;
    transferData.localFile = new QFile(path);
    if(!transferData.localFile->open(QFile::ReadOnly))
    {
        qDebug()<<tr("open file error!")<<endl;
        return;
    }
    /*获取文件大小*/
    transferData.totalBytes  = transferData.localFile->size();
#if defined __DEBUG__
    qDebug()<<"发送文件的内容大小"<<transferData.totalBytes;
#endif
    QDataStream sendOut(&transferData.inOrOutBlock,QIODevice::WriteOnly);

    sendOut.setVersion(QDataStream::Qt_5_7); //设置版本
    /*获得文件名称*/
    QString currentFilename = transferData.fileName.right(transferData.fileName.size()
                                                -transferData.fileName.lastIndexOf('/')-1);
#if defined __DEBUG__
    qDebug()<<"发送文件的名字"<<currentFilename;
#endif

    /*保留总大小信息空间、命令、文件名大小信息空间、然后输入文件名*/
    sendOut << qint64(0) << qint64(0) << qint64(0)<< currentFilename;
    /*总的大小*/
    transferData.totalBytes += transferData.inOrOutBlock.size();

    sendOut.device()->seek(0);
    /*填充实际的存储空间*/
    sendOut << transferData.totalBytes<<_TRANSFER_FILE_
            <<qint64((transferData.inOrOutBlock.size()-(sizeof(qint64)*3)));
#if defined __DEBUG__
    qDebug()<<"加上文件头文件的总大小"<<transferData.totalBytes
           <<"发送的命令为"<<_TRANSFER_FILE_
            <<"文件头的大小"<<transferData.inOrOutBlock.size()
           <<"文件名字的大小"<<qint64((transferData.inOrOutBlock.size()-(sizeof(qint64)*3)));
#endif
    /*
    qint64 sum = 0;
    do {
        sum = 0;
        sum = transferData.localFile->read(buf,sizeof(buf));
        sum = tcpSocket->write(buf,sum);

    }while(sum >0);*/

    qint64 sum = tcpSocket->write(transferData.inOrOutBlock);
#if defined __DEBUG__
    //qDebug()<<transferData.inOrOutBlock;
    qDebug()<<"sum"<<sum<<endl;
#endif
    transferData.bytesToWrite = transferData.totalBytes - sum;
#if defined __DEBUG__
    qDebug()<<"文件内容的大小"<<transferData.bytesToWrite;
#endif

    /*表示数据没有发送完*/


    if(transferData.bytesToWrite>0)
    {
        //发送文件内容部分
        transferData.inOrOutBlock = transferData.localFile->readAll();
        tcpSocket->write(transferData.inOrOutBlock);
        transferData.inOrOutBlock.resize(0);
    }
    transferData.localFile->close();

}

void Widget::receiveFile()
{
    /*标志变量：下载标志变量  同步文件列表标志变量  传输文件标志变量*/
    int downflag = 0  ,  synfilelistflag = 0,   transferfileflag = 0;
    qint32 temp;
    /*如果没有数据可读，就直接返回*/
    if(tcpSocket->bytesAvailable()<=0)
    {
        return;
    }
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_7);
    /*提取出总的大小、命令、文件名字的大小、文件名信息*/
    if(transferData.bytesReceived <= sizeof(qint64)*3)
    {
        if(tcpSocket->bytesAvailable()>=sizeof(qint64)*3
                &&(transferData.fileNameSize==0))
        {
            /*从套接字中提取总大小信息、命令、文件名字大小*/
            in >> transferData.totalBytes >> transferData.command
                    >> transferData.fileNameSize >> temp;
            transferData.bytesReceived += sizeof(qint64)*3;
#if defined __DEBUG__
            qDebug()<< "文件以及头信息总大小"<<transferData.totalBytes
                    << "接收的命令"<<transferData.command
                    << "接收文件名字大小"<<transferData.fileNameSize;
#endif
        }
        if(tcpSocket->bytesAvailable()>=transferData.fileNameSize
                &&transferData.fileNameSize!=0)
        {
            /*提取接收的文件名字*/
            in >> transferData.fileName;
            transferData.bytesReceived += transferData.fileNameSize;
#if defined __DEBUG__
            qDebug()<<"receive file name is"<<transferData.fileName;
            qDebug()<<"transferData.bytesReceive is"<<transferData.bytesReceived;
#endif

#if defined __DEBUG__
            if(tcpSocket->bytesAvailable())
            {
                qDebug()<<"socket have data!";
            }
#endif
        }
    }
    if(transferfileflag ==0)
    {
        switch(transferData.command)
        {
        case _TRANSFER_FILE_ :
        {
            transferfileflag = 1;
            if(transferData.fileNameSize != 0)
            {
                transferData.localFile = new QFile(tempFileName);
                if(!transferData.localFile->open(QFile::WriteOnly))
                {
                    qDebug()<<"open local file error!";
                    return;
                }
            }
        }
        case _TRANSFER_ACK_ :
        {
            qDebug()<<"Send file success!";
        }
            break;
        default:
            qDebug()<<"Receive command nulity!";
        }
    }
    if(transferData.bytesReceived < transferData.totalBytes)
    {
        transferData.bytesReceived += tcpSocket->bytesAvailable();
        transferData.inOrOutBlock = tcpSocket->readAll();
        transferData.localFile->write(transferData.inOrOutBlock);
        transferData.inOrOutBlock.resize(0);
    }
    if(transferData.bytesReceived == transferData.totalBytes)
        {
            clearVariation();
            if(transferfileflag == 1)
            {
                transferfileflag = 0;
                transferData.localFile->close();
                qDebug()<<"Receive file success!";
            }
            else if(synfilelistflag == 1)
            {
                synfilelistflag = 0;
                qDebug()<<"Request file list success!";
            }
            else if(downflag == 1)
            {
                downflag = 0;
                qDebug()<<"Download file success!";
            }
        }
}
void Widget::on_pushButton_clicked()
{
    SYNFlag = 0;
    DOWNFlag = 0;
    transferData.fileName = QFileDialog::getOpenFileName(this);
    if(!transferData.fileName.isEmpty())
    {
       qDebug()<<tr("打开文件成功")<<endl;
    }
    sendFile(transferData.fileName);
}

void Widget::clearVariation()
{
    transferData.totalBytes = 0;
    transferData.bytesReceived = 0;
    transferData.fileNameSize = 0;
    transferData.inOrOutBlock.resize(0);
}

void Widget::diaplayFileListForListWidget()
{

   QFile filelist("FILELIST.txt");
   if(!filelist.open(QFile::ReadOnly|QFile::Text))
   {
       qDebug()<<"open filelist.txt error!"<<endl;
       return;
   }
   QTextStream input(&filelist);
   QString line;
   ui->listWidget->clear();            //每同步之前需要先进行清除工作
   while(input.readLineInto(&line))    //把所有文件名进行显示
   {
       ui->listWidget->addItem(line);
   }

    //tcpSocket->write("")
}


void Widget::socketDisconnected()
{
    ui->ClientLineEdit->clear();
    ui->ClientConnectPB->setText(tr("连接"));
}

void Widget::on_SynFilePtn_clicked()
{

    QString tempFileName;
    //tempFileName = "./FileList/";
    /*初始化发送字节为0*/
    clearVariation();
    SYNFlag = 1;
    QDataStream sendOut(&transferData.inOrOutBlock,QIODevice::WriteOnly);

    /*设置版本*/
    sendOut.setVersion(QDataStream::Qt_5_7);
    QString currentfilename;
    currentfilename = " ";
    /*保留总大小信息空间、文件名大小信息空间、然后输入文件名*/
    sendOut << qint64(0) << qint64(0) << qint64(0) << currentfilename;
    /*总的大小是包含总大小信息、文件名大小信息、文件名和实际文件大小的总和*/
    transferData.totalBytes += transferData.inOrOutBlock.size();

    sendOut.device()->seek(0);
    /*填充实际的存储空间*/
    sendOut << transferData.totalBytes << _TRANSFER_LIST_
            << qint64((transferData.inOrOutBlock.size()-sizeof(qint64)*3));

    qint64 sum = tcpSocket->write(transferData.inOrOutBlock);
    transferData.bytesToWrite = transferData.totalBytes - sum;
#if defined __DEBUG__
    qDebug()<<"sum"<<sum;
    qDebug()<<"文件内容大小"<<transferData.bytesToWrite;
#endif
    transferData.inOrOutBlock.resize(0);
    sleep(100);
    diaplayFileListForListWidget();
    /*如果列表不为空使能下载按钮*/
    if(ui->listWidget->count())
    {
        ui->DownloadPB->setEnabled(true);
    }
    else
    {
        ui->DownloadPB->setEnabled(false);
    }
//    this->displayFileListToWidget();
}


void Widget::sleep(int ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while(QTime::currentTime()< dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}

void Widget::on_DownloadPB_clicked()
{
    SYNFlag = 0;
    DOWNFlag = 1;
    //tempFileName = "./DownloadFile/";
    /*获得要下载的文件名字*/
    QString downloadfile = ui->listWidget->currentItem()->text();
    if(downloadfile.isEmpty())
        return;
    transferData.fileName = downloadfile;
 //#if defined __DEBUG__
    qDebug()<<"发送数据的总大小"<<transferData.totalBytes;
//#endif
    QDataStream sendOut(&transferData.inOrOutBlock,QIODevice::WriteOnly);
    /*设置版本*/
    sendOut.setVersion(QDataStream::Qt_5_7);
    /*保留总大小信息空间、文件名大小信息空间、然后输入文件名*/
    sendOut << qint64(0) << qint64(0) << qint64(0) << downloadfile;
    /*总的大小是包含总大小信息、文件名大小信息、文件名和实际文件大小的总和*/
    transferData.totalBytes += transferData.inOrOutBlock.size();
#if defined __DEBUG__
    qDebug()<<"加上文件头信息的总大小"<<transferData.totalBytes<<"文件头信息的大小"
           <<transferData.inOrOutBlock.size()<<"文件名字为"<<transferData.fileName;
#endif
    sendOut.device()->seek(0);
    /*填充实际的存储空间*/
    sendOut << transferData.totalBytes << _DOWNLOAD_FILE_
            << qint64((transferData.inOrOutBlock.size()-sizeof(qint64)*3));
    int sum = tcpSocket->write(transferData.inOrOutBlock);
    transferData.bytesToWrite = transferData.totalBytes - sum;
#if defined __DEBUG__
    qDebug()<<"sum"<<sum<<endl;
    qDebug()<<"文件内容大小"<<transferData.bytesToWrite;
#endif
    transferData.inOrOutBlock.resize(0);
}
