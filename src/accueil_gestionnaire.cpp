#include "accueil_gestionnaire.h"
#include "ui_accueil_gestionnaire.h"



Accueil_gestionnaire::Accueil_gestionnaire(GestionnaireBanque* gestionnaire, const QString& nomGestionnaire, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Accueil_gestionnaire)
{
    ui->setupUi(this);
    ui->labelNomGestionnaire->setText("Bonjour, " + nomGestionnaire + " !");

    connect(ui->Ajout_client, &QPushButton::clicked, this, &Accueil_gestionnaire::afficherPageAjoutClient);
    connect(ui->Afficher_client, &QPushButton::clicked, this, &Accueil_gestionnaire::afficherPageAfficherClients);
    connect(ui->Supp_client, &QPushButton::clicked, this, &Accueil_gestionnaire::afficherPageSupprimerClient);
    connect(ui->deconnexion, &QPushButton::clicked, this, &Accueil_gestionnaire::afficherPageConnexion);
    connect(ui->Charger_sauver_client, &QPushButton::clicked, this, &Accueil_gestionnaire::afficherPageSauverCharger);
    connect(ui->creer_compte, &QPushButton::clicked, this, &Accueil_gestionnaire::afficherPageCreerCompte);
    connect(ui->supp_compte, &QPushButton::clicked, this, &Accueil_gestionnaire::afficherPageSupprimerCompte);
    connect(ui->afficher_compte, &QPushButton::clicked, this, &Accueil_gestionnaire::afficherPageAfficherComptes);
    connect(ui->support, &QPushButton::clicked, this, &Accueil_gestionnaire::afficherPageSupport);



    gestionnaireBanque = gestionnaire;


}

Accueil_gestionnaire::~Accueil_gestionnaire()
{
    delete ui;
}

void Accueil_gestionnaire::afficherPageAjoutClient() {
    // Créer une instance de la page d'ajout de client
    Ajout_client ajoutClientPage(gestionnaireBanque,this);
    // Afficher la fenêtre
    ajoutClientPage.exec();
}

void Accueil_gestionnaire::afficherPageAfficherClients() {

    // Créer une instance de la page d'affichage des clients
    Afficher_client afficherClientsPage(gestionnaireBanque, this);

    afficherClientsPage.afficherListeClients();
    // Afficher la fenêtre
    afficherClientsPage.exec();
}

void Accueil_gestionnaire::afficherPageSupprimerClient() {
    // Créer une instance de la page
    Sup_client supprimerClientPage(gestionnaireBanque, this);
    //afficher la page
    supprimerClientPage.exec();
}

void Accueil_gestionnaire::afficherPageConnexion(){
    // Fermer la fenêtre actuelle
    this->close();

    // Ouvrir une nouvelle instance de la page de connexion
    Banque *connexionPage = new Banque();
    connexionPage->show();
}

void Accueil_gestionnaire::afficherPageSauverCharger(){
    // Créer une instance de la page
    sauver_charger sauver_chargerPage(gestionnaireBanque, this);
    //afficher
    sauver_chargerPage.exec();

}

void Accueil_gestionnaire::afficherPageCreerCompte() {
    // Créer une instance de la page de création de compte
    creer_compte creerComptePage(gestionnaireBanque, this);

    // Afficher la nouvelle fenêtre
    creerComptePage.exec();
}

void Accueil_gestionnaire::afficherPageSupprimerCompte(){
    // Créer une instance de la page de création de compte
    supp_compte suppComptePage(gestionnaireBanque, this);
    // Afficher la nouvelle fenêtre modale
    suppComptePage.exec();
}

void Accueil_gestionnaire::afficherPageAfficherComptes() {
    // Créer une instance de la page d'affichage des comptes
    afficher_compte afficherComptesPage(gestionnaireBanque, this);
    afficherComptesPage.afficherListeComptes();
    // Afficher la nouvelle fenêtre modale
    afficherComptesPage.exec();
}


void Accueil_gestionnaire::afficherPageSupport() {
    support *pageSupport = new support(this); // Assurez-vous que PageSupport est correctement défini et inclus
    pageSupport->show();
}

