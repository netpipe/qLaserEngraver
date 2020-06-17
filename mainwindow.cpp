#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>

extern "C" {
int mainpottrace(int argc, char **argv);
int mainmkbitmap(int argc, char **argv);

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    char *argv1[]={"appname","-h","test"};
         int argc1 = sizeof(argv1) / sizeof(char*) - 1;

      mainpottrace(argc1,argv1);

         char *argv2[]={"appname","-h","test"};
              int argc2 = sizeof(argv1) / sizeof(char*) - 1;

              // mainmkbitmap(argc2,argv2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{

}

void MainWindow::on_load_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open rx/tx"), "./", tr("rx/tx files (*.png *.jpg)"));


    QImage *img_object = new QImage();
    img_object->load(fileName);
 //   QImage::Format format = img_object->format();
 //   QImage imageF = img_object->convertToFormat(QImage::Format_Grayscale8);
 //   imageF = imageF.convertToFormat(QImage::Format_Indexed8, Qt::ThresholdDither|Qt::AutoColor);

    img_object->convertToFormat(QImage::Format_Indexed8, Qt::ThresholdDither|Qt::AutoColor);
            for (int ii = 0; ii < img_object->width(); ii++) {
                for (int jj = 0; jj < img_object->height(); jj++) {
                    int gray = qGray(img_object->pixel(ii, jj));
                    img_object->setPixel(ii, jj, QColor(gray, gray, gray).rgb());
                }
            }


            // fastgreyscale
 //   img_object->convertToFormat(QImage::Format_Grayscale8);
//        for (int ii = 0; ii < img_object->height(); ii++) {
//            uchar* scan = img_object->scanLine(ii);
//            int depth =4;

//            for (int jj = 0; jj < img_object->width(); jj++) {

//                QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + jj*depth);
//                int gray = qGray(*rgbpixel);
//                *rgbpixel = QColor(gray, gray, gray).rgba();

//            }
//        }


  //  QPixmap image = QPixmap::fromImage(imageF);
      QPixmap image = QPixmap::fromImage(*img_object);
 //   QPixmap scaled_img = image.scaled(this->width(), this->height(), Qt::KeepAspectRatio);
    QPixmap scaled_img = image.scaled(ui->graphicsView->width(), ui->graphicsView->height(), Qt::KeepAspectRatio);
    QGraphicsScene *scene= new QGraphicsScene();
   // scene->addItem(new QGraphicsSvgItem("./tmp.svg"));
    scene->addPixmap(scaled_img);
    scene->setSceneRect(scaled_img.rect());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

}

void MainWindow::on_generate_clicked()
{
    float x = 0;
    float y = 0;
initial = 1;

step = 0.01;
depth = 0.5;

 QImage *img_object = new QImage();
     img_object->load(fileName);
    for (int ii = 0; ii < img_object->width(); ii++) {
//            g.cut(x, y, d, feed=12)
        //    x -= step;
        for (int jj = 0; jj < img_object->height(); jj++) {
            float gray = qGray(img_object->pixel(ii, jj));
            img_object->setPixel(ii, jj, QColor(gray, gray, gray).rgb());
//          d = float(im.getpixel((i, h-j-1)) / 255.0) * depth - depth
            x += step;
            cut(x, y, gray, 12);
//          g.cut(y=y) //end gcode
        }
        x =0;
        y += step;  // steps to make picture larger on printed peice
    }
    QFile file("result_storage.txt");
          if(file.open(QIODevice::ReadWrite | QIODevice::Append)){
                        QTextStream stream(&file);
                        stream << "M2";
          }
          file.close();
    //end gcode
}

void MainWindow::cut(float x,float y,float z,int feed){


    // todo check saftys for non lazer depth cuts

    QFile file("result_storage.txt");
          if(file.open(QIODevice::ReadWrite | QIODevice::Append)){
                        QTextStream stream(&file);
           if (initial){
                       stream <<   "G00 X0.0000 Y0.0000"<< endl;
                       stream <<   "G97"<< endl;
                       stream <<   "G17"<< endl;
                        stream <<  "G20"<< endl;
                        stream <<  "G40"<< endl;
                        stream <<  "M3"<< endl;
                        stream <<  "G64"<< endl;
                        stream <<  "G01 F12.0000"<< endl;
                        initial = 0;
          }

                        if ( lasty == y ){
                              stream <<   "G01 X" << QString::number(x) << endl;
                              stream << "G97 S" << QString::number(z) << endl; //(-z*160)
                        }
                        else{
                             stream <<   "G01 Y" << QString::number(y) << endl;

                        }
          }
          file.close();

          lasty = y;
          lastx = x;
          lastz = z;
  //  file.write(format(self.rapid(x, y, z, a, gcode="G01", feed=feed)+"\n"))
  //  file.write("G97 S{}".format(-z*160)+"\n")



}

