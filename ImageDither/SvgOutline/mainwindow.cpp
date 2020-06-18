#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "svgreader.h"
#include "leftwidget.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->btn_load, SIGNAL(clicked()), this , SLOT(onLoad()));
    QObject::connect(ui->btn_dither, SIGNAL(clicked()), this , SLOT(onDither()));

    m_lw = new LeftWidget(this->centralWidget());
    m_lw->setGeometry( ui->lb_left->geometry());


}

MainWindow::~MainWindow()
{
    delete ui;
}
//when press load button
void MainWindow::onLoad()
{
      QString newPath = QFileDialog::getOpenFileName(this, "Open SVG",
                                                      ".", tr("SVG files (*.svg)"));
       if (newPath.isEmpty())
           return;

       path = newPath;
       // To set a graphic scene objects, received them with a method getElements
       m_lw->m_list = SvgReader::getElements(path);
       m_lw->update();

}

int find_closest_palette_color(int x)
{
    return qRound((float)x / 255.0) * 255;
}

//when press dither button
void MainWindow::onDither()
{
    img_new = img_org;
    int w = img_new.width();
    int h = img_new.height();


    int i,j;
    //make gray
    for(i = 0; i<w; i++)
    {
        for(j = 0; j<h; j++)
        {
            int gray = qGray(img_new.pixel(i,j));
            img_new.setPixel(i, j, QColor(gray,gray,gray).rgb());
        }
    }
    //itereate each row: y axis
    for(j = 0; j<h; j++)
    {
        //iterate each column: x axis
        for(i = 0; i<w; i++)
        {
            int old_pixel = qGray(img_new.pixel(i,j));
            int new_pixel = find_closest_palette_color(old_pixel);

            img_new.setPixel(i,j, QColor(new_pixel, new_pixel, new_pixel).rgb());
            //error
            int quant_error = old_pixel - new_pixel;

            //modify 4 pixels around it
            if( i+1 < w)
            {
                int v = qGray(img_new.pixel(i+1,j));
                v = v + quant_error * 7 /16;
                img_new.setPixel(i+1,j, QColor(v, v, v).rgb());
            }
            if( i+1 < w && j+1 <h)
            {
                int v = qGray(img_new.pixel(i+1,j+1));
                v = v + quant_error * 1 /16;
                img_new.setPixel(i+1,j+1, QColor(v, v, v).rgb());
            }
            if( j+1 < h)
            {
                int v = qGray(img_new.pixel(i,j+1));
                v = v + quant_error * 5 /16;
                img_new.setPixel(i,j+1, QColor(v, v, v).rgb());
            }

            if( j+1 < h && i)
            {
                int v = qGray(img_new.pixel(i-1,j+1));
                v = v + quant_error * 3 /16;
                img_new.setPixel(i-1,j+1, QColor(v, v, v).rgb());
            }
        }
    }



}
