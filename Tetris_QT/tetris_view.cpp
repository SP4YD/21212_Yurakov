#include "tetris_view.h"
#include "ui_tetris_view.h"
#include "gameover_view.h"

#include <time.h>
#include <QPainter>
#include <QKeyEvent>

Tetris_View::Tetris_View(Tetris *tetris) :
    TetrisNow (tetris),
    ui(new Ui::Tetris_View)
{
    QBrush* brush = new QBrush();
    QPalette* palette = new QPalette();

    brush->setTextureImage(QImage(":/image/Cosmos.png"));
    palette->setBrush(QPalette::Window, *brush);
    this->setPalette(*palette);

    ui->setupUi(this);
    setFixedSize(FIELD_WIDTH*BLOCK_LENGTH + INDENT*5 + 4*BLOCK_LENGTH, FIELD_LENGTH*BLOCK_LENGTH + INDENT*2);

    SpeedInMs = TetrisNow->GetInitialSpeedBlock();
    UpdateInterval= DEFAULT_UPDATE_INTERVAL;
    TimeSpeedIncrease = SPEED_INCREASE_INTERVAL;

    TimerFallBlocks = startTimer(SpeedInMs);
    TimerImageRefresh = startTimer(UpdateInterval);
    TimerSpeedIncrease = startTimer(TimeSpeedIncrease);

    FieldWidth = FIELD_WIDTH;
    FieldLength = FIELD_LENGTH;

    TetrisNow->StartGame();
}

Tetris_View::~Tetris_View()
{
    delete ui;
}

void Tetris_View::ColorAssignment(BlockWithColor& block)
{
    if (block.AboutBlock.BlockNumber == 1) {
        block.Color = QColor(241, 161, 0, 255);
    }
    else if (block.AboutBlock.BlockNumber == 2) {
        block.Color =  QColor(1, 0, 241, 255);
    }
    else if (block.AboutBlock.BlockNumber == 3) {
        block.Color = QColor(240, 240, 0, 255);
    }
    else if (block.AboutBlock.BlockNumber == 4) {
        block.Color = QColor(1, 240, 1, 255);
    }
    else if (block.AboutBlock.BlockNumber == 5) {
        block.Color = QColor(241, 0, 1, 255);
    }
    else if (block.AboutBlock.BlockNumber == 6) {
        block.Color = QColor(160, 0, 240, 255);
    }
    else if (block.AboutBlock.BlockNumber == 7) {
        block.Color = QColor(0, 240, 240, 255);
    }
}

void Tetris_View::StartGameOver()
{
    killTimer(TimerFallBlocks);
    killTimer(TimerSpeedIncrease);
    killTimer(TimerImageRefresh);

    GameOver_View window(TetrisNow, TetrisNow->GetScore());

    window.setModal(true);
    window.exec();

    SpeedInMs = TetrisNow->GetInitialSpeedBlock();
    UpdateInterval= DEFAULT_UPDATE_INTERVAL;
    TimeSpeedIncrease = SPEED_INCREASE_INTERVAL;

    TimerFallBlocks = startTimer(SpeedInMs);
    TimerImageRefresh = startTimer(UpdateInterval);
    TimerSpeedIncrease = startTimer(TimeSpeedIncrease);
}

void Tetris_View::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    CurrentBlock.AboutBlock = TetrisNow->GetCurrentBlock();
    ColorAssignment(CurrentBlock);
    NextBlock.AboutBlock = TetrisNow->GetNextBlock();
    ColorAssignment(NextBlock);

    int GameArea[FIELD_LENGTH][FIELD_WIDTH];

    TetrisNow->CopyingGameArea(GameArea);

    painter.setBrush(QBrush(QColor(128, 128, 128, TRANSPARENCY_DEGREE), Qt::SolidPattern));
    painter.drawRect(INDENT, INDENT, FieldWidth * BLOCK_LENGTH, FieldLength * BLOCK_LENGTH);

    painter.drawRect(INDENT*3 + FieldWidth*BLOCK_LENGTH, INDENT, 4 * BLOCK_LENGTH, 5 * BLOCK_LENGTH);
    painter.setBrush(QBrush(NextBlock.Color, Qt::SolidPattern));
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (NextBlock.AboutBlock.BlockMatrix[i][j]) {
                painter.drawRect(INDENT*3 + FieldWidth*BLOCK_LENGTH + j*BLOCK_LENGTH, INDENT + (i + 1)*BLOCK_LENGTH, BLOCK_LENGTH, BLOCK_LENGTH);
            }
        }
    }

    for (int i = 0; i < FieldLength; ++i) {
        for (int j = 0; j < FieldWidth; ++j) {
            if (GameArea[i][j] == 2) {
                painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
                painter.drawRect(j*BLOCK_LENGTH + INDENT, i*BLOCK_LENGTH + INDENT, BLOCK_LENGTH, BLOCK_LENGTH);
            }
            else if (GameArea[i][j] == 1) {
                painter.setBrush(QBrush(CurrentBlock.Color, Qt::SolidPattern));
                painter.drawRect(j*BLOCK_LENGTH + INDENT, i*BLOCK_LENGTH + INDENT, BLOCK_LENGTH, BLOCK_LENGTH);

                for (int i = 0; i < 2; ++i) {
                    int x;

                    if (i == 0) {
                        x = CurrentBlock.AboutBlock.BlockBorders.LeftBorder;
                    }
                    else {
                        x = CurrentBlock.AboutBlock.BlockBorders.RightBorder;
                    }

                    int y = CurrentBlock.AboutBlock.BlockBorders.LowerBorder;
                    while (CurrentBlock.AboutBlock.BlockMatrix[y][x] != 1) {
                        --y;
                    }

                    y += CurrentBlock.AboutBlock.BlockCoordinates.CoordinateY + 1;

                    if (i == 1) {
                        ++x;
                    }

                    while (GameArea[y][x + CurrentBlock.AboutBlock.BlockCoordinates.CoordinateX] == 0 && (y < FieldLength)) {
                        painter.drawLine((CurrentBlock.AboutBlock.BlockCoordinates.CoordinateX + x)*BLOCK_LENGTH + INDENT, y*BLOCK_LENGTH + INDENT,
                                         (CurrentBlock.AboutBlock.BlockCoordinates.CoordinateX + x)*BLOCK_LENGTH + INDENT, (y + 1)*BLOCK_LENGTH + INDENT);
                        ++y;
                    }
                }
            }
        }
    }

    painter.setPen(Qt::white);
    painter.setFont(QFont("Comfortaa", 16, QFont::Bold));
    painter.drawText(QRect(INDENT*2 + FieldWidth*BLOCK_LENGTH, INDENT*2 + 5*BLOCK_LENGTH, BLOCK_LENGTH*5, BLOCK_LENGTH*4),
                     Qt::AlignCenter, "Score: " + QString::number(TetrisNow->GetScore()));
}


void Tetris_View::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == TimerFallBlocks) {
        TetrisNow->BlockMovement(Down);
    }
    if (event->timerId() == TimerImageRefresh) {
        if (TetrisNow->GetIsGameOver()) {
            StartGameOver();
        }
        update();
    }
    if (event->timerId() == TimerSpeedIncrease) {
        SpeedInMs /= ACCELERATION_COEFFICIENT;
        TimerFallBlocks = startTimer(SpeedInMs);
    }
}

void Tetris_View::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up) {
        TetrisNow->BlockMovement(Up);
    }
    else if (event->key() == Qt::Key_Down) {
        TetrisNow->BlockMovement(Down);
        TimerFallBlocks = startTimer(SpeedInMs);
    }
    else if (event->key() == Qt::Key_Left) {
        TetrisNow->BlockMovement(Left);
    }
    else if (event->key() == Qt::Key_Right) {
        TetrisNow->BlockMovement(Right);
    }
    else if (event->key() == Qt::Key_Space) {
        TetrisNow->BlockMovement(Space);
    }
}
