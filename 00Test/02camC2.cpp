// 00Test.cpp: �ܼ� ���� ���α׷��� �������� �����մϴ�.
//

#include "stdafx.h"


/* @ function main */
int cvCaptureFromCAMTest2()
{
	IplImage* image = 0;

	// find a webcam
	CvCapture* capture = cvCaptureFromCAM(0);

	// create window
	cvNamedWindow("WebCam Frame Capture", 0);

	// resize windows to 640 * 480
	cvResizeWindow("WebCam Frame Capture", 640, 480);

	while (true) {
		//cvGrabFrame(capture);
		image = cvQueryFrame(capture);
		//cvQueryFrame���� ���� �̹����� �ڵ� ������
		//cvReleaseImage(&pFrame); // ����� ��� ����
		
		cvFlip(image, image, 1);
		// draw the captured frame onto the window created
		cvShowImage("WebCam Frame Capture", image);

		if (cvWaitKey(10) >= 0) {
			//break;
			return -1;
		}
	}

	// release capture
	//cvReleaseCapture(&capture);

	// destory window created
	cvDestroyWindow("WebCam Frame Capture");
	waitKey(0);
	return 0;
}