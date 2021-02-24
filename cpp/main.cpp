#include <opencv2/opencv.hpp>
#include <iostream>
#include <unordered_map>
#include "util.cpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
  string fileName = "input-medium.mp4"; // default
  if (argc > 1) {
    fileName = argv[1];
  }

  const string inputUri = "../media/" + fileName;
  cout << inputUri << endl;
  VideoCapture cap(inputUri); 

  if (cap.isOpened() == false) {
    cout << "Cannot open the video file" << endl;
    return -1;
  }

  int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
  int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);
  double fps = cap.get(CAP_PROP_FPS); 
  cout << "Frames per second: " << fps << endl;
  cout << "Frame Size: " << frame_width << " x " << frame_height << endl;
  cout << "Frames: " << cap.get(CAP_PROP_FRAME_COUNT) << endl;

  int fourcc = static_cast<int>(cap.get(CAP_PROP_FOURCC));

  VideoWriter video;
  const string outputName = "filtered_" + fileName;
  video.open(outputName, fourcc, 10, Size(frame_width, frame_height), true);

  if (!video.isOpened()) {
    cout  << "Could not open the output video for write: " << endl;
    return -1;
  }
  int numProcessed = 0;
  int framesRemoved = 0;

  clock_t start = clock();

  while (true) {
    Mat frame;
    bool readSuccess = cap.read(frame);

    if (readSuccess == false) {
      cout << "End of video." << endl;
      break;
    }

    if (util::evaluateFrame(frame, framesRemoved)) {
      video << frame;
    }

    if (numProcessed % 5 == 0) {
      cout << numProcessed << endl;
    }
    numProcessed++;
  }

  double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
  cout << "Processing finished in " << duration << " seconds." << endl;
  cout << "Frames Removed: " << framesRemoved << endl;
  cap.release();

  return 0;
}