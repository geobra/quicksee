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
    void incrementTries();
    void incrementCorrect();
    void incrementFailure();
    void setInputTextColor(int color);

    QString lastDisplayedStr_{};
    Ui::MainWindow *ui;

private slots:
    void goPressed();
    void testPressed();
};
#endif // MAINWINDOW_H
