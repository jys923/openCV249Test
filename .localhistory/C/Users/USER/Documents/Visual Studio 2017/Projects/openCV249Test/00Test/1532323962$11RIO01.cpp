#include "stdafx.h"
#define num 3

int main()
{
	const char* winName[num] = { "original","ROI","cvSubS" };
	IplImage* img[num];
	IplImage* src = cvLoadImage("baby.jpg");

	img[0] = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	cvCvtColor(src, img[0], CV_BGR2GRAY);
	img[1] = (IplImage*)cvClone(img[0]);

	//img[1]�� (200, 60)��ǥ�� ����160, ����180�� �ڽ� (�ֱ��)�κи� ���ɿ��� ����
	cvSetImageROI(img[1], cvRect(200, 60, 160, 180));

	//img[2]�� ���ɿ����� ������ img[1]�� �����ϰ�, cvSubS�Լ��� �̿��ؼ�, ������ ����ŭ, ȭ�Ҹ� ����.
	img[2] = (IplImage*)cvClone(img[1]);

	//cvScalar��, 100��ŭ ���� img[2]�� �ִ´�.
	cvSubS(img[1], cvScalar(100, 100, 100), img[2]);

	//ROI�� �����ؼ�, ������ ��� ���ߴ��� Ȯ���Ѵ�.
	cvResetImageROI(img[2]);

	//������ ������ �̹��� ���
	for (int i = 0; i<num; i++)
	{
		cvNamedWindow(winName[i]);
		cvShowImage(winName[i], img[i]);
	}

	cvWaitKey(0);

	//������ ���ſ�, �޸� ����
	for (int i = 0; i<num; i++)
	{
		cvDestroyWindow(winName[i]);
		cvReleaseImage(&img[i]);
	}
	return 0;
}