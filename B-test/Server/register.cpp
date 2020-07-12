#include "register.h"
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
registerwindow::registerwindow(QWidget *parent)
    :QDialog(parent)
{
    //登陆界面定义
    setWindowTitle(tr("注册界面"));
    //窗口只能最小化
    this->setWindowFlags (this->windowFlags () | Qt::WindowMinimizeButtonHint|Qt::MSWindowsFixedSizeDialogHint);
    //成员初始化
    UserName = new QLabel(tr("用户名："));
    Password = new QLabel(tr("密码："));
    RePassword = new QLabel(tr("重复密码："));
    UserNameEdit = new QLineEdit();
    PasswordEdit = new QLineEdit();
    RePasswordEdit = new QLineEdit();
    //Email = new QLabel("邮件：");
    //EmailEdit = new QLineEdit();
    confirm = new QPushButton(tr("确认"));
    resetting = new QPushButton(tr("重置"));
    //实现上方信息网格布局
    MessageLayout = new QGridLayout();
    MessageLayout->addWidget(UserName,0,0);
    MessageLayout->addWidget(UserNameEdit,0,1);
    MessageLayout->addWidget(Password,1,0);
    MessageLayout->addWidget(PasswordEdit,1,1);
    MessageLayout->addWidget(RePassword,2,0);
    MessageLayout->addWidget(RePasswordEdit,2,1);
    //MessageLayout->addWidget(Email,3,0);
    //MessageLayout->addWidget(EmailEdit,3,1);
     //实现下方按钮网格布局
    ButtonLayout = new QGridLayout();
    ButtonLayout->addWidget(confirm,0,0);
    ButtonLayout->addWidget(resetting,0,1);
    ButtonLayout->setSpacing(15);
    //实现主网格
    MainLayout = new QGridLayout(this);
    MainLayout->addLayout(MessageLayout,0,0);
    MainLayout->addLayout(ButtonLayout,1,0);
    MainLayout->setMargin(30);
    MainLayout->setSpacing(20);

    UserNameEdit->setMaxLength(10);
    PasswordEdit->setMaxLength(16);
    UserNameEdit->setPlaceholderText(QString::fromUtf8("设置用户名不超过10位"));
    PasswordEdit->setPlaceholderText(QString::fromUtf8("设置密码不超过16位"));
    RePasswordEdit->setPlaceholderText(QString::fromUtf8("再次输入密码"));
    PasswordEdit->setEchoMode(QLineEdit::Password);
    RePasswordEdit->setEchoMode(QLineEdit::Password);
    //连接信号和槽
    connect(confirm,SIGNAL(clicked()),this,SLOT(confirm_slots()));
    connect(resetting,SIGNAL(clicked()),UserNameEdit,SLOT(clear()));
    connect(resetting,SIGNAL(clicked()),PasswordEdit,SLOT(clear()));
    connect(resetting,SIGNAL(clicked()),RePasswordEdit,SLOT(clear()));
}
//槽函数实现
void registerwindow::confirm_slots()
{
    QString UName = UserNameEdit->text();
    //QString email = EmailEdit->text();
    QString Pword;
    if(UserNameEdit->text().isEmpty()||PasswordEdit->text().isEmpty()){
        QMessageBox::warning(NULL,"Error","用户名或密码为空！！");
    }
    else{
        if(PasswordEdit->text()==RePasswordEdit->text())
        {
            Pword = PasswordEdit->text();
            QString i=QString("insert into 用户信息 values ('%1','%2'); ").arg(UName).arg(Pword);
            QString S =QString("select * from 用户信息 where 用户名='%1' ").arg(UName);
            QSqlQuery query;
            if(query.exec(i))
                QMessageBox::information(NULL, "注册成功", "注册成功！！！", QMessageBox::Yes);
            else if(query.exec(S)&&query.first())
                QMessageBox::warning(NULL,"Error","用户名重复，请重试！！！");
            else
                QMessageBox::warning(NULL,"Error","注册失败，请重试！！！");
            this->close();
        }
        else
            QMessageBox::warning(NULL,"Error","密码不一致，请重试！！！");
    }
}

registerwindow::~registerwindow()
{

}
