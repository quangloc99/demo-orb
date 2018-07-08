#include <opencv2/opencv.hpp>
#include "ORBextractor.h"
using namespace cv;
using namespace std;
using namespace ORB_SLAM2;
//using namespace cv::xfeatures2d;

Mat imreadWithSize(const string& name, int flag, int h, int w) {
  Mat ans;
  cv::rotate(imread(name, flag), ans, ROTATE_90_CLOCKWISE);
  resize(ans, ans, Size(w, h));
  return ans;
}

vector<DMatch> match(Mat des0, Mat des1, float threshold = -1) {
  vector<DMatch> ans;
  flann::Index flannIndex(des0, flann::LshIndexParams(30, 20, 2));
  Mat id, dist;
  flannIndex.knnSearch(des1, id, dist, 1);
  for (int i = 0; i < des1.rows; ++i) {
    float dis = dist.at<int>(i, 0);
    if (threshold >= 0 && dis > threshold) continue;
    ans.push_back(DMatch(id.at<int>(i, 0), i, dis));
  }
  return ans;
}

unordered_map<string, long long>  timeStamp;
void stampTime(const string& name) {
  if (!timeStamp.count(name)) {
    timeStamp[name] = clock();
  } else {
    float duration = (clock() - timeStamp[name]) * 1000.0 / CLOCKS_PER_SEC;
    clog << "Time " << name << ": " << duration << "ms" << endl;
  }
}

string toString(int num) {
  stringstream ss;
  ss << setw(5) << setfill('0') << num;
  return ss.str();
}

int main(void) {
  namedWindow("Matches", WINDOW_AUTOSIZE);

  stampTime("reading image");
  string filename0 = "scene00009.png";
  string filename1 = "scene00010.png";
  Mat img0 = imreadWithSize(filename0, IMREAD_GRAYSCALE, 640, 480);
  Mat img1 = imreadWithSize(filename1, IMREAD_GRAYSCALE, 640, 480);
  stampTime("reading image");

  stampTime("extracting ORB keypoints and descriptors (ORB_SLAM way)");
  ORBextractor extract(1000, 1.2f, 8, 20, 10);
  vector<KeyPoint> kp0, kp1;
  Mat des0, des1;
  extract(img0, noArray(), kp0, des0);
  extract(img1, noArray(), kp1, des1);
  stampTime("extracting ORB keypoints and descriptors (ORB_SLAM way)");

  stampTime("matching descriptors (OPENCV way)");
  vector<DMatch> matches = match(des0, des1, 50);
  Mat out;
  stampTime("matching descriptors (OPENCV way)");

  drawMatches(img0, kp0, img1, kp1, matches, out);
  imshow("Matches", out);


  waitKey(0);

  return 0 ;
}
