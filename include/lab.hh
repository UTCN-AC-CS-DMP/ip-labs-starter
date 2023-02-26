#ifndef LAB_HH
#define LAB_HH

#include <cstdlib>
#include <iostream>
#include <map>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

namespace utcn::ip {
class Lab {
  virtual void runLab() = 0;

 protected:
  static void printMenu(const std::map<uint16_t, std::string>& entries);
};
}  // namespace utcn::ip

#endif  // LAB_HH
