#include "stdafx.h"

typedef struct parameter Parameter;
struct parameter {
	float alpha;
	float beta;
	float gamma;
};

int main()
{
	int i, j = 0, c;
	IplImage *src_img, *dst_img;
	CvPoint *contour;
	CvPoint center;
	int length = 60;              /* 動的輪郭を構成する点数 */
	Parameter snake_param = { 0.45, 0.55, 0.8 };  /* cvSnakeImage のパラメータ */
	CvFont font;
	char iter[8];

	// (1)画像を読み込む
	src_img = cvLoadImage("../images/linux.png", CV_LOAD_IMAGE_GRAYSCALE);
	dst_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 3);

	cvInitFont(&font, CV_FONT_HERSHEY_DUPLEX, 0.7, 0.7);
	center.x = src_img->width / 2;
	center.y = src_img->height / 2;
	// (2)動的輪郭の初期化
	contour = (CvPoint *)cvAlloc(sizeof(CvPoint) * length);
	for (i = 0; i < length; i++) {
		contour[i].x = (int)(center.x * cos(2 * CV_PI * i / length) + center.x);
		contour[i].y = (int)(center.y * sin(2 * CV_PI * i / length) + center.y);
	}

	// (3)初期輪郭の描画
	cvCvtColor(src_img, dst_img, CV_GRAY2RGB);
	for (i = 0; i < length - 1; i++) {
		cvLine(dst_img, contour[i], contour[i + 1], CV_RGB(255, 0, 0), 2, 8, 0);
	}
	cvLine(dst_img, contour[length - 1], contour[0], CV_RGB(255, 0, 0), 2, 8, 0);
	cvNamedWindow("Snakes", CV_WINDOW_AUTOSIZE);
	cvCircle(dst_img, cvPoint(150, 300), 50, CV_RGB(0, 255, 0));// , 5, 8, 0);
	cvShowImage("Snakes", dst_img);
	cvWaitKey(0);

	/* 動的輪郭の収束計算（過程を表示する） */
	while (1) {
		// (4)動的輪郭の輪郭計算
		//cvSnakeImage(src_img, contour, length, &snake_param.alpha, &snake_param.beta, &snake_param.gamma,CV_VALUE, cvSize(15, 15), cvTermCriteria(CV_TERMCRIT_ITER, 1, 0.0), 1);
		cvSnakeImage(
			src_img,			//input 
			contour,			//특징점 좌표
			length,				//특징점 숫자
								//스네이크 알고리즘의 에너지 항에 대한 계수
			&snake_param.alpha,	//연속성 에너지, 단일 플로트 또는 길이의 플로트 어레이 (각 윤곽 지점 당 하나씩).
			&snake_param.beta,	//곡률 에너지, 알파와 비슷합니다.
			&snake_param.gamma,	//이미지 에너지
			CV_VALUE,			//CV_VALUE - alpha, beta and gamma point to a single value
								//CV_MATAY - points to arrays
			cvSize(15, 15),		//최소값을 검색하는 데 사용되는 모든 점의 이웃 크기는 win.width와 win.height가 모두 홀수 여야합니다.
			cvTermCriteria(CV_TERMCRIT_ITER, 1, 0.0), 
			1
		);
		
		// (5)計算された動的輪郭の描画
		cvCvtColor(src_img, dst_img, CV_GRAY2RGB);
		for (i = 0; i < length - 1; i++) {
			cvLine(dst_img, contour[i], contour[i + 1], CV_RGB(255, 0, 0), 2);
		}
		cvLine(dst_img, contour[length - 1], contour[0], CV_RGB(255, 0, 0), 2);
		snprintf(iter, 8, "%03d", ++j);
		cvPutText(dst_img, iter, cvPoint(15, 30), &font, CV_RGB(0, 0, 255));

		// (6)結果の表示
		cvShowImage("Snakes", dst_img);
		c = cvWaitKey(0);
		if (c == '\x1b')
			break;
	}

	cvDestroyWindow("Snakes");
	cvReleaseImage(&src_img);
	cvReleaseImage(&dst_img);

	return 0;
}