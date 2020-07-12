#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>
#include "widget.h"

class Loginwindow : public QDialog
{
    Q_OBJECT

public:
    Loginwindow(QWidget *parent = 0);
    ~Loginwindow();
private:
    //声明布局
   QGridLayout *MessageLayout;
   QGridLayout *ButtonLayout;
   QGridLayout *MainLayout;
    //声明信息成员
   QLabel *UserName;
   QLabel *Password;
   QLineEdit *UserNameEdit;
   QLineEdit *PasswordEdit;
   QPushButton *LoginButton;
   QPushButton *RegisterButton;
   Widget win;
    //声明槽
public slots:
   void Login_slots();
   void Register_slots();
};

#endif // DIALOG_
