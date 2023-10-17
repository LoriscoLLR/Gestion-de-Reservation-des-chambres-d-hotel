#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->page);
    connOpen();
    affiche_chambre();
    affiche_reservation();
    affiche_hotel();
    affiche_client();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_client_ajouter_clicked()
{
    QString name=ui->client_nom->text().toUpper();
    QString firstname=ui->client_prenom->text();
    QString telClient=ui->client_tel->text();
    QString adressClient=ui->client_adresse->text();
    if(!connOpen())
    {
        qDebug()<<"failed to open the database!";
        return;
    }
    connOpen();
    QSqlQuery qry;
    if(name=="" || firstname=="" || telClient=="" || adressClient=="") {
        QMessageBox:: warning(this,"Avertissement","Remplir le formulaire");

    }
    else if(qry.exec("select * from Client where prenomCli='"+firstname+"' and nomCli='"+name+"' or telCli='"+telClient+"'"))
    {
        int i(0);
        while(qry.next())
        {
            i++;
        }
        if(i == 1)
        {
            QMessageBox::warning(this,"Erreur","Vous ètes déja dans la base de donées");
        }
        else
        {
            qry.prepare("INSERT INTO Client(nomCli,prenomCli,telCli,addresseCli) VALUES ('"+name+"','"+firstname+"','"+telClient+"','"+adressClient+"')");
            if(qry.exec())
            {
                QMessageBox:: critical(this,"Information","saved");
                connClose();
            }
            else
            {
                QMessageBox:: critical(this,"Erreur","Not Saved!");
            }
        }
    }
    QSqlQueryModel * model=new QSqlQueryModel();
    connOpen();
    QSqlQuery* qryAffiche=new QSqlQuery(mydb);
    qryAffiche->prepare("select * from Client");
    qryAffiche->exec();
    model->setQuery(*qryAffiche);
    ui->tableView_2->setModel(model);
    ui->tableView_2->setColumnWidth(0,100);
    ui->tableView_2->setColumnWidth(1,200);
    ui->tableView_2->setColumnWidth(2,300);
    ui->tableView_2->setColumnWidth(3,150);
    ui->tableView_2->setColumnWidth(4,150);
    qDebug() <<(model->rowCount());
}


void MainWindow::on_client_modifier_clicked()
{
    QString name=ui->client_nom->text().toUpper();
    QString firstname=ui->client_prenom->text();
    QString telClient=ui->client_tel->text();
    QString adressClient=ui->client_adresse->text();
    QString eid=ui->id_client->text();
    if(!connOpen())
    {
        qDebug()<<"failed to open the database!";
        return;
    }
    connOpen();
    QSqlQuery qry;
    if(name=="" || firstname=="" || telClient=="" || adressClient=="") {
        QMessageBox:: warning(this,"Avertissement","Remplir le formulaire");

    }
    else if(qry.exec("select * from Client where idCli='"+eid+"'"))
    {
        int i(0);
        while(qry.next())
        {
            i++;
        }
        if( i == 1)
        {
            qry.prepare("UPDATE Client set nomCli='"+name+"' ,prenomCli='"+firstname+"' ,telCli='"+telClient+"' ,addresseCli='"+adressClient+"' WHERE idCli='"+eid+"'");
            if(qry.exec())
            {
                QMessageBox:: critical(this,"Information","Update!");
                connClose();
            }
            else
            {
                QMessageBox:: critical(this,"Erreur","Failed to update");
            }
        }
        else {
            QMessageBox:: critical(this,"Erreur","Failed to update");
        }
    }
    QSqlQueryModel * model=new QSqlQueryModel();
    connOpen();
    QSqlQuery* qryAffiche=new QSqlQuery(mydb);
    qryAffiche->prepare("select * from Client");
    qryAffiche->exec();
    model->setQuery(*qryAffiche);
    ui->tableView_2->setModel(model);
    ui->tableView_2->setColumnWidth(0,100);
    ui->tableView_2->setColumnWidth(1,200);
    ui->tableView_2->setColumnWidth(2,300);
    ui->tableView_2->setColumnWidth(3,150);
    ui->tableView_2->setColumnWidth(4,150);
    qDebug() <<(model->rowCount());
}


void MainWindow::on_client_supprimer_clicked()
{
    QString eid=ui->id_client->text();
    if(!connOpen())
    {
        qDebug()<<"failed to open the database!";
        return;
    }
    connOpen();
        QSqlQuery qry;
        if(qry.exec("select * from Client where idCli='"+eid+"'"))
        {
            int i(0);
            while (qry.next()) {
                i++;
            }
            if( i == 1)
            {
                qry.prepare("DELETE FROM Client WHERE idCli='"+eid+"'");
                if(qry.exec())
                {
                    qry.prepare("DELETE FROM reservation WHERE idCli='"+eid+"'");
                    if(qry.exec()){
                        QMessageBox:: critical(this,"Information","Deleted!");
                        QSqlQueryModel * model=new QSqlQueryModel();
                        connOpen();
                        QSqlQuery* qryAffiche=new QSqlQuery(mydb);
                        qryAffiche->prepare("select * from reservation");
                        qryAffiche->exec();
                        model->setQuery(*qryAffiche);
                        ui->tableView_3->setModel(model);
                        ui->tableView_3->setColumnWidth(0,50);
                        ui->tableView_3->setColumnWidth(1,200);
                        ui->tableView_3->setColumnWidth(2,200);
                        ui->tableView_3->setColumnWidth(3,200);
                        ui->tableView_3->setColumnWidth(4,100);
                        ui->tableView_3->setColumnWidth(5,50);
                        ui->tableView_3->setColumnWidth(6,50);
                        ui->tableView_3->setColumnWidth(7,50);
                        qDebug() <<(model->rowCount());
                        connClose();
                    }
                }
                else
                {
                    QMessageBox:: critical(this,"Erreur","Failed to Deleted!");
                }
            }
            else
            {
                QMessageBox:: critical(this,"Erreur","Failed to Deleted!");
            }
        }
        QSqlQueryModel * model=new QSqlQueryModel();
        connOpen();
        QSqlQuery* qryAffiche=new QSqlQuery(mydb);
        qryAffiche->prepare("select * from Client");
        qryAffiche->exec();
        model->setQuery(*qryAffiche);
        ui->tableView_2->setModel(model);
        ui->tableView_2->setColumnWidth(0,100);
        ui->tableView_2->setColumnWidth(1,200);
        ui->tableView_2->setColumnWidth(2,300);
        ui->tableView_2->setColumnWidth(3,150);
        ui->tableView_2->setColumnWidth(4,150);
        qDebug() <<(model->rowCount());
}


void MainWindow::affiche_client()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    connOpen();
    QSqlQuery* qry=new QSqlQuery(mydb);
    qry->prepare("select * from Client");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView_2->setModel(model);
    ui->tableView_2->setColumnWidth(0,100);
    ui->tableView_2->setColumnWidth(1,200);
    ui->tableView_2->setColumnWidth(2,300);
    ui->tableView_2->setColumnWidth(3,150);
    ui->tableView_2->setColumnWidth(4,150);
    qDebug() <<(model->rowCount());
}


void MainWindow::on_hotel_ajouter_clicked()
{
    QString adress=ui->hotel_adresse->text();
    QString tel=ui->hotel_tel->text();
    QString raison=ui->hotel_raison->text();
    if(!connOpen())
    {
        qDebug()<<"failed to open the database!";
        return;
    }
    connOpen();
    QSqlQuery qry;
    if(adress=="" || tel=="" || raison=="") {
        QMessageBox:: warning(this,"Avertissement","Remplir le formulaire");
    }
    else if(qry.exec("select * from hotel where telHotel='"+tel+"' or raison='"+raison+"'"))
    {
        int i(0);
       while(qry.next())
       {
           i++;
       }
       if(i >= 1)
       {
           QMessageBox::warning(this,"Erreur","cette hotel est deja dans la base de données");
       }
       else
       {
           qry.prepare("INSERT INTO hotel(addresseHotel,telHotel,raison) VALUES ('"+adress+"','"+tel+"','"+raison+"')");
           if(qry.exec())
           {
               QMessageBox:: critical(this,"Information","saved");
               connClose();
           }
           else
           {
               QMessageBox:: critical(this,"Erreur","Not saved!");
           }
       }

    }
    QSqlQueryModel * model=new QSqlQueryModel();
    connOpen();
    QSqlQuery* qryAffiche=new QSqlQuery(mydb);
    qryAffiche->prepare("select * from hotel");
    qryAffiche->exec();
    model->setQuery(*qryAffiche);
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,250);
    ui->tableView->setColumnWidth(2,250);
    ui->tableView->setColumnWidth(3,300);
    qDebug() <<(model->rowCount());
}


void MainWindow::on_hotel_modifier_clicked()
{
    QString adress=ui->hotel_adresse->text();
    QString tel=ui->hotel_tel->text();
    QString raison=ui->hotel_raison->text();
    QString eid=ui->id_hotel->text();
    if(!connOpen())
    {
        qDebug()<<"failed to open the database!";
        return;
    }
    connOpen();
    QSqlQuery qry;
    if(adress=="" || tel=="" || raison=="") {
        QMessageBox:: warning(this,"Avertissement","Remplir le formulaire");
    }
    else if(qry.exec("select * from hotel where numHotel='"+eid+"'"))
    {
        int i(0);
        while (qry.next()) {
            i++;
        }
        if(i == 1)
        {
            qry.prepare("UPDATE hotel set addresseHotel='"+adress+"' , telHotel='"+tel+"' , raison='"+raison+"'  WHERE numHotel='"+eid+"'");
            if(qry.exec())
            {
                QMessageBox:: critical(this,"Information","Update!");
                connClose();
            }
            else
            {
                QMessageBox:: critical(this,"Erreur","Failed to update!");
            }
        }
        else
        {
            QMessageBox:: critical(this,"Erreur","Failed to update!");
        }
    }
    QSqlQueryModel * model=new QSqlQueryModel();
    connOpen();
    QSqlQuery* qryAffiche=new QSqlQuery(mydb);
    qryAffiche->prepare("select * from hotel");
    qryAffiche->exec();
    model->setQuery(*qryAffiche);
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,250);
    ui->tableView->setColumnWidth(2,250);
    ui->tableView->setColumnWidth(3,300);
    qDebug() <<(model->rowCount());
}


void MainWindow::on_hotel_supprimer_clicked()
{
    QString eid=ui->id_hotel->text();
    if(!connOpen())
    {
        qDebug()<<"failed to open the database!";
        return;
    }
    connOpen();
    QSqlQuery qry;
    if(qry.exec("select * from hotel where numHotel='"+eid+"'"))
    {
        int i(0);
        while (qry.next()) {
            i++;
        }
        if(i ==1)
        {
            qry.prepare("DELETE FROM hotel WHERE numHotel='"+eid+"'");
            if(qry.exec())
            {
                qry.prepare("DELETE FROM chambre WHERE numHotel='"+eid+"'");
                if(qry.exec()){
                    qry.prepare("DELETE FROM reservation WHERE numHotel='"+eid+"'");
                    if(qry.exec()){
                        QMessageBox:: critical(this,"Information","Deleted!");
                        QSqlQueryModel * model=new QSqlQueryModel();
                        connOpen();
                        QSqlQuery* qryAffiche=new QSqlQuery(mydb);
                        qryAffiche->prepare("select * from chambre");
                        qryAffiche->exec();
                        model->setQuery(*qryAffiche);
                        ui->tableView_4->setModel(model);
                        ui->tableView_4->setColumnWidth(0,100);
                        ui->tableView_4->setColumnWidth(1,400);
                        ui->tableView_4->setColumnWidth(2,400);
                        QSqlQueryModel * model1=new QSqlQueryModel();
                        connOpen();
                        QSqlQuery* qryAffiche1=new QSqlQuery(mydb);
                        qryAffiche1->prepare("select * from reservation");
                        qryAffiche1->exec();
                        model1->setQuery(*qryAffiche);
                        ui->tableView_3->setModel(model1);
                        ui->tableView_3->setColumnWidth(0,50);
                        ui->tableView_3->setColumnWidth(1,200);
                        ui->tableView_3->setColumnWidth(2,200);
                        ui->tableView_3->setColumnWidth(3,200);
                        ui->tableView_3->setColumnWidth(4,100);
                        ui->tableView_3->setColumnWidth(5,50);
                        ui->tableView_3->setColumnWidth(6,50);
                        ui->tableView_3->setColumnWidth(7,50);
                        qDebug() <<(model->rowCount());
                        connClose();
                    }
                }
            }
            else
            {
                QMessageBox:: critical(this,"Erreur","Failed to delete!");
            }
        }
        else
        {
            QMessageBox:: critical(this,"Erreur","Failed to delete!");
        }
    }
    QSqlQueryModel * model=new QSqlQueryModel();
    connOpen();
    QSqlQuery* qryAffiche=new QSqlQuery(mydb);
    qryAffiche->prepare("select * from hotel");
    qryAffiche->exec();
    model->setQuery(*qryAffiche);
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,250);
    ui->tableView->setColumnWidth(2,250);
    ui->tableView->setColumnWidth(3,300);
    qDebug() <<(model->rowCount());
}


void MainWindow::affiche_hotel()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    connOpen();
    QSqlQuery* qry=new QSqlQuery(mydb);
    qry->prepare("select * from hotel");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,250);
    ui->tableView->setColumnWidth(2,250);
    ui->tableView->setColumnWidth(3,300);
    qDebug() <<(model->rowCount());
}


void MainWindow::on_reservation_ajouter_clicked()
{
    QDate res = ui->date_res->date();
    QDate deb = ui->date_deb->date();
    QDate fin = ui->date_fin->date();
    QString pers = ui->nbPersonne->text();
    QString numCli = ui->numClient->text();
    QString numHot = ui->numHotel->text();
    QString numCham = ui->numChambre->text();
    if(!connOpen())
    {
        qDebug()<<"failed to open the database!";
        return;
    }
    connOpen();
    QSqlQuery qry;
    if(numCli == "0" || numCham == "0" || numHot== "0" || pers == "0"){
        QMessageBox:: warning(this,"Avertissement","Remplir le formulaire");
    }
    else if( res > deb || deb >fin){
        QMessageBox:: warning(this,"Avertissement","Date non valide");
    }
    else if(qry.exec("select * from Client where idCli='"+numCli+"'"))
    {
        int i(0);
        while(qry.next())
        {
            i++;
        }
        if(i==1)
        {
            if(qry.exec("select * from hotel where numHotel='"+numHot+"'"))
            {
                i=0;
                while (qry.next())
                {
                    i++;
                }
                if(i==1)
                {

                    if(qry.exec("select * from chambre where numChambre='"+numCham+"' and numHotel='"+numHot+"'"))
                    {
                        i=0;
                        while (qry.next())
                        {
                            i++;
                        }
                        if(i == 1)
                        {
                            qry.prepare("INSERT INTO reservation(dateRes,dateDebut,dateFin,nbPerso,idCli,numHotel,numChambre) VALUES ('"+res.toString("dd-MM-yyyy")+"','"+deb.toString("dd-MM-yyyy")+"','"+fin.toString("dd-MM-yyyy")+"','"+pers+"','"+numCli+"','"+numHot+"','"+numCham+"')");
                            if(qry.exec())
                            {
                                QMessageBox:: critical(this,"Information","saved");
                                connClose();
                            }
                            else
                            {
                                QMessageBox:: critical(this,"Erreur","Not saved!");
                            }
                        }
                        else
                        {
                            QMessageBox::warning(this,"Erreur","Cet Chambre n'existe pas");
                        }
                    }
                }
                else
                {
                    QMessageBox::warning(this,"Erreur","Cet hotel n'existe pas");
                }
            }
        }
        else
        {
            QMessageBox::warning(this,"Erreur","Ce client n'existe pas");
        }
    }
    QSqlQueryModel * model=new QSqlQueryModel();
    connOpen();
    QSqlQuery* qryAffiche=new QSqlQuery(mydb);
    qryAffiche->prepare("select * from reservation");
    qryAffiche->exec();
    model->setQuery(*qryAffiche);
    ui->tableView_3->setModel(model);
    ui->tableView_3->setColumnWidth(0,50);
    ui->tableView_3->setColumnWidth(1,200);
    ui->tableView_3->setColumnWidth(2,200);
    ui->tableView_3->setColumnWidth(3,200);
    ui->tableView_3->setColumnWidth(4,100);
    ui->tableView_3->setColumnWidth(5,50);
    ui->tableView_3->setColumnWidth(6,50);
    ui->tableView_3->setColumnWidth(7,50);
    qDebug() <<(model->rowCount());
}



void MainWindow::on_reservation_modifier_clicked()
{
    QDate res = ui->date_res->date();
    QDate deb = ui->date_deb->date();
    QDate fin = ui->date_fin->date();
    QString pers = ui->nbPersonne->text();
    QString numCli = ui->numClient->text();
    QString numHot = ui->numHotel->text();
    QString numCham = ui->numChambre->text();
    QString eid=ui->id_reservation->text();
    if(!connOpen())
    {
        qDebug()<<"failed to open the database!";
        return;
    }
    connOpen();
    QSqlQuery qry;
    if(numCli == "" || numCham == "" || numHot== ""){
        QMessageBox:: warning(this,"Avertissement","Remplir le formulaire");
    }
    else if( res > deb || deb >fin){
        QMessageBox:: warning(this,"Avertissement","Date non valide");
    }
    else if (qry.exec("select * from reservation where numRes='"+eid+"'"))
    {
        int i(0);
        while (qry.next()) {
            i++;
        }
        if(i == 1)
        {
            qry.prepare("UPDATE reservation set dateRes='"+res.toString()+"',dateDebut='"+deb.toString()+"',dateFin='"+fin.toString()+"',nbPerso='"+pers+"',idCli='"+numCli+"',numHotel='"+numHot+"',numChambre='"+numCham+"' WHERE numRes='"+eid+"'");
            if(qry.exec())
            {
                QMessageBox:: critical(this,"Information","Update!");
                connClose();
            }
            else
            {
                QMessageBox:: critical(this,"Erreur","Failed to update!");
            }
        }
        else
        {
            QMessageBox:: critical(this,"Erreur","Failed to update!");
        }
    }
    QSqlQueryModel * model=new QSqlQueryModel();
    connOpen();
    QSqlQuery* qryAffiche=new QSqlQuery(mydb);
    qryAffiche->prepare("select * from reservation");
    qryAffiche->exec();
    model->setQuery(*qryAffiche);
    ui->tableView_3->setModel(model);
    ui->tableView_3->setColumnWidth(0,50);
    ui->tableView_3->setColumnWidth(1,200);
    ui->tableView_3->setColumnWidth(2,200);
    ui->tableView_3->setColumnWidth(3,200);
    ui->tableView_3->setColumnWidth(4,100);
    ui->tableView_3->setColumnWidth(5,50);
    ui->tableView_3->setColumnWidth(6,50);
    ui->tableView_3->setColumnWidth(7,50);
    qDebug() <<(model->rowCount());
}


void MainWindow::on_reservation_supprimer_clicked()
{
    QString eid=ui->id_reservation->text();
    if(!connOpen())
    {
        qDebug()<<"failed to open the database!";
        return;
    }
    connOpen();
    QSqlQuery qry;
    if (qry.exec("select * from reservation where numRes='"+eid+"'"))
    {
        int i(0);
        while (qry.next()) {
            i++;
        }
        if(i == 1)
        {
            qry.prepare("DELETE FROM reservation WHERE numRes='"+eid+"'");
            if(qry.exec())
            {
                QMessageBox:: critical(this,"Information","Deleted!");
                connClose();
            }
            else
            {
                QMessageBox:: critical(this,"Erreur","Failed to delete!");
            }
        }
        else
        {
            QMessageBox:: critical(this,"Erreur","Failed to delete!");
        }
     }
    QSqlQueryModel * model=new QSqlQueryModel();
    connOpen();
    QSqlQuery* qryAffiche=new QSqlQuery(mydb);
    qryAffiche->prepare("select * from reservation");
    qryAffiche->exec();
    model->setQuery(*qryAffiche);
    ui->tableView_3->setModel(model);
    ui->tableView_3->setColumnWidth(0,50);
    ui->tableView_3->setColumnWidth(1,200);
    ui->tableView_3->setColumnWidth(2,200);
    ui->tableView_3->setColumnWidth(3,200);
    ui->tableView_3->setColumnWidth(4,100);
    ui->tableView_3->setColumnWidth(5,50);
    ui->tableView_3->setColumnWidth(6,50);
    ui->tableView_3->setColumnWidth(7,50);
    qDebug() <<(model->rowCount());

}


void MainWindow::affiche_reservation()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    connOpen();
    QSqlQuery* qry=new QSqlQuery(mydb);
    qry->prepare("select * from reservation");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView_3->setModel(model);
    ui->tableView_3->setColumnWidth(0,50);
    ui->tableView_3->setColumnWidth(1,200);
    ui->tableView_3->setColumnWidth(2,200);
    ui->tableView_3->setColumnWidth(3,200);
    ui->tableView_3->setColumnWidth(4,100);
    ui->tableView_3->setColumnWidth(5,50);
    ui->tableView_3->setColumnWidth(6,50);
    ui->tableView_3->setColumnWidth(7,50);
    qDebug() <<(model->rowCount());
}


void MainWindow::on_pushButton_clicked()
{
    QString numHot = ui->num_hotel->text();
    QString tarif =ui->tarif_chambre->text();
    QString numChambre=ui->num_chambre->text();
    if(!connOpen())
    {
        qDebug()<<"failed to open the database!";
        return;
    }
    connOpen();
    QSqlQuery qry;
    if(numHot=="0" || tarif == "" || numChambre=="0")
    {
         QMessageBox:: warning(this,"Avertissement","Remplir le formulaire");
    }
    else if(qry.exec("select * from chambre where numHotel='"+numHot+"' and numChambre='"+numChambre+"'")) {
        int i(0);
        while(qry.next()) {
            i++;
        }
        if(i==1) {
            QMessageBox::warning(this,"Avertissement","Le chambre existe déjà dans cette hotel");
        }
        else {
            if(qry.exec("select * from hotel where numHotel='"+numHot+"'"))
            {
                int i(0);
                while (qry.next())
                {
                    i++;
                }
                if(i==1)
                {
                    qry.prepare("INSERT INTO chambre(numHotel,tarif,numChambre) VALUES ('"+numHot+"','"+tarif+"', '"+numChambre+"')");
                    if(qry.exec())
                    {
                        QMessageBox:: critical(this,"Information","saved");
                        connClose();
                    }
                    else
                    {
                        QMessageBox:: critical(this,"Erreur","Not saved!");
                    }
                }
                else
                {
                    QMessageBox::warning(this,"Erreur","Cet hotel n'existe pas");
                }
            }

        }
    }
    QSqlQueryModel * model=new QSqlQueryModel();

    connOpen();
    QSqlQuery* qryAffiche=new QSqlQuery(mydb);
    qryAffiche->prepare("select * from chambre");
    qryAffiche->exec();
    model->setQuery(*qryAffiche);
    ui->tableView_4->setModel(model);
    ui->tableView_4->setColumnWidth(0,100);
    ui->tableView_4->setColumnWidth(1,400);
    ui->tableView_4->setColumnWidth(2,400);
    qDebug() <<(model->rowCount());
}


void MainWindow::on_pushButton_2_clicked()
{
    QString numHot = ui->num_hotel->text();
    QString tarif =ui->tarif_chambre->text();
    QString idChambre = ui->id_chambre->text();

    if(!connOpen())
    {
        qDebug()<<"failed to open the database!";
        return;
    }
    connOpen();
    QSqlQuery qry;
    if(numHot=="0" || tarif == "")
    {
         QMessageBox:: warning(this,"Avertissement","Remplir le formulaire");
    }
   else if(qry.exec("select * from chambre where numHotel='"+numHot+"' and numChambre='"+idChambre+"'"))
    {
        int i(0);
        while (qry.next())
        {
            i++;
        }

        if(i==1)
        {
            qry.prepare("UPDATE chambre set tarif='"+tarif+"' where numChambre='"+idChambre+"' and numHotel='"+numHot+"'");
            if(qry.exec())
            {
                QMessageBox:: critical(this,"Information","Update!");
                connClose();
            }
            else
            {
                QMessageBox:: critical(this,"Erreur","Failed to update!");
            }
        }
        else
        {
            QMessageBox:: critical(this,"Erreur","Failed to update!");
        }

     }
    QSqlQueryModel * model=new QSqlQueryModel();
    connOpen();
    QSqlQuery* qryAffiche=new QSqlQuery(mydb);
    qryAffiche->prepare("select * from chambre");
    qryAffiche->exec();
    model->setQuery(*qryAffiche);
    ui->tableView_4->setModel(model);
    ui->tableView_4->setColumnWidth(0,100);
    ui->tableView_4->setColumnWidth(1,400);
    ui->tableView_4->setColumnWidth(2,400);
    qDebug() <<(model->rowCount());
}


void MainWindow::affiche_chambre()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    connOpen();
    QSqlQuery* qry=new QSqlQuery(mydb);
    qry->prepare("select * from chambre");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView_4->setModel(model);
    ui->tableView_4->setColumnWidth(0,100);
    ui->tableView_4->setColumnWidth(1,400);
    ui->tableView_4->setColumnWidth(2,400);
    qDebug() <<(model->rowCount());
}



void MainWindow::on_recherche_clicked()
{
    QString numHot = ui->numHot->text();
    QString dateE = ui->data_debut->date().toString("dd-MM-yyyy");
    QString dateS = ui->date_fin_2->date().toString("dd-MM-yyyy");
    if(!connOpen())
    {
        qDebug()<<"failed to open the database!";
        return;
    }
    connOpen();
    QSqlQuery qry;
    if(numHot == "0")
    {
        QMessageBox:: warning(this,"Avertissement","Remplir le formulaire");
    }
    else if(dateE >dateS){
        QMessageBox:: warning(this,"Avertissement","Date non valide");
    }
    else if(qry.exec("select * from hotel where numHotel='"+numHot+"'"))
    {
        int i(0);
        while (qry.next()) {
            i++;
        }
        if(i==1)
        {
            if(qry.exec("select numChambre,tarif from chambre where numHotel='"+numHot+"' and numChambre not in (select numChambre from reservation where dateDebut<='"+dateE+"' and dateFin>='"+dateE+"' or dateDebut<='"+dateS+"' and dateFin>='"+dateS+"' or dateDebut>='"+dateE+"' and dateFin<='"+dateS+"')"))
            {
                 i=0;
                 while (qry.next()) {
                     i++;
                 }
                 int row(0);
                 modele = new QStandardItemModel(i,2);
                 qry.exec("select numChambre,tarif from chambre where numHotel='"+numHot+"' and numChambre not in (select numChambre from reservation where dateDebut<='"+dateE+"' and dateFin>='"+dateE+"' or dateDebut<='"+dateS+"' and dateFin>='"+dateS+"' or dateDebut>='"+dateE+"' and dateFin<='"+dateS+"')");
                 while (qry.next()) {
                     for(int i=0;i<2;i++)
                     {
                         QStandardItem *item=new QStandardItem(qry.value(i).toString());
                         modele->setItem(row,i,item);
                     }
                     row++;
                 }
                 modele->setHeaderData(0,Qt::Horizontal,"Numero Chambre");
                 modele->setHeaderData(1,Qt::Horizontal,"Tarif Chambre");
                 ui->tableView_5->setModel(modele);
                 ui->tableView_5->setColumnWidth(0,450);
                 ui->tableView_5->setColumnWidth(1,450);
            }
        }
        else
        {
            QMessageBox::warning(this,"Erreur","Cet hotel n'existe pas");
        }
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    QString eid =ui->idClient->text();
    int n(0);
    double total_facture(0);
    double *tarif;
    double *facture;
    int *jour;
    QString *date1;
    QString *date2;
    QString *chambre;
    QString total;
    if(!connOpen())
    {
        qDebug()<<"failed to open the database!";
        return;
    }
    connOpen();
    QSqlQuery qry;
    if(qry.exec("select * from Client where idCli = '"+eid+"'"))
    {
        int j(0);
        while (qry.next()) {
            j++;
        }
        if(j == 1)
        {
            if(qry.exec("select * from reservation where idCli = '"+eid+"'"))
            {
                while (qry.next()) {
                    qry.exec("select dateDebut,dateFin from reservation where idCli = '"+eid+"'");
                    while (qry.next()) {
                        n++;

                    }
                    date1 = new QString[n];
                    date2 = new QString[n];
                    tarif = new double[n];
                    facture = new double[n];
                    jour = new int[n];
                    chambre = new QString[n];
                    int i(0);
                    qry.exec("select dateFin,dateDebut from reservation where idCli = '"+eid+"'");
                    while (qry.next()) {
                             date2[i] = qry.value(0).toString();
                             date1[i] = qry.value(1).toString();
                            i++;
                    }
                    for(int i=0; i<n ; i++) {
                        QDate d1,d2;
                        d1=QDate::fromString(date1[i],"dd-MM-yyyy");
                        d2=QDate::fromString(date2[i],"dd-MM-yyyy");
                        jour[i]=d1.daysTo(d2);
                        qDebug()<< d1;
                    }

                    i=0;
                    qry.exec("select numChambre from reservation where idCli = '"+eid+"'");
                    while (qry.next()) {
                            chambre[i] = qry.value(0).toString();
                            i++;
                    }
                    QString ch;
                    for(int i=0 ;i < n ; i++)
                    {
                        ch=chambre[i];
                        qry.exec("select tarif from chambre where numChambre='"+ch+"'");
                        while(qry.next())
                        {
                            tarif[i] = qry.value(0).toDouble();
                        }
                    }

                    for (int i=0;i < n ; i++) {
                        facture[i]=tarif[i]*jour[i];
                    }
                    for (int i=0;i < n ; i++) {
                        total_facture=total_facture+facture[i];
                    }
                    total=QString::number(total_facture);
                }
                modele = new QStandardItemModel(1,2,nullptr);
                modele->setData(modele->index(0,0),eid);
                modele->setData(modele->index(0,1),total);
                modele->setHeaderData(0,Qt::Horizontal,"Client");
                modele->setHeaderData(1,Qt::Horizontal,"Totale à payé");
                ui->tableView_6->setModel(modele);
                ui->tableView_6->setColumnWidth(0,450);
                ui->tableView_6->setColumnWidth(1,450);
            }
        }
        else
        {
            QMessageBox::warning(this,"Erreur","Ce client n'existe pas");
        }
    }
}



void MainWindow::on_pushButton_6_clicked()
{
    double recettes = 0;
    double *tarif;
    double *montantPayer;
    int compteur(0),i(0);
    int *jour;
    QString *date1;
    QString *date2;
    QString *chambre;
    QString hot=ui->idHotel->text();
    if(!connOpen())
    {
        qDebug()<<"failed to open the database!";
        return;
    }
    connOpen();
    QSqlQuery qry;
    if(qry.exec("select * from hotel where numHotel = '"+hot+"'"))
    {
        int j(0);
        while (qry.next()) {
            j++;
        }
        if(j == 1)
        {
            if(qry.exec("select * from reservation where numHotel='"+hot+"'"))
            {
                while (qry.next()) {
                    compteur++;
                }
                date1 = new QString[compteur];
                date2 = new QString[compteur];
                chambre = new QString[compteur];
                tarif= new double[compteur];
                jour = new int[compteur];
                montantPayer= new double[compteur];
                int j(0);
                qry.exec("select dateFin,dateDebut from reservation where numHotel = '"+hot+"'");
                while (qry.next()) {
                         date2[j] = qry.value(0).toString();
                         date1[j] = qry.value(1).toString();
                        j++;
                }
                for(int i=0; i<compteur ; i++) {
                    QDate d1,d2;
                    d1=QDate::fromString(date1[i],"dd-MM-yyyy");
                    d2=QDate::fromString(date2[i],"dd-MM-yyyy");
                    jour[i]=d1.daysTo(d2);
                }
                qry.exec("select numChambre from reservation where numHotel = '"+hot+"'");
                while (qry.next()) {
                        chambre[i] = qry.value(0).toString();
                        i++;
                }
                QString ch;
                for(int i=0 ;i < compteur ; i++)
                {
                    ch=chambre[i];
                    qry.exec("select tarif from chambre where numChambre='"+ch+"'");
                    while(qry.next())
                    {
                        tarif[i] = qry.value(0).toDouble();
                    }
                }
                for (int i=0;i < compteur; i++) {
                    montantPayer[i]=tarif[i]*jour[i];
                }
                for (int i=0;i < compteur ; i++) {
                    recettes=recettes+montantPayer[i];
                }
                modele = new QStandardItemModel(1,2,nullptr);
                modele->setData(modele->index(0,0),hot);
                modele->setData(modele->index(0,1),recettes);
                modele->setHeaderData(0,Qt::Horizontal,"Hotel");
                modele->setHeaderData(1,Qt::Horizontal,"Recettes");
                ui->tableView_6->setModel(modele);
                ui->tableView_6->setColumnWidth(0,450);
                ui->tableView_6->setColumnWidth(1,450);
            }
        }
        else
        {
            QMessageBox::warning(this,"Erreur","Cet hotel n'existe pas");
        }
    }
}


void MainWindow::on_actionHotel_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void MainWindow::on_actionChambre_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->page_4);
}


void MainWindow::on_actionClient_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void MainWindow::on_actionReservation_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void MainWindow::on_actionRecherche_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->page_5);
}


void MainWindow::on_actionFacture_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->page_6);
}


void MainWindow::on_actionQuitter_triggered()
{
    hide();
}


void MainWindow::on_chambre_supprimer_clicked()
{
    QString eid=ui->id_chambre->text();
    QString numHot=ui->num_hotel->text();
    if(!connOpen())
    {
        qDebug()<<"failed to open the database!";
        return;
    }
    connOpen();
    QSqlQuery qry;
    if(qry.exec("select * from chambre where numHotel='"+numHot+"' and numChambre='"+eid+"'"))
     {
         int i(0);
         while (qry.next())
         {
             i++;
         }

         if(i==1)
         {
             qry.prepare("DELETE FROM chambre WHERE numChambre='"+eid+"' and numHotel='"+numHot+"'");
             if(qry.exec())
             {
                 qry.prepare("DELETE FROM reservation WHERE numChambre='"+eid+"' and numHotel='"+numHot+"'");
                 if(qry.exec()){
                     QMessageBox:: critical(this,"Information","deleted!");
                     QSqlQueryModel * model=new QSqlQueryModel();
                     connOpen();
                     QSqlQuery* qryAffiche=new QSqlQuery(mydb);
                     qryAffiche->prepare("select * from reservation");
                     qryAffiche->exec();
                     model->setQuery(*qryAffiche);
                     ui->tableView_3->setModel(model);
                     ui->tableView_3->setColumnWidth(0,50);
                     ui->tableView_3->setColumnWidth(1,200);
                     ui->tableView_3->setColumnWidth(2,200);
                     ui->tableView_3->setColumnWidth(3,200);
                     ui->tableView_3->setColumnWidth(4,100);
                     ui->tableView_3->setColumnWidth(5,50);
                     ui->tableView_3->setColumnWidth(6,50);
                     ui->tableView_3->setColumnWidth(7,50);
                     qDebug() <<(model->rowCount());
                     connClose();
                 }
             }
             else
             {
                 QMessageBox:: critical(this,"Erreur","Failed to delete!");
             }
         }
         else
         {
             QMessageBox:: critical(this,"Erreur","Failed to delete!");
         }

      }
    QSqlQueryModel * model=new QSqlQueryModel();
    connOpen();
    QSqlQuery* qryAffiche=new QSqlQuery(mydb);
    qryAffiche->prepare("select * from chambre");
    qryAffiche->exec();
    model->setQuery(*qryAffiche);
    ui->tableView_4->setModel(model);
    ui->tableView_4->setColumnWidth(0,100);
    ui->tableView_4->setColumnWidth(1,400);
    ui->tableView_4->setColumnWidth(2,400);
    qDebug() <<(model->rowCount());
}

