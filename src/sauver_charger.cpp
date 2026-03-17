#include "sauver_charger.h"
#include "gestionnairebanque.h"
#include "ui_sauver_charger.h"

sauver_charger::sauver_charger(GestionnaireBanque* gestionnaire, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::sauver_charger), gestionnaireBanque(gestionnaire)
{
    ui->setupUi(this);
    connect(ui->charger, &QPushButton::clicked, this, &sauver_charger::peuplerGestionnaireDeClients);
    connect(ui->sauver, &QPushButton::clicked, this, &sauver_charger::sauvegarderClients);
}

sauver_charger::~sauver_charger()
{
    delete ui;
}

void sauver_charger::peuplerGestionnaireDeClients()
{
    // Chemin du fichier texte contenant les données des clients
    QString cheminFichier = "C:/Users/damie/OneDrive/Documents/clients.txt";

    // Appeler la fonction de chargement des clients depuis le fichier texte
    if(gestionnaireBanque->chargerClientsDepuisTXT(cheminFichier)) {
        qDebug() << "Chargement des clients terminé avec succès.";
    } else {
        qDebug() << "Erreur lors du chargement des clients depuis le fichier.";
    }

    // Chemin du fichier texte contenant les données des clients
    QString cheminFichier1 = "C:/Users/damie/OneDrive/Documents/comptes.txt";

    // Appeler la fonction de chargement des clients depuis le fichier texte
    if(gestionnaireBanque->chargerComptesDepuisTXT(cheminFichier1)) {
        qDebug() << "Chargement des comptes terminé avec succès.";
    } else {
        qDebug() << "Erreur lors du chargement des comptes depuis le fichier.";
    }

    this->close();
}


void sauver_charger::sauvegarderClients() {
    const QString& cheminFichier = "C:/Users/damie/OneDrive/Documents/clients.txt";

    // Appeler la fonction pour sauver des clients dans le fichier texte
    if(gestionnaireBanque->sauvegarderClientsDansTXT(cheminFichier)) {
        qDebug() << "sauvegarde des clients terminé avec succès.";
    } else {
        qDebug() << "Erreur lors de la sauvegarde des clients dans le fichier.";
    }

    const QString& cheminFichier2 = "C:/Users/damie/OneDrive/Documents/comptes.txt";

    // Appeler la fonction pour sauver les comptes dans le fichier texte
    if(gestionnaireBanque->sauvegarderComptesDansTXT(cheminFichier2)) {
        qDebug() << "Sauvegarde des comptes terminée avec succès.";
    } else {
        qDebug() << "Erreur lors de la sauvegarde des comptes dans le fichier.";
    }
    this->close();

}

