#include "sup_client.h"
#include "ui_sup_client.h"
#include <QMessageBox>
#include <QFile>

Sup_client::Sup_client(GestionnaireBanque* gestionnaire, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Sup_client) , gestionnaireBanque(gestionnaire)
{
    ui->setupUi(this);
    connect(ui->Valider, &QPushButton::clicked, this, &Sup_client::supprimerClient);
}

Sup_client::~Sup_client()
{
    delete ui;
}

void Sup_client::supprimerClient() {
    // Obtenir l'ID du client à supprimer depuis l'interface utilisateur
    qint64 idClient = ui->ID->text().toLongLong();

    // Appeler la fonction de suppression dans le gestionnaire de banque
    gestionnaireBanque->supprimerClient(idClient);

    // Supprimer les données du client du fichier texte
    if (supprimerClientDuFichier(idClient)) {
        // Afficher un message de confirmation si la suppression du client du fichier texte réussit
        QMessageBox::information(this, "Suppression", "Le client a été supprimé avec succès.");
    } else {
        // Afficher un message d'erreur si la suppression du client du fichier texte échoue
        QMessageBox::warning(this, "Erreur", "Erreur lors de la suppression du client du fichier texte.");
    }

    // Rafraîchir l'affichage des clients si nécessaire

    // Fermer la fenêtre actuelle
    this->close();
}

bool Sup_client::supprimerClientDuFichier(qint64 idClient) {
    const QString cheminFichier = "C:/Users/damie/OneDrive/Documents/clients.txt";
    QFile file(cheminFichier);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier" << cheminFichier << "pour la lecture.";
        return false;
    }

    // Lire le contenu du fichier dans une liste
    QStringList lines;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList data = line.split(";");
        if (data.size() != 5) {
            qDebug() << "Erreur : Ligne invalide dans le fichier" << cheminFichier << ". Ligne ignorée :" << line;
            continue;
        }
        qint64 id = data[0].toLongLong();
        if (id != idClient) {
            lines.append(line); // Ajouter la ligne au contenu à conserver
        }
    }
    file.close();

    // Écrire le contenu mis à jour dans le fichier
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier" << cheminFichier << "pour l'écriture.";
        return false;
    }
    QTextStream out(&file);
    for (const QString& line : lines) {
        out << line << "\n";
    }
    file.close();

    qDebug() << "Données du client supprimées avec succès du fichier" << cheminFichier;
    return true;
}
