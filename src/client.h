#ifndef CLIENT_H
#define CLIENT_H

#include <QtGlobal>
#include <QString>
#include <QDate>
#include "comptebancaire.h"

/**
 * @brief La classe Client représente un client de la banque.
 */
class Client
{
public:
    /**
     * @brief Constructeur par défaut de la classe Client.
     */
    Client();

    /**
     * @brief Constructeur de la classe Client avec paramètres.
     * @param id L'identifiant du client.
     * @param nom Le nom du client.
     * @param prenom Le prénom du client.
     * @param dateNaissance La date de naissance du client.
     * @param adresse L'adresse du client.
     */
    Client(qint64 id, const QString &nom, const QString &prenom, const QDate &dateNaissance, const QString &adresse);

    /**
     * @brief Destructeur de la classe Client.
     */
    ~Client();

    // Getters

    /**
     * @brief Obtient l'identifiant du client.
     * @return L'identifiant du client.
     */
    qint64 getId() const;

    /**
     * @brief Obtient le nom du client.
     * @return Le nom du client.
     */
    QString getNom() const;

    /**
     * @brief Obtient le prénom du client.
     * @return Le prénom du client.
     */
    QString getPrenom() const;

    /**
     * @brief Obtient la date de naissance du client.
     * @return La date de naissance du client.
     */
    QDate getDateNaissance() const;

    /**
     * @brief Obtient l'adresse du client.
     * @return L'adresse du client.
     */
    QString getAdresse() const;

    // Setters

    /**
     * @brief Définit l'identifiant du client.
     * @param id L'identifiant à définir.
     */
    void setId(qint64 id);

    /**
     * @brief Définit le nom du client.
     * @param nom Le nom à définir.
     */
    void setNom(const QString &nom);

    /**
     * @brief Définit le prénom du client.
     * @param prenom Le prénom à définir.
     */
    void setPrenom(const QString &prenom);

    /**
     * @brief Définit la date de naissance du client.
     * @param dateNaissance La date de naissance à définir.
     */
    void setDateNaissance(const QDate &dateNaissance);

    /**
     * @brief Définit l'adresse du client.
     * @param adresse L'adresse à définir.
     */
    void setAdresse(const QString &adresse);

    // Member functions

    /**
     * @brief Affiche les informations du client.
     */
    void AfficherInformation() const;

    /**
     * @brief Effectue un dépôt sur le compte du client.
     * @param montant Le montant à déposer.
     * @param Compte Le compte sur lequel effectuer le dépôt.
     */
    void Depot(double montant, CompteBancaire &Compte);

    /**
     * @brief Effectue un retrait sur le compte du client.
     * @param montant Le montant à retirer.
     * @param Compte Le compte sur lequel effectuer le retrait.
     */
    void Retrait(double montant, CompteBancaire &Compte);

    /**
     * @brief Effectue un virement vers un autre client.
     * @param montant Le montant à virer.
     * @param destinataire Le client bénéficiaire du virement.
     */
    void Virement(double montant, Client &destinataire);

    /**
     * @brief Surcharge de l'opérateur d'égalité pour comparer les clients.
     * @param other Le client à comparer.
     * @return true si les clients sont égaux, sinon false.
     */
    bool operator==(const Client &other) const;

    //int getNombreComptes();

private:
    qint64 id; /**< L'identifiant du client. */
    QString nom; /**< Le nom du client. */
    QString prenom; /**< Le prénom du client. */
    QDate dateNaissance; /**< La date de naissance du client. */
    QString adresse; /**< L'adresse du client. */
    CompteBancaire *Compte; /**< Le compte bancaire du client. */
};

#endif // CLIENT_H
