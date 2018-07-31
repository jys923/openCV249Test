// 00Test.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
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