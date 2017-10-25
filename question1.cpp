/*
 * question1.cpp
 * Description: Program to calculate difference in grayscale and get the average.
 *  Created on: 10/05/2016
 *      Author: Jason Klamert
 */
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>
#define DEBUG false
float getDistance(int, int, int, int);

int main( int argc, char** argv )
{
  srand(time(NULL));
  
  //Usage check.
  if ( argc < 2)
    {
        std::cerr << "usage: " << "Program takes two image arguments!\n" << std::endl;
        return ( 1 );
    }
  
  cv::Mat imageOne = cv::imread(argv[1]);
  
  //Check if imageOne empty.
  if ( imageOne.empty() )
  {
      std::cerr << "Image One is Empty: " << argv[1] << std::endl;
      return ( 1 );
  }

  cv::Mat imageTwo = cv::imread(argv[2]);
  
  //Check if imageTwo empty.
  if ( imageTwo.empty() )
  {
      std::cerr << "Image Two is Empty: " << argv[2] << std::endl;
      return ( 1 );
  }

  unsigned int pixels = 0;
  int accumulator = 0;
  float result = 0;
  int temp = 0;
  int temp2 = 0;
  
  //Iterate through imageOne and two and calculate absolute distance. Accumulate this distance for later.
  for(int rowNum = 0; rowNum < imageOne.rows; rowNum++ ){
          for(int colNum = 0;colNum < imageOne.cols; colNum++){
			
			if(DEBUG == true){
				std::cout << "imageOne " << "row: " << rowNum << " col: " << colNum << " Itensity: " <<  (int) imageOne.at<uchar>(colNum,rowNum) << std::endl;
				std::cout << "imageTwo " << "row: " << rowNum << " col: " << colNum << " Itensity: " <<  (int) imageTwo.at<uchar>(colNum,rowNum) << std::endl;
				              

	}

			temp = (int) imageOne.at<uchar>(rowNum,colNum);
			temp2 = (int) imageTwo.at<uchar>(rowNum, colNum);
			accumulator += abs(temp - temp2);
			pixels += 1;

			if(DEBUG == true){
				std::cout << "temp1: " << temp << std::endl;
				std::cout << "temp2: " << temp2 << std::endl;
				std::cout << "accumulator: " << accumulator << std::endl;
			}	
          }
  }

  //Use our accumulated absolute difference to find the average distance between the two images.
  float totalPixels = (int) imageOne.rows * imageOne.cols;
  result = (accumulator/totalPixels);
  
  if(DEBUG == true){
  	std::cout << "accumulator: " << accumulator << std::endl;
  	std::cout << "imageOne Rows: " << imageOne.rows << std::endl;
  	std::cout << "imageOne Cols: " << imageOne.cols << std::endl;
  	std::cout << "pixels processed: " << pixels << std::endl;
	std::cout << "image size in pixels: " << imageOne.rows * imageOne.cols << std::endl; 
  }
  
  
  std::cout << "Average difference across the image: " << result << std::endl;
  

  return 0;
}
