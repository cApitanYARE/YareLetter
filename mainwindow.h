#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QPainter>
#include "gamewidget.h"  // Підключаємо тільки заголовок GameWidget
#include "ui_mainwindow.h" // Підключаємо UI, згенерований Qt Designer

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setSpeed(int value);
    int getSpeed() const;

signals:
    void speedChanged(int newSpeed);
private slots:
    void onSlowButtonClicked();  // Оголошення слота для кнопки "Slow"
    void onMiddlwButtonClicked();
    void onFastButtonClicked();

private:
    QWidget *mainWidget;
    QWidget *sideWidget;
    GameWidget *gameWidget; // Вказівник на GameWidget
    QLabel *scoreLabel;
    QLabel *scoreText;
    QLabel *sideInstructionText;
    QLabel *sideInstruction;
    QLabel *changeSpeed;
    QPushButton *slow;
    QPushButton *middle;
    QPushButton *fast;

    int speed;

    Ui::MainWindow *ui;  // Додаємо це для використання UI
};

#endif // MAINWINDOW_H
