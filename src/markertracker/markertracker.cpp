#include <opencv/cv.h>
#include <opencv/highgui.h>




class MarkerTracker {
	public:		
		void find(cv::Mat &img_bgr);
};
		
		
		
void MarkerTracker::find(cv::Mat &img_bgr) {
	
	
	cv::cvtColor(img_bgr, img_bgr, CV_RGB2GRAY);
	
}
