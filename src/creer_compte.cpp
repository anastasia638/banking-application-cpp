#include "creer_compte.h"
#include "ui_creer_compte.h"
#include "gestionnairebanque.h"
#include <QMessageBox>
#include <ctime>
#include "client.h"

creer_compte::creer_compte(GestionnaireBanque* gestionnaire, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::creer_compte), gestionnaireBanque(gestionnaire)
{
    ui->setupUi(this);
    connect(ui->generer, &QPushButton::clicked, this, &creer_compte::genererComptes);
    connect(ui->creer, &QPushButton::clicked, this, &creer_compte::creerComptePourClient);
}

creer_compte::~creer_compte()
{
    delete ui;
}


void creer_compte::creerComptePourClient() {
    // Récupérer l'ID du client à partir de l'interface utilisateur
    qint64 idClient = ui->ID->text().toLongLong();

    // Vérifier si le client existe dans le gestionnaire
    Client* client = gestionnaireBanque->trouverClientParId(idClient);
    if (!client) {
        // Afficher un message d'erreur si le client n'existe pas
        QMessageBox::critical(this, "Erreur", "Client introuvable. Veuillez saisir un ID client valide.");
        return;
    }

    // Créer un compte pour le client avec le montant initial spécifié
    double montantInitial = ui->montant->value();
    CompteBancaire* nouveauCompte = gestionnaireBanque->creerComptePourClient(client, montantInitial);
    if (nouveauCompte) {
        // Afficher un message de succès si le compte est créé avec succès
        QMessageBox::information(this, "Succès", "Compte créé avec succès pour le client.");
        accept(); // Fermer la boîte de dialogue après la création du compte
    } else {
        // Afficher un message d'erreur si la création du compte a échoué
        QMessageBox::critical(this, "Erreur", "Erreur lors de la création du compte.");
    }
}


void creer_compte::genererComptes() {
    // Initialiser le générateur de nombres aléatoires avec une graine basée sur l'heure actuelle
    srand(time(nullptr));

    // Récupérer tous les clients du gestionnaire
    QList<Client*> clients = gestionnaireBanque->listeClients1();

    // Parcourir tous les clients
    for (Client* client : clients) {
        // Vérifier si le client n'a pas déjà de compte
        if (gestionnaireBanque->getNombreComptes(client) == 0) {
            // Générer un montant aléatoire pour le compte initial entre 100 et 10000
            double montantInitial = 100 + (rand() % ((10000 + 1) - 100));

            // Créer un nouveau compte pour le client avec le montant initial généré
            CompteBancaire* nouveauCompte = gestionnaireBanque->creerComptePourClient(client, montantInitial);

            if (nouveauCompte) {
                qDebug() << "Compte créé avec succès pour le client " << client->getNom() << client->getPrenom() << " avec un solde initial de " << montantInitial;
            } else {
                qDebug() << "Erreur lors de la création du compte pour le client " << client->getNom() << client->getPrenom();
            }
        }
    }

    QMessageBox::information(this, "Succès", "Les comptes ont été générés avec succès pour les clients sans compte.");
}

