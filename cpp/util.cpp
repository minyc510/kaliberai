#include <opencv2/opencv.hpp>
#include <unordered_map>
#include <iostream>
#include "constants.h"
using namespace cv;
using namespace std;

namespace util {

  // Given a cell, return it's R.G.B string
  string getPixelColor(Mat_<Vec3b>& _I, int row, int col) {
    const string B = to_string(_I(row,col)[0]);
    const string G = to_string(_I(row,col)[1]);
    const string R = to_string(_I(row,col)[2]);
    return R + '.' + G + '.' + B;
  }

  // Given a frame, return the begin and end indices of the relevant range
  pair<int, int> findRelevantRange(Mat_<Vec3b>& _I, int row) {
    int begin = 0;
    int end = 0;

    // Find begin, ie the first non-black pixel
    for (int col = 0; col < _I.cols; col++) {
      if (getPixelColor(_I, row, col) != RGB_BLACK) {
        begin = col;
        break;
      }
    }
    // Find end, ie the first non-black pixel when iterating in reverse
    for (int col = _I.cols-1; col >= 0; col--) {
      if (getPixelColor(_I, row, col) != RGB_BLACK) {
        end = col;
        break;
      }
    }

    return pair<int, int>(begin, end);
  }

  // Given a frame, evaluate whether it contains 75% or more of the same color, excluding the black around the lens
  bool evaluateFrame(Mat& I) {
    // Accept only char type matrices and 3-channels
    CV_Assert(I.depth() == CV_8U);
    CV_Assert(I.channels() == 3);

    // Map to store color frequencies (RGB -> Frequency of that RGB)
    unordered_map<string, int> colorFreqs;
    int relevantPixelCount = 0;
    Mat_<Vec3b> _I = I;

    // For each row, find the relevant range and count the color frequencies within it
    for (int row = 0; row < _I.rows; row++) {
      pair<int, int> range = findRelevantRange(_I, row);

      if (range.first == 0 && range.second == 0) { continue; }

      for (int col = range.first; col <= range.second; col++) {
        const string pixelColor = getPixelColor(_I, row, col);
        colorFreqs[pixelColor] = (colorFreqs.find(pixelColor) != colorFreqs.end()) ? colorFreqs[pixelColor]+1 : 1;
      }  

      relevantPixelCount += range.second - range.first + 1;
    }

    // Check if any color's frequency is more than 75% of the frame
    int tolerance = relevantPixelCount*THRESHOLD;
    unordered_map<string, int>::iterator it;

    for (it = colorFreqs.begin(); it != colorFreqs.end(); ++it) {
      if (it->second > tolerance) {
        return false;
      }
    }
    return true;
  }
}