#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H


#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QVector>
#include <QLabel>

struct CharInfo {
    char character;
    int x, y;
};

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget();

    void setScore(int num);
    QLabel *getScore();
    void keyPressEvent(QKeyEvent *even);


public slots:
    void onSpeedChanged(int newSpeed);


protected:
    void paintEvent(QPaintEvent *event) override;
    void updatePosition();
    bool containsCharacter(char c) const;
    void scoreDown();
    void scoreUp();

private:

    QVector<CharInfo> characters;
    const int screenHeight = 500;
    const int screenWidth = 500;

    int speed = 40;
    QTimer *updateTimer;

    char randomChar();
    int randomX();

    QLabel* scoreLabel;
    int score = 0;

};


#endif // GAMEWIDGET_H
