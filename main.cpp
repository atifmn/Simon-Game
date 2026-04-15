/**
 * The main file which runs the Simon Game
 *
 * Atif Memon and Gus Daskalakis
 * Github usernames: atifmn & vfiRepos (Gus Daskalakis)
 * https://github.com/UofU-CS3505/cs3505-assignment6-gusd21.git
 *
 * Creative element: Added multimedia within the game to have music playing during a round
 * of simon and a lose sound effect when the game has been lost
 *
 * 2025-3-5
 */
#include "mainwindow.h"
#include "model.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model model;
    MainWindow w(&model);
    w.show();
    return QCoreApplication::exec();
}
