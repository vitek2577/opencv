
#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

void medianfilter (IplImage* dst, IplImage* image) {
    cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
    cvShowImage("original", image);
    cvNamedWindow("smooth", CV_WINDOW_AUTOSIZE);
    cvSmooth(image, dst, CV_MEDIAN, 3, 3);
    cvShowImage("smooth", dst);
    cvWaitKey(0);
    cvDestroyWindow("original");
    cvDestroyWindow("smooth");
}

void convolution(IplImage* dst1, IplImage* image) {
    int size = 0;
    std::cout << "Enter quantity of matrix elements" << "\n";
    std::cin >> size;
    std::cout << "Enter matrix elements" << "\n";
    float *kernel = new float[size];
    for (int i = 0; i < size; ++i) {
        std::cin >> kernel[i];
    }
    
    CvMat kernel_matrix = cvMat(3, 3, CV_32FC1, kernel);
    cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
    cvShowImage("original", image);
    cvNamedWindow("convolution", CV_WINDOW_AUTOSIZE);
    cvFilter2D(image, dst1, &kernel_matrix, cvPoint(-1, -1));
    cvShowImage("convolution", dst1);
    cvWaitKey(0);
    delete[] kernel;
    cvDestroyWindow("original");
    cvDestroyWindow("convolution");
}

void net(IplImage* dst2, IplImage* image) {
    int height1;
    int width1;
    std::cout << "Enter height and width" << "\n";
    std::cin >> height1 >> width1;
    for (int y = 0; y<dst2->height; y += height1) {
        uchar* ptr = (uchar*)(dst2->imageData + y * dst2->widthStep);
        for (int x = 0; x<dst2->width; ++x) {
            ptr[3 * x] = 0;
            ptr[3 * x + 1] = 0;
            ptr[3 * x + 2] = 0;
        }
    }
    for (int x = 0; x<dst2->width; ++x) {
        uchar* ptr = (uchar*)(dst2->imageData + x * dst2->widthStep);
        for (int y = 0; y<dst2->height; y += height1) {
            ptr[3 * y] = 0;
            ptr[3 * y + 1] = 0;
            ptr[3 * y + 2] = 0;
        }
    }
    cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
    cvShowImage("original", image);
    cvNamedWindow("net", CV_WINDOW_AUTOSIZE);
    cvShowImage("net", dst2);
    cvWaitKey(0);
    cvDestroyWindow("original");
    cvDestroyWindow("net");
}

IplImage* image = 0;
IplImage* dst = 0;
IplImage* dst1 = 0;
IplImage* dst2 = 0;



int main(int argc, char* argv[]) {
    char* filename = new char[1024];
    std::cout << "Enter name of image" << "\n";
    scanf_s("%s", filename);
    
    image = cvLoadImage(filename, 1);
    
    dst = cvCloneImage(image);
    dst1 = cvCloneImage(image);
    dst2 = cvCloneImage(image);
    
    assert(image != 0);
    
    int command;
    std::cout << "Enter command 1 - median filter; 2 - convolution; 3 - making net on image" << "\n";
    std::cin >> command;
    
    if (command == 1) {
        medianfilter(dst, image);
        
    } else if (command == 2) {
        convolution(dst1, image);
        
    } else if (command == 3) {
        net(dst2, image);
    }
    cvWaitKey(0);
    cvReleaseImage(&image);
    cvReleaseImage(&dst1);
    cvReleaseImage(&dst);
    cvDestroyAllWindows();
    return 0;
}
