#ifndef CREER_GESTIONNAIRE_H
#define CREER_GESTIONNAIRE_H

#include <QDialog>

namespace Ui {
class creer_gestionnaire;
}

/**
 * @brief La classe creer_gestionnaire permet de créer un gestionnaire pour la banque.
 */
class creer_gestionnaire : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe creer_gestionnaire.
     * @param parent Le widget parent.
     */
    explicit creer_gestionnaire(QWidget *parent = nullptr);

    /**
     * @brief Destructeur de la classe creer_gestionnaire.
     */
    ~creer_gestionnaire();

    /**
     * @brief Écrit les informations du gestionnaire dans un fichier.
     * @param identifiant L'identifiant du gestionnaire.
     * @param motDePasse Le mot de passe du gestionnaire.
     * @param nom Le nom du gestionnaire.
     * @param prenom Le prénom du gestionnaire.
     */
    void ecrireDansFichier(const QString& identifiant, const QString& motDePasse, const QString& nom, const QString& prenom);


private:
    Ui::creer_gestionnaire *ui; /**< L'interface utilisateur de la classe creer_gestionnaire. */
};

#endif // CREER_GESTIONNAIRE_H
