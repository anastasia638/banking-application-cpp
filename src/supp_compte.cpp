#include "supp_compte.h"
#include "ui_supp_compte.h"
#include <QMessageBox>
#include "comptebancaire.h"
#include <QFile>



supp_compte::supp_compte(GestionnaireBanque* gestionnaire,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::supp_compte), gestionnaireBanque(gestionnaire)
{
    ui->setupUi(this);
     connect(ui->supprimer, &QPushButton::clicked, this, &supp_compte::supprimerComptePourClient);
}

supp_compte::~supp_compte()
{
    delete ui;
}


void supp_compte::supprimerComptePourClient() {
    // Récupérer l'ID du client à partir de l'interface utilisateur
    qint64 idClient = ui->ID->text().toLongLong();

    // Vérifier si le client existe dans le gestionnaire
    Client* client = gestionnaireBanque->trouverClientParId(idClient);
    if (!client) {
        // Afficher un message d'erreur si le client n'existe pas
        QMessageBox::critical(this, "Erreur", "Client introuvable. Veuillez saisir un ID client valide.");
        return;
    }

    // Récupérer la liste des comptes du client
    QList<CompteBancaire*> comptesClient = gestionnaireBanque->getComptes(client);

    // Vérifier s'il y a des comptes associés au client
    if (comptesClient.isEmpty()) {
        // Afficher un message si aucun compte n'est associé à ce client
        QMessageBox::information(this, "Information", "Aucun compte associé à ce client n'a été trouvé.");
        return;
    }

    // Parcourir et supprimer tous les comptes du client
    for (CompteBancaire* compte : comptesClient) {
        gestionnaireBanque->supprimerCompte(compte);
    }

    // Enregistrement des mises à jour dans le fichier comptes.txt
    const QString& cheminFichier = "C:/Users/damie/OneDrive/Documents/comptes.txt";
    if (gestionnaireBanque->miseAJourFichierComptes(cheminFichier)) {
        qDebug() << "Suppression des comptes terminée avec succès.";
    } else {
        qDebug() << "Erreur lors de la suppression des comptes dans le fichier.";
    }

    // Afficher un message de succès après la suppression de tous les comptes
    QMessageBox::information(this, "Succès", "Tous les comptes associés à ce client ont été supprimés avec succès.");
    accept(); // Fermer la boîte de dialogue après la suppression des comptes
}



