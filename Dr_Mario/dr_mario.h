#pragma once

#ifndef DR_MARIO_H
#define DR_MARIO_H

#include <QFile>

namespace {
    constexpr int FIELD_LENGTH = 17;                 //Длина поля (по Y)
    constexpr int FIELD_WIDTH = 8;                  //Ширина поля (по X)
    constexpr int INITIAL_SPEED = 1000;             //Начальная скорость
}

enum Keys {
    Up,
    Down,
    Left,
    Right,
    Space
};


struct Coordinates {
    int CoordinateX;
    int CoordinateY;
};

struct Borders {
    int UpperBorder;
    int LowerBorder;
    int LeftBorder;
    int RightBorder;
};

struct Pill {
    int PillMatrix[2][2];
    int PillNumber;
    Borders PillBorders;
    Coordinates PillCoordinates;
};

class Dr_Mario
{
public:
    Dr_Mario();
    ~Dr_Mario();

    void StartNewGame();
    void ContinueGame();
    void InitializingGame();
    void CreatePillForField();
    void CreateNextPill();
    Borders GetBorders(int block[2][2]);///////////////////////////////////////////////
    void PillMovement(Keys key);
    bool PillOutOfRange(Coordinates coordinates, Keys key);
    void DeleteLines();
    void CheckingFieldOnLine();
    void CreatingViruses();
    void PillDrop(int X, int Y);
    void DeletingOldPill();
    void RemovingLines(int X, int Y, int (&InfoField)[FIELD_LENGTH][FIELD_WIDTH], bool isNewBlock);
    void CheckingForGameOver();
    void CopyingPill(const int (&from)[2][2], int (&to)[2][2]);
    void AddPillToPlayingField();
    void TurningPill(int (&block)[2][2]);//////////////////////////block ->pill
    void CopyingPlayingField(int (&Field)[FIELD_LENGTH][FIELD_WIDTH]);
    int GetScore();
    int GetRecord();
    int GetCountVirus();
    bool GetIsGameOver();
    bool GetIsGameWin();
    Pill GetNextPill();
    Pill GetCurrentPill();
    int GetInitialSpeedPill();
    int GetNumStage();
private:
    bool IsGameOver;                            //Этой проигрыш?
    bool IsGameWin;                             //Этой победа?
    int InitialSpeedInMs;                       //Скорость смещения блока вниз
    int PlayingField[FIELD_LENGTH][FIELD_WIDTH];//Область сцены в квадратах
    int Score;                              //Счёт
    Pill CurrentPill;                         //Блок сейчас
    Pill NextPill;                            //Следующий блок
    int NumStage;                               //Номер этапа
    int CountVirus;                             //Количество вирусов
    int Record;                                 //Рекорд
    QFile FileWithRecord;                       //Файл с рекордом
};

#endif // DR_MARIO_H
