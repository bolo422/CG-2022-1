#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void drawText(Mat& image);

int main()
{
    cout << "Built with OpenCV " << CV_VERSION << endl;
    Mat imgOriginal;
    Mat imgCinza, imgBlur, imgCanny, imgBlurCanny, imgDilate, imgErode;
    Mat imgCrop, imgReSize, imgScale;

    imgOriginal = imread("pikachu.jpg");

    cvtColor(imgOriginal, imgCinza, COLOR_BGR2GRAY);

    GaussianBlur(imgCinza, imgBlur, Size(15, 15), 5, 0);

    Canny(imgCinza, imgCanny, 25, 75);
    Canny(imgBlur, imgBlurCanny, 25, 75);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(imgBlurCanny, imgDilate, kernel);
    
    erode(imgDilate, imgErode, kernel);

    Rect areaCrop(423, 416, 200, 200); //a partir do ponto 100x100 recorto uma area de 200/200

    //novaIMG  img Base   area do crop
    imgCrop = imgOriginal(areaCrop);

    cout << imgOriginal.size();
    resize(imgBlur, imgReSize, Size(50, 60));
    resize(imgOriginal, imgScale, Size(), 0.4, 0.4);

    imshow("Pikachu Normal", imgOriginal);
    imshow("Pikachu Grayscale", imgCinza);
    imshow("Pikachu Borrado", imgBlur);
    imshow("Pikachu Canny1", imgCanny);
    imshow("Pikachu Canny2", imgBlurCanny);
    imshow("Pikachu Dilatado", imgDilate);
    imshow("Pikachu Erodido", imgErode);
    imshow("Pikachu de Cropped", imgCrop);
    imshow("Pikachu Deformado", imgReSize);
    imshow("Pikachu Escalado", imgScale);
    
    waitKey(0);

    //VideoCapture capture;

    //capture.open(0);
    //if (capture.isOpened())
    //{
    //    cout << "Capture is opened" << endl;
    //    for (;;)
    //    {
    //        capture >> imgOriginal;
    //        if (imgOriginal.empty())
    //            break;
    //        //drawText(imgOriginal);
    //        cvtColor(imgOriginal, imgCinza, COLOR_BGR2GRAY);
    //        GaussianBlur(imgCinza, imgBlur, Size(5, 5), 5, 0);
    //        Canny(imgCinza, imgCanny, 25, 75);
    //        Canny(imgBlur, imgBlurCanny, 25, 75);
    //        imshow("Sample", imgCanny);
    //        if (waitKey(10) >= 0)
    //            break;
    //    }
    //}
    //else
    //{
    //    cout << "No capture" << endl;
    //    imgOriginal = Mat::zeros(480, 640, CV_8UC1);
    //    drawText(imgOriginal);
    //    imshow("Sample", imgOriginal);
    //    waitKey(0);
    //}
    return 0;
}

void drawText(Mat& image)
{
    putText(image, "Hello OpenCV",
        Point(20, 50),
        FONT_HERSHEY_COMPLEX, 1, // font face and scale
        Scalar(255, 255, 255), // white
        1, LINE_AA); // line thickness and type
}
