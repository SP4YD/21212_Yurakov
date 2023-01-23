#include "dr_mario_view.h"
#include "ui_dr_mario_view.h"

#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>
#include <time.h>

Dr_Mario_View::Dr_Mario_View(Dr_Mario* Model) :
    ModelNow (Model),
    ui(new Ui::Dr_Mario_View)
{
    BackGroundBrush = new QBrush();
    BackGroundPalette = new QPalette();

    BackGroundBrush->setTextureImage(QImage(":/images/Mario.jpg"));
    BackGroundPalette->setBrush(QPalette::Window, *BackGroundBrush);
    this->setPalette(*BackGroundPalette);

    ui->setupUi(this);
    setFixedSize(830, 725);
    IsNewStage = false;

    SpeedInMs = ModelNow->GetInitialSpeedPill();
    UpdateInterval= DEFAULT_UPDATE_INTERVAL;

    TimerFallPills = startTimer(SpeedInMs);
    TimerImageRefresh = startTimer(UpdateInterval);

    FieldWidth = FIELD_WIDTH;
    FieldLength = FIELD_LENGTH;
}

Dr_Mario_View::~Dr_Mario_View()
{
    delete BackGroundBrush;
    delete BackGroundPalette;
    delete ui;
}

void Dr_Mario_View::StartGameOver()
{
    BackGroundBrush->setTextureImage(QImage(":/images/MarioGameOver.jpg"));
    BackGroundPalette->setBrush(QPalette::Window, *BackGroundBrush);
    this->setPalette(*BackGroundPalette);

    killTimer(TimerFallPills);
    killTimer(TimerImageRefresh);
}

void Dr_Mario_View::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Comfortaa", 22, QFont::Bold));
    painter.drawText(QRect(600, 435, 80, 50), Qt::AlignCenter, "ЭТАП");
    painter.setFont(QFont("Comfortaa", 25, QFont::Bold));
    painter.drawText(QRect(700, 475, 50, 50), Qt::AlignRight, QString::number(ModelNow->GetNumStage()));

    painter.setFont(QFont("Comfortaa", 22, QFont::Bold));
    painter.drawText(QRect(590, 585, 150, 50), Qt::AlignCenter, "ВИРУСЫ");
    painter.setFont(QFont("Comfortaa", 25, QFont::Bold));
    painter.drawText(QRect(700, 625, 50, 50), Qt::AlignRight, QString::number(ModelNow->GetCountVirus()));



    painter.setFont(QFont("Comfortaa", 22, QFont::Bold));
    painter.drawText(QRect(40, 150, 150, 50), Qt::AlignCenter, "РЕКОРД");
    painter.setFont(QFont("Comfortaa", 25, QFont::Bold));
    painter.drawText(QRect(45, 190, 190, 50), Qt::AlignRight, QString::number(ModelNow->GetRecord()));

    painter.drawText(QRect(48, 230, 90, 50), Qt::AlignCenter, "СЧЁТ");
    painter.setFont(QFont("Comfortaa", 25, QFont::Bold));
    painter.drawText(QRect(45, 270, 190, 50), Qt::AlignRight, QString::number(ModelNow->GetScore()));

    if (ModelNow->GetIsGameOver() || ModelNow->GetIsGameWin()) {
        return;
    }

    CurrentPill = ModelNow->GetCurrentPill();
    NextPill = ModelNow->GetNextPill();

    int PlayingField[FIELD_LENGTH][FIELD_WIDTH];

    ModelNow->CopyingPlayingField(PlayingField);

    for (int j = 0; j < 2; ++j) {
        if (NextPill.PillMatrix[1][j] == 1) {
            painter.setBrush(QBrush(QColor(255, 37, 78, 255), Qt::SolidPattern));
        }

        if (NextPill.PillMatrix[1][j] == 2) {
            painter.setBrush(QBrush(QColor(251, 189, 27, 255), Qt::SolidPattern));
        }

        if (NextPill.PillMatrix[1][j] == 3) {
            painter.setBrush(QBrush(QColor(6, 216, 255, 255), Qt::SolidPattern));
        }

        painter.drawRect(LEFT_INDENTATION_FOR_NEXT_PILL + j*PILL_LENGTH, TOP_INDENTATION_FOR_NEXT_PILL + 2*PILL_LENGTH, PILL_LENGTH, PILL_LENGTH);
    }

    for (int i = 0; i < FieldLength; ++i) {
        for (int j = 0; j < FieldWidth; ++j) {
            if (PlayingField[i][j] == 1) {
                painter.setBrush(QBrush(QColor(255, 37, 78, 255), Qt::SolidPattern));
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD, PILL_LENGTH, PILL_LENGTH);
            }
            else if (PlayingField[i][j] == 2) {
                painter.setBrush(QBrush(QColor(251, 189, 27, 255), Qt::SolidPattern));
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD, PILL_LENGTH, PILL_LENGTH);
            }
            else if (PlayingField[i][j] == 3) {
                painter.setBrush(QBrush(QColor(6, 216, 255, 255), Qt::SolidPattern));
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD, PILL_LENGTH, PILL_LENGTH);
            }
            else if (PlayingField[i][j] == -1) {
                painter.setBrush(QBrush(QColor(255, 37, 78, 255), Qt::SolidPattern));
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD, PILL_LENGTH, PILL_LENGTH);
                painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD + 3, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD + 4, 8, 8);
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD + 15, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD + 4, 8, 8);
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD + 7, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD + 19, 13, 2);
                painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD + 5, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD + 7, 4, 4);
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD + 16, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD + 7, 4, 4);
            }
            else if (PlayingField[i][j] == -2) {
                painter.setBrush(QBrush(QColor(251, 189, 27, 255), Qt::SolidPattern));
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD, PILL_LENGTH, PILL_LENGTH);
                painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD + 3, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD + 4, 8, 8);
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD + 15, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD + 4, 8, 8);
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD + 7, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD + 19, 13, 2);
                painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD + 5, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD + 7, 4, 4);
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD + 16, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD + 7, 4, 4);
            }
            else if (PlayingField[i][j] == -3) {
                painter.setBrush(QBrush(QColor(6, 216, 255, 255), Qt::SolidPattern));
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD, PILL_LENGTH, PILL_LENGTH);
                painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD + 3, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD + 4, 8, 8);
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD + 15, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD + 4, 8, 8);
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD + 7, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD + 19, 13, 2);
                painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD + 5, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD + 7, 4, 4);
                painter.drawRect(j*PILL_LENGTH + LEFT_INDENTATION_FOR_FIELD + 16, i*PILL_LENGTH + TOP_INDENTATION_FOR_FIELD + 7, 4, 4);
            }
        }
    }
}


void Dr_Mario_View::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == TimerFallPills && !ModelNow->GetIsGameWin()) {
        ModelNow->PillMovement(Down);
    }
    if (event->timerId() == TimerImageRefresh) {
        if (ModelNow->GetIsGameOver()) {
            StartGameOver();
        }
        else if (ModelNow->GetIsGameWin() && !IsNewStage) {
            BackGroundBrush->setTextureImage(QImage(":/images/MarioNextStage.jpg"));
            BackGroundPalette->setBrush(QPalette::Window, *BackGroundBrush);
            this->setPalette(*BackGroundPalette);
            killTimer(TimerFallPills);
            IsNewStage = true;
        }
        update();
    }
}

void Dr_Mario_View::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up && !ModelNow->GetIsGameWin()) {
        ModelNow->PillMovement(Up);
    }
    else if (event->key() == Qt::Key_Down && !ModelNow->GetIsGameWin()) {
        ModelNow->PillMovement(Down);
        TimerFallPills = startTimer(SpeedInMs);
    }
    else if (event->key() == Qt::Key_Left && !ModelNow->GetIsGameWin()) {
        ModelNow->PillMovement(Left);
    }
    else if (event->key() == Qt::Key_Right && !ModelNow->GetIsGameWin()) {
        ModelNow->PillMovement(Right);
    }
    else if (event->key() == Qt::Key_Space && ModelNow->GetIsGameOver()) {
        BackGroundBrush->setTextureImage(QImage(":/images/Mario.jpg"));
        BackGroundPalette->setBrush(QPalette::Window, *BackGroundBrush);
        this->setPalette(*BackGroundPalette);

        ModelNow->StartNewGame();
        SpeedInMs = ModelNow->GetInitialSpeedPill();

        TimerFallPills = startTimer(SpeedInMs);
        TimerImageRefresh = startTimer(UpdateInterval);
    }
    else if (event->key() == Qt::Key_Space && ModelNow->GetIsGameWin()) {
        BackGroundBrush->setTextureImage(QImage(":/images/Mario.jpg"));
        BackGroundPalette->setBrush(QPalette::Window, *BackGroundBrush);
        this->setPalette(*BackGroundPalette);

        ModelNow->ContinueGame();

        TimerImageRefresh = startTimer(UpdateInterval);
        SpeedInMs /= ACCELERATION_COEFFICIENT;
        TimerFallPills = startTimer(SpeedInMs);
        IsNewStage = false;
    }
    else if (event->key() == Qt::Key_Space) {
        ModelNow->PillMovement(Space);
    }

}
