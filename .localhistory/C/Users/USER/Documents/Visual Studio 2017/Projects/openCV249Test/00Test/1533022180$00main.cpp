// 00Main.cpp: �ܼ� ���� ���α׷��� �������� �����մϴ�.
//

#include "stdafx.h"
int cvSnakeImageTest(string filePath);
int histogram03(String filePath);
int cornerHarrisTest(String filePath);
int sobel(String filePath);

int main()
{
	histogram03("../images/lena.png");
	cvSnakeImageTest("../images/linux.png");
	return 0;
}