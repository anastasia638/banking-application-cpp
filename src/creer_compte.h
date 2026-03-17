#ifndef CREER_COMPTE_H
#define CREER_COMPTE_H

#include <QDialog>
#include "gestionnairebanque.h"
#include "comptebancaire.h"

namespace Ui {
class creer_compte;
}

/**
 * @brief La classe creer_compte permet de créer des comptes bancaires.
 */
class creer_compte : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe creer_compte.
     * @param gestionnaire Un pointeur vers le gestionnaire de la banque.
     * @param parent Le widget parent.
     */
    explicit creer_compte(GestionnaireBanque* gestionnaire, QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe creer_compte.
     */
    ~creer_compte();

    /**
     * @brief Crée un compte bancaire pour un client.
     */
    void creerComptePourClient();

    /**
     * @brief Génère des comptes bancaires.
     */
    void genererComptes();

private:
    Ui::creer_compte *ui; /**< L'interface utilisateur de la classe creer_compte. */
    GestionnaireBanque* gestionnaireBanque; /**< Le gestionnaire de la banque. */
};

#endif // CREER_COMPTE_H
