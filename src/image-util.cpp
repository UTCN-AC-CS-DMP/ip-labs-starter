#include "image-util.hh"

void utcn::ip::ImageUtil::resizeImg(cv::Mat src, cv::Mat &dst, int maxSize,
                                    bool interpolate) {
  double ratio = 1;
  double w = src.cols;
  double h = src.rows;
  if (w > h)
    ratio = w / (double)maxSize;
  else
    ratio = h / (double)maxSize;
  int nw = (int)(w / ratio);
  int nh = (int)(h / ratio);
  cv::Size sz(nw, nh);
  if (interpolate)
    cv::resize(src, dst, sz);
  else
    resize(src, dst, sz, 0, 0, cv::INTER_NEAREST);
}