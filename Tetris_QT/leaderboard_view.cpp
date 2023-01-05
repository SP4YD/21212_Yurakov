#include "leaderboard_view.h"
#include "ui_leaderboard_view.h"

#include <fstream>
#include <stdio.h>
#include <QFile>
#include <string>
#include <sstream>
#include <QTextStream>

Leaderboard_View::Leaderboard_View(int score, bool *flag, QWidget *parent) :
    QDialog(parent),
    Table("./Leaderboard.txt"),
    NeedHide(flag),
    ui(new Ui::Leaderboard_View),
    Score(score)
{
    ui->setupUi(this);

    if (*NeedHide) {
        ui->lineEdit->hide();
        ui->pushButton->hide();
    }
    update();

    setFixedSize(477, 717);

    QBrush* brush = new QBrush();
    QPalette* palette = new QPalette();

    brush->setTextureImage(QImage(":/image/TabletVertic(2).jpg"));
    palette->setBrush(QPalette::Window, *brush);

    setPalette(*palette);

    Table.open(QFile::ReadOnly | QFile::Text);

    std::string tmpScore;
    std::string nickName;
    std::string tmpstr;
    QString str;
    while(!Table.atEnd()) {
        str = Table.readLine();
        tmpstr = str.toStdString();
        std::istringstream ist (tmpstr);
        ist >> tmpScore;
        ist >> nickName;
        NickNameByScore.insert(std::pair<int, std::string>(stoi(tmpScore), nickName));
    }

    FillingInTheTable();

    Table.close();
}

Leaderboard_View::~Leaderboard_View()
{
    delete ui;
}

void Leaderboard_View::FillingInTheTable()
{
    if (NickNameByScore.size()) {
        std::multimap<int, std::string, std::greater<int>>::iterator itr = NickNameByScore.begin();
        ui->label_4->setText(QString::fromStdString(itr->second));
        ui->label_5->setText(QString::number(itr->first));
        ++itr;
        if (itr != NickNameByScore.end()) {
            ui->label_7->setText(QString::fromStdString(itr->second));
            ui->label_8->setText(QString::number(itr->first));
            ++itr;
            if (itr != NickNameByScore.end()) {
                ui->label_10->setText(QString::fromStdString(itr->second));
                ui->label_11->setText(QString::number(itr->first));
                ++itr;
                if (itr != NickNameByScore.end()) {
                    ui->label_13->setText(QString::fromStdString(itr->second));
                    ui->label_14->setText(QString::number(itr->first));
                    ++itr;
                    if (itr != NickNameByScore.end()) {
                        ui->label_16->setText(QString::fromStdString(itr->second));
                        ui->label_17->setText(QString::number(itr->first));
                    }
                }
            }
        }
    }
}

void Leaderboard_View::paintEvent(QPaintEvent *)
{
    QPainter paint(this);

    paint.setBrush(QBrush(QColor(128, 128, 128, 180), Qt::SolidPattern));
    paint.drawRect(50, 50, 377, 450);
}

void Leaderboard_View::on_pushButton_clicked()
{
    QString str = ui->lineEdit->text();
    NickName = str.toStdString();
    if (NickName.length() < 12 && NickName.length() > 0) {
        *NeedHide = true;

        ui->lineEdit->hide();
        ui->pushButton->hide();

        std::multimap<int, std::string, std::greater<int>>::iterator itr = NickNameByScore.begin();

        for (int i = 0; itr != NickNameByScore.end(); ++i) {
            if (itr->second == NickName) {
                if (itr->first < Score) {
                    NickNameByScore.erase(itr);
                    break;
                }
                else {
                    return;
                }
            }
            ++itr;
        }

        NickNameByScore.insert(std::pair<int, std::string>(Score, NickName));

        FillingInTheTable();
    }
}

void Leaderboard_View::on_Leaderboard_View_finished(int result)
{
    Table.open(QIODevice::WriteOnly);
    QTextStream out(&Table);

    std::multimap<int, std::string, std::greater<int>>::iterator itr = NickNameByScore.begin();

    for (int i = 0; i < 5 && itr != NickNameByScore.end(); ++i) {
        out << QString::fromStdString(std::to_string(itr->first) + " " + itr->second + "\n");
        ++itr;
    }

    Table.close();
}

