#pragma once

#ifndef GameOver_View_H
#define GameOver_View_H

#include "tetris.h"

#include <QDialog>

namespace Ui {
class GameOver_View;
}

class GameOver_View : public QDialog
{
    Q_OBJECT

public:
    explicit GameOver_View(Tetris *tetris = nullptr, int score = 0);

    ~GameOver_View();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_GameOver_View_finished(int result);

    void on_pushButton_4_clicked();

private:
    bool IsRestart;
    bool NeedHide;
    Ui::GameOver_View *ui;
    Tetris *TetrisNow;
    int Score;
};

#endif // GameOver_View_H
