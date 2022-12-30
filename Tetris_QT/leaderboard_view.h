#pragma once

#ifndef Leaderboard_View_H
#define Leaderboard_View_H

#include <QDialog>
#include <QPainter>
#include <set>
#include <map>
#include <QFile>

namespace Ui {
class Leaderboard_View;
}

class Leaderboard_View : public QDialog
{
    Q_OBJECT

public:
    explicit Leaderboard_View(int score = 0, bool *flag = nullptr, QWidget *parent = nullptr);

    ~Leaderboard_View();

    void FillingInTheTable();

    virtual void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

    void on_Leaderboard_View_finished(int result);

private:
    Ui::Leaderboard_View *ui;
    std::string NickName;
    int Score;
    //bool FirstTime;
    bool *NeedHide;
    std::multimap<int, std::string, std::greater<int>> NickNameByScore;
    QFile Table;
};

#endif // Leaderboard_View_H
