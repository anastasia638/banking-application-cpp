#include "banqueappli.h"

#include "banque.h"
#include <QDebug>
#include <QTextStream>
#include <iostream>

using namespace std;

Banque1::Banque1(QString nomGestionnaire, QString prenomGestionnaire, QObject *parent)
    : QObject(parent), gestionnaireBanque(nomGestionnaire, prenomGestionnaire)
{
    run();
}

Banque1::~Banque1() {
    // Nettoyage si nécessaire
}



void Banque1::run() {


    QTextStream stream(stdin);
    bool continuer = true;
    do {
        qInfo() << "Gestionnaire : " << gestionnaireBanque.getNom() << " " << gestionnaireBanque.getPrenom();
        qInfo() << "Que souhaitez-vous faire ?";
        qInfo() << "1. Ajouter un client";
        qInfo() << "2. Supprimer un client";
        qInfo() << "3. Créer un compte pour un client";
        qInfo() << "4. Supprimer un compte";
        qInfo() << "5. Effectuer un virement";
        qInfo() << "6. Afficher la liste des clients";
        qInfo() << "7. Afficher la liste des comptes";
        qInfo() << "8. Sauvegarder les données dans la base de données";
        qInfo() << "9. Charger les données depuis la base de données";
        //qInfo() << "11. Ajouter de l'argent dans le compte";
        qInfo() << "10. Quitter";


        cout << "Entrez votre choix : ";
        int choix;
        cin >> choix;
        cin.ignore();

        switch (choix) {
        case 1: {
            // Ajouter un client
            QString nom, prenom, adresse;
            QDate dateNaissance;
            qInfo() << "Entrez le nom du client :";
            nom = stream.readLine();
            qInfo() << "Entrez le prenom du client :";
            prenom = stream.readLine();
            qInfo() << "Entrez la date de naissance du client (format : YYYY-MM-DD) :";
            QString dateString = stream.readLine();
            dateNaissance = QDate::fromString(dateString, "yyyy-MM-dd");
            qInfo() << "Entrez l'adresse du client :";
            adresse = stream.readLine();
            qint64 ID = gestionnaireBanque.obtenirProchainIdClient();
            gestionnaireBanque.creerClient(ID, nom, prenom, dateNaissance, adresse);
            break;
        }
        case 2: {
            // Supprimer un client
            qInfo() << "Entrez l'ID du client a supprimer :";
            qint64 idClient;
            stream >> idClient;
            Client* client = gestionnaireBanque.trouverClientParId(idClient);
            if (client) {
                gestionnaireBanque.supprimerClient(client);
            } else {
                qInfo() << "Client non trouve.";
            }
            break;
        }
        case 3: {
            // Creer un compte pour un client
            qInfo() << "Entrez l'ID du client :";
            qint64 idClient;
            stream >> idClient;
            Client* client = gestionnaireBanque.trouverClientParId(idClient);
            if (client) {
                qInfo() << "Entrez le montant initial à déposer sur le compte :";
                double montantInitial;
                stream >> montantInitial;
                gestionnaireBanque.creerComptePourClient(client,  montantInitial);
            } else {
                qInfo() << "Client non trouve.";
            }
            break;
        }
        case 4: {
            // Supprimer un compte
            qInfo() << "Entrez l'ID du client associe au compte a supprimer :";
            qint64 idClient;
            stream >> idClient;
            Client* client = gestionnaireBanque.trouverClientParId(idClient);
            if (client)
            {
                QList<CompteBancaire*> comptesClient = gestionnaireBanque.getComptes(client);
                CompteBancaire* compteASupprimer = nullptr;
                for (CompteBancaire* compte : comptesClient) {
                    if (compte->getProprietaire().getId() == idClient) {
                        compteASupprimer = compte;
                        break;
                    }
                }
                if (compteASupprimer) {
                    gestionnaireBanque.supprimerCompte(compteASupprimer);
                    qInfo() << "Compte supprime avec succes.";
                } else {
                    qInfo() << "Aucun compte associe a ce client.";
                }
            }
            else
            {
                qInfo() << "Client non trouve.";
            }
            break;
        }
        case 5: {
            // Effectuer un virement
            qInfo() << "Entrez le numero de compte source :";
            qint64 numeroSource;
            stream >> numeroSource;
            qInfo() << "Entrez le numero de compte destination :";
            qint64 numeroDestination;
            stream >> numeroDestination;
            qInfo() << "Entrez le montant :";
            double montant;
            stream >> montant;
            CompteBancaire* source = nullptr;
            CompteBancaire* destination = nullptr;

            QList<CompteBancaire*> comptes = gestionnaireBanque.getListeComptes();
            for (CompteBancaire* compte : comptes) {
                if (compte->getNumeroCompte() == numeroSource) {
                    source = compte;
                }
                if (compte->getNumeroCompte() == numeroDestination) {
                    destination = compte;
                }
            }

            if (source && destination) {
                gestionnaireBanque.effectuerVirement(source, destination, montant);
            } else {
                qInfo() << "Comptes non trouves.";
            }
            break;
        }
        case 6: {
            // Afficher la liste des clients
            gestionnaireBanque.afficherClients();
            break;
        }
        case 7: {
            // Afficher la liste des comptes
            gestionnaireBanque.afficherComptes();
            break;
        }
        case 8: {
            // Sauvegarder les donnees dans la base de donnees
            //gestionnaireBanque.sauverEnBD();
            break;
        }
        case 9: {
            // Charger les donnees depuis la base de donnees
           // gestionnaireBanque.chargerDepuisBD();
            break;
        }
        case 10: {
            // Quitter
            continuer = false;
            break;
        }
        /*case 11: {
            // Ajouter de l'argent dans un compte
            QTextStream stream(stdin);
            gestionnaireBanque.afficherComptes();
            qInfo() << "Entrez le numéro de compte :";
            qint64 numeroCompte;
            stream >> numeroCompte;
            qInfo() << "Entrez le montant à ajouter :";
            double montant;
            stream >> montant;
            CompteBancaire* compte = gestionnaireBanque.trouverCompteParNumero(numeroCompte);
            if (compte) {
                gestionnaireBanque.ajouterArgent(compte, montant);
            } else {
                qInfo() << "Compte non trouvé.";
            }
            break;
        }*/
        default: {
            qInfo() << "Choix invalide. Veuillez choisir une option valide.";
            continuer=false;
            break;
        }
        }
    }while (continuer);
}
