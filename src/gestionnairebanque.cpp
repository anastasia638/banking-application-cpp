#include "gestionnairebanque.h"
#include "client.h"
#include "comptebancaire.h"
#include <QtGlobal>
#include <QDebug>
#include <QRandomGenerator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtSql>
#include <QFile>
#include <QTextStream>


using namespace std;

GestionnaireBanque::GestionnaireBanque(QString nom, QString prenom) : nom(nom), prenom(prenom)
{
    identifiant = nom;
    mot_de_passe = nom;
    // Initialisation des coordonées du Gestionnaire
}

GestionnaireBanque::~GestionnaireBanque()
{
    // Libération des clients
    for (Client *client : clients)
    {
        delete client;
    }
    clients.clear();

    // Libération des comptes bancaires
    for (CompteBancaire *compte : comptes)
    {
        delete compte;
    }
    comptes.clear();
}

// Implémentation de la méthode setNom
void GestionnaireBanque::setNom(const QString& nom) {
    this->nom = nom;
}

// Implémentation de la méthode setNom
void GestionnaireBanque::setPrenom(const QString& prenom) {
    this->prenom = prenom;
}





QString GestionnaireBanque::getNom()
{
    return nom;
}

QString GestionnaireBanque::getPrenom()
{
    return prenom;
}

qint64 GestionnaireBanque::getCompte(Client *client)
{
    // Parcourez la liste des comptes et trouvez le numéro de compte du client
    for (CompteBancaire *compte : comptes)
    {
        if (compte->getProprietaire() == *client)
        {
            // Retournez le numéro de compte s'il correspond au client donné
            return compte->getNumeroCompte();
        }
    }

    // Si aucun compte correspondant au client n'est trouvé, retournez -1 ou une autre valeur d'erreur
    qDebug() << "Aucun compte trouvé pour le client";
    return -1; // Vous pouvez également retourner une autre valeur d'erreur selon votre logique
}

QList<CompteBancaire *> GestionnaireBanque::getComptes(Client *client)
{
    QList<CompteBancaire *> comptesClient;

    // Parcourir la liste des comptes et ajouter ceux qui appartiennent au client donné
    for (CompteBancaire *compte : comptes)
    {
        if (compte->getProprietaire() == *client)
        {
            comptesClient.append(compte);
        }
    }

    return comptesClient;
}

QList<CompteBancaire *> GestionnaireBanque::getListeComptes() const
{
    return comptes; // Supposons que 'comptes' soit le conteneur contenant tous les comptes
}

qint64 GestionnaireBanque::obtenirProchainIdClient() const
{
    // Recherche de l'ID client maximum et incrémentation de 1
    qint64 maxId = 0;
    for (Client *client : clients) {
        if (client->getId() > maxId) {
            maxId = client->getId();
        }
    }
    return maxId + 1; // Retourne le prochain ID client
}

Client *GestionnaireBanque::creerClient(qint64 id, QString nom, QString prenom, QDate dateNaissance, QString adresse)
{
    // Création d'une nouvelle instance de client
    //qint64 randomNumber = QRandomGenerator::global()->bounded(1000);
    Client *nouveauClient = new Client(id, nom, prenom, dateNaissance, adresse);
    ajouterClient(nouveauClient); // Le nouveau client est automatiquement ajouté à la liste répertoriant l'intégralité des clients.
    return nouveauClient;
}

void GestionnaireBanque::ajouterClient(Client *client)
{
    clients.append(client);
}

void GestionnaireBanque::supprimerClient(qint64 idClient) {
    // Trouver le client avec l'ID spécifié
    Client* client = trouverClientParId(idClient);
    if (client) {
        // Supprimer le client de la liste
        clients.removeOne(client);
        delete client; // Libérer la mémoire allouée au client
        qDebug() << "Client supprimé avec succès.";
    } else {
        qDebug() << "Client non trouvé.";
    }
}

void GestionnaireBanque::supprimerClient(Client *client)
{
    clients.removeOne(client);
    delete client; // Supprimer l’objet client de la mémoire
}

CompteBancaire *GestionnaireBanque::creerComptePourClient(Client *client, double montantInitial)
{
    // Crée un nouveau compte pour le client
    qint64 randomNumber = QRandomGenerator::global()->bounded(1000);
    CompteBancaire *nouveauCompte = new CompteBancaire(randomNumber, montantInitial, *client);
    ajouterCompte(nouveauCompte); // Ajoute automatiquement le nouveau compte à la liste
    return nouveauCompte;
}

void GestionnaireBanque::ajouterCompte(CompteBancaire *compte)
{
    comptes.append(compte);
}

void GestionnaireBanque::supprimerCompte(CompteBancaire *compte)
{
    comptes.removeOne(compte);
    delete compte;
}

bool GestionnaireBanque::effectuerVirement(CompteBancaire *source, CompteBancaire *destination, double montant)
{

    QSqlDatabase::database().transaction();
    // Verification du solde avant l'exécution du processus

    if (source->getSolde() < montant)
    {
        qDebug() << " Erreur : Le solde de votre compte est insuffisant.";
        return false;
    } // Note : On pourrait également faire un assert

    // Effectue un retrait du compte source

    source->retirerArgent(montant);

    // Effectue un dépot dans le compte destinataire

    destination->deposerArgent(montant);

    QSqlDatabase::database().commit();
    qDebug() << " Le virement a été effectué.";
    return true;
}


int GestionnaireBanque::getNombreComptes(Client* client) const {
    int compteCount = 0;
    // Parcourir la liste des comptes et compter ceux qui appartiennent au client donné
    for (CompteBancaire* compte : comptes) {
        if (compte->getProprietaire() == *client) {
            compteCount++;
        }
    }
    return compteCount;
}


QStringList GestionnaireBanque::listeClients() const
{
    QStringList liste;
    for (Client *client : clients)
    {
        QString infoClient = QString("ID: %1, Nom: %2, Prénom: %3, Date de naissance: %4, Adresse: %5")
                                 .arg(client->getId())
                                 .arg(client->getNom())
                                 .arg(client->getPrenom())
                                 .arg(client->getDateNaissance().toString("yyyy-MM-dd"))
                                 .arg(client->getAdresse());
        liste.append(infoClient);
    }
    return liste;
}

QList<Client*> GestionnaireBanque::listeClients1() const
{
    QList<Client*> liste;
    for (Client *client : clients)
    {
        liste.append(client);
    }
    return liste;
}


void GestionnaireBanque::afficherClientGraphique() const
{
    QStringList listeClients;
    for (Client *client : clients)
    {
        QString infoClient = QString("ID: %1, Nom: %2, Prénom: %3, Date de naissance: %4, Adresse: %5")
                                 .arg(client->getId())
                                 .arg(client->getNom())
                                 .arg(client->getPrenom())
                                 .arg(client->getDateNaissance().toString("yyyy-MM-dd"))
                                 .arg(client->getAdresse());
        listeClients.append(infoClient);
    }
    qDebug() << "Liste des Clients : " << listeClients;
}


void GestionnaireBanque::afficherClients() const
{
    qDebug() << "Liste des Clients : "
             << "\n"
             << " ";
    for (Client *client : clients)
    {
        qDebug() << "ID:" << client->getId()
                 << "Nom:" << client->getNom()
                 << "Prénom:" << client->getPrenom()
                 << "Date de naissance:" << client->getDateNaissance().toString("yyyy-MM-dd")
                 << "Adresse:" << client->getAdresse();
    }
}
void GestionnaireBanque::afficherComptes()
{
    qDebug() << "List des comptes : "
             << "\n"
             << " ";

    for (CompteBancaire *compte : comptes)
    {
        qDebug() << "Numéro:" << compte->getNumeroCompte() << "Solde:" << compte->getSolde() << "\n"
                 << " ";
    }
}


bool GestionnaireBanque::chargerClientsDepuisTXT(const QString& cheminFichier) {
    QFile file(cheminFichier);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier" << cheminFichier;
        return false;
    }

    // Ignorer la première ligne (en-tête)
    file.readLine();

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList data = line.split(";");
        if (data.size() != 5) {
            qDebug() << "Erreur : Ligne invalide dans le fichier" << cheminFichier << ". Ligne ignorée :" << line;
            continue;
        }
        qint64 id = data[0].toLongLong();
        QString nom = data[1];
        QString prenom = data[2];
        QDate dateNaissance = QDate::fromString(data[3], "yyyy-MM-dd");
        QString adresse = data[4];

        // Vérifier si le client existe déjà dans le gestionnaire
        bool clientExiste = false;
        for (Client* client : clients) {
            if (client->getId() == id) {
                clientExiste = true;
                break;
            }
        }

        if (clientExiste) {
            qDebug() << "Client avec ID" << id << "existe déjà. Ignoré.";
            continue;
        }

        // Créer le client à partir des données et l'ajouter à la liste des clients
        ajouterClient(new Client(id, nom, prenom, dateNaissance, adresse));
    }
    file.close();
    return true;
}


bool GestionnaireBanque::chargerComptesDepuisTXT(const QString& cheminFichier) {
    QFile file(cheminFichier);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier" << cheminFichier << "pour la lecture.";
        return false;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();

        // Analyser chaque ligne pour extraire les données des comptes
        // Vous devez mettre en œuvre votre propre logique d'analyse des données en fonction du format de votre fichier texte
        // Par exemple, vous pouvez utiliser des expressions régulières ou des fonctions de découpage de chaîne pour extraire les données

        // Exemple de logique pour analyser une ligne et extraire les données des comptes
        QStringList tokens = line.split(";"); // Supposons que les données sont séparées par des points-virgules
        if (tokens.size() >= 4) {
            qint64 idClient = tokens[0].toLongLong();
            QString nomClient = tokens[1];
            qint64 numeroCompte = tokens[2].toLongLong();
            double solde = tokens[3].toDouble();

            // Vérifier si le compte existe déjà dans le gestionnaire
            bool compteExisteDeja = false;
            for (CompteBancaire* compte : comptes) {
                if (compte->getNumeroCompte() == numeroCompte) {
                    compteExisteDeja = true;
                    break;
                }
            }

            // Si le compte n'existe pas déjà, l'ajouter au gestionnaire
            if (!compteExisteDeja) {
                Client* client = trouverClientParId(idClient); // Vous devez avoir une méthode pour trouver un client par son ID
                if (client) {
                    ajouterCompte(new CompteBancaire(numeroCompte, solde, *client)); // Supposons que votre classe GestionnaireBanque a une méthode ajouterCompte
                } else {
                    qDebug() << "Client introuvable pour le compte avec l'ID :" << idClient;
                }
            } else {
                qDebug() << "Le compte avec le numéro :" << numeroCompte << "existe déjà dans le gestionnaire.";
            }
        }
    }

    file.close();
    qDebug() << "Chargement des comptes terminé avec succès depuis le fichier" << cheminFichier;
    return true;
}



bool GestionnaireBanque::sauvegarderClientsDansTXT(const QString& cheminFichier) {
    QFile file(cheminFichier);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier" << cheminFichier << "pour l'écriture.";
        return false;
    }

    QTextStream out(&file);

    // Parcourir la liste des clients et écrire leurs données dans le fichier
    for (Client* client : clients) {
        // Vérifier si le client existe déjà dans le fichier
        if (clientExisteDansFichier(client, cheminFichier)) {
            qDebug() << "Le client avec l'ID" << client->getId() << "existe déjà dans le fichier. Ignoré.";
            continue;
        }

        out << client->getId() << ";"
            << client->getNom() << ";"
            << client->getPrenom() << ";"
            << client->getDateNaissance().toString("yyyy-MM-dd") << ";"
            << client->getAdresse() << "\n";
    }

    file.close();
    qDebug() << "Données des clients sauvegardées avec succès dans le fichier" << cheminFichier;
    return true;
}

bool GestionnaireBanque::sauvegarderComptesDansTXT(const QString& cheminFichier) {
    QFile file(cheminFichier);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier" << cheminFichier << "pour l'écriture.";
        return false;
    }

    QTextStream out(&file);

    // Liste pour stocker les numéros de compte déjà écrits
    QSet<qint64> numerosDeCompteEcrits;

    // Parcourir la liste des comptes et écrire leurs données dans le fichier
    for (CompteBancaire* compte : comptes) {
        // Vérifier si le numéro de compte a déjà été écrit
        if (numerosDeCompteEcrits.contains(compte->getNumeroCompte())) {
            continue;  // Passer au prochain compte si le numéro de compte existe déjà dans la liste
        }

        // Ajouter le numéro de compte à la liste des numéros déjà écrits
        numerosDeCompteEcrits.insert(compte->getNumeroCompte());

        out << compte->getProprietaire().getId() << ";"
            << compte->getProprietaire().getNom() << ";"
            << compte->getNumeroCompte() << ";"
            << compte->getSolde() << "\n";
    }

    file.close();
    qDebug() << "Comptes sauvegardés avec succès dans le fichier" << cheminFichier;
    return true;
}


bool GestionnaireBanque::miseAJourFichierComptes(const QString& cheminFichier) {
    QFile file(cheminFichier);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier" << cheminFichier << "pour l'écriture.";
        return false;
    }

    QTextStream out(&file);

    // Parcourir la liste des comptes et écrire leurs données dans le fichier
    for (CompteBancaire* compte : comptes) {
        out << compte->getProprietaire().getId() << ";"
            << compte->getProprietaire().getNom() << ";"
            << compte->getNumeroCompte() << ";"
            << compte->getSolde() << "\n";
    }

    file.close();
    qDebug() << "Données des comptes mises à jour avec succès dans le fichier" << cheminFichier;
    return true;
}


bool GestionnaireBanque::clientExisteDansFichier(Client* client, const QString& cheminFichier) {
    QFile file(cheminFichier);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier" << cheminFichier << "pour la lecture.";
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList data = line.split(";");
        if (data.size() != 5) {
            qDebug() << "Erreur : Ligne invalide dans le fichier" << cheminFichier << ". Ligne ignorée :" << line;
            continue;
        }
        qint64 id = data[0].toLongLong();
        if (id == client->getId()) {
            file.close();
            return true; // Le client existe déjà dans le fichier
        }
    }

    file.close();
    return false; // Le client n'existe pas dans le fichier
}

Client *GestionnaireBanque::trouverClientParId(qint64 id) const
{
    for (Client *client : clients)
    {
        if (client->getId() == id)
        {
            return client;
        }
    }
    return nullptr;
}

bool GestionnaireBanque::verifierIdentifiant(QString identifiant, QString motDePasse) const
{
    return (this->identifiant == identifiant && this->mot_de_passe == motDePasse);
}
