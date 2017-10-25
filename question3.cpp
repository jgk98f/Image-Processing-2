/**
 * Author: Jason Klamert
 * Date: 10/09/2016
 * Description: Program to find image statistics and calculate the histogram. The histogram is displayed at the end
 * of the program and some conclusions are reached based on some basic information found thorughout the program.
 **/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>
#define DEBUG true
using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  //Usage check!
  if ( argc < 1)
  {
        std::cerr << "usage: " << "Program " << argv[0] << " takes an image as an argument!\n" << std::endl;
        return ( 1 );
  }

  cv::Mat imageOne = cv::imread(argv[1]);
  
  //Empty check!
  if ( imageOne.empty() )
  {
      std::cerr << "Image One is Empty: " << argv[1] << std::endl;
      return ( 1 );
  }

  //Initialize and declare vars.
  double min,max = 0;
  int normalizedHistogram[256];
  float coefficientOfVariation = 0;
  int const totalBins = 256;
  int accumulator = 0;
  int sumOfSquares = 0;
  float standardDeviation = 0;
  float variance = 0;
  int meanAccumulator = 0;
  short int mean = 0;
  imageOne.convertTo(imageOne,CV_8UC1);
  int histogram[totalBins];
  double probability[totalBins];
  double accumulatorHist[totalBins];
  double previousTerm;

  //Set all histogram to 0.
  for(int count = 0; count < totalBins; count++){
	histogram[count] = 0;
  }

	  //Count all of the intensity values found at each pixel and place it in histogram. In addition add up all of
	  //the values found so we can take the mean later.
	  for(int rowNum = 0; rowNum < imageOne.rows; rowNum++ ){
	          for(int colNum = 0;colNum < imageOne.cols; colNum++){
	
	              	if(DEBUG == true)
			{
	                	//std::cout << "imageOne " << "row: " << rowNum << " col: " << colNum << " Itensity: " 
				//<<  (int) imageOne.at<uchar>(colNum,rowNum) << std::endl;
	                }
			
			int temp = (int)  imageOne.at<uchar>(rowNum,colNum);
 			meanAccumulator += temp;
	                histogram[temp] = histogram[temp] + 1;
			accumulator = accumulator + 1;
	          }
	  }

  //Find the mean intensity of the image.
  mean = (short int) (meanAccumulator/(imageOne.rows*imageOne.cols));

	 //Calculate variance summation of the image from the mean.
	 for(int rowNum = 0; rowNum < imageOne.rows; rowNum++){
		for(int colNum = 0; colNum < imageOne.cols; colNum++){
		
			int temp = (int) imageOne.at<uchar>(rowNum,colNum);
			int result = temp - mean;
			result = result * result;
			sumOfSquares += result;
		}
	 }

  //Probability of each intensity calculation!
  for(int count = 0; count < 256; count++){
	probability[count] = (histogram[count] / (imageOne.rows * imageOne.cols));
  }

  //Calculate new pixel distribution.
  for(int count = 0; count < 256; count++){
	double temp = 256 * probability[count];
	previousTerm += temp;
	accumulatorHist[count] = floor(previousTerm);
  }
  
  for(int rowNum = 0; rowNum < imageOne.rows; rowNum++){
	for(int colNum = 0; colNum < imageOne.cols; colNum++){
		imageOne.at<uchar>(rowNum,colNum) = (uchar) accumulatorHist[(int) imageOne.at<uchar>(rowNum,colNum)];
	}
  }

  //compute the standard deviation and coefficient Of Variation for the data set.
  variance = (sumOfSquares/((imageOne.rows*imageOne.cols) - 1));
  standardDeviation = sqrt(variance);
  coefficientOfVariation = standardDeviation/mean;

  //Draw conclusions from our statistical measures.
  if(DEBUG == true){
	for(int count = 0; count < 256; count++){
        	std::cout << "Intensity Level: " << count << " has probability" << probability[count] << " .\n";
  	}

	for(int count = 0; count < 256; count++){
		cout << "New pixel distribution numbers: " << accumulatorHist[count] << endl;
	}
 
        std::cout << "imageOne: Rows: " << imageOne.rows << std::endl;
        std::cout << "imageOne: Cols: " << imageOne.cols << std::endl;
	std::cout << "imageOne: total pixels: " << imageOne.rows * imageOne.cols << std::endl;
	std::cout << "imageOne: pixels processed for histogram: " << accumulator << std::endl;
	std::cout << "imageOne: mean intensity for image: " << mean << std::endl;
	std::cout << "imageOne: standard deviation: " << standardDeviation << std::endl;
	std::cout << "imageOne: variance: " << variance << std::endl;
  }else{
  	std::cout << "imageOne: mean intensity for image: " << mean << std::endl;
        std::cout << "imageOne: standard deviation: " << standardDeviation << std::endl;
        std::cout << "imageOne: variance: " << variance << std::endl;
  }

  //Finally, display the image.
  cv::namedWindow( "Display Image", cv::WINDOW_AUTOSIZE );
  cv::imshow( "Display Image", imageOne );
  cv::waitKey(0);

  return 0;
}

