// 00Test.cpp: �ܼ� ���� ���α׷��� �������� �����մϴ�.
//

#include "stdafx.h"


/* @ function main */
int main(int argc, char** argv)
{
	IplImage* image = 0;

	// find a webcam
	//CvCapture* capture = cvCaptureFromCAM(0);
	CvCapture* capture = cvCaptureFromCAM(CV_CAP_DSHOW);
	//capture->VI.listDevices();
	//videoInput ���̺귯�� ���������
	// create window
	//cvNamedWindow("WebCam Frame Capture", 0);

	//// resize windows to 640 * 480
	//cvResizeWindow("WebCam Frame Capture", 640, 480);

	//while (true) {
	//	cvGrabFrame(capture);

	//	// capture a frame from webcam
	//	image = cvRetrieveFrame(capture);

	//	// draw the captured frame onto the window created
	//	cvShowImage("WebCam Frame Capture", image);

	//	if (cvWaitKey(10) >= 0)
	//		break;
	//}

	//// release capture
	//cvReleaseCapture(&capture);

	//// destory window created
	//cvDestroyWindow("WebCam Frame Capture");
	waitKey(0);
	return 0;
}