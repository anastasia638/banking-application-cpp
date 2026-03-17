#ifndef TYPETRANSACTION_H
#define TYPETRANSACTION_H

// Déclaration des différents types de transaction

enum class typetransaction
{
    DEPOT,
    RETRAIT,
    // J'ai directement impléménté les deux types de virements pouvant être possible
    VIREMENT_SORTANT,
    VIREMENT_ENTRANT,
    INTERETS,
    AUTRE
};

#endif // TYPETRANSACTION_H
