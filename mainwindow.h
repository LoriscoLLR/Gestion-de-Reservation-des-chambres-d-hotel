#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "QStandardItemModel"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QDebug"
#include <QMessageBox>
#include "QSqlRecord"
#include "QTableView"
#include <QVector>
#include <QDate>
#include "QCoreApplication"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;
    void connClose()
    {
        mydb.close();
        mydb.removeDatabase("gestion.db");
    }
    bool connOpen()
    {
        mydb=QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/Users/Rantosoa/Desktop/Project/gestion.db");

        if(mydb.open())
        {
            qDebug()<<("Connected....");
            return true;
        }

        else
        {
            qDebug()<<("failed to open the database!");
            return false;
        }
    }

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_client_ajouter_clicked();

    void on_client_modifier_clicked();

    void on_client_supprimer_clicked();

    void affiche_client();

    void on_hotel_ajouter_clicked();

    void on_hotel_modifier_clicked();

    void on_hotel_supprimer_clicked();

    void affiche_hotel();

    void on_reservation_ajouter_clicked();

    void on_reservation_modifier_clicked();

    void on_reservation_supprimer_clicked();

    void affiche_reservation();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void affiche_chambre();

    void on_recherche_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_actionHotel_triggered();

    void on_actionChambre_triggered();

    void on_actionClient_triggered();

    void on_actionReservation_triggered();

    void on_actionRecherche_triggered();

    void on_actionFacture_triggered();

    void on_actionQuitter_triggered();

    void on_chambre_supprimer_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *modele;
};
#endif // MAINWINDOW_H
