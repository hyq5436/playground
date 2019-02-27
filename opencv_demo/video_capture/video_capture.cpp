// video_capture.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
#include "opencv2\opencv.hpp"
using namespace cv;

int main()
{
	auto cap = VideoCapture(0);
	Mat outImg;
	bool ret = false;
	while (true) {
		if (cap.isOpened()) {
			ret = cap.read(outImg);
			imshow("Captrue", outImg);
			if (waitKey(100) == 'q')
				break;
		}
	}
	destroyAllWindows();

	return 0;
}
