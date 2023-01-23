#include "dr_mario.h"
#include "Pills.h"

#include <algorithm>
#include <cstdlib>
#include <QTextStream>
#include <string>
#include <time.h>

//https://github.com/angelortizv/Tetris

Dr_Mario::Dr_Mario() : FileWithRecord("./Record.txt")
{
    StartNewGame();
}

void Dr_Mario::CopyingPill(const int (&from)[2][2], int (&to)[2][2])
{
    std::copy(&from[0][0], &from[0][0] + 4, &to[0][0]);
}

void Dr_Mario::AddPillToPlayingField()
{
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            if(CurrentPill.PillMatrix[i][j]) {
                PlayingField[CurrentPill.PillCoordinates.CoordinateY + i][CurrentPill.PillCoordinates.CoordinateX + j] = CurrentPill.PillMatrix[i][j];
            }
        }
    }
}

void Dr_Mario::TurningPill(int (&pill)[2][2])
{
    int tmpPill[2][2];
    CopyingPill(pill, tmpPill);

    if (pill[0][0]) {
        pill[1][1] = pill[0][0];
        pill[0][0] = 0;
    }
    else {
        pill[0][0] = pill[1][0];
        pill[1][0] = pill[1][1];
        pill[1][1] = 0;
    }
}



void Dr_Mario::StartNewGame()
{
    NumStage = 1;
    Score = 0;

    InitializingGame();
//    PlayingField[8][3] = 1;
//    PlayingField[8][4] = 1;
//    PlayingField[8][5] = 1;
//    PlayingField[8][6] = 3;
//    PlayingField[8][7] = 2;
//    PlayingField[9][3] = 1;
//    PlayingField[9][4] = 2;
//    PlayingField[9][5] = 2;
//    PlayingField[9][6] = 1;
//    PlayingField[9][7] = 2;
//    PlayingField[10][3] = 2;
//    PlayingField[10][4] = 2;
//    PlayingField[10][5] = 2;
//    PlayingField[10][6] = 1;
//    PlayingField[10][7] = 1;
//    PlayingField[11][3] = 2;
//    PlayingField[11][4] = 2;
//    PlayingField[11][5] = 2;
//    PlayingField[11][6] = 1;
//    PlayingField[11][7] = 1;

//    PlayingField[13][3] = 1;
//    PlayingField[13][4] = 1;
//    PlayingField[13][5] = 1;
//    PlayingField[13][6] = 3;
//    PlayingField[13][7] = 2;
//    PlayingField[14][3] = 1;
//    PlayingField[14][4] = 2;
//    PlayingField[14][5] = 2;
//    PlayingField[14][6] = 1;
//    PlayingField[14][7] = 2;
//    PlayingField[15][3] = 2;
//    PlayingField[15][4] = 2;
//    PlayingField[15][5] = 2;
//    PlayingField[15][6] = 1;
//    PlayingField[15][7] = 1;
//    PlayingField[16][3] = 2;
//    PlayingField[16][4] = 2;
//    PlayingField[16][5] = 2;
//    PlayingField[16][6] = 1;
//    PlayingField[16][7] = 1;
}

void Dr_Mario::ContinueGame()
{
    ++NumStage;

    InitializingGame();
}

void Dr_Mario::InitializingGame()
{
    IsGameOver = false;
    IsGameWin = false;
    srand(time(0));
    CountVirus = 4 * NumStage;
    std::fill(&PlayingField[0][0], &PlayingField[0][0] + FIELD_LENGTH * FIELD_WIDTH, 0);

    CreatingViruses();

    Pill1.PillNumber = 1;
    CopyingPill(PatternPill1, Pill1.PillMatrix);
    Pill2.PillNumber = 2;
    CopyingPill(PatternPill2, Pill2.PillMatrix);
    Pill3.PillNumber = 3;
    CopyingPill(PatternPill3, Pill3.PillMatrix);
    Pill4.PillNumber = 4;
    CopyingPill(PatternPill4, Pill4.PillMatrix);
    Pill5.PillNumber = 5;
    CopyingPill(PatternPill5, Pill5.PillMatrix);
    Pill6.PillNumber = 6;
    CopyingPill(PatternPill6, Pill6.PillMatrix);

    InitialSpeedInMs = INITIAL_SPEED;
    IsGameOver = false;
    IsGameWin = false;

    FileWithRecord.open(QFile::ReadOnly | QFile::Text);

    QString Qstr;
    std::string strStd;

    Qstr = FileWithRecord.readLine();
    strStd = Qstr.toStdString();
    Record = stoi(strStd);

    FileWithRecord.close();

    CreateNextPill();

    CreatePillForField();
}

void Dr_Mario::CreatePillForField()
{
    CurrentPill = NextPill;
    CurrentPill.PillBorders = GetBorders(CurrentPill.PillMatrix);
    CreateNextPill();

    CurrentPill.PillCoordinates.CoordinateX = FIELD_WIDTH/2 - 1;
    CurrentPill.PillCoordinates.CoordinateY = -1;
}

void Dr_Mario::CreateNextPill()
{
    int pillId = rand() % 6;

    if (pillId == 0) {
        NextPill = Pill1;
    }
    else if (pillId == 1) {
        NextPill = Pill2;
    }
    else if (pillId == 2) {
        NextPill = Pill3;
    }
    else if (pillId == 3) {
        NextPill = Pill4;
    }
    else if (pillId == 4) {
        NextPill = Pill5;
    }
    else if (pillId == 5) {
        NextPill = Pill6;
    }

}

Borders Dr_Mario::GetBorders(int pill[2][2])
{
    Borders bord;
    bord.LeftBorder = 0;
    bord.LowerBorder = 1;

    if (pill[0][0]) {
        bord.RightBorder = 0;
        bord.UpperBorder = 0;
    }
    else {
        bord.RightBorder = 1;
        bord.UpperBorder = 1;
    }

    return bord;
}

void Dr_Mario::PillMovement(Keys key)
{
    bool isNewPill = (CurrentPill.PillCoordinates.CoordinateY == -1);

    if (key == Down) {
            if (CurrentPill.PillCoordinates.CoordinateY + 2 >= FIELD_LENGTH || PillOutOfRange(CurrentPill.PillCoordinates, key)) {
                DeleteLines();

                CheckingFieldOnLine();

                if (!IsGameWin) {
                    CreatePillForField();
                    CheckingForGameOver();
                }
            }

            DeletingOldPill();

            ++(CurrentPill.PillCoordinates.CoordinateY);

            AddPillToPlayingField();

    }
    else if (key == Left && !isNewPill) {
        if ((CurrentPill.PillCoordinates.CoordinateX > 0) && !PillOutOfRange(CurrentPill.PillCoordinates, key)) {
            DeletingOldPill();

            --(CurrentPill.PillCoordinates.CoordinateX);

            AddPillToPlayingField();
        }
    }
    else if (key == Right && !isNewPill) {
        if (CurrentPill.PillCoordinates.CoordinateX + CurrentPill.PillBorders.RightBorder < (FIELD_WIDTH - 1)
            && !PillOutOfRange(CurrentPill.PillCoordinates, key)) {
            DeletingOldPill();

            ++(CurrentPill.PillCoordinates.CoordinateX);

            AddPillToPlayingField();
        }
    }
    else if (key == Up && !isNewPill && CurrentPill.PillCoordinates.CoordinateY != 0) {
        if (!PillOutOfRange(CurrentPill.PillCoordinates, key)) {
            DeletingOldPill();
            TurningPill(CurrentPill.PillMatrix);
            CurrentPill.PillBorders = GetBorders(CurrentPill.PillMatrix);

            AddPillToPlayingField();
        }
        else {
            if (PlayingField[CurrentPill.PillCoordinates.CoordinateY + 1][CurrentPill.PillCoordinates.CoordinateX - 1] == 0 && CurrentPill.PillMatrix[0][0]) {
                DeletingOldPill();
                --CurrentPill.PillCoordinates.CoordinateX;

                if (!PillOutOfRange(CurrentPill.PillCoordinates, key)) {
                    TurningPill(CurrentPill.PillMatrix);
                    CurrentPill.PillBorders = GetBorders(CurrentPill.PillMatrix);
                }
                else {
                    ++CurrentPill.PillCoordinates.CoordinateX;
                }

                AddPillToPlayingField();
            }
            else if (PlayingField[CurrentPill.PillCoordinates.CoordinateY + 2][CurrentPill.PillCoordinates.CoordinateX] == 0 && CurrentPill.PillMatrix[1][1]) {
                DeletingOldPill();
                ++CurrentPill.PillCoordinates.CoordinateY;

                if (!PillOutOfRange(CurrentPill.PillCoordinates, key)) {
                    TurningPill(CurrentPill.PillMatrix);
                    CurrentPill.PillBorders = GetBorders(CurrentPill.PillMatrix);
                }
                else {
                    ++CurrentPill.PillCoordinates.CoordinateY;
                }

                AddPillToPlayingField();
            }
        }
    }
    else if (key == Space) {
        while((CurrentPill.PillCoordinates.CoordinateY + 2 < FIELD_LENGTH) && !PillOutOfRange(CurrentPill.PillCoordinates, Down)) {
            DeletingOldPill();

            ++(CurrentPill.PillCoordinates.CoordinateY);

            AddPillToPlayingField();
        }

        DeleteLines();

        CheckingFieldOnLine();

        if (!IsGameWin) {
            CreatePillForField();
            CheckingForGameOver();
        }
    }
}

bool Dr_Mario::PillOutOfRange(Coordinates coordinates, Keys key)
{
    if (coordinates.CoordinateX >= 0 && coordinates.CoordinateX + CurrentPill.PillBorders.RightBorder < FIELD_WIDTH
        && coordinates.CoordinateY >= -1 && coordinates.CoordinateY + 1 < FIELD_LENGTH) {
        bool oldPillIs = PlayingField[coordinates.CoordinateY + 1][coordinates.CoordinateX];
        if (oldPillIs) {
            DeletingOldPill();
        }

        Pill tmpPill = CurrentPill;

        Borders tmpBorders;
        if (key == Up) {
            TurningPill(tmpPill.PillMatrix);
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
        tmpBorders = GetBorders(tmpPill.PillMatrix);

        for (int i = 0; i < 2; ++i){
            for (int j = 0; j < 2; ++j){
                if (((PlayingField[coordinates.CoordinateY + i][coordinates.CoordinateX + j] != 0) && (tmpPill.PillMatrix[i][j]))
                        || ((coordinates.CoordinateX + tmpBorders.RightBorder) > (FIELD_WIDTH - 1)) || (coordinates.CoordinateX < 0) ) {
                    if (oldPillIs) {
                        AddPillToPlayingField();
                    }

                    return true;
                }
            }
        }

        if (oldPillIs) {
            AddPillToPlayingField();
        }

        return false;
    }
    return true;
}

void Dr_Mario::DeleteLines()
{
    int CopyField[FIELD_LENGTH][FIELD_WIDTH];

    CopyingPlayingField(CopyField);

    int x1 = CurrentPill.PillCoordinates.CoordinateX + CurrentPill.PillBorders.LeftBorder;
    int y1 = CurrentPill.PillCoordinates.CoordinateY + CurrentPill.PillBorders.LowerBorder;
    int x2 = CurrentPill.PillCoordinates.CoordinateX + CurrentPill.PillBorders.RightBorder;
    int y2 = CurrentPill.PillCoordinates.CoordinateY + CurrentPill.PillBorders.UpperBorder;

    RemovingLines(x1, y1, CopyField, true);

    CopyField[y2][x2] = CurrentPill.PillMatrix[CurrentPill.PillBorders.UpperBorder][CurrentPill.PillBorders.RightBorder];

    RemovingLines(x2, y2, CopyField, true);

    if (PlayingField[y1][x1] == 0 || PlayingField[y2][x2] == 0) {
        PillDrop(x1, y1);
        PillDrop(x2, y2);
    }
}

void Dr_Mario::CheckingFieldOnLine()
{
    bool WereChanges = true;
    while (WereChanges) {
        int CopyField[FIELD_LENGTH][FIELD_WIDTH];

        CopyingPlayingField(CopyField);
        WereChanges = false;

        for (int x = FIELD_WIDTH - 1; x >= 0; --x) {
            for (int y = FIELD_LENGTH - 1; y >= 0; --y) {
                int initialColor = PlayingField[y][x];
                RemovingLines(x, y, CopyField, true);
                if (PlayingField[y][x] != initialColor) {
                    WereChanges = true;
                }
            }
        }
    }
}

void Dr_Mario::CreatingViruses()
{
    for (int i = 0; i < CountVirus; ++i) {
        int Y = rand() % FIELD_LENGTH;
        int X = rand() % FIELD_WIDTH;
        int color = rand() % 4;

        while (Y < 4 || Y > (FIELD_LENGTH - 1) || PlayingField[Y][X] != 0) {
           Y = rand() % FIELD_LENGTH;
           X = rand() % FIELD_WIDTH;
        }

        while (color == 0) {
            color = rand() % 4;
        }

        PlayingField[Y][X] = -1 * color;
    }

}

void Dr_Mario::PillDrop(int X, int Y){
    int tmpY = Y;
    if (Y >= 0 && Y < FIELD_LENGTH && X < FIELD_WIDTH && X >= 0 && PlayingField[Y][X] > 0 && Y + 1 < FIELD_LENGTH && PlayingField[Y + 1][X] == 0) {
        int color = PlayingField[Y][X];

        while((tmpY < FIELD_LENGTH - 1) && PlayingField[tmpY + 1][X] == 0) {
            PlayingField[tmpY][X] = 0;

            ++tmpY;

            PlayingField[tmpY][X] = color;
        }

        if (Y > 0 && PlayingField[Y - 1][X]) {
            PillDrop(X, Y - 1);
        }
    }
}

void Dr_Mario::DeletingOldPill()
{
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (CurrentPill.PillMatrix[i][j]) {
                PlayingField[CurrentPill.PillCoordinates.CoordinateY + i][CurrentPill.PillCoordinates.CoordinateX + j] = 0;
            }
        }
    }
}


void Dr_Mario::RemovingLines(int X, int Y, int (&InfoField)[FIELD_LENGTH][FIELD_WIDTH], bool isNewPill)
{
    int tmpColor = abs(InfoField[Y][X]);
    if (tmpColor) {
        int tmpCoordX = X - 1;
        int tmpCoordY = Y;
        int leftX = X;
        int rightX = X;
        int upperY = Y;
        int countVertical = 1;

        while (tmpCoordX >= 0 && tmpColor == abs(InfoField[tmpCoordY][tmpCoordX])) {
            leftX = tmpCoordX;
            --tmpCoordX;
            ++countVertical;
        }
        tmpCoordX = X + 1;

        while (tmpCoordX < FIELD_WIDTH && tmpColor == abs(InfoField[tmpCoordY][tmpCoordX])) {
            rightX = tmpCoordX;
            ++tmpCoordX;
            ++countVertical;
        }

        tmpCoordX = X;
        tmpCoordY = Y - 1;
        int countHorizontal = 1;

        while (tmpCoordY >= 0 && tmpColor == abs(InfoField[tmpCoordY][tmpCoordX])) {
            --tmpCoordY;
            ++countHorizontal;
        }

        tmpCoordY = Y + 1;

        while (tmpCoordY < FIELD_LENGTH && tmpColor == abs(InfoField[tmpCoordY][tmpCoordX])) {
            upperY = tmpCoordY;
            ++tmpCoordY;
            ++countHorizontal;
        }

        tmpCoordX = rightX;
        tmpCoordY = Y;

        if (countVertical >= 4) {
            while (tmpCoordX >= 0 && tmpColor == abs(InfoField[tmpCoordY][tmpCoordX])) {
                if (PlayingField[tmpCoordY][tmpCoordX] < 0) {
                    Score += 200;
                    --CountVirus;
                }
                PlayingField[tmpCoordY][tmpCoordX] = 0;
                if (tmpCoordX != X) {
                    InfoField[tmpCoordY][tmpCoordX] = 0;
                }
                --tmpCoordX;
            }
        }

        tmpCoordX = X;

        if (countHorizontal >= 4) {
            while (upperY >= 0 && tmpColor == abs(InfoField[upperY][tmpCoordX])) {
                if (PlayingField[upperY][tmpCoordX] < 0) {
                    Score += 200;
                    --CountVirus;
                }
                PlayingField[upperY][tmpCoordX] = 0;
                InfoField[upperY][tmpCoordX] = 0;
                --upperY;
            }
            PillDrop(tmpCoordX, upperY);
        }

        if (countVertical >= 4) {
            for (int i = leftX; i <= rightX; ++i) {
                PillDrop(i, Y - 1);
            }
        }

        if (!isNewPill && PlayingField[Y][X] && Y + 1 < FIELD_LENGTH && PlayingField[Y + 1][X] == 0) {
            PillDrop(X, Y);
        }

        if (CountVirus == 0) {
            IsGameWin = true;
        }
    }
}

void Dr_Mario::CheckingForGameOver()
{
    for (int j = 0; j < 2; ++j) {
        if (PlayingField[1][FIELD_WIDTH/2 - 1 + j] != 0) {
            IsGameOver = true;
        }
    }

    if (IsGameOver && Score > Record) {
        FileWithRecord.open(QIODevice::WriteOnly);
        QTextStream out(&FileWithRecord);

        out << QString::fromStdString(std::to_string(Score));

        FileWithRecord.close();
    }
}

int Dr_Mario::GetScore()
{
    return Score;
}

int Dr_Mario::GetRecord()
{
    return Record;
}

int Dr_Mario::GetCountVirus()
{
    return CountVirus;
}

bool Dr_Mario::GetIsGameOver()
{
    return IsGameOver;
}

bool Dr_Mario::GetIsGameWin()
{
    return IsGameWin;
}

Pill Dr_Mario::GetNextPill()
{
    return NextPill;
}

Pill Dr_Mario::GetCurrentPill()
{
    return CurrentPill;
}

int Dr_Mario::GetInitialSpeedPill()
{
    return InitialSpeedInMs;
}

int Dr_Mario::GetNumStage()
{
    return NumStage;
}

void Dr_Mario::CopyingPlayingField(int (&Field)[FIELD_LENGTH][FIELD_WIDTH])
{
    std::copy(&PlayingField[0][0], &PlayingField[0][0] + FIELD_LENGTH * FIELD_WIDTH, &Field[0][0]);
}
