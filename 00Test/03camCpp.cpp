// 00Test.cpp: �ܼ� ���� ���α׷��� �������� �����մϴ�.
//

#include "stdafx.h"


int main()
{
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cout << "fail cam" << endl;
		return -1;
	}

	namedWindow("cam", 0);
	Mat frame;
	while (true) {
		cap >> frame;
		imshow("cam", frame);
		flip(frame, frame, 1);
		if (waitKey(10) >= 0) {
			//return -1;
			break;
		}
	}
	return 0;
}