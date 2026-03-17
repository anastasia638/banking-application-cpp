#ifndef COMPTEBANCAIRE_H
#define COMPTEBANCAIRE_H

#include "transaction.h"
#include "periode.h"
#include <QList>
#include <QtGlobal>

class Client;

/**
 * @brief La classe CompteBancaire représente un compte bancaire.
 */
class CompteBancaire
{
public:
    // Constructeur et destructeur de la classe
    CompteBancaire();

    // Constructor declaration in comptebancaire.h
    /**
     * @brief Constructeur de la classe CompteBancaire avec un numéro de compte et un propriétaire.
     * @param NumCompte Le numéro du compte bancaire.
     * @param proprio Le propriétaire du compte bancaire.
     */
    CompteBancaire(qint64 NumCompte, Client &proprio);

    /**
     * @brief Constructeur de la classe CompteBancaire avec un numéro de compte, un solde initial et un propriétaire.
     * @param NumCompte Le numéro du compte bancaire.
     * @param soldeInitial Le solde initial du compte bancaire.
     * @param proprio Le propriétaire du compte bancaire.
     */
    CompteBancaire(qint64 NumCompte, double soldeInitial, Client &proprio);

    //Destructeur
    ~CompteBancaire();

    // Getters
    /**
     * @brief Obtient le numéro du compte bancaire.
     * @return Le numéro du compte bancaire.
     */
    qint64 getNumeroCompte() const;

    /**
     * @brief Obtient le solde du compte bancaire.
     * @return Le solde du compte bancaire.
     */
    double getSolde() const;

    /**
     * @brief Obtient la date du dernier virement effectué sur le compte bancaire.
     * @return La date du dernier virement.
     */
    QDateTime getDateDernierVirement() const;

    /**
     * @brief Obtient le propriétaire du compte bancaire.
     * @return Le propriétaire du compte bancaire.
     */
    Client getProprietaire() const;

    // Fonctions pour manipuler le solde du compte
    /**
     * @brief Dépose un montant sur le compte bancaire.
     * @param montant Le montant à déposer.
     */
    void deposerArgent(double montant);

    /**
     * @brief Retire un montant du compte bancaire.
     * @param montant Le montant à retirer.
     */
    void retirerArgent(double montant);

    /**
     * @brief Retire un montant du compte bancaire avec vérification du solde.
     * @param montant Le montant à retirer.
     * @return true si le retrait a réussi, sinon false.
     */
    bool retirerArgent1(double montant);

    /**
     * @brief Effectue un virement vers un autre compte bancaire.
     * @param destinataire Le compte bancaire bénéficiaire du virement.
     * @param montant Le montant à virer.
     */
    void effectuerVirement(CompteBancaire &destinataire, double montant);

    // Fonctions spécifiques au compte bancaire
    /**
     * @brief Calcule les intérêts du compte bancaire.
     */
    void calculerInterets();

    /**
     * @brief Ferme le compte bancaire.
     */
    void fermerCompte();

    // void changerProprietaire(const Client &nouveauProprietaire);

    /**
     * @brief Définit la limite de découvert autorisée sur le compte bancaire.
     * @param limite La limite de découvert à définir.
     */
    void definirLimiteDecouvert(double limite);

    /**
     * @brief Obtient la périodicité en jours.
     * @param periodicite La périodicité à calculer.
     * @return La périodicité en jours.
     */
    int periodiciteEnJours(periode periodicite) const;

    /**
     * @brief Effectue un virement automatique vers un autre compte bancaire à une périodicité donnée.
     * @param destinataire Le compte bancaire bénéficiaire du virement.
     * @param montant Le montant à virer.
     * @param periodicite La périodicité du virement.
     */
    void virementAutomatique(CompteBancaire &destinataire, double montant, periode periodicite);

    /**
     * @brief Définit la date du dernier virement effectué sur le compte bancaire.
     * @param date La date du dernier virement.
     */
    void setDernierVirement(const QDateTime &date);

    /**
     * @brief Gèle le compte bancaire.
     */
    void gelerCompte();

    /**
     * @brief Bloque le compte bancaire.
     */
    void bloquerCompte();

private:
    qint64 numeroCompte; /**< Le numéro du compte bancaire. */
    double solde; /**< Le

 solde du compte bancaire. */
    //QList<transaction> historiqueTransactions;
    Client *const proprietaire; /**< Le propriétaire du compte bancaire. */
    QDateTime dernierVirement; /**< La date du dernier virement effectué sur le compte bancaire. */
    double limiteDecouvert; /**< La limite de découvert autorisée sur le compte bancaire. */
    bool compteGele; /**< Indique si le compte bancaire est gelé. */
    bool compteBloque; /**< Indique si le compte bancaire est bloqué. */
    int autrePeriode = -1; /**< Périodicité personnalisée. */
};

#endif // COMPTEBANCAIRE_H
