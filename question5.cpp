/*`
 * question5.cpp
 * Description: Program to take an image and seperate it into bit planes. .
 *  Created on: 10/09/2016
 *      Author: Jason Klamert
 */
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>
#define DEBUG true
using namespace cv;
float getDistance(int, int, int, int);

int main( int argc, char** argv )
{
  srand(time(NULL));
  
  //Check for proper usage.
  if ( argc < 1)
    {
        std::cerr << "usage: " << argv[0]  << " takes an image argument!\n" << std::endl;
        return ( 1 );
    }
  
  cv::Mat imageOne = cv::imread(argv[1]);
  
  //Check if the image is empty.
  if ( imageOne.empty() )
  {
      std::cerr << "Image One is Empty: " << argv[1] << std::endl;
      return ( 1 );
  }
  
  //Clone the image into 8 Mat objects.
  Mat plane0 = imageOne.clone();
  Mat plane1 = imageOne.clone();
  Mat plane2 = imageOne.clone();
  Mat plane3 = imageOne.clone();
  Mat plane4 = imageOne.clone();
  Mat plane5 = imageOne.clone();
  Mat plane6 = imageOne.clone();
  Mat plane7 = imageOne.clone();

  //Iterate through the image given and segment each pixel value into 8 seperate bit planes.
  //This is easily done using the binary operator & to draw out the specific bit we want.
  for(int rowNum = 0; rowNum < imageOne.rows; rowNum++ ){
          for(int colNum = 0;colNum < imageOne.cols; colNum++){
		for(int c = 0; c < 3; c++){
			plane0.at<Vec3b>(colNum,rowNum)[c] = (unsigned char) imageOne.at<Vec3b>(colNum,rowNum)[c] & 1;
			plane1.at<Vec3b>(colNum,rowNum)[c] = (unsigned char) imageOne.at<Vec3b>(colNum,rowNum)[c] & 2;
			plane2.at<Vec3b>(colNum,rowNum)[c] = (unsigned char) imageOne.at<Vec3b>(colNum,rowNum)[c] & 4;
			plane3.at<Vec3b>(colNum,rowNum)[c] = (unsigned char) imageOne.at<Vec3b>(colNum,rowNum)[c] & 8;
			plane4.at<Vec3b>(colNum,rowNum)[c] = (unsigned char) imageOne.at<Vec3b>(colNum,rowNum)[c] & 16;
			plane5.at<Vec3b>(colNum,rowNum)[c] = (unsigned char) imageOne.at<Vec3b>(colNum,rowNum)[c] & 32;
			plane6.at<Vec3b>(colNum,rowNum)[c] = (unsigned char) imageOne.at<Vec3b>(colNum,rowNum)[c] & 64;
			plane7.at<Vec3b>(colNum,rowNum)[c] = (unsigned char) imageOne.at<Vec3b>(colNum,rowNum)[c] & 128;	
        	}  
	}
  }

  //Finally, display all the bit planes from least significant to most significant.
  cv::namedWindow( "Bit Plane 0", cv::WINDOW_AUTOSIZE );
  cv::imshow( "Bit Plane 0", plane0 );
  cv::waitKey(0);

  cv::namedWindow( "Bit Plane 1", cv::WINDOW_AUTOSIZE );
  cv::imshow( "Bit Plane 1", plane1 );
  cv::waitKey(0);

  cv::namedWindow( "Bit Plane 2", cv::WINDOW_AUTOSIZE );
  cv::imshow( "Bit Plane 2", plane2 );
  cv::waitKey(0);

  cv::namedWindow( "Bit Plane 3", cv::WINDOW_AUTOSIZE );
  cv::imshow( "Bit Plane 3", plane3 );
  cv::waitKey(0);

  cv::namedWindow( "Bit Plane 4", cv::WINDOW_AUTOSIZE );
  cv::imshow( "Bit Plane 4", plane4 );
  cv::waitKey(0);

  cv::namedWindow( "Bit Plane 5", cv::WINDOW_AUTOSIZE );
  cv::imshow( "Bit Plane 5", plane5 );
  cv::waitKey(0);

  cv::namedWindow( "Bit Plane 6", cv::WINDOW_AUTOSIZE );
  cv::imshow( "Bit Plane 6", plane6 );
  cv::waitKey(0);

  cv::namedWindow( "Bit Plane 7", cv::WINDOW_AUTOSIZE );
  cv::imshow( "Bit Plane 7", plane7 );
  cv::waitKey(0);
 
  return 0;
}
