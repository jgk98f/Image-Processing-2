# Image-Processing-2
Slightly more advanced image processing techniques. Most of these will involve histogram calculations to perform operations on an image.

----------------------------------------------------------------------------
README
----------------------------------------------------------------------------
Author: Jason Klamert
Programs: question[1-5]
Digital Image Processing
----------------------------------------------------------------------------
Summary:
----------------------------------------------------------------------------

The following programs correspond to the questions of project number two and
are named accordingly.

Question 1 takes two images as arguements of the same size and it calculates
the absolute distance between them. This means that we iterate through the
image one pixel at a time and compare each pixel at (x,y) to the corresponding
pixel at (x,y) in the second image. This accumulate this difference and
average it at the end.

Question 2 takes one image as an arguement and copies the image into two
other Mats. One I convert to grayscale by hand and the other is converted
into grayscale by using cvtColor. Once converted, the absolute distanace
between the two images is calculated.

Question 3 takes one image as an arguement and it finds statistics about the
image. This includes the variance, standard deviation, and the histogram
(both normalized and unnormalized). Once calculated and normalized, the
histogram is displayed for the user to see.

Question 4 takes one image as an arguement and it uses subsampling of the
pixels (every other row and column) to shrink the image to a lesser size.
Then the image is displayed for the user and saved to the local directory.

Question 5 takes one image as an arguement and it seperates the image out
into a series of bit planes. The program displays them in the order of
least significant to most significant.

----------------------------------------------------------------------------
Directions:
----------------------------------------------------------------------------

Makefile:
	make -f MakeFile

clean:
	make -f MakeFile clean

run:
	question1 imageName1 imageName2
	question2 imageName
	question3 imageName
	question4 imageName
	question5 imageName

