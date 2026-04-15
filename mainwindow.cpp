/**
 * The Simon game view of the Simon Game application.
 *
 * Atif Memon and Gus Daskalakis
 * 2025-3-5
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(Model* model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mediaPlayer(new QMediaPlayer(this))
    , audioPlayer(new QAudioOutput(this))
    , loseSoundEffect(new QSoundEffect(this))
{
    ui->setupUi(this);

    // Connects the buttons to the model and signals

    // Connects startButton to startGame method in the model
    connect(ui->startButton,
            &QPushButton::clicked,
            model,
            &Model::startGame);

    // Connects redButton to checkButtonPress method in the model
    connect(ui->redButton,
            &QPushButton::clicked,
            this,
            [model]() { model->checkButtonPress(0); });

    // Connects blueButton to checkButtonPress method in the model
    connect(ui->blueButton,
            &QPushButton::clicked,
            this,
            [model]() { model->checkButtonPress(1); });

    // Connects startButton to the playMusic method in the View
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::playMusic);

    // Connects the percentage bar to the model, which is updated
    // whenever a new value is emitted
    connect(model,
            &Model::updatePercentageBar,
            ui->percentageBar,
            &QProgressBar::setValue);

    // Connects model to view

    // Connects the loseGame signal in the model to the loseGameMessage in the View
    connect(model, &Model::loseGame, this, &MainWindow::loseGameMessage);

    // Connects flashRedButton signal in the model to the flashRed method in the view
    connect(model, &Model::flashRedButton, this, &MainWindow::flashRed);

    // Connects flashBlueButton signal in the model to the flashBlue method in the view
    connect(model, &Model::flashBlueButton, this, &MainWindow::flashBlue);

    // Connects the enableButtons signal in the model to the enableButtons method in the view
    connect(model, &Model::enableButtons, this, &MainWindow::enableButtons);

    // Connects the setStartButton signal in the model to the enableStartButton method in the view
    connect(model, &Model::setStartButton, this, &MainWindow::enableStartButton);

    // Sets the colors for all of the buttons
    ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgba(200,50,50, 150);} QPushButton:pressed {background-color: rgb(255,0,0);}"));
    ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgba(50,50,200, 150);} QPushButton:pressed {background-color: rgb(0,0,255);}"));
    ui->startButton->setStyleSheet( QString("QPushButton {background-color: rgb(50,200,50);} QPushButton:pressed {background-color: rgb(150,255,150);}"));

    // Disables both buttons
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);

    ui->percentageBar->setValue(0);

    // Sets up main music for simon game
    mediaPlayer.setAudioOutput(&audioPlayer);

    mediaPlayer.setSource(QUrl("qrc:/Sounds/mainSong.mp3"));

    audioPlayer.setVolume(50);

    // If the main song ends, it starts and plays again
    mediaPlayer.setLoops(QMediaPlayer::Infinite);

    // Sets up the losing sound effect
    loseSoundEffect.setSource(QUrl("qrc:/Sounds/loseGame.wav"));

    loseSoundEffect.setVolume(0.3f);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loseGameMessage(){
    // Updates buttons/progress bar
    enableButtons(false);
    enableStartButton(true);
    ui->percentageBar->setValue(0);

    mediaPlayer.stop();

    // Plays sound effect
    loseSoundEffect.play();

    // Uses pop-up box to display that the game has been lost
    QMessageBox loseMsg(this);

    loseMsg.setWindowTitle("Game Over");
    loseMsg.setText("Wrong button, Try again");

    loseMsg.exec();
}

void MainWindow::flashRed()
{
    // Flashes a color then sets it back to the original after the QTimer has ended
    ui->redButton->setStyleSheet("background-color: rgba(200,50,50,255);");

    QTimer::singleShot(250, this, [this]() {
        ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgba(200,50,50, 150);} QPushButton:pressed {background-color: rgb(255,150,150);}"));
    });
}
void MainWindow::flashBlue()
{
    // Flashes a color then sets it back to the original after the QTimer has ended
    ui->blueButton->setStyleSheet("background-color: rgba(50,50,255, 255);");

    QTimer::singleShot(250, this, [this]() {
        ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgba(50,50,200, 150);} QPushButton:pressed {background-color: rgb(150,150,255);}"));
    });
}

void MainWindow::enableButtons(bool enable){

    ui->redButton->setEnabled(enable);
    ui->blueButton->setEnabled(enable);
}

void MainWindow::enableStartButton(bool enable){

    ui->startButton->setEnabled(enable);
}

void MainWindow::playMusic(){
    mediaPlayer.play();
}
