#include <opencv2/opencv.hpp>
#include <unordered_map>
#include <iostream>
using namespace cv;
using namespace std;

namespace util {
  bool evaluateFrame(Mat& I) {
    // Accept only char type matrices and 3-channel
    CV_Assert(I.depth() == CV_8U);
    CV_Assert(I.channels() == 3);

    unordered_map<string, int> colorFreqs;
    MatIterator_<Vec3b> it, end;
    for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it) {
      // R-G-B
      string pixelColor = to_string((*it)[0]) + "-" + to_string((*it)[1]) + "-" + to_string((*it)[2]);
      colorFreqs[pixelColor] = (colorFreqs.find(pixelColor) != colorFreqs.end()) ? colorFreqs[pixelColor]+1 : 1;
    }

    int pixelCount = I.size().height * I.size().width;
    int tolerance = (int)(pixelCount*0.75);
    unordered_map<string, int>::iterator mapIt;
    for (mapIt = colorFreqs.begin(); mapIt != colorFreqs.end(); ++mapIt) {
      if (mapIt->second > tolerance) {
        return false;
      }
    }
    return true;
  }
}
