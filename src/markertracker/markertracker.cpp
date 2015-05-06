#include "markertracker.h"
#include <iostream> 
#include <string>

using namespace cv;
using namespace std;



MarkerTracker::MarkerTracker() {
	
	thresh = 100;
	max_value = 255;
	
}
		
		
void MarkerTracker::find(cv::Mat &img_bgr) {

  Mat img_grey, img_thresh;
  cv::vector<cv::vector<cv::Point>> contours0;
  cv::vector<cv::Vec4i> hierarchy;
  
  vector<vector<Point>> sampledOnLinePoints;
 

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
	 
	// we want bounding rectangles now around our stuff - new var here.
	vector<Rect> boundRect( contours.size() );
	
	
	for (size_t i = 0; i < contours0.size(); ++i) {
		
		// Process Polygons here
		approxPolyDP(Mat(contours0[i]), contours[i], 3, true);
		boundRect[i] = boundingRect( Mat(contours[i]) );

		
		
		// Filter all the wrong polygons
		if (
			// the poly should have 4 or 5 borders
		contours[i].size() == 4 && contours[i].size() <= 5
			// size of rectangle around
			&& boundRect[i].width >= 40
			&& boundRect[i].height >= 40
		) 
		
		
		
		{
			// Debug Text
			putText(img_bgr, 
				std::to_string(contours[i].size()) + "h" + std::to_string(boundRect[i].height) + "w" + std::to_string(boundRect[i].width), 
				boundRect[i].br(), 
				FONT_HERSHEY_PLAIN, 
				1, 
				cvScalar(200,200,250), 1, CV_AA);
			
			Scalar circlecolor = Scalar(84,223,93);
			//circle(img_bgr, contours[i][0], 5, circlecolor, 5);
			//circle(img_bgr, contours[i][1], 5, circlecolor, 5);
			//circle(img_bgr, contours[i][2], 5, circlecolor, 5);
			//circle(img_bgr, contours[i][3], 5, circlecolor, 5);
			
			
			// Circle in the middle

			//sampledOnLinePoints.push_back(getSeventh(7, contours[i][0], contours[i][1]));
			
			//cout << sampledOnLinePoints[0].size() << " - ";
			
			for (int kk = 0; kk < 4; kk++ )
			 {
					Point point1 = contours[i][kk];
					Point point2;
					
					if (kk < 3)
						point2 = contours[i][kk+1];
					else
						point2 = contours[i][0];
					
					
					
				
					int distanceX = point2.x - point1.x;
					int distanceY = point2.y - point1.y;
					
					//cout << "\n\n" << point1.x << " : " << point1.y << " \n ";
					//cout << point2.x << " : " << point2.y << " \n ";
					//cout << distanceX << " \n ";
					//cout << distanceY << " \n ";
					
					
					
					for (int j = 1; j < 7; j++)
					{
							//circle(img_bgr, Point(distanceX/7*j+point1.x, distanceY/7*j+point1.y), 1, circlecolor, 5);
							
							line(img_bgr,
								Point(distanceX/7.0*j+point1.x+distanceY/14.0,
									distanceY/7.0*j+point1.y-distanceX/14.0),
									
								Point(distanceX/7.0*j+point1.x-distanceY/14.0, 
									distanceY/7.0*j+point1.y+distanceX/14.0),
								Scalar(0,165,255),
								1,
								8
							);
							
							//cout << "(" << distanceX/7*j+point1.x << ":";
							//cout << distanceY/7*j+point1.y << ")";
								
					}
				}
			
			
			/*
			
			for (int i = 0; i < sampledOnLinePoints[0].size(); i++)
			{
				circle(img_bgr, sampledOnLinePoints[0][i], 5, circlecolor, 5);
			}
			
			*/
			drawContours(img_bgr,contours,i,Scalar(93,239,255),1,8,hierarchy, 0, cv::Point());
			
			
			
			
			//rectangle( img_bgr, boundRect[i].tl(), boundRect[i].br(), Scalar(100,165,255), 2, 8, 0 );
		}
	}
	
	
}


int sampleSubPix(const cv::Mat &pSrc, const cv::Point2f &p)
{
	int x = int(floorf(p.x));
	int y = int(floorf(p.y));

	if (x < 0 || x >= pSrc.cols - 1 ||
		y < 0 || y >= pSrc.rows - 1)
		return 127;

	int dx = int(256 * (p.x - floorf(p.x)));
	int dy = int(256 * (p.y - floorf(p.y)));

	unsigned char* i = (unsigned char*)((pSrc.data + y * pSrc.step) + x);
	int a = i[0] + ((dx * (i[1] - i[0])) / 256);
	i += pSrc.step;
	int b = i[0] + ((dx * (i[1] - i[0])) / 256);
	return a + ((dy * (b - a)) / 256);
}



/*
What does this code do?

This function solves the following problem: The image is stored as an OpenCV matrix pSrc.
Now, what we are doing is trying to get the intensity at a certain location p in the image.
If p = (x,y) and x,y are natural numbers we can simply access the image pSrc.at<uchar>(y,x).
But since we are interested in non integer locations p, we can use this function. 

So what it does is bilinear interpolation (http://en.wikipedia.org/wiki/Bilinear_interpolation)
of the image pSrc at location p.
*/

int getDelta( int value1, int value2)
{
	if (value1 > value2)
		return value1-value2;
	else
		return value2-value1;
	
}

int getMiddle( int value1, int value2){
	if (value1 > value2)
		return value2 + (value1-value2)/2;
	else
		return value1 + (value2-value1)/2;
	
}


cv::vector<Point> getSeventh(int divider, Point point1, Point point2) {


		
		
	
	
}

