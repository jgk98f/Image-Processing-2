/**
 * Author: Jason Klamert
 * Date: 10/09/2016
 * Description: Program to shrink an image by removing every other row and column. Then display this newly shrunken image.
 **/ 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>
using namespace cv;
#define DEBUG true

int main( int argc, char** argv )
{
  srand(time(NULL));

  //Usage check!
  if ( argc < 1)
  {
      std::cerr << "usage: " << "Program " << argv[0] << " takes an image as an argument!\n" << std::endl;
      return ( 1 );
  }

  Mat imageOne = imread(argv[1]);
  
  //Empty check!
  if ( imageOne.empty() )
  {
      std::cerr << "Image One is Empty: " << argv[1] << std::endl;
      return ( 1 );
  }

  Mat rows(ceil(imageOne.rows/2),ceil(imageOne.cols/2),CV_8U);
  string const fileName = "Shrunken.jpg";

  //Loop through and copy every other row/col into new mat.
  for(int rowNum = 0; rowNum < imageOne.rows; rowNum = rowNum + 2){
        for(int colNum = 0; colNum < imageOne.cols; colNum = colNum + 2){
	       		rows.at<uchar>(rowNum/2,colNum/2) = imageOne.at<uchar>(rowNum,colNum);
        }
  }
  
  if(DEBUG == true){
	std::cout << "Original Image Size in Pixels: " << imageOne.rows * imageOne.cols << std::endl;
	std::cout << "Shrunken Image Size in Pixels: " << rows.rows * rows.cols << std::endl;
  }

  //Save the shrunken image.
  imwrite(fileName,rows);

  //Display shrunken image.
  cv::namedWindow( "Display Image", cv::WINDOW_AUTOSIZE );
  cv::imshow( "Display Image", rows );
  cv::waitKey(0);

  return 0;
}
