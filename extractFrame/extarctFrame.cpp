#include <iostream>
#include <string>
using namespace std;
using namespace cv;
#include <opencv2/opencv.hpp>
#include <opencv2/videoio/videoio_c.h>
#include "opencv2/highgui/highgui.hpp"
#include "geturl.h"


int main()
{
	// Get the streaming server URL
	std::string videoAddress;
	getVideoAddress(&videoAddress);
	std::cout <<  "Video Address: " + videoAddress << std::endl;

	// Capture the Stream
    VideoCapture cap(videoAddress);
    cap.open(videoAddress);
    if ( !cap.isOpened() )  // isOpened() returns true if capturing has been initialized.
    {
        cout << "Cannot open the video file" << endl;
        return -1;
    }

    // Open window to play the stream
    String window_name = "VideoWindow";
    namedWindow(window_name, CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
   
   
   	// Capture frame by frame - play the stream and save the last frame
    Mat lastFrame;
    while(true)
    {
        Mat frame;
        if (!captured = cap.read(frame)) // if not success, break loop
        // read() decodes and captures the next frame.
        {
            cout << "Cannot read the video file" << endl;
            break;
        }
        else {
        	lastFrame = frame; 
        }

        imshow(window_name, frame);

        if(waitKey(10) == 27) // Wait for 'esc' key press to exit
        { 
        	cout << "Esc key is pressed by user. Stoppig the video" << endl;
            break; 
        }
    }
    
    // Save the last frame
    if(lastFrame != NULL){
    	imwrite("./img.jpg", lastFrame);
    }
    
    return 0;
}
