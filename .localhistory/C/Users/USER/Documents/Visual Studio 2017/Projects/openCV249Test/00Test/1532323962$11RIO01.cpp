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

	//img[1]에 (200, 60)좌표에 가로160, 세로180의 박스 (애기얼굴)부분만 관심영역 설정
	cvSetImageROI(img[1], cvRect(200, 60, 160, 180));

	//img[2]는 관심영역이 설정된 img[1]을 복사하고, cvSubS함수를 이용해서, 설정한 값만큼, 화소를 뺀다.
	img[2] = (IplImage*)cvClone(img[1]);

	//cvScalar로, 100만큼 빼서 img[2]에 넣는다.
	cvSubS(img[1], cvScalar(100, 100, 100), img[2]);

	//ROI를 해제해서, 원본이 어떻게 변했는지 확인한다.
	cvResetImageROI(img[2]);

	//윈도우 생성과 이미지 출력
	for (int i = 0; i<num; i++)
	{
		cvNamedWindow(winName[i]);
		cvShowImage(winName[i], img[i]);
	}

	cvWaitKey(0);

	//윈도우 제거와, 메모리 해제
	for (int i = 0; i<num; i++)
	{
		cvDestroyWindow(winName[i]);
		cvReleaseImage(&img[i]);
	}
	return 0;
}