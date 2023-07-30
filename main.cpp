#include <opencv2/opencv.hpp>
// #include <iostream>

// using namespace cv;
// using namespace std;
    /*
 // Read the image file
 Mat image = imread("/home/miki/Pictures/tatra.jpg");

 // Check for failure
 if (image.empty()) 
 {
  cout << "Could not open or find the image" << endl;
  cin.get(); //wait for any key press
  return -1;
 }

 String windowName = "Tatry"; //Name of the window

 namedWindow(windowName, WINDOW_NORMAL); // Create a window

 imshow(windowName, image); // Show our image inside the created window.

 waitKey(0); // Wait for any keystroke in the window

 destroyWindow(windowName); //destroy the created window

    */

#include <iostream>
#include <fstream>
#include <sstream>
using namespace cv;
using namespace cv::face;
using namespace std;

// static Mat norm_0_255(InputArray _src) {
//     Mat src = _src.getMat();
//     Mat dst;
//     switch(src.channels()) {
//         case 1:
//             cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
//             break;
//         case 3:
//             cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
//             break;
//         default:
//             src.copyTo(dst);
//             break;
//     }
//     return dst;
// }
static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') 
{
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(Error::StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);

        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}
int main(int argc, const char *argv[]) {

    string fn_csv = "/home/miki/repo/EngineeringThesis/facesDB.txt";

    String windowName = "Face recognition"; 
    namedWindow(windowName, WINDOW_NORMAL); 

    vector<Mat> images;
    vector<int> labels;

    try {
        read_csv(fn_csv, images, labels);
    } catch (const cv::Exception& e) {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;

        exit(1);
    }

    Mat testSample = images[images.size() - 1];
    int testLabel = labels[labels.size() - 1];
    images.pop_back();
    labels.pop_back();

    Ptr<EigenFaceRecognizer> model = EigenFaceRecognizer::create();
    model->train(images, labels);

    int predictedLabel = model->predict(testSample);

    if(predictedLabel == testLabel)
    {
        string result_message = format("Recognition successful for face: %d ", testLabel);
        cout << result_message << endl;
    }
    imshow(windowName, testSample); 

    destroyWindow(windowName);
    waitKey(0);
    return 0;
}
