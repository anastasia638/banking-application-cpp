#ifndef SAUVER_CHARGER_H
#define SAUVER_CHARGER_H

#include <QDialog>
#include "gestionnairebanque.h"

namespace Ui {
class sauver_charger;
}

class sauver_charger : public QDialog
{
    Q_OBJECT

public:
    explicit sauver_charger(GestionnaireBanque* gestionnaire,QWidget *parent = nullptr);
    ~sauver_charger();
    void peuplerGestionnaireDeClients();
    void sauvegarderClients() ;

private:
    Ui::sauver_charger *ui;
     GestionnaireBanque* gestionnaireBanque;
};

#endif // SAUVER_CHARGER_H
