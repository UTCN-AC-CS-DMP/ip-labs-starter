#include "lab1.hh"

void utcn::ip::Lab1::runLab() {
  int op;
  do {
    utcn::ip::Lab1::printMenu(LAB1_MENU);
    std::cin >> op;
    switch (op) {
      case 0:
        break;
      case 1:
        testOpenImage();
        break;
      case 2:
        testOpenImagesFld();
        break;
      case 3:
        testNegativeImage();
        break;
      case 4:
        testNegativeImageFast();
        break;
      case 5:
        testColor2Gray();
        break;
      case 6:
        testImageOpenAndSave();
        break;
      case 7:
        testBGR2HSV();
        break;
      case 8:
        testResize();
        break;
      case 9:
        testCanny();
        break;
      case 10:
        testVideoSequence();
        break;
      case 11:
        testSnap();
        break;
      case 12:
        testMouseClick();
        break;
      default:
        std::cout << "Invalid selection" << std::endl;
    }
  } while (op != 0);
}

void utcn::ip::Lab1::testOpenImage() {
  const std::string abs_image_path = fileutil::getSingleFileAbsPath();
  if (!abs_image_path.empty()) {
    cv::Mat src;
    src = cv::imread(abs_image_path);
    imshow("image", src);
    cv::waitKey();
  }
}

// Not recursive
void utcn::ip::Lab1::testOpenImagesFld() {
  const std::string dir_abs_path = fileutil::getDirectoryAbsPath();
  if (!dir_abs_path.empty()) {
    const fs::path path_to_traverse(dir_abs_path);
    if (fs::exists(path_to_traverse) && fs::is_directory(path_to_traverse)) {
      for (const auto &entry : fs::directory_iterator(path_to_traverse)) {
        auto abs_file_path = entry.path().string();
        cv::Mat src;
        src = cv::imread(abs_file_path);
        imshow(entry.path().filename(), src);
      }
      cv::waitKey();
    }
  }
}

void utcn::ip::Lab1::testNegativeImage() {
  const std::string abs_image_path = fileutil::getSingleFileAbsPath();
  if (!abs_image_path.empty()) {
    cv::Mat src = imread(abs_image_path, cv::IMREAD_GRAYSCALE);
    int height = src.rows;
    int width = src.cols;
    cv::Mat dst = cv::Mat(height, width, CV_8UC1);

    auto t1 = std::chrono::high_resolution_clock::now();

    // Accessing individual pixels in an 8 bits/pixel image
    // Inefficient way -> slow
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        uchar val = src.at<uchar>(i, j);
        uchar neg = 255 - val;
        dst.at<uchar>(i, j) = neg;
      }
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    // Compute the time difference [ms]
    std::cout << "It took "
              << std::chrono::duration<double, std::milli>(t2 - t1)
              << std::endl;

    imshow("input image", src);
    imshow("negative image", dst);
    cv::waitKey();
  }
}

void utcn::ip::Lab1::testNegativeImageFast() {
  const std::string abs_image_path = fileutil::getSingleFileAbsPath();
  if (!abs_image_path.empty()) {
    cv::Mat src = imread(abs_image_path, cv::IMREAD_GRAYSCALE);
    int height = src.rows;
    int width = src.cols;
    cv::Mat dst = cv::Mat(height, width, CV_8UC1);

    auto t1 = std::chrono::high_resolution_clock::now();

    // The fastest approach of accessing the pixels -> using pointers
    uchar *lpSrc = src.data;
    uchar *lpDst = dst.data;
    int w = (int)src.step;  // no dword alignment is done !!!
    for (int i = 0; i < height; i++)
      for (int j = 0; j < width; j++) {
        uchar val = lpSrc[i * w + j];
        lpDst[i * w + j] = 255 - val;
      }

    auto t2 = std::chrono::high_resolution_clock::now();

    // Compute the time difference [ms]
    std::cout << "It took "
              << std::chrono::duration<double, std::milli>(t2 - t1)
              << std::endl;

    imshow("input image", src);
    imshow("negative image", dst);
    cv::waitKey();
  }
}

void utcn::ip::Lab1::testColor2Gray() {
  const std::string abs_image_path = fileutil::getSingleFileAbsPath();
  if (!abs_image_path.empty()) {
    cv::Mat src = cv::imread(abs_image_path);

    int height = src.rows;
    int width = src.cols;

    cv::Mat dst = cv::Mat(height, width, CV_8UC1);

    // Accessing individual pixels in a RGB 24 bits/pixel image
    // Inefficient way -> slow
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        cv::Vec3b v3 = src.at<cv::Vec3b>(i, j);
        uchar b = v3[0];
        uchar g = v3[1];
        uchar r = v3[2];
        dst.at<uchar>(i, j) = (r + g + b) / 3;
      }
    }

    imshow("input image", src);
    imshow("gray image", dst);
    cv::waitKey();
  }
}

void utcn::ip::Lab1::testImageOpenAndSave() {
  cv::Mat src, dst;
  const std::string path_to_src = ASSETS_DIR "Images/Lena_24bits.bmp";
  src = imread(path_to_src, cv::IMREAD_COLOR);  // Read the image

  if (!src.data) {
    std::cout << "Could not open or find the image" << std::endl;
    return;
  }

  // Get the image resolution
  cv::Size src_size = cv::Size(src.cols, src.rows);

  // Display window
  const char *WIN_SRC = "Src";  // window for the source image
  cv::namedWindow(WIN_SRC, cv::WINDOW_AUTOSIZE);
  cv::moveWindow(WIN_SRC, 0, 0);

  const char *WIN_DST = "Dst";  // window for the destination (processed) image
  cv::namedWindow(WIN_DST, cv::WINDOW_AUTOSIZE);
  cv::moveWindow(WIN_DST, src_size.width + 10, 0);

  cvtColor(src, dst,
           cv::COLOR_BGR2GRAY);  // converts the source image to a grayscale one

  const std::string path_to_dst = ASSETS_DIR "Images/Lena_24bits_gray.bmp";
  imwrite(path_to_dst, dst);  // writes the destination to
                              // file

  cv::imshow(WIN_SRC, src);
  cv::imshow(WIN_DST, dst);

  cv::waitKey(0);
}

void utcn::ip::Lab1::testBGR2HSV() {
  const std::string abs_image_path = fileutil::getSingleFileAbsPath();
  if (!abs_image_path.empty()) {
    cv::Mat src = cv::imread(abs_image_path);
    int height = src.rows;
    int width = src.cols;

    // HSV components
    cv::Mat H = cv::Mat(height, width, CV_8UC1);
    cv::Mat S = cv::Mat(height, width, CV_8UC1);
    cv::Mat V = cv::Mat(height, width, CV_8UC1);

    // Defining pointers to each matrix (8 bits/pixels) of the individual
    // components H, S, V
    uchar *lpH = H.data;
    uchar *lpS = S.data;
    uchar *lpV = V.data;

    cv::Mat hsvImg;
    cv::cvtColor(src, hsvImg, cv::COLOR_BGR2HSV);

    // Defining the pointer to the HSV image matrix (24 bits/pixel)
    uchar *hsvDataPtr = hsvImg.data;

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        int hi = i * width * 3 + j * 3;
        int gi = i * width + j;

        lpH[gi] = hsvDataPtr[hi] * 510 / 360;  // lpH = 0 .. 255
        lpS[gi] = hsvDataPtr[hi + 1];          // lpS = 0 .. 255
        lpV[gi] = hsvDataPtr[hi + 2];          // lpV = 0 .. 255
      }
    }

    cv::imshow("input image", src);
    cv::imshow("H", H);
    cv::imshow("S", S);
    cv::imshow("V", V);

    cv::waitKey();
  }
}

void utcn::ip::Lab1::testResize() {
  const std::string abs_image_path = fileutil::getSingleFileAbsPath();
  if (!abs_image_path.empty()) {
    cv::Mat src;
    src = cv::imread(abs_image_path);
    cv::Mat dst1, dst2;
    // without interpolation
    imageutil::resizeImg(src, dst1, 320, false);
    // with interpolation
    imageutil::resizeImg(src, dst2, 320, true);
    imshow("input image", src);
    imshow("resized image (without interpolation)", dst1);
    imshow("resized image (with interpolation)", dst2);
    cv::waitKey();
  }
}

void utcn::ip::Lab1::testCanny() {
  const std::string abs_image_path = fileutil::getSingleFileAbsPath();
  if (!abs_image_path.empty()) {
    cv::Mat src, dst, gauss;
    src = imread(abs_image_path, cv::IMREAD_GRAYSCALE);
    double k = 0.4;
    int pH = 50;
    int pL = (int)k * pH;
    GaussianBlur(src, gauss, cv::Size(5, 5), 0.8, 0.8);
    Canny(gauss, dst, pL, pH, 3);
    imshow("input image", src);
    imshow("canny", dst);
    cv::waitKey();
  }
};

void utcn::ip::Lab1::testVideoSequence() {
  const std::string path_to_vid = ASSETS_DIR "Videos/rubic.avi";
  cv::VideoCapture cap(path_to_vid);  // off-line video from file
  // VideoCapture cap(0);	// live video from webcam
  if (!cap.isOpened()) {
    std::cout << "Cannot open video capture device" << std::endl;
    cv::waitKey(0);
    return;
  }

  cv::Mat edges;
  cv::Mat frame;
  uchar c;

  while (cap.read(frame)) {
    cv::Mat grayFrame;
    cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    Canny(grayFrame, edges, 40, 100, 3);
    imshow("source", frame);
    imshow("gray", grayFrame);
    imshow("edges", edges);
    c = cv::waitKey(100);  // waits 100ms and advances to the next frame
    if (c == 27) {
      // press ESC to exit
      std::cout << "ESC pressed - capture finished" << std::endl;
      break;  // ESC pressed
    };
  }
}

void utcn::ip::Lab1::testSnap() {
  cv::VideoCapture cap(
      0);                 // open the deafult camera (i.e. the built in web cam)
  if (!cap.isOpened()) {  // openenig the video device failed
    printf("Cannot open video capture device.\n");
    return;
  }

  cv::Mat frame;
  char numberStr[256];
  char fileName[256];

  // video resolution
  cv::Size capS = cv::Size((int)cap.get(cv::CAP_PROP_FRAME_WIDTH),
                           (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT));

  // Display window
  const char *WIN_SRC = "Src";  // window for the source frame
  namedWindow(WIN_SRC, cv::WINDOW_AUTOSIZE);
  cv::moveWindow(WIN_SRC, 0, 0);

  const char *WIN_DST = "Snapped";  // window for showing the snapped frame
  namedWindow(WIN_DST, cv::WINDOW_AUTOSIZE);
  cv::moveWindow(WIN_DST, capS.width + 10, 0);

  uchar c;
  int frameNum = -1;
  int frameCount = 0;

  for (;;) {
    cap >> frame;  // get a new frame from camera
    if (frame.empty()) {
      printf("End of the video file\n");
      break;
    }

    ++frameNum;

    imshow(WIN_SRC, frame);

    c = cv::waitKey(10);  // waits a key press to advance to the next frame
    if (c == 27) {
      // press ESC to exit
      std::cout << "ESC pressed - capture finished" << std::endl;
      break;  // ESC pressed
    }
    if (c == 115) {  //'s' pressed - snap the image to a file
      frameCount++;
      fileName[0] = '\0';
      sprintf(numberStr, "%d", frameCount);
      strcat(fileName, ASSETS_DIR "Images/A");
      strcat(fileName, numberStr);
      strcat(fileName, ".bmp");
      bool bSuccess = cv::imwrite(fileName, frame);
      if (!bSuccess) {
        std::cout << "Error writing the snapped image" << std::endl;
      } else
        cv::imshow(WIN_DST, frame);
    }
  }
}

void utcn::ip::Lab1::myCallBackFunc(int event, int x, int y, int flags, void *param) {
  // More examples:
  // http://opencvexamples.blogspot.com/2014/01/detect-mouse-clicks-and-moves-on-image.html
  auto *src = (cv::Mat *)param;
  if (event == cv::EVENT_LBUTTONDOWN) {
    printf("Pos(x,y): %d,%d  Color(RGB): %d,%d,%d\n", x, y,
           (int)(*src).at<cv::Vec3b>(y, x)[2],
           (int)(*src).at<cv::Vec3b>(y, x)[1],
           (int)(*src).at<cv::Vec3b>(y, x)[0]);
  }
}

void utcn::ip::Lab1::testMouseClick() {
  const std::string abs_image_path = fileutil::getSingleFileAbsPath();
  if (!abs_image_path.empty()) {
    cv::Mat src = cv::imread(abs_image_path);
    // Create a window
    cv::namedWindow("My Window", 1);

    // set the callback function for any mouse event
    cv::setMouseCallback("My Window", myCallBackFunc, &src);

    // show the image
    cv::imshow("My Window", src);

    // Wait until user press some key
    cv::waitKey(0);
  }
}