#include <opencv2/opencv.hpp>
#include <iostream>
#include <unordered_map>

using namespace cv;
using namespace std;

bool evaluateFrame(Mat& I, int& good, int& bad) {
  // Accept only char type matrices and 3-channel
  CV_Assert(I.depth() == CV_8U);
  CV_Assert(I.channels() == 3);

  unordered_map<string, int> colorFreqs;
  MatIterator_<Vec3b> it, end;
  for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it) {
    string pixelColor = to_string((*it)[0]) + "-" + to_string((*it)[1]) + "-" + to_string((*it)[2]);
    colorFreqs[pixelColor] = (colorFreqs.find(pixelColor) != colorFreqs.end()) ? colorFreqs[pixelColor]+1 : 1;
  }

  int pixelCount = I.size().height * I.size().width;
  int tolerance = (int)(pixelCount*0.75);

  unordered_map<string, int>::iterator mapIt;

  for (mapIt = colorFreqs.begin(); mapIt != colorFreqs.end(); ++mapIt) {
    if (mapIt->second > tolerance) {
      bad++;
      return false;
    }
  }
  good++;
  return true;
}

int main(int argc, char* argv[])
{
  VideoCapture cap("input-short.mp4"); 

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

  Size S = Size((int) cap.get(CAP_PROP_FRAME_WIDTH),
                (int) cap.get(CAP_PROP_FRAME_HEIGHT));
  int fourcc = static_cast<int>(cap.get(CAP_PROP_FOURCC));

  VideoWriter video;
  video.open("output.mp4", fourcc, fps, Size(frame_width, frame_height), true);

  if (!video.isOpened()) {
    cout  << "Could not open the output video for write: " << endl;
    return -1;
  }
  int numProcessed = 0;
  int good = 0;
  int bad = 0;

  clock_t start = clock();

  while (true) {
    Mat frame;
    bool bSuccess = cap.read(frame); // read a new frame from video 

    if (bSuccess == false) {
      cout << "End of video." << endl;
      break;
    }

    if (evaluateFrame(frame, good, bad)) {
      video << frame;
    }

    if (numProcessed % 5 == 0) {
      cout << numProcessed << endl;
    }
    numProcessed++;
  }

  cout << "good: " << good << endl;
  cout << "bad: " << bad << endl;

 double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
 cout << "Processing finished in " << duration << " seconds." << endl;
 cap.release();

 return 0;
}