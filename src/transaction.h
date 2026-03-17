#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDateTime>
#include "typetransaction.h"

/**
 * @brief La classe transaction représente une transaction effectuée sur un compte bancaire.
 */
class transaction
{
public:
    /**
     * @brief Constructeur de la classe transaction.
     * @param type Le type de la transaction (dépôt, retrait, virement).
     * @param montant Le montant de la transaction.
     */
    transaction(typetransaction type, double montant);

    /**
     * @brief Getter pour le type de la transaction.
     * @return Le type de la transaction.
     */
    typetransaction getType() const;

    /**
     * @brief Getter pour le montant de la transaction.
     * @return Le montant de la transaction.
     */
    double getMontant() const;

    /**
     * @brief Getter pour la date de la transaction.
     * @return La date de la transaction.
     */
    QDateTime getDate() const;

private:
    typetransaction type; /**< Le type de la transaction. */
    double montant; /**< Le montant de la transaction. */
    QDateTime date; /**< La date de la transaction. */
};

#endif // TRANSACTION_H
