#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QTimer>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->horizontalSliderChars->setSliderPosition(3);
    ui->lcdNumberChars->display(3);
    ui->horizontalSliderTime->setSliderPosition(3);
    ui->lcdNumberTime->display(3);

    // make go button blue
    QPalette pal = ui->pushButtonGo->palette();
    pal.setColor(QPalette::Button, QColor(Qt::blue));
    ui->pushButtonGo->setAutoFillBackground(true);
    ui->pushButtonGo->setPalette(pal);
    ui->pushButtonGo->update();

    connect(ui->pushButtonGo, SIGNAL(clicked()), this, SLOT(goPressed()));

    connect(ui->pushButtonTest, SIGNAL(clicked()), this, SLOT(testPressed()));
    connect(ui->lineEditTest, SIGNAL(returnPressed()), this, SLOT(testPressed()));

}

void MainWindow::goPressed()
{
    incrementTries();

    lastDisplayedStr_.clear();
    auto nrOfChars = ui->lcdNumberChars->value();

    for(auto i = 0; i < nrOfChars; i++)
    {
        QChar randomChar = getRandomChar();
        lastDisplayedStr_ += randomChar;
    }

    // display the text
    ui->textEdit->setAlignment(Qt::AlignCenter);
    ui->textEdit->setText(lastDisplayedStr_);

    // remove the text after given timeout
    auto timeout = ui->lcdNumberTime->value() * 100;
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->start(timeout);

    connect(timer, &QTimer::timeout, [=]() {
      ui->textEdit->clear();
      timer->deleteLater();
    } );
}

void MainWindow::testPressed()
{
    QString enteredText = ui->lineEditTest->text();
    ui->lineEditTest->clear();

    if (enteredText.isEmpty())
    {
        goPressed();
    }
    else
    {
        if (enteredText.compare(lastDisplayedStr_, Qt::CaseInsensitive) == 0)
        {
            incrementCorrect();

            setInputTextColor(0);
        }
        else
        {
            incrementFailure();

            setInputTextColor(1);
        }

        auto timeout = 6 * 100;
        QTimer *timer = new QTimer(this);
        timer->setSingleShot(true);
        timer->start(timeout);

        connect(timer, &QTimer::timeout, [=]() {
          this->setInputTextColor(2);
          timer->deleteLater();
        } );
    }
}

void MainWindow::setInputTextColor(int color) // 0: green, 1: orange, 2: no
{
    // display a colored background for a short period of time
    Qt::GlobalColor targetColor = Qt::green;
    if (color == 1)
        targetColor = Qt::red;
    else if (color == 2)
        targetColor = Qt::transparent;

    QPalette pal = ui->textEdit->palette();
    pal.setColor(QPalette::Base, QColor(targetColor));
    ui->textEdit->setAutoFillBackground(true);
    ui->textEdit->setPalette(pal);
    ui->textEdit->update();
}

void MainWindow::incrementTries()
{
    auto tries = ui->lcdNumberTries->value();
    tries++;
    ui->lcdNumberTries->display(tries);
}

void MainWindow::incrementCorrect()
{
    auto tries = ui->lcdNumberCorrect->value();
    tries++;
    ui->lcdNumberCorrect->display(tries);
}

void MainWindow::incrementFailure()
{
    auto tries = ui->lcdNumberWrong->value();
    tries++;
    ui->lcdNumberWrong->display(tries);
}


QChar MainWindow::getRandomChar()
{
    int diff = 'Z'-'A';
    char c = 'A'+(QRandomGenerator::global()->generate() % diff);

    return c;
}

MainWindow::~MainWindow()
{
    delete ui;
}

