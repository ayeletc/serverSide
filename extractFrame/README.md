## Extracting frames from video stream using OpenCV(C++) and Javascript 

### 1. Installation

Save all the files from [my git](https://github.com/ayeletc/serverSide/tree/master/extractFrame/) in one folder (inside the main folder of the mechnics project).

### 2. Compile the C++ files

Try compile using the next command in the project's dir:
```bash	
g++ *.cpp -o extractFrame /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so -lopencv_calib3d /usr/lib/x86_64-linux-gnu/libopencv_contrib.so -lopencv_contrib /usr/lib/x86_64-linux-gnu/libopencv_core.so -lopencv_core /usr/lib/x86_64-linux-gnu/libopencv_features2d.so -lopencv_features2d /usr/lib/x86_64-linux-gnu/libopencv_flann.so -lopencv_flann /usr/lib/x86_64-linux-gnu/libopencv_gpu.so -lopencv_gpu /usr/lib/x86_64-linux-gnu/libopencv_highgui.so -lopencv_highgui /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so -lopencv_imgproc /usr/lib/x86_64-linux-gnu/libopencv_legacy.so -lopencv_legacy /usr/lib/x86_64-linux-gnu/libopencv_ml.so -lopencv_ml /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so -lopencv_objdetect /usr/lib/x86_64-linux-gnu/libopencv_ocl.so -lopencv_ocl /usr/lib/x86_64-linux-gnu/libopencv_photo.so -lopencv_photo /usr/lib/x86_64-linux-gnu/libopencv_stitching.so -lopencv_stitching /usr/lib/x86_64-linux-gnu/libopencv_superres.so -lopencv_superres /usr/lib/x86_64-linux-gnu/libopencv_ts.so -lopencv_ts /usr/lib/x86_64-linux-gnu/libopencv_video.so -lopencv_video /usr/lib/x86_64-linux-gnu/libopencv_videostab.so -lopencv_videostab
```

Getting errors ("undefined reference to `cv::VideoCapture::VideoCapture(int)", for example)?  
Maybe you need another set of libraries.  
Check what libraries are installed in your computer using this command in the terminal:

```bash
pkg-config --libs opencv
```

Then, copy the libs you get as an output to:
```bash
g++ *.cpp LIBRARIES
```

### 3. Install JS packages

In the project dir run the following commands: 
```bash
npm install rtmp-server
npm install child_process 
npm install socket.io
```

### 4. Open the server

Run in the project's dir:
```bash
node serverForFramesTest.js
```
	
### 5. Start streaming

- Check your [server's IP](https://www.whatismyip.com/) 
- Open the application in the device
- Insert the server's IP
- Start streaming 

Now you should see the stream from the device in a new window in th server, and when you finish the streaming you may refresh the dir and see there the last frame.

