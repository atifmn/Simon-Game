/**
 * The Simon game view header of the Simon Game application.
 *
 * Atif Memon and Gus Daskalakis
 * 2025-3-5
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSoundEffect>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * MainWindow class, used as both the View/Controller for the Simon Game
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * Constructor for MainWindow, initializes a model obect and a QObject
     * @param model: Model object to be used
     * @param parent: QObject parent to be used
     */
    explicit MainWindow(Model* model, QWidget *parent = nullptr);

    // Destructor for MainWindow class
    ~MainWindow() override;

public slots:

    /**
     * Shows the message and disables any buttons requried for when
     * the game is lost
     */
    void loseGameMessage();

    /**
     * Flashes the red button during a sequence
     */
    void flashRed();

    /**
     * Flashes the blue button during a sequence
     */
    void flashBlue();

    /**
     * Enables/disables both red and blue buttons based on the parameter input
     * @param enable: True if both buttons are to be enabled, false if both become disabled
     */
    void enableButtons(bool enable);

    /**
     * Enables/disables the Start Game button based on the parameter input
     * @param enable: True if the buttons is to be enabled, false if it becomes disabled
     */
    void enableStartButton(bool enable);

    /**
     * Calls the play() method to start the main theme music for the
     * simon game (custom feature)
     */
    void playMusic();

private:
    // ui object
    Ui::MainWindow *ui;

    // Media player object plays main theme music
    QMediaPlayer mediaPlayer;

    // AudioOutput object, used for mediaPlayer
    QAudioOutput audioPlayer;

    // SoundEffect object, used for the lose game sound effect
    QSoundEffect loseSoundEffect;
};
#endif // MAINWINDOW_H
