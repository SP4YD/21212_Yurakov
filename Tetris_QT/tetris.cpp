#include "tetris.h"
#include "Blocks.h"

#include <algorithm>
#include <cstdlib>
#include <time.h>

void Tetris::CopyingBlock(const int (&from)[4][4], int (&to)[4][4])
{
    std::copy(&from[0][0], &from[0][0] + 16, &to[0][0]);
}

void Tetris::TurningBlock(int (&block)[4][4])
{
    int tmpBlock[4][4];
    CopyingBlock(block, tmpBlock);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            block[i][j] = tmpBlock[3-j][i];
        }
    }
}

void Tetris::CopyingGameArea(int (&Area)[FIELD_LENGTH][FIELD_WIDTH])
{
    for (int i = 0; i < FIELD_LENGTH; ++i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            Area[i][j] = GameArea[i][j];
        }
    }
}

Tetris::Tetris()
{
    StartGame();
}

void Tetris::StartGame()
{
    Initialization();

    CreateNextBlock();

    CreateBlockForStage();
}

void Tetris::Initialization()
{
    std::fill(&GameArea[0][0], &GameArea[0][0] + FIELD_LENGTH * FIELD_WIDTH, 0);

    Block1.BlockNumber = 1;
    CopyingBlock(PatternBlock1, Block1.BlockMatrix);
    Block2.BlockNumber = 2;
    CopyingBlock(PatternBlock2, Block2.BlockMatrix);
    Block3.BlockNumber = 3;
    CopyingBlock(PatternBlock3, Block3.BlockMatrix);
    Block4.BlockNumber = 4;
    CopyingBlock(PatternBlock4, Block4.BlockMatrix);
    Block5.BlockNumber = 5;
    CopyingBlock(PatternBlock5, Block5.BlockMatrix);
    Block6.BlockNumber = 6;
    CopyingBlock(PatternBlock6, Block6.BlockMatrix);
    Block7.BlockNumber = 7;
    CopyingBlock(PatternBlock7, Block7.BlockMatrix);

    srand(time(0));
    ScoreGame = 0;
    InitialSpeedInMs = INITIAL_SPEED;
    IsGameOver = false;
}

void Tetris::CreateBlockForStage()
{
    CurrentBlock = NextBlock;
    GetBorders(CurrentBlock.BlockMatrix, CurrentBlock.BlockBorders);
    CreateNextBlock();

    CurrentBlock.BlockCoordinates.CoordinateX = FIELD_WIDTH/2 - 2;
    CurrentBlock.BlockCoordinates.CoordinateY = -1;
}

void Tetris::CreateNextBlock()
{
    int blockId = rand() % 7;

    if (blockId == 0) {
        NextBlock = Block1;
    }
    else if (blockId == 1) {
        NextBlock = Block2;
    }
    else if (blockId == 2) {
        NextBlock = Block3;
    }
    else if (blockId == 3) {
        NextBlock = Block4;
    }
    else if (blockId == 4) {
        NextBlock = Block5;
    }
    else if (blockId == 5) {
        NextBlock = Block6;
    }
    else if (blockId == 6) {
        NextBlock = Block7;
    }

}

void Tetris::GetBorders(int block[4][4], Borders& bord)
{
    bool flagToStop = false;
    for (int i = 0; i < 4 && !flagToStop; ++i) {
        for (int j = 0; j < 4 && !flagToStop; ++j) {
            if (block[i][j]) {
                bord.UpperBorder = i;
                flagToStop = true;
            }
        }
    }
    flagToStop = false;
    for (int i = 3; i >= 0 && !flagToStop; --i) {
        for (int j = 0; j < 4 && !flagToStop; ++j) {
            if (block[i][j]) {
                bord.LowerBorder = i;
                flagToStop = true;
            }
        }
    }
    flagToStop = false;
    for (int j = 0; j < 4 && !flagToStop; ++j) {
        for (int i = 0; i < 4 && !flagToStop; ++i) {
            if (block[i][j]) {
                bord.LeftBorder = j;
                flagToStop = true;
            }
        }
    }
    flagToStop = false;
    for (int j = 3; j >= 0 && !flagToStop; --j) {
        for (int i = 0; i < 4 && !flagToStop; ++i) {
            if (block[i][j]) {
                bord.RightBorder = j;
                flagToStop = true;
            }
        }
    }
}

void Tetris::BlockMovement(Keys key)
{
    bool isNewBlock = CurrentBlock.BlockCoordinates.CoordinateY == -1;

    if (key == Up && !isNewBlock) {
        if (!BlockOutOfRange(CurrentBlock.BlockCoordinates, key) && CurrentBlock.BlockNumber != Block3.BlockNumber) {
            DeletingOldBlock();
            TurningBlock(CurrentBlock.BlockMatrix);
            GetBorders(CurrentBlock.BlockMatrix, CurrentBlock.BlockBorders);

            for (int i = CurrentBlock.BlockBorders.UpperBorder; i <= CurrentBlock.BlockBorders.LowerBorder; ++i) {
                for (int j = CurrentBlock.BlockBorders.LeftBorder; j <= CurrentBlock.BlockBorders.RightBorder; ++j) {
                    if (CurrentBlock.BlockMatrix[i][j]) {
                        GameArea[CurrentBlock.BlockCoordinates.CoordinateY + i][CurrentBlock.BlockCoordinates.CoordinateX + j] = CurrentBlock.BlockMatrix[i][j];
                    }
                }
            }
        }
    }
    else if (key == Down) {
        if (CurrentBlock.BlockCoordinates.CoordinateY + CurrentBlock.BlockBorders.LowerBorder >= FIELD_LENGTH - 1
           || BlockOutOfRange(CurrentBlock.BlockCoordinates, Down)) {
            FixingBlocks();
            CreateBlockForStage();
        }

        if (!isNewBlock) {
            DeletingOldBlock();
        }

        ++(CurrentBlock.BlockCoordinates.CoordinateY);

        for (int i = CurrentBlock.BlockBorders.UpperBorder; i <= CurrentBlock.BlockBorders.LowerBorder; ++i) {
            for (int j = CurrentBlock.BlockBorders.LeftBorder; j <= CurrentBlock.BlockBorders.RightBorder; ++j) {
                if(((CurrentBlock.BlockCoordinates.CoordinateY + i) <= (FIELD_LENGTH - 1))
                     && (GameArea[CurrentBlock.BlockCoordinates.CoordinateY + i][CurrentBlock.BlockCoordinates.CoordinateX + j] != 2)) {
                    GameArea[CurrentBlock.BlockCoordinates.CoordinateY + i][CurrentBlock.BlockCoordinates.CoordinateX + j] = CurrentBlock.BlockMatrix[i][j];
                }
            }
        }
    }
    else if (key == Left && !isNewBlock) {
        if ((CurrentBlock.BlockCoordinates.CoordinateX + CurrentBlock.BlockBorders.LeftBorder > 0) && !BlockOutOfRange(CurrentBlock.BlockCoordinates, key)) {
            DeletingOldBlock();

            --(CurrentBlock.BlockCoordinates.CoordinateX);

            for (int i = CurrentBlock.BlockBorders.UpperBorder; i <= CurrentBlock.BlockBorders.LowerBorder; ++i) {
                for (int j = CurrentBlock.BlockBorders.LeftBorder; j <= CurrentBlock.BlockBorders.RightBorder; ++j) {
                    if (((CurrentBlock.BlockCoordinates.CoordinateX + j) >= 0)
                          && GameArea[CurrentBlock.BlockCoordinates.CoordinateY + i][CurrentBlock.BlockCoordinates.CoordinateX + j] != 2) {
                        GameArea[CurrentBlock.BlockCoordinates.CoordinateY + i][CurrentBlock.BlockCoordinates.CoordinateX + j] = CurrentBlock.BlockMatrix[i][j];
                    }
                }
            }
        }
    }
    else if (key == Right && !isNewBlock) {
        if (CurrentBlock.BlockCoordinates.CoordinateX + CurrentBlock.BlockBorders.RightBorder < (FIELD_WIDTH - 1) && !BlockOutOfRange(CurrentBlock.BlockCoordinates, key)) {
            DeletingOldBlock();

            ++(CurrentBlock.BlockCoordinates.CoordinateX);

            for (int i = CurrentBlock.BlockBorders.UpperBorder; i <= CurrentBlock.BlockBorders.LowerBorder; ++i) {
                for (int j = CurrentBlock.BlockBorders.LeftBorder; j <= CurrentBlock.BlockBorders.RightBorder; ++j) {
                    if ((CurrentBlock.BlockCoordinates.CoordinateX + j <= FIELD_WIDTH - 1)
                         && GameArea[CurrentBlock.BlockCoordinates.CoordinateY + i][CurrentBlock.BlockCoordinates.CoordinateX + j] != 2) {
                        GameArea[CurrentBlock.BlockCoordinates.CoordinateY + i][CurrentBlock.BlockCoordinates.CoordinateX + j] = CurrentBlock.BlockMatrix[i][j];
                    }
                }
            }
        }
    }
    else if (key == Space) {
        while((CurrentBlock.BlockCoordinates.CoordinateY + CurrentBlock.BlockBorders.LowerBorder < (FIELD_LENGTH - 1))
               && !BlockOutOfRange(CurrentBlock.BlockCoordinates, Down)) {
            DeletingOldBlock();

            ++(CurrentBlock.BlockCoordinates.CoordinateY);

            for (int i = CurrentBlock.BlockBorders.UpperBorder; i <= CurrentBlock.BlockBorders.LowerBorder; ++i) {
                for (int j = CurrentBlock.BlockBorders.LeftBorder; j <= CurrentBlock.BlockBorders.RightBorder; ++j) {
                    if (CurrentBlock.BlockCoordinates.CoordinateY + i <= FIELD_LENGTH - 1
                        && GameArea[CurrentBlock.BlockCoordinates.CoordinateY + i][CurrentBlock.BlockCoordinates.CoordinateX + j] != 2) {
                       GameArea[CurrentBlock.BlockCoordinates.CoordinateY + i][CurrentBlock.BlockCoordinates.CoordinateX + j] = CurrentBlock.BlockMatrix[i][j];
                    }
                }
            }
        }
        FixingBlocks();

        CreateBlockForStage();
    }

    RemovingFullLines();

    CheckingForGameOver();
}

bool Tetris::BlockOutOfRange(Coordinates coordinates, Keys key)
{
    Block tmpBlock = CurrentBlock;

    Borders tmpBorders = CurrentBlock.BlockBorders;
    if (key == Up) {
        TurningBlock(tmpBlock.BlockMatrix);
        GetBorders(tmpBlock.BlockMatrix, tmpBorders);
    }
    else if (key == Down) {
        ++(coordinates.CoordinateY);
    }
    else if (key == Left) {
        --(coordinates.CoordinateX);
    }
    else if (key == Right) {
        ++(coordinates.CoordinateX);
    }

    for (int i = tmpBorders.UpperBorder; i <= tmpBorders.LowerBorder; ++i){
        for (int j = tmpBorders.LeftBorder; j <= tmpBorders.RightBorder; ++j){
            if (((GameArea[coordinates.CoordinateY + i][coordinates.CoordinateX + j] == 2) && (tmpBlock.BlockMatrix[i][j] == 1))
                    || ((coordinates.CoordinateX + tmpBorders.RightBorder) > (FIELD_WIDTH - 1)) || (coordinates.CoordinateX + tmpBorders.LeftBorder) < 0 ) {
                return true;
            }
        }
    }

    return false;
}

void Tetris::FixingBlocks()
{
    for (int i = CurrentBlock.BlockBorders.UpperBorder; i <= CurrentBlock.BlockBorders.LowerBorder; ++i) {
        for (int j = CurrentBlock.BlockBorders.LeftBorder; j <= CurrentBlock.BlockBorders.RightBorder; ++j) {
            if(CurrentBlock.BlockMatrix[i][j] == 1) {
                GameArea[CurrentBlock.BlockCoordinates.CoordinateY + i][CurrentBlock.BlockCoordinates.CoordinateX + j] = 2;
            }
        }
    }
}

void Tetris::DeletingOldBlock()
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (CurrentBlock.BlockMatrix[i][j]) {
                GameArea[CurrentBlock.BlockCoordinates.CoordinateY + i][CurrentBlock.BlockCoordinates.CoordinateX + j] = 0;
            }
        }
    }
}


void Tetris::RemovingFullLines()
{
    int lineNum = FIELD_LENGTH - 1;
    bool lineIsEmpty = false;
    bool lineIsFull;

    while (!lineIsEmpty && lineNum >= 0) {
        lineIsFull = true;
        lineIsEmpty = true;

        for (int i = 0; i < FIELD_WIDTH; ++i) {
            if (GameArea[lineNum][i] != 2){
                lineIsFull = false;
            }
            else {
                lineIsEmpty = false;
            }
        }

        if (lineIsFull) {
            for (int i = lineNum; i >= 0; --i) {
                for (int j = 0; j < FIELD_WIDTH; ++j) {
                    GameArea[i][j] = GameArea[i - 1][j];
                }
            }

            ScoreGame += 10;
        }
        else {
            --lineNum;
        }
    }
}

void Tetris::CheckingForGameOver()
{
    for (int i = CurrentBlock.BlockBorders.UpperBorder; i <= CurrentBlock.BlockBorders.LowerBorder; ++i) {
        for (int j = CurrentBlock.BlockBorders.LeftBorder; j <= CurrentBlock.BlockBorders.RightBorder; ++j) {
            if (CurrentBlock.BlockCoordinates.CoordinateY + i >= 0 && CurrentBlock.BlockMatrix[i][j]
                && GameArea[i + CurrentBlock.BlockCoordinates.CoordinateY][j + CurrentBlock.BlockCoordinates.CoordinateX] == 2) {

                IsGameOver = true;
                return;
            }
        }
    }
}

int Tetris::GetScore()
{
    return ScoreGame;
}

bool Tetris::GetIsGameOver()
{
    return IsGameOver;
}

Block Tetris::GetNextBlock()
{
    return NextBlock;
}

Block Tetris::GetCurrentBlock()
{
    return CurrentBlock;
}

int Tetris::GetInitialSpeedBlock()
{
    return InitialSpeedInMs;
}
