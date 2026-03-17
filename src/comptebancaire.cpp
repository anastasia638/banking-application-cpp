#include "comptebancaire.h"
#include "client.h"
#include "periode.h"
#include <QDateTime>
#include <QDebug>
#include <QtGlobal>

// Constructeur par défaut
CompteBancaire::CompteBancaire() : proprietaire(nullptr)
{
    numeroCompte = 0;
    solde = 0;
    limiteDecouvert = 0;
    compteGele = false;
    compteBloque = false;
}

// Constructeur prenant en compte le numéro de compte et le propriétaire

CompteBancaire::CompteBancaire(qint64 NumCompte, Client &proprio) : proprietaire(&proprio)
{
    numeroCompte = NumCompte;
    solde = 0;
    // proprietaire = &proprio;
    limiteDecouvert = 0;
    compteGele = false;
    compteBloque = false;
}

CompteBancaire::CompteBancaire(qint64 NumCompte, double soldeInitial, Client &proprio)
    : numeroCompte(NumCompte), solde(soldeInitial), proprietaire(&proprio) {}

// Destructeur

CompteBancaire::~CompteBancaire()
{
    //historiqueTransactions.clear(); // Nettoyage de l'historique des transactions
}

/////////////////////////////////////////////////////////// Définition des différents Getters /////////////////////////////////////////////////////////

// Numéros de Compte

qint64 CompteBancaire::getNumeroCompte() const
{
    return numeroCompte;
}

// Le solde du compte

double CompteBancaire::getSolde() const
{
    return solde;
}

// L'historique des transactions

/*QList<transaction> CompteBancaire::getHistoriqueTransactions() const
{
    return historiqueTransactions;
}*/

// le propriétaire du compte

Client CompteBancaire::getProprietaire() const
{
    return *proprietaire;
}

/////////////////////////////////////////////////////////// Définition des fonctions /////////////////////////////////////////////////////////

// Déposer de l'argent dans le compte

void CompteBancaire::deposerArgent(double montant)
{
    solde += montant;
   // historiqueTransactions.append(transaction(typetransaction::DEPOT, montant)); // Ajouter la transaction à l'historique
}

// Retirer de l'argent du compte

void CompteBancaire::retirerArgent(double montant)
{
    if (solde - montant >= -limiteDecouvert)
    {
        solde -= montant;
        //historiqueTransactions.append(transaction(typetransaction::RETRAIT, -montant));
    }
}

bool CompteBancaire::retirerArgent1(double montant) {
    if (solde >= montant) {
        solde -= montant;
        return true;
    } else {
        return false;
    }
}

// Effectuer un virement vers un autre compte

void CompteBancaire::effectuerVirement(CompteBancaire &destinataire, double montant)
{
    if (solde - montant >= -limiteDecouvert) // On pourrait éventuellement faire un assert
    {
        retirerArgent(montant);
        destinataire.deposerArgent(montant);
        //historiqueTransactions.append(transaction(typetransaction::VIREMENT_SORTANT, -montant));
        //destinataire.getHistoriqueTransactions().append(transaction(typetransaction::VIREMENT_ENTRANT, montant));
    }
}

// Calculer les qint64érêts sur le solde du compte

void CompteBancaire::calculerInterets()
{
    if (solde > 0) // Vérifie que le solde est positif
    {
        double tauxInteret = 0.05;             // En se basant sur le site du gouvernement, on a un taux d'intérêt fixe moyen allant de 3,90% à 5%
        double interets = solde * tauxInteret; // Calcul des intérêts
        solde += interets;                     // Ajout des intérêts au solde
    }
}

// Clôturer le compte

void CompteBancaire::fermerCompte()
{
    if (solde == 0) // Vérifie que le solde est nul
    {
        solde = 0;           // Mettre le solde à zéro
        compteBloque = true; // Bloquer le compte
    }
    else
    {
        qDebug() << "Impossible de fermer le compte car le solde n'est pas nul.";
    }
}

// Changer le propriétaire du compte

/*void CompteBancaire::changerProprietaire(const Client &nouveauProprietaire)
{
    if (solde == 0)
    {
        proprietaire = nouveauProprietaire; // Changement du propriétaire
    }
    else
    {
        qDebug() << "Impossible de changer le propriétaire car le solde n'est pas nul.";
    }
}*/

// Définir une limite de découvert pour le compte

void CompteBancaire::definirLimiteDecouvert(double limite)
{
    if (limite >= 0) // Vérifie que la limite de découvert est positive ou nulle
    {
        limiteDecouvert = limite; // Définition de la limite de découvert
    }
    else
    {
        qDebug() << "La limite de découvert doit être positive.";
    }
}

// Définir la date du dernier virement

void CompteBancaire::setDernierVirement(const QDateTime &date)
{
    dernierVirement = date;
}

// Obtenir la date du dernier virement

QDateTime CompteBancaire::getDateDernierVirement() const
{
    return dernierVirement;
}

/*/ Fonction pour obtenir la périodicité en jours
qint64 CompteBancaire::periodiciteEnJours(Periode periodicite) const
{
    switch (periodicite)
    {
        case journalier:
            return 1; // Périodicité journalière
        case hebdomadaire:
            return 7; // Périodicité hebdomadaire (7 jours)
        case mensuel:
            return 30; // Périodicité mensuelle (30 jours)
        default:
            return -1; // Valeur par défaut en cas d'erreur
    }
}*/
//// Note : Je ne sais pas encore s'il faut que je l'implémente comme ça

int CompteBancaire::periodiciteEnJours(periode periodicite) const
{
    // Vérification de la validité de la périodicité

    Q_ASSERT(periodicite == periode::HEBDOMADAIRE || periodicite == periode::MENSUELLE ||
             periodicite == periode::TRIMESTRIELLE || periodicite == periode::SEMESTRIELLE ||
             periodicite == periode::AUTRE);

    // Conversion de la périodicité en nombre de jours correspondant

    switch (periodicite)
    {
    case periode::HEBDOMADAIRE:
        return 7; // Périodicité hebdomadaire (7 jours)
    case periode::MENSUELLE:
        return 30; // Périodicité mensuelle (30 jours)
    case periode::TRIMESTRIELLE:
        return 90; // Périodicité trimestrielle (90jours ou 3 mois)
    case periode::SEMESTRIELLE:
        return 120; // Périodicité Semestrielle (120 jours ou 4 mois)
    case periode::AUTRE:
        if (autrePeriode > 0 && autrePeriode <= 365)
        {
            return autrePeriode; // Périodicité définie manuellement
        }
        else
        {
            qWarning() << "Périodicité invalide ! Veuillez revérifier."; // Message de débogage en cas d'erreur
            return -1;                                                   // Valeur par défaut en cas d'erreur
        }
    default:
        qWarning() << "Périodicité invalide ! Veuillez revérifier.";
        break;
    }
}
// Je vais finalement utiliser la version 2 car la 1 n'est pas complète, j'ai décider d'enlever le virement journalier car il n'était pas conceptuellement cohérent

// Effectuer un virement automatique ou virement "permanent"

void CompteBancaire::virementAutomatique(CompteBancaire &destinataire, double montant, periode periodicite)
{
    QDateTime dateActuelle = QDateTime::currentDateTime();     // Obtient la date et l'heure actuelles
    QDateTime derniereDateVirement = getDateDernierVirement(); // Obtient la date du dernier virement

    qint64 joursDepuisDernierVirement = derniereDateVirement.daysTo(dateActuelle); // Calcule le nombre de jours depuis le dernier virement

    if (joursDepuisDernierVirement >= periodiciteEnJours(periodicite)) // Vérifie si le délai depuis le dernier virement est supérieur ou égal à la périodicité en jours
    {
        if (montant > 0) // Vérifie que le montant est positif
        {
            if (solde - montant >= -limiteDecouvert) // Vérifie que le solde après le virement ne dépasse pas la limite de découvert
            {
                retirerArgent(montant);              // Retrait du montant du compte actuel
                destinataire.deposerArgent(montant); // Dépôt du montant dans le compte destinataire
                setDernierVirement(dateActuelle);    // Mettre à jour la date du dernier virement
            }
            else
            {
                qDebug() << "Solde insuffisant pour effectuer le virement.";
            }
        }
        else
        {
            qDebug() << "Le montant du virement doit être positif.";
        }
    }
    else
    {
        qDebug() << "La date de virement n'a pas encore été atteinte pour effectuer le virement.";
    }
}

// Geler le compte

void CompteBancaire::gelerCompte()
{
    compteGele = true;
}

// Bloquer le compte

void CompteBancaire::bloquerCompte()
{
    compteBloque = true;
}
