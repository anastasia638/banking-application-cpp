#include "client.h"
#include <iostream>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
//#include <comptebancaire.h>

using namespace std;

// Constructeur par défaut



Client::Client()
{
    id = 0;
    nom = "";
    prenom = "";
    dateNaissance = QDate();
    adresse = "";
}

Client::Client(qint64 id, const QString& nom, const QString& prenom, const QDate& dateNaissance, const QString& adresse)
    : id(id), nom(nom), prenom(prenom), dateNaissance(dateNaissance), adresse(adresse) {}

// Destructeur

Client::~Client() {}

///////////////////////////////////////////// Les différents Getters  /////////////////////////////////////

// Identifiant du client

qint64 Client::getId() const {
    return id;
}

// Nom du client

QString Client::getNom() const {
    return nom;
}

// Prénom du client

QString Client::getPrenom() const {
    return prenom;
}

// Date de naissance du client

QDate Client::getDateNaissance() const {
    return dateNaissance;
}

// Adresse du client

QString Client::getAdresse() const {
    return adresse;
}

///////////////////////////////////////////// Les différents Setters  /////////////////////////////////////

// Identifiant du client

void Client::setId(qint64 id) {
    this->id = id;
}

// Nom du client

void Client::setNom(const QString& nom) {
    this->nom = nom;
}

// Prénom du client

void Client::setPrenom(const QString& prenom) {
    this->prenom = prenom;
}

// Date de naissance du client

void Client::setDateNaissance(const QDate& dateNaissance) {
    this->dateNaissance = dateNaissance;
}

// Adresse du client

void Client::setAdresse(const QString& adresse) {
    this->adresse = adresse;
}

// Implémentation de la surcharge de l'opérateur ==
bool Client::operator==(const Client& other) const {

    return this->id == other.id;
}

///////////////////////////////////////////// Les différentes fonctions  ////////////////////////////////////////////


// Afficher les informations sur le client

void Client::AfficherInformation() const {
    cout << "Client Information:" << endl;
    cout << "ID: " << id << endl;
    cout << "Nom: " << nom.toStdString() << endl;
    cout << "Prenom: " << prenom.toStdString() << endl;
    cout << "Date de naissance: " << dateNaissance.toString("dd-MM-yyyy").toStdString() << endl;
    cout << "Adresse: " << adresse.toStdString() << endl;

}

// Déposer de l’argent dans le compte bancaire du client

void Client::Depot(double montant, CompteBancaire& CompteBancaire)
{
    // Vérifiez que le montant du dépôt est positif
    if (montant > 0.0)
    {
        // Mettez à jour le solde du compte bancaire en ajoutant le montant du dépôt
        CompteBancaire.deposerArgent(montant);

        // Affichez un message indiquant que le dépôt a été effectué
        cout << "Un dépôt de " << montant << "€ a été fait dans votre compte courant." << endl;
        cout << "Nouveau solde : " << CompteBancaire.getSolde() << "€" << endl;
    }
    else
    {
        cout << "Le montant du dépôt doit être positif." << endl;
    }
}

// Retirer de l’argent du compte bancaire du client


void Client::Retrait(double montant, CompteBancaire& compteBancaire) {
    bool retraitReussi = compteBancaire.retirerArgent1(montant);

    if (retraitReussi) {
        // Logique à effectuer si le retrait est réussi
        // Par exemple, afficher un message de confirmation
        std::cout << "Retrait de " << montant << " effectué avec succès.\n";
    } else {
        // Logique à effectuer si le retrait échoue
        // Par exemple, afficher un message d'erreur
        std::cerr << "Impossible de retirer " << montant << ". Solde insuffisant.\n";
    }
}

// Transférer de l’argent sur le compte bancaire d’un autre client

void Client::Virement(double montant, Client& destinataire)
{
    // Vérifiez que le montant du virement est positif
    if (montant > 0.0)
    {
        // Utilisez la fonction d'effectuerVirement de la classe CompteBancaire
        (*Compte).effectuerVirement(*(destinataire.Compte), montant);

        // Affichez un message indiquant que le virement a été initié
        cout << "Transfert d'un montant de " << montant << "€ vers le compte de " << destinataire.prenom.toStdString() << " " << destinataire.nom.toStdString() << "." << endl;
        cout << "Nouveau solde de votre compte : " << Compte->getSolde() << "€" << endl;
    }
    else
    {
        cout << "Le montant du virement doit être positif." << endl;
    }
}
