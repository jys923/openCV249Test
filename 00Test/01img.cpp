// 00Test.cpp: �ܼ� ���� ���α׷��� �������� �����մϴ�.
//

#include "stdafx.h"


int main()
{
	Mat img = imread("../images/lena.png", IMREAD_ANYCOLOR);
	namedWindow("test", WINDOW_AUTOSIZE);
	// Create a window for display.
	//if(!img.empty())
	//{
	//	imshow("test",img);
	//	//return -1;
	//}
	//else
	//{
	//	std::cerr << "Cannot read image file: "  << std::endl;
	//}
	//if(img.empty())
	if (!img.data)
	{
		std::cerr << "Cannot read image file: " << std::endl;
		destroyWindow("test");
		//waitKey(0);
		return -1;
	}
	imshow("test", img);
	waitKey(0);
	return 0;
}