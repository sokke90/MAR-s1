#include "markertracker.h"


MarkerTracker::MarkerTracker() {
	
	thresh = 100;
	max_value = 255;
	
}
		
		
void MarkerTracker::find(cv::Mat &img_bgr) {

  cv::Mat img_grey, img_thresh;
  cv::vector<cv::vector<cv::Point>> contours0;
  cv::vector<cv::Vec4i> hierarchy;

  cv::cvtColor(img_bgr, img_grey, CV_RGB2GRAY);
  cv::blur(img_grey,img_grey, cv::Size(3,3));
  cv::threshold(img_grey,img_thresh,this->thresh,this->max_value,cv::THRESH_BINARY);
  cv::findContours(img_thresh,
		  contours0,
		  hierarchy,
		  CV_RETR_TREE,
		  CV_CHAIN_APPROX_SIMPLE,
		  cv::Point(0,0));
  contours.resize(contours0.size());
  for (size_t i = 0; i < contours0.size(); ++i) {
	  // Process Polygons here
	  cv::approxPolyDP(cv::Mat(contours0[i]), contours[i], 3, true); 
	  cv::drawContours(img_bgr,contours,i,cv::Scalar(0,165,255),2,8,hierarchy, 0, cv::Point());
  }
	
}
