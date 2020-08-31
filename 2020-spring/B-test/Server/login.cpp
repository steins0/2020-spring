#include "login.h"
#include "register.h"
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
Loginwindow::Loginwindow(QWidget *parent)
    : QDialog(parent)
{
    //登陆界面定义
    setWindowTitle(tr("登陆界面"));
    //窗口只能最小化
    this->setWindowFlags (this->windowFlags () | Qt::WindowMinimizeButtonHint|Qt::MSWindowsFixedSizeDialogHint);
    //成员初始化
    UserName = new QLabel(tr("用户名："));
    Password = new QLabel(tr("密码："));
    UserNameEdit = new QLineEdit();
    PasswordEdit = new QLineEdit();
    LoginButton = new QPushButton(tr("登陆"));
    RegisterButton = new QPushButton(tr("注册"));
    //实现上方信息网格布局
    MessageLayout = new QGridLayout();
    MessageLayout->addWidget(UserName,0,0);
    MessageLayout->addWidget(UserNameEdit,0,1);
    MessageLayout->addWidget(Password,1,0);
    MessageLayout->addWidget(PasswordEdit,1,1);
    //实现下方按钮网格布局
    ButtonLayout = new QGridLayout();
    ButtonLayout->addWidget(LoginButton,0,0);
    ButtonLayout->addWidget(RegisterButton,0,1);
    ButtonLayout->setSpacing(15);
    //实现主网格
    MainLayout = new QGridLayout(this);
    MainLayout->addLayout(MessageLayout,0,0);
    MainLayout->addLayout(ButtonLayout,1,0);
    MainLayout->setMargin(50);
    MainLayout->setSpacing(20);

    UserNameEdit->setPlaceholderText(QString::fromUtf8("请输入用户名"));
    PasswordEdit->setPlaceholderText(QString::fromUtf8("请输入密码"));
    PasswordEdit->setEchoMode(QLineEdit::Password);
    //连接信号和槽
    connect(LoginButton,SIGNAL(clicked()),this,SLOT(Login_slots()));
    connect(RegisterButton,SIGNAL(clicked()),this,SLOT(Register_slots()));

}
//槽函数实现
void Loginwindow::Login_slots()
{
        QString  UName = UserNameEdit->text();
        QString  Pword = PasswordEdit->text();
        if(UserNameEdit->text().isEmpty()||PasswordEdit->text().isEmpty()){
            QMessageBox::warning(NULL,QStringLiteral("Error"),QStringLiteral("用户名或密码为空！！"));
        }
        else{
            QString s=QString(QStringLiteral("select * from 用户信息 where 用户名='%1'and 密码='%2' ")).arg(UName).arg(Pword);
            //查询数据库如果账号和密码匹配返回真否则返回假
            QSqlQuery query;
            query.exec(s);
            if(query.first()){
                QMessageBox::information(NULL, QStringLiteral("登陆成功"), QStringLiteral("登陆成功！！！"), QMessageBox::Yes);
                this->close();
                win.show();
                //win.exec();
            }
            else
                QMessageBox::warning(NULL,QStringLiteral("Error"),QStringLiteral("登录失败，请重试！！！"));

        }

}
void Loginwindow::Register_slots()
{
    this->hide();
    registerwindow re;
    re.show();
    re.exec();
    this->show();
    UserNameEdit->clear();
    PasswordEdit->clear();
}
Loginwindow::~Loginwindow()
{

}
