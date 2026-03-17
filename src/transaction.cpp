#include "transaction.h"

// Constructeur par défaut

transaction::transaction(typetransaction type, double montant)
    : type(type), montant(montant),  date(QDateTime::currentDateTime())
{
    // Date de la transaction est définie comme étant la date et l'heure au moment de la transaction
}

// Récupération du type de transaction

typetransaction transaction::getType() const
{
    return type;
}

// Récupération du montant de la transaction

double transaction::getMontant() const
{
    return montant;
}

// Récupération de la date de la transaction

QDateTime transaction::getDate() const
{
    return date;
}



