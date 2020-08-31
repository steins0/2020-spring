#include "widget.h"
#include <QApplication>
#include <QDir>
#include <QtSql/QSqlDatabase>
#include <QtSql/Qsql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "Login.h"
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Loginwindow w;
    //连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server
    //qDebug()<<"ODBC driver?"<<db.isValid();
    db.setHostName("127.0.0.1");                        //选择本地主机，127.0.1.1
    db.setPort(3306);
    db.setDatabaseName("filestream");                            //设置数据源名称
    db.setUserName("root");                               //登录用户
    db.setPassword("123456");                           //密码
    //如果数据库连接成功打开窗口否则退出程序
    if(db.open())
    {
        w.show();
    }
    else
    {
        QMessageBox::warning(NULL,QStringLiteral("error"),QStringLiteral("数据库连接失败"));
        return 0;
    }
    return a.exec();
}
