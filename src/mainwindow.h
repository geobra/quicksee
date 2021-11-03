#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QChar getRandomChar();
    QChar getRandomSymbol();
    void incrementTries();
    void incrementCorrect();
    void incrementFailure();
    void setInputTextColor(int color);

    QString lastDisplayedStr_{};
    Ui::MainWindow *ui;

private slots:
    void lcdCharInc();
    void lcdCharDec();

    void lcdTimeInc();
    void lcdTimeDec();

    void goPressed();
    void testPressed();
};
#endif // MAINWINDOW_H
