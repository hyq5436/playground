// record_video.cpp : Defines the entry point for the console application.
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
	const std::string video_name_ext("out.avi");
	auto writer = VideoWriter(video_name_ext, VideoWriter::fourcc('D', 'I', 'V', 'X'), 20.0, Size(640, 480));
	while (true) {
		if (!cap.isOpened()) {
			break;
		}

		image_index++;
		ret = cap.read(outImg);
		writer.write(outImg);
		imshow("Captrue", outImg);

		if (waitKey(1) == 'q')
			break;

	}
	cap.release();
	destroyAllWindows();

	return 0;
}