#include "gameover_view.h"
#include "ui_gameover_view.h"
#include "tetris.h"
#include "leaderboard_view.h"

GameOver_View::GameOver_View(Tetris *tetris, int score) :
    TetrisNow(tetris),
    Score(score),
    ui(new Ui::GameOver_View),
    IsRestart(false),
    NeedHide(false)
{
    setFixedSize(612,612);

    QBrush* brush = new QBrush();
    QPalette* palette = new QPalette();

    brush->setTextureImage(QImage(":/image/GameOver.jpg"));
    palette->setBrush(QPalette::Window, *brush);

    setPalette(*palette);

    ui->setupUi(this);
    ui->label_2->setStyleSheet("color: rgb(255, 255, 255)");
    ui->label_2->setText("Score: " + QString::number(Score));

}

GameOver_View::~GameOver_View()
{
    delete ui;
}

void GameOver_View::on_pushButton_2_clicked()
{
    qApp->exit(0);
}


void GameOver_View::on_pushButton_3_clicked()
{
    TetrisNow->StartGame();
    IsRestart = true;
    close();
}

void GameOver_View::on_pushButton_4_clicked()
{
    Leaderboard_View window(Score, &NeedHide);
    window.setModal(true);
    window.exec();
}

void GameOver_View::on_GameOver_View_finished(int result)
{
    if (!IsRestart) {
        qApp->exit(0);
    }
}
