//#include "laserImage.h"

////https://stackoverflow.com/questions/27949569/convert-a-qimage-to-grayscale

//TestImage::TestImage(QObject *parent)
//    : QObject(parent)
//    , imgop("path_to_test_image.png")
//    , imgfast("path_to_test_image.png")
//{
//}


//void TestImage::grayscaleOp()
//{
//    QBENCHMARK
//    {
//        QImage& image = imgop;

//        for (int ii = 0; ii < image.width(); ii++) {
//            for (int jj = 0; jj < image.height(); jj++) {
//                int gray = qGray(image.pixel(ii, jj));
//                image.setPixel(ii, jj, QColor(gray, gray, gray).rgb());
//            }
//        }
//    }
//}


//void TestImage::grayscaleFast()
//{

//    QBENCHMARK {

//    QImage& image = imgfast;


//    for (int ii = 0; ii < image.height(); ii++) {
//        uchar* scan = image.scanLine(ii);
//        int depth =4;
//        for (int jj = 0; jj < image.width(); jj++) {

//            QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + jj*depth);
//            int gray = qGray(*rgbpixel);
//            *rgbpixel = QColor(gray, gray, gray).rgba();
//        }
//    }

//    }
//}
