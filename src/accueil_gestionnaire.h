#ifndef ACCUEIL_GESTIONNAIRE_H
#define ACCUEIL_GESTIONNAIRE_H


#include <QDialog>
#include "gestionnairebanque.h"
#include <QTextEdit>
#include "ajout_client.h"
#include "afficher_client.h"
#include "sup_client.h"
#include "banque.h"
#include "gestionnairebanque.h"
#include "sauver_charger.h"
#include "creer_compte.h"
#include "supp_compte.h"
#include "afficher_compte.h"
#include "support.h"

/**
 * @brief La classe Accueil_gestionnaire représente la fenêtre principale de l'interface pour le gestionnaire de la banque.
 */
class Accueil_gestionnaire : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe Accueil_gestionnaire.
     * @param gestionnaire Un pointeur vers le gestionnaire de la banque.
     * @param nomGestionnaire Le nom du gestionnaire.
     * @param parent Le widget parent (par défaut nullptr).
     */
    explicit Accueil_gestionnaire(GestionnaireBanque* gestionnaire, const QString& nomGestionnaire, QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe Accueil_gestionnaire.
     */
    ~Accueil_gestionnaire();

    /**
     * @brief Affiche la page pour ajouter un client.
     */
    void afficherPageAjoutClient();

    /**
     * @brief Affiche la page pour afficher les clients.
     */
    void afficherPageAfficherClients();

    /**
     * @brief Affiche la page pour supprimer un client.
     */
    void afficherPageSupprimerClient();

    /**
     * @brief Affiche la page de connexion.
     */
    void afficherPageConnexion();

    /**
     * @brief Affiche la page pour sauvegarder ou charger les données.
     */
    void afficherPageSauverCharger();

    /**
     * @brief Peuple le gestionnaire de clients.
     */
    void peuplerGestionnaireDeClients();

    /**
     * @brief Affiche la page pour créer un compte bancaire.
     */
    void afficherPageCreerCompte();

    /**
     * @brief Affiche la page pour supprimer un compte bancaire.
     */
    void afficherPageSupprimerCompte();

    /**
     * @brief Affiche la page pour afficher les comptes bancaires.
     */
    void afficherPageAfficherComptes();


    /**
     * @brief Affiche la page pour afficher la page support.
     */
    void afficherPageAfficherComptes();

    void afficherPageSupport();


private:
    Ui::Accueil_gestionnaire *ui; /**< L'interface utilisateur de la fenêtre. */
    GestionnaireBanque* gestionnaireBanque; /**< Le gestionnaire de la banque. */
};

#endif // ACCUEIL_GESTIONNAIRE_H
