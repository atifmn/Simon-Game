#ifndef MODEL_H
#define MODEL_H
/**
 * The logic/model header of the Simon Game application.
 *
 * Atif Memon and Gus Daskalakis
 * 2025-3-5
 */
#include <QObject>
#include <vector>

/**
 * The Model class which handles the logic and sequencing for the Simon Game
 */
class Model : public QObject
{
    Q_OBJECT

private:
    // Stores the sequence pattern for the simon game in this vector
    std::vector<int> sequence;

    // Holds players pos within that round for the sequence
    int playerPos;

    // Determines whether it is currently the players turn in the round
    bool playerTurn;

    int flashTime;

public:
    /**
     * Constructs the model
     * @param parent QObject parent
     */
    explicit Model(QObject *parent = nullptr);

private:
    /**
     * Adds a color to the sequence
     */
    void addMove();

    /**
     * Starts the computers turn, sets buttons and flashes sequence
     */
    void computerTurn();

    /**
     * Starts the players turn, sets button for player to give input
     */
    void startPlayerTurn();

    /**
     * Flashes sequence based on color order in the sequence vector, done recursively
     * @param index: Current index in the sequence vector for which color is flashed
     */
    void flashSequence(int index);

public slots:

    /**
     * Start/initializes the game.
     */
    void startGame();

    /**
     * Checks the button pressed to the sequence
     */
    void checkButtonPress(int color);

signals:
    /**
     * Emitted when the player inputted the wrong color and the game has been lost
     * and when the Game Over label must appear
     */
    void loseGame();

    /**
     * Emitted when red/blue button needs to be enabled
     */
    void enableButtons(bool enable);

    /**
     * Emitted when start game button needs to be enabled
     */
    void setStartButton(bool enable);

    /**
     * Emitted when the progress bar needs to be updated to fit current turn
     */
    void updatePercentageBar(int percentAmount);

    /**
     * Emitted when the redbutton needs to be flashed
     */
    void flashRedButton();

    /**
     * Emitted when the blueButton needs to be flashed
     */
    void flashBlueButton();
};

#endif // MODEL_H
