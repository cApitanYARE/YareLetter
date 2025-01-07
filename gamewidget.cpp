#include "gamewidget.h"
#include <cstdlib>
#include <ctime>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QLabel>
#include "mainwindow.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent),updateTimer(new QTimer(this))
{
    srand(time(0));

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]() {
        CharInfo newChar;
        do {
            newChar.character = randomChar();
        } while (containsCharacter(newChar.character));
        newChar.x = randomX();
        newChar.y = 0;
        characters.append(newChar);
    });
    timer->start(600);

    scoreLabel = new QLabel(this);
    setScore(0);


    connect(updateTimer, &QTimer::timeout, this, &GameWidget::updatePosition);
    updateTimer->start(speed);

    this->setFocus();
}

GameWidget::~GameWidget() {}

void GameWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    QPen pen(Qt::black);  // Чорний колір бордера
    pen.setWidth(2);      // Товщина бордера
    painter.setPen(pen);
    // Малюємо закруглений прямокутник
    int radius = 5; // Радіус закруглення кутів
    painter.drawRoundedRect(this->rect().adjusted(2, 2, -2, -2), radius, radius);  // Коригуємо внутрішні відступи

    QFont font("Arial", 32);
    painter.setFont(font);

    // Малюємо кожен символ
    for (const CharInfo &charInfo : characters) {
        painter.drawText(charInfo.x, charInfo.y, QString(charInfo.character));  // Малюємо символ
    }
}


void GameWidget::updatePosition() {
    for (int i = 0; i < characters.size(); ++i) {
        characters[i].y += 5;

        if (characters[i].y > screenHeight) {
            scoreDown();
            characters.remove(i);
            break;
        }
    }
    update();
}

char GameWidget::randomChar() {
    return rand() % 26 + 97;
}

int GameWidget::randomX() {
    return rand() % screenWidth;
}

bool GameWidget::containsCharacter(char c) const {
    for (const CharInfo &charInfo : characters) {
        if (charInfo.character == c) {
            return true;
        }
    }
    return false;
}

void GameWidget::scoreDown(){
    score -= 1;
    setScore(score);
}

void GameWidget::scoreUp(){
    score += 1;
    setScore(score);
}

void GameWidget::setScore(int num) {
    score = num;
    scoreLabel->setText(QString::number(num));  // Оновлюємо текст на лейблі
}
QLabel*  GameWidget::getScore(){
    return scoreLabel;
}

void GameWidget::onSpeedChanged(int newSpeed) {
    speed = newSpeed;

    // Зупиняємо таймер, очищуємо символи і рахунок
    if (updateTimer) {
        updateTimer->stop();
    }

    // Очищаємо екран і символи
    characters.clear();
    setScore(0);

    // Оновлюємо відображення
    update();

    // Перезапускаємо таймер із новою швидкістю
    if (updateTimer) {
        updateTimer->setInterval(speed);
        updateTimer->start();
    }
    this->setFocus();
}



void GameWidget::keyPressEvent(QKeyEvent *event) {
    if (!event->text().isEmpty()) {
        char ch = event->text().toLower().at(0).toLatin1();
        bool found = false;

        // Перевіряємо, чи є символ у списку
        for (int i = 0; i < characters.size(); ++i) {
            if (characters[i].character == ch) {
                scoreUp();            // Збільшуємо рахунок
                characters.remove(i); // Видаляємо символ
                found = true;
                break;
            }
        }

        if (!found) {
            scoreDown(); // Якщо символ не знайдено, зменшуємо рахунок
        }

        // Оновлюємо відображення
        update();
    }
}


