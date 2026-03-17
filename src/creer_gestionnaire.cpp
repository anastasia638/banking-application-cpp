#include "creer_gestionnaire.h"
#include "ui_creer_gestionnaire.h"
#include <QFile>
#include <QMessageBox>

creer_gestionnaire::creer_gestionnaire(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::creer_gestionnaire)
{
    ui->setupUi(this);
    connect(ui->creation, &QPushButton::clicked, this, [this]() {
        // Récupérer les données depuis les champs d'entrée
        QString identifiant = ui->identifiant->text();
        QString motDePasse = ui->mdp->text();
        QString nom = ui->nom->text();
        QString prenom = ui->prenom->text();

        // Appeler la fonction pour écrire dans le fichier avec les données récupérées
        ecrireDansFichier(identifiant, motDePasse, nom, prenom);
    });
}


creer_gestionnaire::~creer_gestionnaire()
{
    delete ui;
}


void creer_gestionnaire::ecrireDansFichier(const QString& identifiant, const QString& motDePasse, const QString& nom, const QString& prenom) {
    QFile file("C:/Users/damie/OneDrive/Documents/comptes_gestionnaire.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier.";
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier.");
        return;
    }

    QTextStream out(&file);
    out << identifiant << ";" << motDePasse << ";" << nom << ";" << prenom << "\n";
    file.close();

    QMessageBox::information(this, "Succès", "Le gestionnaire a été créé avec succès.");
    this->close(); // Ferme la page de création une fois terminée
}

