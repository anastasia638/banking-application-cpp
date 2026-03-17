#ifndef BANQUEAPPLI_H
#define BANQUEAPPLI_H

#include <QObject>
#include "gestionnairebanque.h"
#include "client.h"
#include "comptebancaire.h"

/**
 * @brief The Banque1 class
 * Cette classe représente l'application de gestion bancaire principale.
 */
class Banque1 : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe Banque1.
     * @param nomGestionnaire Le nom du gestionnaire de la banque.
     * @param prenomGestionnaire Le prénom du gestionnaire de la banque.
     * @param parent Le widget parent (par défaut nullptr).
     */
    Banque1(QString nomGestionnaire, QString prenomGestionnaire, QObject *parent = nullptr);

    /**
     * @brief Destructeur de la classe Banque1.
     */
    ~Banque1();

    /**
     * @brief Lance l'application de gestion bancaire.
     */
    void run();

private:
    GestionnaireBanque gestionnaireBanque; /**< Le gestionnaire de la banque. */
};

#endif // BANQUEAPPLI_H
