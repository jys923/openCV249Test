// 00Test.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"


int main()
{
	cv::Mat gray = cv::imread("../images/lena.png", IMREAD_GRAYSCALE);
	cv::namedWindow("Gray", 1);
	cv::imshow("Gray", gray);

	/// Initialize parameters
	int histSize = 256;    // bin size
	float range[] = { 0, 255 };
	const float *ranges[] = { range };

	/// Calculate histogram
	cv::MatND hist;
	cv::calcHist(&gray, 1, 0, cv::Mat(), hist, 1, &histSize, ranges, true, false);

	/// Show the calculated histogram in command window
	double total;
	total = gray.rows * gray.cols;

	for (int h = 0; h < histSize; h++)
	{
		float binVal = hist.at<float>(h);
		std::cout << " " << binVal;
	}

	/// Plot the histogram
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	cv::Mat histImage(hist_h, hist_w, CV_8UC1, cv::Scalar(0, 0, 0));
	cv::normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, cv::Mat());

	for (int i = 1; i < histSize; i++)
	{
		line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			cv::Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
			cv::Scalar(255, 0, 0), 2, 8, 0);
	}

	cv::namedWindow("Result", 1);
	cv::imshow("Result", histImage);

	cv::waitKey(0);

	return 0;
}