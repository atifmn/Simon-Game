/**
 * The model of the Simon Game application.
 *
 * Atif Memon and Gus Daskalakis
 * 2025-3-5
 */
#include "model.h"
#include <QRandomGenerator>
#include <QTimer>

Model::Model(QObject *parent)
    : QObject{parent}, playerPos(0), playerTurn(false), flashTime(700)
    // Sets playerPos to 0, playerTurn to false and sets the starting flash delay to 700
{}

void Model::startGame(){
    sequence.clear(); // Clears seqeuence for new round

    playerTurn = false;
    playerPos = 0;
    flashTime = 700;

    emit enableButtons(false);
    emit setStartButton(false);
    emit updatePercentageBar(0);

    computerTurn();
}

void Model::checkButtonPress(int color){
    // If it is NOT the players turn, end the check
    if (!playerTurn){
        return;
    }

    int sequenceSize = sequence.size();

    // If the player clicks the current button on the round, increment and update progress bar
    if (sequence[playerPos] == color){

        playerPos++;
        emit updatePercentageBar((100 * playerPos)/sequenceSize);

        // If player reaches the end of the seqeunce (clicks all buttons correctly) then start the computers turn
        if (playerPos == sequenceSize){
            playerTurn = false;
            emit enableButtons(false);

            // At the end of the sequence, the flash Time is reduced to increase round speed
            // until it reaches 300, where the speed will then remain the same (very fast)
            if (flashTime > 300){
                flashTime -= 40;
            }

            // QTimer, waits to start the computerTurn after the Timer has ended
            QTimer::singleShot(550, this, [this]() {
                computerTurn();
            });
        }
    }
    // If the player presses the wrong button, end the round and send the lose game message
    else {
        playerTurn = false;
        emit loseGame();
    }
}

void Model::addMove(){
    // Randomly pick between 0 (red) or 1 (blue) and add it to the sequence
    int value = QRandomGenerator::global() -> bounded(2);
    sequence.push_back(value);
}

void Model::computerTurn(){
    playerTurn = false;
    playerPos = 0;

    emit enableButtons(false);
    emit setStartButton(false);
    emit updatePercentageBar(0);

    addMove();

    // QTimer which starts the flash seqeuence after a slight delay
    QTimer::singleShot(400, this, [this]() {
        flashSequence(0);
    });
}

void Model::flashSequence(int index){

    // If the index had passed the size of the sequence, then start the players turn after a delay and return
    if (index >= (int) sequence.size()){
        // QTimer which delays the start of the player turn
        QTimer::singleShot(100, this, [this]() {
            startPlayerTurn();
        });
        return;

    } else {

        // If current seqeuence color is red (0) flash red
        if (sequence[index] == 0){

            emit flashRedButton();
        }

        // Else, flash blue
        else {
            emit flashBlueButton();
        }

        // QTimer which leaves a pause between each flash before going to the next index in the sequence vector
        QTimer::singleShot(flashTime, this, [this, index]() {
            flashSequence(index + 1);
        });

    }
}


void Model::startPlayerTurn(){
    playerTurn = true;
    playerPos = 0;

    emit enableButtons(true);
    emit setStartButton(false);
}
