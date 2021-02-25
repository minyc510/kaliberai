#include <opencv2/opencv.hpp>
#include <iostream>
#include <unordered_map>
#include "util.cpp"

using namespace cv;
using namespace std;

int testFindRelevantRange() {
  vector<string> imgs {
    "../media/test-media/20x20.jpg",
    "../media/test-media/allblack.jpg",
    "../media/test-media/greenbox.jpg",
  };
  
  for (int i = 0; i < imgs.size(); i++) {
    const string imagePath = imgs[i];
    Mat img = imread(imagePath, IMREAD_COLOR);
    
    Mat_<Vec3b> _I = img;
    cout << imagePath << endl;
    // For each row, find the relevant range and count the color frequencies within it
    for (int row = 0; row < _I.rows; row++) {
      pair<int, int> range = util::findRelevantRange(_I, row);
      cout << range.first << " , " << range.second << endl;
    }
  }

  return 0;

}

int main(int argc, char* argv[]) {
  testFindRelevantRange();
}

