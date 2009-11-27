#include <QApplication>
#include "setgametable.h"
#include "setcard.h"
#include <time.h>

int main(int argc, char* argv[])
{
    /* initialize random seed: */
    srand ( time(NULL) );
    // qt...
    QApplication cApp(argc, argv);
    SetGameTable wdgTable;
    wdgTable.show();
    return cApp.exec();
}
