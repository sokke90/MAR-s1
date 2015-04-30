#include "markertracker.h"

using namespace cv;


MarkerTracker::MarkerTracker() {
	
	thresh = 100;
	max_value = 255;
	
}
		
		
void MarkerTracker::find(cv::Mat &img_bgr) {

  Mat img_grey, img_thresh;
  vector<cv::vector<cv::Point>> contours0;
  vector<cv::Vec4i> hierarchy;

	// make the image B/W
	cvtColor(img_bgr, img_grey, CV_RGB2GRAY);
	
	
	blur(img_grey,img_grey, Size(3,3));
	threshold(img_grey,img_thresh,this->thresh,this->max_value,cv::THRESH_BINARY);
	
	// Find contours
	findContours(img_thresh,
		  contours0,
		  hierarchy,
		  RETR_TREE,
		  CHAIN_APPROX_SIMPLE,
		  Point(0,0));
		  
		 
	contours.resize(contours0.size());
	
	
	for (size_t i = 0; i < contours0.size(); ++i) {
		// Process Polygons here
		approxPolyDP(Mat(contours0[i]), contours[i], 4, true); 
		drawContours(img_bgr,contours,i,Scalar(0,165,255),2,8,hierarchy, 0, cv::Point());
	}
	
}
