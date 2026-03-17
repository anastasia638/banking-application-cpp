#ifndef AFFICHER_COMPTE_H
#define AFFICHER_COMPTE_H

#include <QDialog>
#include "gestionnairebanque.h"
#include <QDebug>
#include <QTableWidgetItem>
#include "client.h"
#include "transaction.h"
#include <QTimer>

namespace Ui {
class afficher_compte;
}

/**
 * @brief La classe afficher_compte représente la fenêtre pour afficher les détails d'un compte.
 */
class afficher_compte : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe afficher_compte.
     * @param gestionnaire Un pointeur vers le gestionnaire de la banque.
     * @param parent Le widget parent (par défaut nullptr).
     */
    explicit afficher_compte(GestionnaireBanque* gestionnaire,QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe afficher_compte.
     */
    ~afficher_compte();

    /**
     * @brief Affiche la liste des comptes dans l'interface utilisateur.
     */
    void afficherListeComptes();

    /**
     * @brief Effectue un virement entre deux comptes.
     * @param numeroSource Le numéro du compte source.
     * @param numeroDestination Le numéro du compte de destination.
     * @param montant Le montant du virement.
     */
    void effectuerVirement1(qint64 numeroSource, qint64 numeroDestination, double montant);

    /**
     * @brief Active ou désactive le timer pour les opérations automatiques.
     * @param checked Indique si le timer doit être activé ou désactivé.
     */
    void toggleTimer(bool checked);

    /**
     * @brief Effectue un virement automatique entre deux comptes.
     */
    void effectuerVirementAutomatique();

    /**
     * @brief Effectue un virement entre deux comptes.
     */
    void effectuerVirement();

    /**
     * @brief Réalise une transaction.
     */
    void transaction();

    /**
     * @brief Gère l'événement de basculement de la case à cocher.
     * @param checked Indique si la case à cocher est cochée ou non.
     */
    void onCheckBoxToggled(bool checked);

    /**
     * @brief Active le timer pour les opérations à la seconde.
     */
    void activerTimerSeconde();

    /**
     * @brief Active le timer pour les opérations à intervalle de jours.
     */
    void activerTimerJours();

    /**
     * @brief Effectue un virement de démonstration.
     */
    void effectuerVirementDemo();

private:
    Ui::afficher_compte *ui; /**< L'interface utilisateur de la fenêtre. */
    GestionnaireBanque* gestionnaireBanque; /**< Le gestionnaire de la banque. */
    QTimer *timer; /**< Le timer pour les opérations automatiques. */
};

#endif // AFFICHER_COMPTE_H
