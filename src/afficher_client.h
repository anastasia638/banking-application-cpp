#ifndef AFFICHER_CLIENT_H
#define AFFICHER_CLIENT_H

#include <QDialog>
#include "gestionnairebanque.h"
#include "ajout_client.h"

/**
 * @brief La classe Afficher_client représente la fenêtre pour afficher la liste des clients.
 */
class Afficher_client : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe Afficher_client.
     * @param gestionnaire Un pointeur vers le gestionnaire de la banque.
     * @param parent Le widget parent (par défaut nullptr).
     */
    explicit Afficher_client(GestionnaireBanque* gestionnaire, QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe Afficher_client.
     */
    ~Afficher_client();

    /**
     * @brief Affiche la liste des clients dans l'interface utilisateur.
     */
    void afficherListeClients();

private:
    Ui::Afficher_client *ui; /**< L'interface utilisateur de la fenêtre. */
    GestionnaireBanque* gestionnaireBanque; /**< Le gestionnaire de la banque. */
};

#endif // AFFICHER_CLIENT_H
