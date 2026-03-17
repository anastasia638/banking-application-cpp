#include "afficher_client.h"
#include "ui_afficher_client.h"
#include <QDebug>
#include <QRegularExpression>

Afficher_client::Afficher_client(GestionnaireBanque* gestionnaire, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Afficher_client)
{
    ui->setupUi(this);
    ui->tableau_client->setEditTriggers(QAbstractItemView::NoEditTriggers);
    gestionnaireBanque = gestionnaire;
}

Afficher_client::~Afficher_client()
{
    delete ui;
}


void Afficher_client::afficherListeClients() {
    // Récupérer la liste des clients depuis le gestionnaire de banque
    gestionnaireBanque->afficherClients(); //afficher dans la console
    // Effacer toutes les lignes existantes dans le tableau
    ui->tableau_client->clearContents();

    // Récupérer la liste des clients
    QStringList listeClients = gestionnaireBanque->listeClients();

    int row = 0;
    foreach(QString infoClient, listeClients) {
        // Utiliser une expression pour capturer les différentes parties de la chaîne
        QRegularExpression regex("ID:\\s*(\\d+),\\s*Nom:\\s*(.*?),\\s*Prénom:\\s*(.*?),\\s*Date de naissance:\\s*(.*?),\\s*Adresse:\\s*(.*)");
        QRegularExpressionMatch match = regex.match(infoClient);

        if (match.hasMatch()) {
            // Extraire les différentes parties de la chaîne
            QString id = match.captured(1);
            QString nom = match.captured(2);
            QString prenom = match.captured(3);
            QString dateNaissance = match.captured(4);
            QString adresse = match.captured(5);

            // Ajouter les informations dans les cellules correspondantes du tableau
            ui->tableau_client->setItem(row, 0, new QTableWidgetItem(id));
            ui->tableau_client->setItem(row, 1, new QTableWidgetItem(nom));
            ui->tableau_client->setItem(row, 2, new QTableWidgetItem(prenom));
            ui->tableau_client->setItem(row, 3, new QTableWidgetItem(dateNaissance));
            ui->tableau_client->setItem(row, 4, new QTableWidgetItem(adresse));
        }

        row++;
    }
}
