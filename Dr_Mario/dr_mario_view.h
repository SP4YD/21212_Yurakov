#pragma once
#ifndef DR_MARIO_VIEW_H
#define DR_MARIO_VIEW_H

#include "dr_mario.h"

#include <QWidget>
#include <QColor>

namespace {
    constexpr int PILL_LENGTH = 26;                        //Длина стороны блока
    constexpr int TOP_INDENTATION_FOR_FIELD = 208;           //Отступ сверху для игровой зоны
    constexpr int LEFT_INDENTATION_FOR_FIELD = 310;          //Отступ слева для игровой зоны
    constexpr int TOP_INDENTATION_FOR_NEXT_PILL = 144;     //Отступ сверху для следующего блока
    constexpr int LEFT_INDENTATION_FOR_NEXT_PILL = 615;    //Отступ слева для следующего блока
    constexpr int TRANSPARENCY_DEGREE = 150;                //Уровень прозрачности
    constexpr int DEFAULT_UPDATE_INTERVAL = 50;             //Стандартный интервал обновления
    constexpr float ACCELERATION_COEFFICIENT = 1.2;         //Коэффицент ускорения
}

namespace Ui {
class Dr_Mario_View;
}

class Dr_Mario_View : public QWidget
{
    Q_OBJECT

public:
    explicit Dr_Mario_View(Dr_Mario* Model = nullptr);
    ~Dr_Mario_View();

    void StartGameOver ();

    virtual void paintEvent(QPaintEvent *);
    virtual void timerEvent(QTimerEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

private:
    QBrush* BackGroundBrush;
    QPalette* BackGroundPalette;

    Pill CurrentPill;
    Pill NextPill;

    Dr_Mario* ModelNow;
    int FieldWidth;                 // Ширина поля
    int FieldLength;                // Длинна поля
    int SpeedInMs;                  // Скорость смещения блока вниз
    int UpdateInterval;             // Интервал обновления изображения
    int TimeSpeedIncrease;          // Время увеличения скорости
    int TimerImageRefresh;          // Таймер обновления картинки
    int TimerFallPills;            // Таймер падения блоков
    bool IsNewStage;

    Ui::Dr_Mario_View *ui;
};

#endif // DR_MARIO_VIEW_H
