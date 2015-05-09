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

int getDelta(int value1, int value2);
int getMiddle( int value1, int value2);
cv::vector<cv::Point> getSeventh(int divider, cv::Point point1, cv::Point point2);
int sampleSubPix(const cv::Mat &pSrc, const cv::Point2f &p);

		
		
#endif
