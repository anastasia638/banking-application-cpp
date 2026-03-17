#ifndef AJOUT_CLIENT_H
#define AJOUT_CLIENT_H

#include <QDialog>
#include "gestionnairebanque.h"
#include <QMessageBox>
#include "afficher_client.h"

namespace Ui {
class Ajout_client;
}

/**
 * @brief La classe Ajout_client représente la fenêtre pour ajouter un nouveau client.
 */
class Ajout_client : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe Ajout_client.
     * @param gestionnaireBanque Un pointeur vers le gestionnaire de la banque.
     * @param parent Le widget parent (par défaut nullptr).
     */
    explicit Ajout_client(GestionnaireBanque* gestionnaireBanque, QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe Ajout_client.
     */
    ~Ajout_client();

    /**
     * @brief Ajoute un nouveau client à la banque.
     */
    void ajouterNouveauClient();

    /**
     * @brief Crée des comptes bancaires aléatoires pour le nouveau client.
     */
    void creerCompteAleatoires();

private:
    Ui::Ajout_client *ui; /**< L'interface utilisateur de la fenêtre. */
    GestionnaireBanque* gestionnaireBanque; /**< Le gestionnaire de la banque. */
    QMessageBox msgBox; /**< La boîte de message pour afficher les messages d'erreur ou de confirmation. */
};

#endif // AJOUT_CLIENT_H
