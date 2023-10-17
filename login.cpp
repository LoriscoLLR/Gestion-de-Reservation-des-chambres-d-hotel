#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    QString mot("groupe1");
    QString pwd=ui->pwd->text();
    if(mot==pwd)
    {
        page=new MainWindow(this);
        page->show();
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Mot de Passe incorrecte!");
    }
}

