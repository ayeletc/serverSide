#include <iostream>
#include "VideoProcess.h"
#include "geturl.h" //added by Ayelet

//include added by Roni&Dolev
#include "darknet.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

//added by Roni&Dolev
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/core/version.hpp>
#include <opencv2/core/types_c.h>//addedR&D

#ifndef CV_VERSION_EPOCH
#include <opencv2/videoio/videoio_c.h>
#define OPENCV_VERSION CVAUX_STR(CV_VERSION_MAJOR)""CVAUX_STR(CV_VERSION_MINOR)""CVAUX_STR(CV_VERSION_REVISION)
#pragma comment(lib, "opencv_world" OPENCV_VERSION ".lib")
#else
#define OPENCV_VERSION CVAUX_STR(CV_VERSION_EPOCH)""CVAUX_STR(CV_VERSION_MAJOR)""CVAUX_STR(CV_VERSION_MINOR)
#pragma comment(lib, "opencv_core" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_imgproc" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_highgui" OPENCV_VERSION ".lib")
#endif
//end of addition

#include <chrono> //added by Roni&Dolev for measuring the time process for each frame
#include </usr/include/opencv2/core/mat.hpp>


#include <stdio.h>   //   
#include <sys/types.h> //
#include <ifaddrs.h> //
#include <netinet/in.h> // 
#include <string.h>  //
#include <arpa/inet.h> //

using namespace std;
using namespace cv; //added by Roni&Dolev

//added by Roni&Dolev
int framesDecision[5] = { 0 }; //contains 5 frames' decision
int framesCount = 0; //counter for 5-frame-decision
int finalDecision = 1; // 1 = red, 2 = green

extern IplImage *currFrameRes; //global frame result to return to main

void process_frame(Mat frame,VideoMeta meta);

//int getVideoAddress(std::string *videoAddress);

int main(int argc, char **argv) {

	std::string videoAddress;
	getVideoAddress(&videoAddress);
	std::cout <<  "Video Address: " + videoAddress << std::endl;
    try {
        // 1: create VideoProcess Instance with the location of the video.
        // best idea is to write the full  path to it.
//	auto vp = VideoProcess(string(argv[1]));
	auto vp = VideoProcess(videoAddress);

 //       vp.play(); // just play the video if you want

        // 2: call the process method and
        // pass to it the name of function that going to handle each frame
        vp.process(process_frame);




    }catch(...){
        std::cout << "video process failed" << endl;
    }
    return 0;
}

void process_frame(Mat frame,VideoMeta meta)
{
       		//std::cout << "start process frames" << "\n";
	    //added by Roni&Dolev. measure runtime for each frame
		std::chrono::high_resolution_clock::time_point start, end;

    		start = std::chrono::high_resolution_clock::now(); 
		double time_elapsed;


//modeFlag - 1: detector test , 2: detector test (debug mode) , 3: detector train , 4: partial (modify initial weight file)
int modeFlag = 1;

//convert Mat frame to IplImage type
IplImage im = frame;

int decision = darknet_main(modeFlag, &im, meta.currentFrameNumber);

framesDecision[framesCount] = decision;
framesCount = ++framesCount;
//std::cout << "check frames num" << "\n";
if(meta.currentFrameNumber >= 5){
	
	//make a decision based on 5-frames
	int redNum = 0;
	int greenNum = 0;
	int i;
	for(i=0 ; i < 5 ; i++){
		if(framesDecision[i] == 2){
			++greenNum;
		}
		else{
			++redNum;
		}
	}
     //  	std::cout << "before decision" << "\n";
	if(greenNum > redNum){
//		printf("\n/////////////////\ngreen\n////////////////\n");
//		printf("\n/green/\n");
//		std::cout <<  "green" << "\n";
		std::cout <<  "green" << std::endl;
		finalDecision = 2; // green
	} else if(greenNum <= redNum){
//		printf("\n/////////////////\nred\n////////////////\n");
//		printf("\n/red/\n");
//		std::cout <<  "red" << "\n";
		std::cout <<  "red" << std::endl;
		finalDecision = 1; // red
	} else{
//		printf("an error occurred!\n");
//		std::cout <<  "an error occurred!" << "\n";
		std::cout <<  "an error occurred!" << std::endl;
	}

	if(framesCount >= 5){ // instead of using "mod"
		//reset framesDecision array
		framesCount = 0;
	}

}
else{ //for having a logo on the first 5 frames
	finalDecision = decision;
	if(decision == 2){
//		printf("\n/////////////////\ngreen\n////////////////\n");
//		printf("\n/green/\n");
//		std::cout <<  "green" << "\n";
		std::cout <<  "green" << std::endl;	
	}
	else{
//		printf("\n/////////////////\nred\n////////////////\n");
//		printf("\n/red/\n");
//		std::cout <<  "red" << "\n";
		std::cout <<  "red" << std::endl;
	}
}

if(modeFlag == 2){ //added for showing image result
	cvShowImage("prediction", currFrameRes);
	const string s = std::string("green");
	Mat imO = currFrameRes;
	
	Mat LOGOimage;
	if(finalDecision == 2){ //load green logo
		LOGOimage = imread("./green_logo.jpg", CV_LOAD_IMAGE_COLOR);
	} else { //load red logo
		LOGOimage = imread("./red_logo.jpg", CV_LOAD_IMAGE_COLOR);
	}
//size of logo: rows=987,cols=986 . resized - 197 both rows and cols
	LOGOimage.copyTo(imO(cv::Rect(50,50,LOGOimage.cols, LOGOimage.rows)));

	std::ostringstream name;
	name << "./outputFrames/" << meta.currentFrameNumber << ".jpg";
	cv::imwrite(name.str(), imO);

	//imshow("prediction", imO);
	cvReleaseImage(&currFrameRes);
}

	    //added by Roni&Dolev
    end = std::chrono::high_resolution_clock::now();
    time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
//    std::cout << "Code took " << time_elapsed << " miliseconds to execute\n";



}

