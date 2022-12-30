#pragma once

#ifndef TETRIS_H
#define TETRIS_H

namespace {
    constexpr int FIELD_LENGTH = 20;                 //Длина поля (по Y)
    constexpr int FIELD_WIDTH = 10;                  //Ширина поля (по X)
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

struct Block {
    int BlockMatrix[4][4];
    int BlockNumber;
    Borders BlockBorders;
    Coordinates BlockCoordinates;
};

class Tetris
{
public:
    Tetris();
    ~Tetris();

    void StartGame();
    void Initialization();
    void CreateBlockForStage();
    void CreateNextBlock();
    void GetBorders(int block[4][4], Borders& bord);
    void BlockMovement(Keys key);
    bool BlockOutOfRange(Coordinates coordinates, Keys key);
    void FixingBlocks();
    void DeletingOldBlock();
    void RemovingFullLines();
    void CheckingForGameOver();
    void CopyingBlock(const int (&from)[4][4], int (&to)[4][4]);
    void TurningBlock(int (&block)[4][4]);
    void CopyingGameArea(int (&Area)[FIELD_LENGTH][FIELD_WIDTH]);
    int GetScore();
    bool GetIsGameOver();
    Block GetNextBlock();
    Block GetCurrentBlock();
    int GetInitialSpeedBlock();
private:
    bool IsGameOver;                            //Этой проигрыш?
    int InitialSpeedInMs;                              // Скорость смещения блока вниз
    int GameArea[FIELD_LENGTH][FIELD_WIDTH];    //Область сцены в квадратах (0 - пусто, 1 - в движении, 2 - стоит)
    int ScoreGame;                              //Счёт
    Block CurrentBlock;                         //Блок сейчас
    Block NextBlock;                            //Следующий блок
};

#endif // TETRIS_H
