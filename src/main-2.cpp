#include "banque.h"
#include <iostream>

#include <QApplication>
#include "banqueappli.h"
using namespace std;


int main(int argc, char *argv[])
{

    //Banque1 maBanque("NomGestionnaire", "PrenomGestionnaire");
    QApplication a(argc, argv);
    Banque b;
    b.show();


    //maBanque.run();
    return a.exec();
    //return 0;
}
