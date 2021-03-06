// first_opencv_demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
#include "opencv2\opencv.hpp"
using namespace cv;

int main()
{
	Mat inImg = imread("./test.jpg", IMREAD_GRAYSCALE);
	if (inImg.empty())
		return -1;

	namedWindow("OpenCV3", WINDOW_AUTOSIZE);
	imshow("OpenCV3", inImg);
	waitKey(0);
	destroyAllWindows();

	return 0;
}

