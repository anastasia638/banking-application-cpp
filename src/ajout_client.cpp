#include "ajout_client.h"
#include "ui_ajout_client.h"
#include "gestionnairebanque.h"
#include <QMessageBox>
#include "afficher_client.h"
#include <QDebug>
#include <cstdlib>
#include <QTime>

Ajout_client::Ajout_client(GestionnaireBanque* gestionnaire, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Ajout_client)
{
    ui->setupUi(this);
    gestionnaireBanque = gestionnaire;
    connect(ui->creer, &QPushButton::clicked, this, &Ajout_client::ajouterNouveauClient);
    connect(ui->creerNbr, &QPushButton::clicked, this, &Ajout_client::creerCompteAleatoires);
}

Ajout_client::~Ajout_client()
{
    delete ui;
}


void Ajout_client::ajouterNouveauClient() {

    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString adresse = ui->adresse->text();
    QDate date = QDate::fromString(ui->naissance->text(), "yyyy-MM-dd");
    // ... Autres attributs du client

    // Vérifiez si la date est valide
    if (!date.isValid()) {
        QMessageBox::critical(this, "Erreur", "Format de date invalide. Utilisez le format yyyy-MM-dd.");
        return;
    }


    qint64 ID = gestionnaireBanque->obtenirProchainIdClient();
    gestionnaireBanque->creerClient(ID, nom, prenom, date, adresse);

    QMessageBox::information(this, "Succès", "Le client a été ajouté avec succès.");
    qDebug()<<"ajout reussi";

    this->close();
}


void Ajout_client::creerCompteAleatoires() {
    // Récupérer le nombre de clients à créer à partir du texte du QLabel
    int nombreClients = ui->nombre_client->text().toInt();

    // Vérifier si le nombre de clients est valide
    if (nombreClients <= 0) {
        QMessageBox::critical(this, "Erreur", "Nombre de clients invalide.");
        return;
    }

     srand(static_cast<unsigned int>(time(nullptr)));
    // Boucler pour créer le nombre spécifié de clients
    for (int i = 0; i < nombreClients; ++i) {
        // Générer des informations aléatoires pour le nouveau client
        QString nom = "Client" + QString::number(i);
        QString prenom = "Prenom" + QString::number(i);
        QString adresse = "Adresse" + QString::number(i);
        // Générez une date de naissance aléatoire dans les 18 dernières années
        QDate dateNaissance = QDate::currentDate().addYears(-(rand() % 18));
        // Créez un nouveau client avec les informations aléatoires
        qint64 ID = gestionnaireBanque->obtenirProchainIdClient();
        gestionnaireBanque->creerClient(ID, nom, prenom, dateNaissance, adresse);


        qDebug() << "Client créé avec succès: " << nom << prenom;
    }

    QMessageBox::information(this, "Succès", QString::number(nombreClients) + " clients ont été ajoutés avec succès.");
}
