#include "stdafx.h"

int main()
{
	cv::Mat src1;
	//cv::Mat gray = cv::imread("../images/lena.png", IMREAD_GRAYSCALE);
	src1 = cv::imread("../images/lena.png", CV_LOAD_IMAGE_COLOR);

	cv::Mat gray, dst;

	/// convert to gray
	cv::cvtColor(src1, gray, CV_BGR2GRAY);
	cv::namedWindow("Original image", CV_WINDOW_AUTOSIZE);
	cv::imshow("Original image", gray);

	/// hisogram equalization
	cv::equalizeHist(gray, dst);

	cv::namedWindow("image", CV_WINDOW_AUTOSIZE);
	cv::imshow("image", dst);

	cv::waitKey(0);

	return 0;
}