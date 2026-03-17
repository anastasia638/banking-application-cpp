#include "afficher_compte.h"
#include "ui_afficher_compte.h"
#include "gestionnairebanque.h"
#include "comptebancaire.h"
#include "client.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QTimer>

afficher_compte::afficher_compte(GestionnaireBanque* gestionnaire, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::afficher_compte)
{
    ui->setupUi(this);
    connect(ui->virement, &QPushButton::clicked, this, &afficher_compte::effectuerVirement); // Connecter le bouton "Virement" au slot
    connect(ui->virement_demo, &QPushButton::clicked, this, &afficher_compte::effectuerVirementDemo);

    connect(ui->se, &QRadioButton::clicked, this, &afficher_compte::activerTimerSeconde);
    connect(ui->jo, &QRadioButton::clicked, this, &afficher_compte::activerTimerJours);


    timer = new QTimer(this);
    gestionnaireBanque = gestionnaire;
}

afficher_compte::~afficher_compte()
{
    delete ui;
}

void afficher_compte::afficherListeComptes() {
    // Effacer toutes les lignes existantes dans le tableau
    gestionnaireBanque->afficherClients();
    ui->tableau_comptes->clearContents();

    // Récupérer la liste des comptes bancaires du gestionnaire de banque
    QList<CompteBancaire*> listeComptes = gestionnaireBanque->getListeComptes();

    int row = 0;
    foreach(CompteBancaire* compte, listeComptes) {
        // Obtenir les informations sur le compte bancaire
        qint64 id = compte->getNumeroCompte();
        double solde = compte->getSolde();
        QString nomProprietaire = compte->getProprietaire().getNom(); // Obtenez le nom du propriétaire
        qint64 idClient = compte->getProprietaire().getId();

        // Ajouter les informations dans les cellules correspondantes du tableau
        ui->tableau_comptes->setItem(row, 0, new QTableWidgetItem(QString::number(idClient))); // Ajouter l'ID du client
        ui->tableau_comptes->setItem(row, 1, new QTableWidgetItem(nomProprietaire));
        ui->tableau_comptes->setItem(row, 2, new QTableWidgetItem(QString::number(id)));
        ui->tableau_comptes->setItem(row, 3, new QTableWidgetItem(QString::number(solde)));

        row++;
    }
}

void afficher_compte::effectuerVirementAutomatique() {
    qint64 numeroSource = ui->compteSource->text().toLongLong();
    qint64 numeroDestination = ui->compteDestinataire->text().toLongLong();
    double montant = ui->montant->value();

    CompteBancaire* source = nullptr;
    CompteBancaire* destination = nullptr;

    QList<CompteBancaire*> comptes = gestionnaireBanque->getListeComptes();

    for (CompteBancaire* compte : comptes) {
        if (compte->getNumeroCompte() == numeroSource) {
            source = compte;
        }
        if (compte->getNumeroCompte() == numeroDestination) {
            destination = compte;
        }
    }

    if (source && destination) {
        bool success = gestionnaireBanque->effectuerVirement(source, destination, montant);

        if (success) {
            qDebug() << "Virement effectué avec succès !";
            afficherListeComptes();
        } else {
            qDebug() << "Le virement a échoué. Veuillez vérifier les informations saisies.";
        }
    } else {
        qDebug() << "Comptes non trouvés.";
    }
}


// Slot pour activer le timer pour les secondes
void afficher_compte::activerTimerSeconde() {
    ui->jo->setChecked(false); // Désactiver l'autre bouton radio
    if (ui->virement->isEnabled()) {
        timer->start(1000);
        // Démarrer le timer avec un intervalle d'une seconde
        // Appeler la fonction pour effectuer le virement automatique immédiatement
        effectuerVirementAutomatique();
    }
}

// Slot pour activer le timer pour les jours
void afficher_compte::activerTimerJours() {
    ui->se->setChecked(false); // Désactiver l'autre bouton radio
    // Configurer le timer pour le virement chaque jour
    // À faire selon les besoins
}


void afficher_compte::effectuerVirement() {
    // Obtenir les informations sur le virement
    qint64 numeroSource = ui->compteSource->text().toLongLong();
    qint64 numeroDestination = ui->compteDestinataire->text().toLongLong();
    double montant = ui->montant->value();

    CompteBancaire* source = nullptr;
    CompteBancaire* destination = nullptr;

    // Récupérer la liste des comptes bancaires
    QList<CompteBancaire*> comptes = gestionnaireBanque->getListeComptes();

    // Parcourir la liste des comptes pour trouver les comptes source et destination
    for (CompteBancaire* compte : comptes) {
        if (compte->getNumeroCompte() == numeroSource) {
            source = compte;
        }
        if (compte->getNumeroCompte() == numeroDestination) {
            destination = compte;
        }
    }

    // Vérifier si les comptes source et destination ont été trouvés
    if (source && destination) {
        if(ui->se->isChecked()){
            connect(timer, &QTimer::timeout, this, &afficher_compte::effectuerVirementAutomatique);
            activerTimerSeconde();
        }else {
        // Appeler la méthode de votre gestionnaire de banque pour effectuer le virement
        bool success = gestionnaireBanque->effectuerVirement(source, destination, montant);

        if (success) {
            qDebug() << "Virement effectué avec succès !";
            // Rafraîchir l'affichage des comptes
            afficherListeComptes();
        } else {
            qDebug() << "Le virement a échoué. Veuillez vérifier les informations saisies.";
        }}
    } else {
        qDebug() << "Comptes non trouvés.";
    }
}


void afficher_compte::effectuerVirementDemo() {

    srand(time(nullptr));
    // Récupérer la liste des comptes bancaires
    QList<CompteBancaire*> comptes = gestionnaireBanque->getListeComptes();

    // Si le nombre de comptes est inférieur à 2, les virements ne sont pas possibles
    if (comptes.size() < 2) {
        qDebug() << "Il n'y a pas suffisamment de comptes pour effectuer des virements.";
        return;
    }

    // Configurer un QTimer pour déclencher les virements à intervalle régulier
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this, comptes]() {
        // Sélectionner un compte source et un compte destination différents au hasard
        CompteBancaire* source = comptes[rand() % comptes.size()];
        CompteBancaire* destination = source;
        while (destination == source) {
            destination = comptes[rand() % comptes.size()];
        }

        // Générer un montant aléatoire pour le virement entre 1 et le solde du compte source
        double montant = 1 + (rand() % ((int)source->getSolde() - 1));

        // Effectuer le virement entre les comptes source et destination
        bool success = gestionnaireBanque->effectuerVirement(source, destination, montant);
        if (success) {
            qDebug() << "Virement de" << montant << "effectué de " << source->getNumeroCompte() << " à " << destination->getNumeroCompte();
            // Rafraîchir l'affichage des comptes
            afficherListeComptes();
        } else {
            qDebug() << "Le virement a échoué de " << source->getNumeroCompte() << " à " << destination->getNumeroCompte();
        }
    });

    // Démarrer le timer avec un intervalle de 5 secondes
    timer->start(5000);
}






