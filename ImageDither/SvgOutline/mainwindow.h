#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "leftwidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
#include <QImage>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QImage img_org, img_new;
    QString path;

    LeftWidget * m_lw;
public slots:
    void onLoad();
    void onDither();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
