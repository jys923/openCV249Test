// Histogram.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Histogram.h"


//영상처리용 opencv include
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <cvcam.h>
//영상처리용 opencv include


#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 유일한 응용 프로그램 개체입니다.

CWinApp theApp;

using namespace std;

char *getFileDialog();	
IplImage *GS_imhist( IplImage *src_image, int max_length);
IplImage *GS_histEqual( IplImage *src_image);
IplImage *GS_histBright( IplImage *src_image, int method);



int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// MFC를 초기화합니다. 초기화하지 못한 경우 오류를 인쇄합니다.
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: 오류 코드를 필요에 따라 수정합니다.
		_tprintf(_T("심각한 오류: MFC를 초기화하지 못했습니다.\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: 응용 프로그램의 동작은 여기에서 코딩합니다.

		//원본 파일 스트링값 받기
		char *readFileName = getFileDialog();
		if(!readFileName) 
		{
			AfxMessageBox(_T("Can't read file."), 0, 0);
			return -1;
		}

		//원본영상 로딩
		IplImage *src_image = cvLoadImage(readFileName, CV_LOAD_IMAGE_UNCHANGED);
		IplImage *ori_histo_image = NULL;
		IplImage *histo_equl_image = NULL;
		IplImage *equal_histo_image = NULL;
		IplImage *nor_image = NULL;
		IplImage *nor_histo_image = NULL;
		IplImage *bright_image = NULL;
		IplImage *bright_histo_image = NULL;
	

		IplImage *src_gray_image = cvCreateImage(cvGetSize(src_image), IPL_DEPTH_8U, 1);
		cvCvtColor(src_image, src_gray_image, CV_RGB2GRAY);	// 컬러를 흑백으로 변환 
		
		ori_histo_image = GS_imhist(src_gray_image, -1);//오리지날 이미지의 히스토그램 이미지

		histo_equl_image = GS_histEqual(src_gray_image);//히스토그램 평활화한 이미지 

		equal_histo_image = GS_imhist(histo_equl_image, -1);//평활화한 히스토그램 이미지

		bright_image = GS_histBright(src_gray_image, -1);//히스토그램 밝기 조정

		bright_histo_image = GS_imhist(bright_image, -1);//밝기 조정 이미지의 히스토그램 이미지


		
		


		//보여주기
		char *originalwindow = "원본 이미지";
		cvNamedWindow(originalwindow, CV_WINDOW_AUTOSIZE);
		cvShowImage(originalwindow, src_image);

		char *graywindow = "gray 이미지";
		cvNamedWindow(graywindow, CV_WINDOW_AUTOSIZE);
		cvShowImage(graywindow, src_gray_image);

		char *orihistwindow = "오리지날 이미지의 히스토그램 이미지";//오리지날 이미지의 히스토그램 이미지
		cvNamedWindow(orihistwindow, CV_WINDOW_AUTOSIZE);
		cvShowImage(orihistwindow, ori_histo_image);

		char *histequalwindow = "히스토그램평활한 이미지 ";
		cvNamedWindow(histequalwindow, CV_WINDOW_AUTOSIZE);//히스토 그램평활한 이미지 
		cvShowImage(histequalwindow, histo_equl_image);

		char *equalhistowindow = "평활화한 히스토그램 이미지";//평활화한 히스토그램 이미지
		cvNamedWindow(equalhistowindow, CV_WINDOW_AUTOSIZE);
		cvShowImage(equalhistowindow, equal_histo_image);
		
		char *brightwindow = "히스토그램 조정";//히스토그램 조정
		cvNamedWindow(brightwindow, CV_WINDOW_AUTOSIZE);
		cvShowImage(brightwindow, bright_image);
		
		char *brighthistowindow = "명암 값 조정한 히스토그램 이미지";//명암 값 조정한 히스토그램 이미지
		cvNamedWindow(brighthistowindow, CV_WINDOW_AUTOSIZE);
		cvShowImage(brighthistowindow, bright_histo_image);

		cvWaitKey(0); 
		
		//할당된 메모리들 해제
		cvReleaseImage(&src_image);
		cvReleaseImage(&src_gray_image);
		cvReleaseImage(&ori_histo_image);
		cvReleaseImage(&histo_equl_image);
		cvReleaseImage(&bright_image);
		cvReleaseImage(&bright_histo_image);
				
		cvDestroyWindow(originalwindow);
		cvDestroyWindow(graywindow);
		cvDestroyWindow(orihistwindow);
		cvDestroyWindow(histequalwindow);
		cvDestroyWindow(equalhistowindow);
		cvDestroyWindow(brightwindow);
		cvDestroyWindow(brighthistowindow);
	
	



	}

	return nRetCode;
}

// 파일 대화상자에서 갖고 온다.
char *getFileDialog()
{
	char *readFileName = (char *)NULL;

	// 파일 포맷
	char szFilter[] = "지원 영상 파일(*.bmp, *.jpg, *.gif, *.png, *.tif) \
						|*.bmp;*.jpg;*.gif;*.png;*.tif||";

	printf("\n");
	printf("\t * 파일 대화상자를 이용하여 영상 파일을 선택하십시오. \n\n");
	printf("\t \n");

	CFileDialog fileDlg(TRUE, 
			  NULL, 
				NULL, 
				OFN_EXPLORER|OFN_HIDEREADONLY, 
				szFilter
				);

	if( fileDlg.DoModal() == IDOK ) 
	{
		// CString to char *
		readFileName 
			= (char *)strdup((char *)(LPCTSTR)fileDlg.GetPathName());
	}

	return readFileName;
}

IplImage *GS_imhist( IplImage *src_image, int max_length)
{
	int i, j;
	int bin_size = 256;
	int tmp = 0;

	float ranges[] = {0, 255};
	float *hist_range[] = { ranges };
	
	//히스토그램 영상의 높이, 너비를 설정
	int hist_height = 128;
	int hist_width = 256;
	//히스토그램 바 높이 설정
	int hist_bar_height = 20;
	//히스토그램 데이터 구조 초기화
	CvHistogram *hist = cvCreateHist(1, &bin_size, CV_HIST_ARRAY, hist_range, 1);

	//원 영상의 히스토그램 계산
	cvCalcHist(&src_image, hist, 0, NULL);//그레이 이미지가 들어가야하지 않냐? 아님 알아서 해주냐?

	//cvNormalizeHist(hist, 100);
	//원영상의 빈도수, 레벨을 가져오기
	float max_bin_value = 0;
	float min_bin_value = 0;
	int max_level = 0;
	int min_level = 0;

	//히스토그램에서 통계정보를 가져온다.
	cvGetMinMaxHistValue(hist, &min_bin_value, &max_bin_value, &min_level, &max_level);

	//히스토그램 보여줄 영상 초기화
	IplImage *hist_image = cvCreateImage(cvSize(hist_width, hist_height+hist_bar_height), IPL_DEPTH_8U, 1);

	//임시 히스토그램 영상 초기화
	int tmp_hist_height = cvRound(max_bin_value);//최대빈도를 정수화

	//사용자 정의 max_length 반영(최대 빈도수 제한)
	if(max_length>0) tmp_hist_height = max_length;

	IplImage * tmp_hist_image1 = cvCreateImage(cvSize(hist_width, tmp_hist_height), IPL_DEPTH_8U, 1);
	IplImage * tmp_hist_image2 = cvCreateImage(cvSize(hist_width, hist_height), IPL_DEPTH_8U, 1);

	//배경셋 설정
	cvSetZero(tmp_hist_image1);
	for(i=0 ; i<hist_width; i++)//열기준
	{
		tmp = tmp_hist_height - cvRound(cvQueryHistValue_1D(hist,i));

		//아래 조건의범위는 없는 값이므로 패쓰시킨다~
		if(tmp == 0 || tmp > tmp_hist_height) continue;

		//배경색을 채운다. -- 히스토그램 막대바를 세로로 내려가며 채운다.
		for(j=tmp-1 ; j>=0 ; j--)
		{
			//cvSetReal2D 속도가 느리므로 직접 이미지 데이터에 접급함.
			tmp_hist_image1->imageData[j * (tmp_hist_image1->widthStep) + i] = 192.0;
			//cvSetReal2D(tmp_hist_image1, j, i, 192.0);//열기준이기 땜시롱 i,j가 j,i가 된다. 
		}
	}

	//이미지 축소
	cvResize(tmp_hist_image1, tmp_hist_image2, CV_INTER_CUBIC);

	//히스토그램 영상 복사
	for(i = 0; i < hist_height; i++)
	{
		for(j=0; j<hist_width ; j++)
		{
			//cvSetReal2D 속도가 느리므로 직접 이미지 데이터에 접급함.
			hist_image->imageData[i * (tmp_hist_image1->widthStep) + j] = tmp_hist_image2->imageData[i * (tmp_hist_image2->widthStep) + j];
			//cvSetReal2D(hist_image, i, j, cvGetReal2D(tmp_hist_image2, i, j));
		}
	}

	//히스토그램 바를 붙임(명암도 범위를 시각적으로 알려주는 바)
	for(i = hist_height; i<hist_height + hist_bar_height; i++)
	{
		for(j=0 ; j < hist_width; j++)
		{
			cvSetReal2D(hist_image, i, j, j);
		}
	}
	cvReleaseHist(&hist);
	cvReleaseImage(&tmp_hist_image1);
	cvReleaseImage(&tmp_hist_image2);

	return hist_image;

}

IplImage *GS_histEqual( IplImage *src_image)
{
	IplImage * dst_image = cvCreateImage(cvGetSize(src_image), IPL_DEPTH_8U, src_image->nChannels);

	cvEqualizeHist(src_image, dst_image);

	return dst_image;

}

IplImage *GS_histBright( IplImage *src_image, int method)
{
	IplImage * dst_image = cvCreateImage(cvGetSize(src_image), IPL_DEPTH_8U, 1);

	int i, j;
	for( i = 0; i< dst_image->height; i++)
	{
		for(j=0 ; j < dst_image->width; j++)
		{
			int  val = cvGetReal2D(src_image, i, j);
			
			if(method>0)
			{
				val = val + 50;
				if(val >=255)
				{
					val = 255;
				}
			}
			else
			{
				val = val - 50;
				if(val <=0)
				{
					val = 0;
				}

			}
			cvSetReal2D(dst_image, i, j, val);
		}
	}

	return dst_image;

}

