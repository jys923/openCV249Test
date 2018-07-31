// Histogram.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Histogram.h"


//����ó���� opencv include
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <cvcam.h>
//����ó���� opencv include


#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ������ ���� ���α׷� ��ü�Դϴ�.

CWinApp theApp;

using namespace std;

char *getFileDialog();	
IplImage *GS_imhist( IplImage *src_image, int max_length);
IplImage *GS_histEqual( IplImage *src_image);
IplImage *GS_histBright( IplImage *src_image, int method);



int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// MFC�� �ʱ�ȭ�մϴ�. �ʱ�ȭ���� ���� ��� ������ �μ��մϴ�.
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: ���� �ڵ带 �ʿ信 ���� �����մϴ�.
		_tprintf(_T("�ɰ��� ����: MFC�� �ʱ�ȭ���� ���߽��ϴ�.\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: ���� ���α׷��� ������ ���⿡�� �ڵ��մϴ�.

		//���� ���� ��Ʈ���� �ޱ�
		char *readFileName = getFileDialog();
		if(!readFileName) 
		{
			AfxMessageBox(_T("Can't read file."), 0, 0);
			return -1;
		}

		//�������� �ε�
		IplImage *src_image = cvLoadImage(readFileName, CV_LOAD_IMAGE_UNCHANGED);
		IplImage *ori_histo_image = NULL;
		IplImage *histo_equl_image = NULL;
		IplImage *equal_histo_image = NULL;
		IplImage *nor_image = NULL;
		IplImage *nor_histo_image = NULL;
		IplImage *bright_image = NULL;
		IplImage *bright_histo_image = NULL;
	

		IplImage *src_gray_image = cvCreateImage(cvGetSize(src_image), IPL_DEPTH_8U, 1);
		cvCvtColor(src_image, src_gray_image, CV_RGB2GRAY);	// �÷��� ������� ��ȯ 
		
		ori_histo_image = GS_imhist(src_gray_image, -1);//�������� �̹����� ������׷� �̹���

		histo_equl_image = GS_histEqual(src_gray_image);//������׷� ��Ȱȭ�� �̹��� 

		equal_histo_image = GS_imhist(histo_equl_image, -1);//��Ȱȭ�� ������׷� �̹���

		bright_image = GS_histBright(src_gray_image, -1);//������׷� ��� ����

		bright_histo_image = GS_imhist(bright_image, -1);//��� ���� �̹����� ������׷� �̹���


		
		


		//�����ֱ�
		char *originalwindow = "���� �̹���";
		cvNamedWindow(originalwindow, CV_WINDOW_AUTOSIZE);
		cvShowImage(originalwindow, src_image);

		char *graywindow = "gray �̹���";
		cvNamedWindow(graywindow, CV_WINDOW_AUTOSIZE);
		cvShowImage(graywindow, src_gray_image);

		char *orihistwindow = "�������� �̹����� ������׷� �̹���";//�������� �̹����� ������׷� �̹���
		cvNamedWindow(orihistwindow, CV_WINDOW_AUTOSIZE);
		cvShowImage(orihistwindow, ori_histo_image);

		char *histequalwindow = "������׷���Ȱ�� �̹��� ";
		cvNamedWindow(histequalwindow, CV_WINDOW_AUTOSIZE);//������ �׷���Ȱ�� �̹��� 
		cvShowImage(histequalwindow, histo_equl_image);

		char *equalhistowindow = "��Ȱȭ�� ������׷� �̹���";//��Ȱȭ�� ������׷� �̹���
		cvNamedWindow(equalhistowindow, CV_WINDOW_AUTOSIZE);
		cvShowImage(equalhistowindow, equal_histo_image);
		
		char *brightwindow = "������׷� ����";//������׷� ����
		cvNamedWindow(brightwindow, CV_WINDOW_AUTOSIZE);
		cvShowImage(brightwindow, bright_image);
		
		char *brighthistowindow = "��� �� ������ ������׷� �̹���";//��� �� ������ ������׷� �̹���
		cvNamedWindow(brighthistowindow, CV_WINDOW_AUTOSIZE);
		cvShowImage(brighthistowindow, bright_histo_image);

		cvWaitKey(0); 
		
		//�Ҵ�� �޸𸮵� ����
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

// ���� ��ȭ���ڿ��� ���� �´�.
char *getFileDialog()
{
	char *readFileName = (char *)NULL;

	// ���� ����
	char szFilter[] = "���� ���� ����(*.bmp, *.jpg, *.gif, *.png, *.tif) \
						|*.bmp;*.jpg;*.gif;*.png;*.tif||";

	printf("\n");
	printf("\t * ���� ��ȭ���ڸ� �̿��Ͽ� ���� ������ �����Ͻʽÿ�. \n\n");
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
	
	//������׷� ������ ����, �ʺ� ����
	int hist_height = 128;
	int hist_width = 256;
	//������׷� �� ���� ����
	int hist_bar_height = 20;
	//������׷� ������ ���� �ʱ�ȭ
	CvHistogram *hist = cvCreateHist(1, &bin_size, CV_HIST_ARRAY, hist_range, 1);

	//�� ������ ������׷� ���
	cvCalcHist(&src_image, hist, 0, NULL);//�׷��� �̹����� �������� �ʳ�? �ƴ� �˾Ƽ� ���ֳ�?

	//cvNormalizeHist(hist, 100);
	//�������� �󵵼�, ������ ��������
	float max_bin_value = 0;
	float min_bin_value = 0;
	int max_level = 0;
	int min_level = 0;

	//������׷����� ��������� �����´�.
	cvGetMinMaxHistValue(hist, &min_bin_value, &max_bin_value, &min_level, &max_level);

	//������׷� ������ ���� �ʱ�ȭ
	IplImage *hist_image = cvCreateImage(cvSize(hist_width, hist_height+hist_bar_height), IPL_DEPTH_8U, 1);

	//�ӽ� ������׷� ���� �ʱ�ȭ
	int tmp_hist_height = cvRound(max_bin_value);//�ִ�󵵸� ����ȭ

	//����� ���� max_length �ݿ�(�ִ� �󵵼� ����)
	if(max_length>0) tmp_hist_height = max_length;

	IplImage * tmp_hist_image1 = cvCreateImage(cvSize(hist_width, tmp_hist_height), IPL_DEPTH_8U, 1);
	IplImage * tmp_hist_image2 = cvCreateImage(cvSize(hist_width, hist_height), IPL_DEPTH_8U, 1);

	//���� ����
	cvSetZero(tmp_hist_image1);
	for(i=0 ; i<hist_width; i++)//������
	{
		tmp = tmp_hist_height - cvRound(cvQueryHistValue_1D(hist,i));

		//�Ʒ� �����ǹ����� ���� ���̹Ƿ� �о���Ų��~
		if(tmp == 0 || tmp > tmp_hist_height) continue;

		//������ ä���. -- ������׷� ����ٸ� ���η� �������� ä���.
		for(j=tmp-1 ; j>=0 ; j--)
		{
			//cvSetReal2D �ӵ��� �����Ƿ� ���� �̹��� �����Ϳ� ������.
			tmp_hist_image1->imageData[j * (tmp_hist_image1->widthStep) + i] = 192.0;
			//cvSetReal2D(tmp_hist_image1, j, i, 192.0);//�������̱� ���÷� i,j�� j,i�� �ȴ�. 
		}
	}

	//�̹��� ���
	cvResize(tmp_hist_image1, tmp_hist_image2, CV_INTER_CUBIC);

	//������׷� ���� ����
	for(i = 0; i < hist_height; i++)
	{
		for(j=0; j<hist_width ; j++)
		{
			//cvSetReal2D �ӵ��� �����Ƿ� ���� �̹��� �����Ϳ� ������.
			hist_image->imageData[i * (tmp_hist_image1->widthStep) + j] = tmp_hist_image2->imageData[i * (tmp_hist_image2->widthStep) + j];
			//cvSetReal2D(hist_image, i, j, cvGetReal2D(tmp_hist_image2, i, j));
		}
	}

	//������׷� �ٸ� ����(��ϵ� ������ �ð������� �˷��ִ� ��)
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

