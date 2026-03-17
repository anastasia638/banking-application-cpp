#ifndef BANQUE_H
#define BANQUE_H

#include "gestionnairebanque.h"
#include <QMainWindow>
#include "creer_gestionnaire.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Banque;
}
QT_END_NAMESPACE

/**
 * @brief The Banque class
 * Cette classe représente la fenêtre principale de l'application bancaire.
 */
class Banque : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe Banque.
     * @param parent Le widget parent (par défaut nullptr).
     */
    Banque(QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe Banque.
     */
    ~Banque();

    /**
     * @brief Vérifie l'identité de l'utilisateur.
     */
    void verifierIdentite();

    /**
     * @brief Affiche la page de création du gestionnaire de banque.
     */
    void afficherPageCreation();

private:
    Ui::Banque *ui; /**< L'interface utilisateur de la fenêtre. */
};

#endif // BANQUE_H
