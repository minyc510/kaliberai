#include <opencv2/opencv.hpp>
#include <unordered_map>
#include <iostream>
#include "constants.h"
using namespace cv;
using namespace std;



namespace util {

  string getPixelColor(Mat_<Vec3b>& _I, int row, int col) {
    const string R = to_string(_I(row,col)[0]);
    const string G = to_string(_I(row,col)[1]);
    const string B = to_string(_I(row,col)[2]);
    return R + '.' + G + '.' + B;
  }

  pair<int, int> findLensRange(Mat& I, int row) {
    // Need to use Mat_ type to access by specific (row,col)
    Mat_<Vec3b> _I = I;
    int begin = 0;
    int end = 0;
    // Find begin, ie the first non-black pixel
    for ( int col = 0; col < I.cols; ++col ) {
      if (getPixelColor(_I, row, col) != RGB_BLACK) {
        begin = col;
        break;
      }
    }
    // Find end, ie the first non-black pixel when iterating in reverse
    for ( int col = I.cols-1; col >= 0; --col ) {
      if (getPixelColor(_I, row, col) != RGB_BLACK) {
        end = col;
        break;
      }
    }

    return pair<int, int>(begin, end);
  }

  void countColorFrequency(Mat& I, unordered_map<string, int>& colorFreqs, int row, int begin, int end) {
    Mat_<Vec3b> _I = I;
    for ( int col = begin; col <= end; ++col ) {
      const string pixelColor = getPixelColor(_I, row, col);
      colorFreqs[pixelColor] = (colorFreqs.find(pixelColor) != colorFreqs.end()) ? colorFreqs[pixelColor]+1 : 1;
    }  
  }
  
  bool evaluateFrame(Mat& I) {
    // Accept only char type matrices and 3-channel
    CV_Assert(I.depth() == CV_8U);
    CV_Assert(I.channels() == 3);

    // Map to store color frequencies (RGB -> Frequency of that RGB)
    unordered_map<string, int> colorFreqs;
    int relevantPixelCount = 0;

    for (int row = 0; row < I.rows; row++) {
      pair<int, int> range = findLensRange(I, row);
      if (range.first != 0 && range.second != 0) {
        countColorFrequency(I, colorFreqs, row, range.first, range.second);
        relevantPixelCount += range.second - range.first + 1;
      }
    }

    int tolerance = relevantPixelCount*THRESHOLD;
    unordered_map<string, int>::iterator it;
    
    for (it = colorFreqs.begin(); it != colorFreqs.end(); ++it) {
      if (it->second > tolerance) {
        return false;
      }
    }
    return true;

/*
    unordered_map<string, int> colorFreqs;
    MatIterator_<Vec3b> it, end;
    int currRow = 0
    for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it) {
      // R-G-B
      string pixelColor = to_string((*it)[0]) + "-" + to_string((*it)[1]) + "-" + to_string((*it)[2]);
      colorFreqs[pixelColor] = (colorFreqs.find(pixelColor) != colorFreqs.end()) ? colorFreqs[pixelColor]+1 : 1;
      currRow = currRow+1 % I.size().width;
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
  */
}
}