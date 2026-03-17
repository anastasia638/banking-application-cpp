#ifndef SUP_CLIENT_H
#define SUP_CLIENT_H

#include <QDialog>
#include "gestionnairebanque.h"

namespace Ui {
class Sup_client;
}

/**
 * @brief La classe Sup_client représente la fenêtre de suppression d'un client.
 */
class Sup_client : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe Sup_client.
     * @param gestionnaire Un pointeur vers le gestionnaire de la banque.
     * @param parent Le widget parent (par défaut à nullptr).
     */
    explicit Sup_client(GestionnaireBanque* gestionnaire, QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe Sup_client.
     */
    ~Sup_client();

    /**
     * @brief supprimerClient Supprime le client sélectionné.
     */
    void supprimerClient();

    /**
     * @brief supprimerClientDuFichier Supprime le client du fichier avec l'identifiant spécifié.
     * @param idClient L'identifiant du client à supprimer.
     * @return True si le client a été supprimé avec succès, sinon False.
     */
    bool supprimerClientDuFichier(qint64 idClient);

private:
    Ui::Sup_client *ui; /**< Interface utilisateur de la fenêtre de suppression de client. */
    GestionnaireBanque* gestionnaireBanque; /**< Pointeur vers le gestionnaire de la banque. */
};

#endif // SUP_CLIENT_H
