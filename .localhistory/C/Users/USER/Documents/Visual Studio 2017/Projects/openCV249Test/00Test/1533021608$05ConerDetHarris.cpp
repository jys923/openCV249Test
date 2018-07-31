#include "stdafx.h"

cv::Mat src, src_gray;
int thresh = 200;
int max_thresh = 255;
const char* source_window = "Source image";
const char* corners_window = "Corners detected";
void cornerHarris_demo( int, void* );
 
 
/* @ function main */
int cornerHarrisTest(String filePath);
{
  src = cv::imread( "../images/lena.png", 1 );
   
  cv::cvtColor( src, src_gray, COLOR_BGR2GRAY );
   
  cv::namedWindow( source_window, WINDOW_AUTOSIZE );
   
  cv::createTrackbar( "Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo );
   
  cv::imshow( source_window, src );
   
  cornerHarris_demo( 0, 0 );
   
  cv::waitKey(0);
 
  return(0);
}
 
 
/* @function cornerHarris_demo */
void cornerHarris_demo( int, void* )
{
  cv::Mat dst, dst_norm, dst_norm_scaled;
  dst = cv::Mat::zeros( src.size(), CV_32FC1 );
 
  int blockSize = 2;
  int apertureSize = 3;
  double k = 0.04;
 
  cv::cornerHarris( src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT );
 
  cv::normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
 
  cv::convertScaleAbs( dst_norm, dst_norm_scaled );
 
  for( int j = 0; j < dst_norm.rows ; j++ ) {
    for( int i = 0; i < dst_norm.cols; i++ ) {
      if( (int) dst_norm.at<float>(j,i) > thresh ) {
        cv::circle( dst_norm_scaled, Point( i, j ), 5,  Scalar(0), 2, 8, 0 );
      }
    }
  }
 
  cv::namedWindow( corners_window, WINDOW_AUTOSIZE );
 
  cv::imshow( corners_window, dst_norm_scaled );
}
