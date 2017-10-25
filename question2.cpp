/**
 * question1.cpp
 * Description: Program to calculate difference in grayscale and get the average.
 * Created on: 10/05/2016
 * Author: Jason Klamert
 **/
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

  //Usage check!
  if ( argc < 1)
    {
        std::cerr << "usage: " << "Program " << argv[0] << " takes an image as an argument!\n" << std::endl;
        return ( 1 );
    }

  Mat imageOne = cv::imread(argv[1]);

  //Check if imageOne is empty.
  if ( imageOne.empty() )
  {
      std::cerr << "Image One is Empty: " << argv[1] << std::endl;
      return ( 1 );
  }
  
  Mat imageTwo =  imageOne.clone();
  cvtColor(imageTwo, imageTwo, CV_BGR2GRAY);
  float ratio[] = {0.11,0.59,0.30};
  Mat newImage(imageOne.size(),CV_8U);
  
  //Loop through all values and use the corresponding convert value for the channel.
  for(int rowNum = 0; rowNum < imageOne.rows; rowNum++){
	for(int colNum = 0; colNum < imageOne.cols; colNum++){
		float blue = imageOne.at<Vec3b>(rowNum,colNum)[0] * ratio[0];
		float green = imageOne.at<Vec3b>(rowNum,colNum)[1] * ratio[1];
		float red = imageOne.at<Vec3b>(rowNum,colNum)[2] * ratio[2];
		newImage.at<uchar>(rowNum,colNum) = blue + green + red;
	}
  }

  int accumulator = 0;
  float result = 0;
  int temp = 0;
  int temp2 = 0;

  //Calculate absolute difference between two images and accumulate it.
  for(int rowNum = 0; rowNum < imageOne.rows; rowNum++ ){
          for(int colNum = 0;colNum < imageOne.cols; colNum++){

                        if(DEBUG == true){
                               // std::cout << "imageOne " << "row: " << rowNum << " col: " << colNum << " Itensity: " <<  (int) imageOne.at<uchar>(colNum,rowNum) << std::endl;
                               // std::cout << "imageTwo " << "row: " << rowNum << " col: " << colNum << " Itensity: " <<  (int) imageTwo.at<uchar>(colNum,rowNum) << std::endl;
			}

                        temp = (int) imageTwo.at<uchar>(rowNum,colNum);
                        temp2 = (int) newImage.at<uchar>(rowNum, colNum);
                        accumulator += abs(temp - temp2);

                        if(DEBUG == true){
                                //std::cout << "temp1: " << temp << std::endl;
                                //std::cout << "temp2: " << temp2 << std::endl;
                                //std::cout << "accumulator: " << accumulator << std::endl;
                        }
          }
  }

  //Calculate average difference using the previously accumulated total.
  float totalPixels = (int) imageOne.rows * imageOne.cols;
  result = (accumulator/totalPixels);

  if(DEBUG == true){
        std::cout << "accumulator: " << accumulator << std::endl;
        std::cout << "imageOne Rows: " << imageOne.rows << std::endl;
        std::cout << "imageOne Cols: " << imageOne.cols << std::endl;
  }

  std::cout << "Average difference across the image: " << result << std::endl;

  //Display our images to the user.
  cv::namedWindow( "Display Image", cv::WINDOW_AUTOSIZE );
  cv::imshow( "Display Image", newImage );
  cv::waitKey(0);

  cv::namedWindow( "Display Image2", cv::WINDOW_AUTOSIZE );
  cv::imshow( "Display Image2", imageTwo );
  cv::waitKey(0);


  return 0;
}

