#ifndef FILE_UTIL_HH
#define FILE_UTIL_HH

#include <iostream>
#include <numeric>

#include "portable-file-dialogs.h"

namespace utcn::ip {
class FileUtil {
 private:
  static inline std::string DEFAULT_IMAGES_PATH = ASSETS_DIR "Images/*";

 public:
  static std::string getSingleFileAbsPath();
  static std::string getDirectoryAbsPath();
};
}  // namespace utcn::ip

#endif  // FILE_UTIL_HH
