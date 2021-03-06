#include "stdafx.h"

static void help(void)
{
	printf("\nThis program illustrates Linear-Polar and Log-Polar image transforms\n"
		"Usage :\n"
		"./polar_transforms [[camera number -- Default 0],[path_to_filename]]\n\n");
}
int main(int camNumber)
{
	VideoCapture capture;
	Mat log_polar_img, lin_polar_img, recovered_log_polar, recovered_lin_polar_img;
	IplImage* plog_polar_img, plin_polar_img, precovered_log_polar, precovered_lin_polar_img;

	capture.open(camNumber);
	if (!capture.isOpened())
	{
		fprintf(stderr, "Could not initialize capturing...\n");
		return -1;
	}
	namedWindow("Linear-Polar", WINDOW_AUTOSIZE);
	namedWindow("Log-Polar", WINDOW_AUTOSIZE);
	namedWindow("Recovered Linear-Polar", WINDOW_AUTOSIZE);
	namedWindow("Recovered Log-Polar", WINDOW_AUTOSIZE);
	moveWindow("Linear-Polar", 20, 20);
	moveWindow("Log-Polar", 700, 20);
	moveWindow("Recovered Linear-Polar", 20, 350);
	moveWindow("Recovered Log-Polar", 700, 350);
	for (;;)
	{
		Mat frame;
		IplImage* pframe;
		capture >> frame;
		if (frame.empty())
			break;
		Point2f center((float)frame.cols / 2, (float)frame.rows / 2);
		double M = 70;

		pframe = new IplImage(frame);

		cvLogPolar(pframe, plog_polar_img, center, M, INTER_LINEAR);
		cvLinearPolar(pframe, plin_polar_img, center, M, INTER_LINEAR);
		cvLogPolar(plog_polar_img, precovered_log_polar, center, M, WARP_INVERSE_MAP + INTER_LINEAR);
		cvLinearPolar(plin_polar_img, precovered_lin_polar_img, center, M, WARP_INVERSE_MAP + INTER_LINEAR);
		/*logPolar(frame, log_polar_img, center, M, INTER_LINEAR + WARP_FILL_OUTLIERS);
		linearPolar(frame, lin_polar_img, center, M, INTER_LINEAR + WARP_FILL_OUTLIERS);
		logPolar(log_polar_img, recovered_log_polar, center, M, WARP_INVERSE_MAP + INTER_LINEAR);
		linearPolar(lin_polar_img, recovered_lin_polar_img, center, M, WARP_INVERSE_MAP + INTER_LINEAR + WARP_FILL_OUTLIERS);*/
		imshow("Log-Polar", log_polar_img);
		imshow("Linear-Polar", lin_polar_img);
		imshow("Recovered Linear-Polar", recovered_lin_polar_img);
		imshow("Recovered Log-Polar", recovered_log_polar);
		if (waitKey(10) >= 0)
			break;
	}
	waitKey(0);
	return 0;
}