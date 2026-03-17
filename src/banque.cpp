#include "banque.h"
#include "accueil_gestionnaire.h"
#include "ui_banque.h"
#include "creer_gestionnaire.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>




GestionnaireBanque gestionnaireBanque("NomGestionnaire", "PrenomGestionnaire");

Banque::Banque(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Banque)
{
    ui->setupUi(this);

    connect(ui->connection, &QPushButton::clicked, this, &Banque::verifierIdentite);
    connect(ui->creer, &QPushButton::clicked, this, &Banque::afficherPageCreation);

}



Banque::~Banque()
{
    delete ui;
}


void Banque::afficherPageCreation(){
    // Créer une instance de la page de création de compte
    creer_gestionnaire *pageCreation = new creer_gestionnaire(this);
    // Afficher la fenêtre modale de création de compte
    pageCreation->exec();
}



void Banque::verifierIdentite()
{
    // Obtenir l'identifiant et le mot de passe saisis par l'utilisateur

    QString identifiant = ui->identifiant->text();
    QString motDePasse = ui->mdp->text();

    // Ouvrir le fichier texte contenant les identifiants et les mots de passe
    QFile file("C:/Users/damie/OneDrive/Documents/comptes_gestionnaire.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier.";
        return;
    }

    QTextStream in(&file);
    bool identifiantsCorrects = false;
    QString nomGestionnaire;
    QString prenomGestionnaire;

    // Parcourir le fichier pour vérifier les identifiants et les mots de passe
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList tokens = line.split(";"); // Supposons que les données sont séparées par des points-virgules

        // Vérifier si l'identifiant et le mot de passe correspondent
        if (tokens.size() >= 4 && tokens[0] == identifiant && tokens[1] == motDePasse) {
            identifiantsCorrects = true;
            nomGestionnaire = tokens[2];
            prenomGestionnaire = tokens[3];
            break;
        }
    }

    file.close();

    if (identifiantsCorrects) {
        // Les identifiants sont corrects, initialiser le gestionnaire avec le nom et le prénom
        gestionnaireBanque.setNom(nomGestionnaire);
        gestionnaireBanque.setPrenom(prenomGestionnaire);

        // Ouvrir la fenêtre d'accueil du gestionnaire avec le gestionnaire initialisé
        this->close();
        Accueil_gestionnaire* Page_accueil= new Accueil_gestionnaire(&gestionnaireBanque, nomGestionnaire, this);
        Page_accueil->show();
        qDebug() << "Identifiants corrects. Connexion réussie.";
    } else {
        // Les identifiants sont incorrects, vous pouvez afficher un message d'erreur.
        qDebug() << "Identifiants incorrects. Connexion échouée.";
        QMessageBox msgBox;
        msgBox.setText("Identifiant ou mot de passe incorrects. Veuillez réessayer.");
        // Définir la feuille de style pour changer la couleur du texte
        msgBox.setStyleSheet("QLabel{ color : red; }");
        msgBox.exec();
    }
}
