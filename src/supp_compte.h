#ifndef SUPP_COMPTE_H
#define SUPP_COMPTE_H

#include <QDialog>
#include "gestionnairebanque.h"
#include "comptebancaire.h"

namespace Ui {
class supp_compte;
}

/**
 * @brief La classe supp_compte représente la fenêtre de suppression d'un compte pour un client.
 */
class supp_compte : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe supp_compte.
     * @param gestionnaire Un pointeur vers le gestionnaire de la banque.
     * @param parent Le widget parent (par défaut à nullptr).
     */
    explicit supp_compte(GestionnaireBanque* gestionnaire, QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe supp_compte.
     */
    ~supp_compte();

    /**
     * @brief supprimerComptePourClient Supprime le compte sélectionné pour un client.
     */
    void supprimerComptePourClient();


private:
    Ui::supp_compte *ui; /**< Interface utilisateur de la fenêtre de suppression de compte. */
    GestionnaireBanque* gestionnaireBanque; /**< Pointeur vers le gestionnaire de la banque. */
};

#endif // SUPP_COMPTE_H
