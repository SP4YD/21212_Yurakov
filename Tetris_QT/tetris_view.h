#pragma once

#ifndef TETRIS_VIEW_H
#define TETRIS_VIEW_H

#include "tetris.h"

#include <QWidget>
#include <QColor>

namespace {
    constexpr int BLOCK_LENGTH = 25;                //Длина стороны блока
    constexpr int INDENT = 10;                      //Размер отступов между элементами виджета
    constexpr int TRANSPARENCY_DEGREE = 150;        //Уровень прозрачности
    constexpr int DEFAULT_UPDATE_INTERVAL = 50;     //Стандартный интервал обновления
    constexpr int SPEED_INCREASE_INTERVAL = 20000;  //Интервал увеличения скорости
    constexpr float ACCELERATION_COEFFICIENT = 1.2; //Коэффицент ускорения
}

struct BlockWithColor {
    Block AboutBlock;
    QColor Color;
};

namespace Ui {
    class Tetris_View;
}

class Tetris_View : public QWidget
{
    Q_OBJECT

public:
    explicit Tetris_View(Tetris* tetris = nullptr);

    ~Tetris_View();

    void ColorAssignment (BlockWithColor& block);
    void StartGameOver ();

    virtual void paintEvent(QPaintEvent *);
    virtual void timerEvent(QTimerEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
private:
    BlockWithColor CurrentBlock;
    BlockWithColor NextBlock;

    Tetris* TetrisNow;
    int FieldWidth;                 // Ширина поля
    int FieldLength;                // Длинна поля
    int SpeedInMs;                  // Скорость смещения блока вниз
    int UpdateInterval;             // Интервал обновления изображения
    int TimeSpeedIncrease;          // Время увеличения скорости
    int TimerImageRefresh;          // Таймер обновления картинки
    int TimerSpeedIncrease;         // Таймер увеличения скорости
    int TimerFallBlocks;            // Таймер падения блоков

    Ui::Tetris_View *ui;
};

#endif // TETRIS_VIEW_H
