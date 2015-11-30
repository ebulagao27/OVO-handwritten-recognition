// generate_data.cpp

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/ml/ml.hpp>

#include<iostream>
#include<vector>

// global variables ///////////////////////////////////////////////////////////////////////////////
const int MIN_CONTOUR_AREA = 100;
const int RESIZED_IMAGE_WIDTH = 20;
const int RESIZED_IMAGE_HEIGHT = 30;

//Contour With Data //////////////////////////////////////////////////////////////////////////////
class ContourWithData {
public:
	// member variables
	std::vector<cv::Point> ptContour;											// contour
	cv::Rect boundingRect;														// bounding rect for contour
	float fltArea;																// area of contour


	bool checkIfContourIsValid() {												// obviously in a production grade program
		if (fltArea < MIN_CONTOUR_AREA) return false;							// we would have a much more robust function for 
		return true;															// identifying if a contour is valid !!
	}

	static bool sortByBoundingRectXPosition(const ContourWithData& cwdLeft, const ContourWithData& cwdRight) {		// this function allows us to sort
		return(cwdLeft.boundingRect.x < cwdRight.boundingRect.x);				// the contours from left to right
	}

};

///////////////////////////////////////////// MAIN //////////////////////////////////////////////
int main() {
	std::vector<ContourWithData> allContoursWithData;							// declare empty vectors,
	std::vector<ContourWithData> validContoursWithData;							// we will fill these shortly
	cv::Mat matTrainingNumbers;													// input image
	cv::Mat matGrayscale;														// for greyscaling
	cv::Mat matBlurred;															// declare various images
	cv::Mat matThresh;															// for otsu method
	cv::Mat matThreshCopy;														// create a copy of the image before finding contours

	std::vector<std::vector<cv::Point> > ptContours;							// declare contours vector
	std::vector<cv::Vec4i> v4iHierarchy;										// declare contours hierarchy

	
																				// these are our training images
	cv::Mat matTrainingImages;													// we have to declare a single Mat, then append to it as though it's a vector

	

	matTrainingNumbers = cv::imread("training_numbers.png");					// read in training numbers image


	if (matTrainingNumbers.empty()) {											// if unable to open image
		std::cout << "error: image not read from file\n\n";						// show error message on command line
		return(0);																// and exit program
	}


	cv::cvtColor(matTrainingNumbers, matGrayscale, CV_BGR2GRAY);				// convert to grayscale

																				//Get the size of the image for otsu method
	int rows = matGrayscale.rows;
	int cols = matGrayscale.cols;
	cv::Size s = matGrayscale.size();
	rows = s.height;
	cols = s.width;
	
																				//convert into binary image using Otsu method
	cv::Mat left = matGrayscale(cv::Rect(0, 0, cols, rows));
	cv::Mat right = matGrayscale(cv::Rect(cols, 0, matGrayscale.cols - cols, rows));
	cv::threshold(left, left, 0, 255, CV_THRESH_OTSU);
	cv::threshold(right, right, 0, 255, CV_THRESH_OTSU);

	cv::threshold(matGrayscale, matThresh, 70, 255, CV_THRESH_BINARY_INV);		//Invert the binary image

	cv::imshow("matThresh", matThresh);											// show threshold image for reference

	matThreshCopy = matThresh.clone();											// make a copy of the thresh image, this in necessary b/c findContours modifies the image

	cv::findContours(matThreshCopy,												// input image, make sure to use a copy since the function will modify this image in the course of finding contours
		ptContours,																// output contours
		v4iHierarchy,															// output hierarchy
		cv::RETR_EXTERNAL,														// retrieve the outermost contours only
		cv::CHAIN_APPROX_SIMPLE);												// compress horizontal, vertical, and diagonal segments and leave only their end points

	for (int i = 0; i < ptContours.size(); i++) {								// for each contour
		ContourWithData contourWithData;												// instantiate a contour with data object
		contourWithData.ptContour = ptContours[i];										// assign contour to contour with data
		contourWithData.boundingRect = cv::boundingRect(contourWithData.ptContour);		// get the bounding rect
		contourWithData.fltArea = cv::contourArea(contourWithData.ptContour);			// calculate the contour area
		allContoursWithData.push_back(contourWithData);									// add contour with data object to list of all contours with data
	}	// end for
	
	for (int i = 0; i < allContoursWithData.size(); i++) {						// for all contours
		if (allContoursWithData[i].checkIfContourIsValid()) {					// check if valid
			validContoursWithData.push_back(allContoursWithData[i]);			// if so, append to valid contour list
		}
	}
	// sort contours from left to right
	std::sort(validContoursWithData.begin(), validContoursWithData.end(), ContourWithData::sortByBoundingRectXPosition);

	for (int i = 0; i < validContoursWithData.size(); i++) {					// for each contour

																				// draw a green rect around the current char
		cv::rectangle(matTrainingNumbers,										// draw rectangle on original image
			validContoursWithData[i].boundingRect,								// rect to draw
			cv::Scalar(0, 0, 255),												// green
			2);																	// thickness

		cv::Mat matROI = matThresh(validContoursWithData[i].boundingRect);							// get ROI image of bounding rect

		cv::Mat matROIResized;
		cv::resize(matROI, matROIResized, cv::Size(RESIZED_IMAGE_WIDTH, RESIZED_IMAGE_HEIGHT));		// resize image, this will be more consistent for recognition and storage
		cv::imshow("matROI", matROI);											// show ROI image for reference
		cv::imshow("matROIResized", matROIResized);								// show resized ROI image for reference
		cv::imshow("matROIBinarized", matGrayscale);
		cv::imshow("matTrainingNumbers", matTrainingNumbers);					// show training numbers image, this will now have red rectangles drawn on it

		std::cout << "\n NUMBER : "<<i<<"\n\n";

		int intChar = cv::waitKey(0);											// get key press

		if (intChar == 27) {													// if esc key was pressed
			return(0);															// exit program
		}
		// end if
	}

	std::cout << "\nsegmentation complete\n\n";
	return(0);
}


