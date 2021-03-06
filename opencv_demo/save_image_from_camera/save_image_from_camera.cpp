// save_image_from_camera.cpp : Defines the entry point for the console application.
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
	int image_index = 0;
	int image_name = 0;
	const std::string image_name_ext(".jpg");
	const std::string image_name_base("camera");
	while (true) {
		if (!cap.isOpened()) {
			break;
		}

		image_index++;
		ret = cap.read(outImg);
		imshow("Captrue", outImg);

		if (image_index == 100) {
			image_name++;
			imwrite(image_name_base + std::to_string(image_name) + image_name_ext, outImg);
			image_index = 0;
		}
		if (waitKey(50) == 'q')
			break;

	}
	cap.release();
	destroyAllWindows();

	return 0;
}


