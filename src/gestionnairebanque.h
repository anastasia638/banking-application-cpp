#ifndef GESTIONNAIREBANQUE_H
#define GESTIONNAIREBANQUE_H

#include <QtGlobal>
#include <Qstring>
#include <QList>
#include <QDate>

class Client;
class CompteBancaire;

/**
 * @brief La classe GestionnaireBanque représente le gestionnaire de la banque.
 */
class GestionnaireBanque
{
private:
    QString identifiant; /**< L'identifiant du gestionnaire. */
    QString mot_de_passe; /**< Le mot de passe du gestionnaire. */
    QString nom; /**< Le nom du gestionnaire. */
    QString prenom; /**< Le prénom du gestionnaire. */
    QList<Client *> clients; /**< La liste des clients de la banque. */
    QList<CompteBancaire *> comptes; /**< La liste des comptes de la banque. */

public:
    // Constructor
    /**
     * @brief Constructeur de la classe GestionnaireBanque.
     * @param nom Le nom du gestionnaire.
     * @param prenom Le prénom du gestionnaire.
     */
    GestionnaireBanque(QString nom, QString prenom);

    // Destructor
    /**
     * @brief Destructeur de la classe GestionnaireBanque.
     */
    ~GestionnaireBanque();

    //setter
    /**
     * @brief Définit le nom du gestionnaire.
     * @param nom Le nom du gestionnaire.
     */
    void setNom(const QString& nom);

    /**
     * @brief Définit le prénom du gestionnaire.
     * @param prenom Le prénom du gestionnaire.
     */
    void setPrenom(const QString& prenom);


    // Getters
    /**
     * @brief Obtient le nom du gestionnaire.
     * @return Le nom du gestionnaire.
     */
    QString getNom();

    /**
     * @brief Obtient le prénom du gestionnaire.
     * @return Le prénom du gestionnaire.
     */
    QString getPrenom();

    /**
     * @brief Obtient le compte d'un client.
     * @param client Le client dont on veut obtenir le compte.
     * @return Le numéro de compte du client.
     */
    qint64 getCompte(Client *client);

    /**
     * @brief Obtient la liste des comptes d'un client.
     * @param client Le client dont on veut obtenir les comptes.
     * @return La liste des comptes du client.
     */
    QList<CompteBancaire *> getComptes(Client *client);

    /**
     * @brief Obtient la liste de tous les comptes de la banque.
     * @return La liste de tous les comptes de la banque.
     */
    QList<CompteBancaire *> getListeComptes() const; // Déclaration de la méthode

    // Member functions
    /**
     * @brief Obtient le prochain identifiant de client disponible.
     * @return L'identifiant du prochain client.
     */
    qint64 obtenirProchainIdClient() const;

    /**
     * @brief Crée un nouveau client.
     * @param id L'identifiant du client.
     * @param nom Le nom du client.
     * @param prenom Le prénom du client.
     * @param dateNaissance La date de naissance du client.
     * @param adresse L'adresse du client.
     * @return Un pointeur vers le nouveau client créé.
     */
    Client *creerClient(qint64 id, QString nom, QString prenom, QDate dateNaissance, QString adresse);

    /**
    * @brief Ajoute un client à la liste des clients de la banque.
    * @param client Le client à ajouter.
    */
    void ajouterClient(Client *client);

    /**
    * @brief Supprime un client de la liste des clients de la banque.
    * @param client Le client à supprimer.
    */
    void supprimerClient(Client *client);

    /**
    * @brief Supprime un client de la liste des clients de la banque en utilisant son identifiant.
    * @param idClient L'identifiant du client à supprimer.
    */
    void supprimerClient(qint64 idClient);

    /**
    * @brief Recherche un client dans la liste des clients de la banque en utilisant son identifiant.
    * @param id L'identifiant du client à rechercher.
    * @return Un pointeur vers le client trouvé, ou nullptr s'il n'est pas trouvé.
    */
    Client *trouverClientParId(qint64 id) const;

    /**
    * @brief Crée un compte pour un client avec un montant initial donné.
    * @param client Le client pour lequel créer le compte.
    * @param montantInitial Le montant initial à déposer sur le compte.
    * @return Un pointeur vers le compte bancaire créé.
    */
    CompteBancaire *creerComptePourClient(Client *client, double montantInitial);

    /**
    * @brief Ajoute un compte à la liste des comptes de la banque.
    * @param compte Le compte à ajouter.
    */
    void ajouterCompte(CompteBancaire *compte);

    /**
    * @brief Supprime un compte de la liste des comptes de la banque.
    * @param compte Le compte à supprimer.
    */
    void supprimerCompte(CompteBancaire *compte);

    /**
    * @brief Obtient le nombre de comptes d'un client.
    * @param client Le client dont on veut obtenir le nombre de comptes.
    * @return Le nombre de comptes du client.
    */
    int getNombreComptes(Client* client) const;

    /**
    * @brief Effectue un virement d'un compte source vers un compte destination avec un montant donné.
    * @param source Le compte source à partir duquel effectuer le virement.
    * @param destination Le compte destination vers lequel effectuer le virement.
    * @param montant Le montant à transférer.
    * @return true si le virement a été effectué avec succès, sinon false.
    */
    bool effectuerVirement(CompteBancaire *source, CompteBancaire *destination, double montant);

    /**
    * @brief Retourne une liste des noms des clients de la banque.
    * @return Une liste contenant les noms des clients de la banque.
    */
    QStringList listeClients() const;

    /**
    * @brief Retourne une liste des pointeurs vers les clients de la banque.
    * @return Une liste contenant les pointeurs vers les clients de la banque.
    */
    QList<Client*> listeClients1() const;

    /**
    * @brief Affiche les informations des clients de la banque sous forme graphique.
    */
    void afficherClientGraphique() const;

    /**
    * @brief Affiche les informations des clients de la banque.
    */
    void afficherClients() const;

    /**
    * @brief Affiche les informations des comptes de la banque.
    */
    void afficherComptes();


    /**
    * @brief Charge les clients à partir d'un fichier texte spécifié.
    * @param chemin_fichier Le chemin vers le fichier texte contenant les clients.
    * @return true si le chargement a été effectué avec succès, sinon false.
    */
    bool chargerClientsDepuisTXT(const QString& chemin_fichier);

    /**
    * @brief Sauvegarde les clients dans un fichier texte spécifié.
    * @param cheminFichier Le chemin du fichier où sauvegarder les clients.
    * @return true si la sauvegarde a été effectuée avec succès, sinon false.
    */
    bool sauvegarderClientsDansTXT(const QString& cheminFichier);

    /**
    * @brief Vérifie si un client existe déjà dans un fichier texte spécifié.
    * @param client Le client à rechercher.
    * @param cheminFichier Le chemin du fichier où vérifier l'existence du client.
    * @return true si le client existe dans le fichier, sinon false.
    */
    bool clientExisteDansFichier(Client* client, const QString& cheminFichier);

    /**
    * @brief Sauvegarde les comptes dans un fichier texte spécifié.
    * @param cheminFichier Le chemin du fichier où sauvegarder les comptes.
    * @return true si la sauvegarde a été effectuée avec succès, sinon false.
    */
    bool sauvegarderComptesDansTXT(const QString& cheminFichier);

    /**
    * @brief Charge les comptes à partir d'un fichier texte spécifié.
    * @param cheminFichier Le chemin vers le fichier texte contenant les comptes.
    * @return true si le chargement a été effectué avec succès, sinon false.
    */
    bool chargerComptesDepuisTXT(const QString& cheminFichier);

    /**
    * @brief Met à jour le fichier de comptes avec les informations actuelles.
    * @param cheminFichier Le chemin du fichier de comptes à mettre à jour.
    * @return true si la mise à jour a été effectuée avec succès, sinon false.
    */
    bool miseAJourFichierComptes(const QString& cheminFichier);

    /**
    * @brief Vérifie si un identifiant et un mot de passe correspondent à ceux du gestionnaire de banque.
    * @param identifiant L'identifiant à vérifier.
    * @param motDePasse Le mot de passe à vérifier.
    * @return true si l'identifiant et le mot de passe sont corrects, sinon false.
    */
    bool verifierIdentifiant(QString identifiant, QString motDePasse) const;


};

#endif
