// 00Main.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
int cvSnakeImageTest(string filePath);

int main()
{
	histogram03("../images/lena.png");
	cvSnakeImageTest("../images/linux.png");
	return 0;
}