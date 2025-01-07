#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),speed(0), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    mainWidget = new QWidget(this);

    setCentralWidget(mainWidget);


    gameWidget = new GameWidget(mainWidget);

    sideWidget = new QWidget(this);
    sideWidget->setFixedSize(150, 500);
    sideWidget->setStyleSheet("border: 2px hidden black;"
                              "border-radius: 5px;"
                              "margin:15px 0px 5px 5px;");

    scoreText = new QLabel("Score", sideWidget);
    scoreText->setStyleSheet("border: none;"
                             "font-size: 20px;"
                             "font-family: bold;");
    scoreText->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    scoreLabel = gameWidget->getScore();
    scoreLabel->setFixedSize(125, 50);
    scoreLabel->setStyleSheet("border: 2px dashed black;"
                              "margin-top:1px;"
                              "font-size:30px;"
                              "font-family:bold;");
    scoreLabel->setAlignment(Qt::AlignCenter);


    changeSpeed = new QLabel("Speed",sideWidget);
    changeSpeed->setStyleSheet(
        "font-size: 20px;"
        "font-family: bold;"
        "margin:30px 0px 0px 0px;");


    slow = new QPushButton("Slow",changeSpeed);
    slow->setFixedSize(135, 50);
    slow->setStyleSheet("QPushButton{"
                        "font-size: 15px;"
                        "background: green;"
                        "color:white;"
                        "padding: 3px;"
                        "margin:5px;"
                        "text-align: center;"
                        "}"
                        "QPushButton:hover{"
                        "background: white;"
                        "color:black;"
                        "padding: 3px;"
                        "margin:5px;"
                        "text-align: center;"
                        "}");
    middle = new QPushButton("Middle",changeSpeed);
    middle->setFixedSize(135, 50);
    middle->setStyleSheet("QPushButton{"
                          "font-size: 15px;"
                          "background: green;"
                          "color:white;"
                          "padding: 3px;"
                          "margin:5px;"
                          "text-align: center;"
                          "}"
                          "QPushButton:hover{"
                          "background: white;"
                          "color:black;"
                          "padding: 3px;"
                          "margin:5px;"
                          "text-align: center;"
                          "}");
    fast = new QPushButton("Fast",changeSpeed);
    fast->setFixedSize(135, 50);
    fast->setStyleSheet("QPushButton{"
                        "font-size: 15px;"
                        "background: green;"
                        "color:white;"
                        "padding: 3px;"
                        "margin:5px;"
                        "text-align: center;"
                        "}"
                        "QPushButton:hover{"
                        "background: white;"
                        "color:black;"
                        "padding: 3px;"
                        "margin:5px;"
                        "text-align: center;"
                        "}");
    changeSpeed->setAlignment(Qt::AlignCenter);

    connect(slow, &QPushButton::clicked, this, &MainWindow::onSlowButtonClicked);
    connect(middle, &QPushButton::clicked, this, &MainWindow::onMiddlwButtonClicked);
    connect(fast, &QPushButton::clicked, this, &MainWindow::onFastButtonClicked);

    connect(this, &MainWindow::speedChanged, gameWidget, &GameWidget::onSpeedChanged);


    QVBoxLayout *sideLayout = new QVBoxLayout(sideWidget);
    sideLayout->addWidget(scoreText);
    sideLayout->addWidget(scoreLabel);
    sideLayout->addWidget(changeSpeed);
    sideLayout->addWidget(slow);
    sideLayout->addWidget(middle);
    sideLayout->addWidget(fast);

    sideLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    sideWidget->setLayout(sideLayout);


    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(gameWidget);
    mainLayout->addWidget(sideWidget);
    mainWidget->setLayout(mainLayout);

}

MainWindow::~MainWindow() {
    delete ui;
}

int MainWindow::getSpeed() const {
    return speed;  // Повертаємо значення змінної speed
}

void MainWindow::onSlowButtonClicked() {
    setSpeed(60);
    emit speedChanged(getSpeed());  // Випускаємо сигнал зі значенням speed
}

void MainWindow::onMiddlwButtonClicked() {
    setSpeed(40);
    emit speedChanged(getSpeed());
}

void MainWindow::onFastButtonClicked() {
    setSpeed(20);
    emit speedChanged(getSpeed());
}

void MainWindow::setSpeed(int value) {
    speed = value;
    emit speedChanged(speed);  // Викликаємо сигнал при зміні швидкості
}

