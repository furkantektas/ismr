// Standard C++ Libraries
#include <iostream>
#include <sstream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <pthread.h>
#include "server.h"

using std::cout;
using std::endl;
using namespace cv;

#define BOXSIZE 50

string text = "Lorem Ipsum Dolor Sit Amet";


cv::Point getPt1(Mat& frame) {
    return cv::Point(frame.cols,frame.rows-BOXSIZE);
}

cv::Point getPt2(Mat& frame) {
    return cv::Point(0,frame.rows);
}


void drawRectangle (Mat& frame) {
    static cv::Point pt1(getPt1(frame));
    static cv::Point pt2(getPt2(frame));
    static cv::Scalar white(0,0,0);


    Mat overlay;
    frame.copyTo(overlay);

    cv::rectangle(
        overlay,
        pt1,
        pt2,
        white,
        CV_FILLED
    );
    double opacity = 0.6;
    addWeighted(overlay, opacity, frame, 1 - opacity, 0, frame);

}

void drawText(Mat& frame) {
    int baseline=0;
    const int fontFace = CV_FONT_HERSHEY_SIMPLEX;
    const double fontScale = 1;
    const int thickness = 1;

    static Size textSize = getTextSize(text, fontFace,
                                fontScale, thickness, &baseline);

    static Point textOrg((getPt1(frame).x - getPt2(frame).x)/2-textSize.width/2, (getPt1(frame).y + getPt2(frame).y)/2+textSize.height/2);

    putText(frame, text, textOrg, fontFace, fontScale,
            Scalar::all(255), thickness, 8);
}

void* fnSetText(void* newPath) {
    std::cout << (char*)newPath << std::endl;
    text = (char*) newPath;
    return 0;
}

void* fnServer(void* args) {
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL );
    return task(LOCALHOST,atoi(((char*)args)+2),fnSetText);
}


void usage(void) {
    printf("Invalid arguments\nUsage: ./opencv-stream-overlay STREAMADDR AugmentationPORT\n");
}

int main(int argc, char *argv[]) {
    pthread_t pthreadtPortListener;
    pthread_attr_t pattrDetachableAttr;

    if(argc != 3) {
        usage();
        return -1;
    }
    pthread_attr_init(&pattrDetachableAttr);
    pthread_attr_setdetachstate(&pattrDetachableAttr, PTHREAD_CREATE_DETACHED);


    if (pthread_create(&pthreadtPortListener, &pattrDetachableAttr,
        fnServer, argv )) {
        fputs("Error on creating thread. Terminating.", stderr);
        exit(-1);
    }

    Mat frame;

    VideoCapture cap;
    
    if(!cap.open(argv[1])) {
        std::cout << "Error while opening video stream" << std::endl;
        return -1;
    }

    cap >> frame;

    char c = 0;

    namedWindow("Augmented Video Stream - G2", CV_WINDOW_AUTOSIZE);
    
    while ( cap.isOpened() && (c != 27)) {
        cap >> frame;
        if(frame.empty()) break;

        drawRectangle(frame);

        drawText(frame);

        imshow("Augmented Video Stream - G2", frame);
        c = waitKey(30);

    }

    return 0;
}
