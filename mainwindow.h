#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


    QString fileName;

    float step = 0.01;
    float depth = 0.5;

    float lastx;
    float lasty;
    float lastz;
    int initial;
    void cut(float x,float y,float z,int feed);


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_load_clicked();

    void on_generate_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
