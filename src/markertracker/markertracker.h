#ifndef MARKERTRAKER_H
#define MARKERTRAKER_H


#include <opencv/cv.h>



class MarkerTracker {
	public:
		MarkerTracker();
		void find(cv::Mat &img_bgr);
	private:
		double thresh;
		double max_value;
		cv::vector<cv::vector<cv::Point>> contours;
};
		
		
		
#endif
