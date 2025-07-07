#include "paddle_api.h"
#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <fstream>
#include <string>

using namespace paddle::lite_api;
// saveimage
// viewimage

std::vector<std::vector<cv::Point>> locate_candidats(cv::Mat &gray)
{

    cv::Mat rectKern = cv::getStructuringElement(cv::MORPH_RECT, cv::Point(13, 5));
    cv::Mat blackhat;
    cv::morphologyEx(gray, blackhat, cv::MORPH_BLACKHAT, rectKern);
    cv::imwrite("output/blackhat.jpeg", blackhat);

    cv::Mat squareKern = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::Mat light;
    cv::morphologyEx(gray, light, cv::MORPH_CLOSE, squareKern);
    cv::threshold(light, light, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::imwrite("output/light.jpeg", light);

    cv::Mat gradient;

    cv::Sobel(blackhat, gradient, CV_32F, 1, 0, -1);

    cv::Mat absGradient = cv::abs(gradient);

    double minVal, maxVal;
    cv::minMaxLoc(absGradient, &minVal, &maxVal);
    absGradient.convertTo(gradient, CV_8U, 255.0 / (maxVal - minVal), -255.0 * minVal / (maxVal - minVal));
    cv::imwrite("output/gradient.jpeg", gradient);

    cv::GaussianBlur(gradient, gradient, cv::Size(5, 5), 0);

    cv::morphologyEx(gradient, gradient, cv::MORPH_CLOSE, rectKern);

    cv::Mat thresh;
    cv::threshold(gradient, thresh, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::erode(thresh, thresh, cv::Mat(), cv::Point(-1, -1), 2);
    cv::dilate(thresh, thresh, cv::Mat(), cv::Point(-1, -1), 2);

    cv::imwrite("output/thresh.jpeg", thresh);

    cv::bitwise_and(thresh, thresh, thresh, light);

    cv::dilate(thresh, thresh, cv::Mat(), cv::Point(-1, -1), 2);
    cv::erode(thresh, thresh, cv::Mat(), cv::Point(-1, -1), 1);

    cv::imwrite("output/final.jpeg", thresh);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(thresh.clone(), contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::sort(contours.begin(), contours.end(), [](const std::vector<cv::Point> &a, const std::vector<cv::Point> &b)
              { return cv::contourArea(a) > cv::contourArea(b); });

    return contours;
}

std::pair<cv::Mat, std::vector<cv::Point>> locateLicensePlate(
    const cv::Mat &gray,
    const std::vector<std::vector<cv::Point>> &candidates,
    double minAR = 4,
    double maxAR = 5)
{
    cv::Mat roi;
    std::vector<cv::Point> lpContour;

    for (const auto &c : candidates)
    {
        cv::Rect bbox = cv::boundingRect(c);
        double ar = static_cast<double>(bbox.width) / bbox.height;

        if (ar >= minAR && ar <= maxAR)
        {
            lpContour = c;

            cv::Mat licensePlate = gray(bbox);
            cv::resize(licensePlate, licensePlate, cv::Size(), 5.0, 5.0, cv::INTER_LINEAR);

            cv::threshold(licensePlate, roi, 0, 255,
                          cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
            cv::bitwise_not(roi, roi);
            cv::resize(roi, roi, cv::Size(), 5.0, 5.0, cv::INTER_LINEAR);
            cv::equalizeHist(roi, roi);

            ///////

            std::vector<std::vector<cv::Point>> contours;
            cv::findContours(roi, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

            int max_idx = 0;
            double max_area = 0;
            for (size_t i = 0; i < contours.size(); ++i)
            {
                double area = cv::contourArea(contours[i]);
                if (area > max_area)
                {
                    max_area = area;
                    max_idx = i;
                }
            }

            cv::Rect box = cv::boundingRect(contours[max_idx]);

            roi = roi(box);

            ////

            cv::Mat mask;
            cv::threshold(roi, mask, 30, 255, cv::THRESH_BINARY_INV);

            roi.setTo(0, mask);

            cv::floodFill(roi, cv::Point(roi.cols / 2.0, 0), cv::Scalar(255, 255, 255));
            cv::floodFill(roi, cv::Point(roi.cols - 1, roi.rows - 1), cv::Scalar(255, 255, 255));
            cv::imwrite("output/plate.jpeg", licensePlate);
            cv::imwrite("output/roi.jpeg", roi);

            break; // нашли, выходим
        }
    }

    return std::make_pair(roi, lpContour);
}

std::vector<std::string> load_dict(const std::string &dict_path)
{
    std::vector<std::string> labels;
    std::ifstream ifs(dict_path);
    if (!ifs.is_open())
    {
        std::cerr << "Failed to open dict file: " << dict_path << std::endl;
        return labels;
    }
    std::string line;
    while (std::getline(ifs, line))
    {
        if (!line.empty())
        {
            labels.push_back(line);
        }
    }
    return labels;
}
std::pair<std::string, std::vector<cv::Point>> findAndOCR(
    cv::Mat gray,
    double minAR,
    double maxAR)
{
    std::string lpText;
    std::vector<cv::Point> lpContour;
    cv::Mat lp;

    std::vector<std::vector<cv::Point>> candidates = locate_candidats(gray);
    std::tie(lp, lpContour) = locateLicensePlate(gray, candidates, minAR, maxAR);

    if (!lp.empty())
    {
        MobileConfig config;
        config.set_model_from_file("Paddle-Lite/ch_ppocr_mobile_v2.0_rec_infer_opt.nb");
        auto predictor = CreatePaddlePredictor(config);

        cv::Mat resized;
        if (lp.channels() == 1)
            cv::cvtColor(lp, resized, cv::COLOR_GRAY2RGB);
        else
            resized = lp.clone();

        const int target_w = 320;
        const int target_h = 32;

        float scale = std::min(target_w * 1.0f / resized.cols, target_h * 1.0f / resized.rows);
        int new_w = static_cast<int>(resized.cols * scale);
        int new_h = static_cast<int>(resized.rows * scale);

        cv::resize(resized, resized, cv::Size(new_w, new_h));
        cv::Mat padded;
        int pad_w = target_w - new_w;
        int pad_h = target_h - new_h;
        cv::copyMakeBorder(resized, padded, 0, pad_h, 0, pad_w, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255));

        padded.convertTo(padded, CV_32FC3, 1.0 / 255);
        cv::Scalar mean(0.5f, 0.5f, 0.5f);
        cv::Scalar std(0.5f, 0.5f, 0.5f);
        cv::subtract(padded, mean, padded);
        cv::divide(padded, std, padded);

        auto input_tensor = predictor->GetInput(0);
        input_tensor->Resize({1, 3, target_h, target_w});
        float *input_data = input_tensor->mutable_data<float>();

        std::vector<cv::Mat> input_channels;
        for (int i = 0; i < 3; ++i)
        {
            cv::Mat channel(target_h, target_w, CV_32FC1, input_data + i * target_h * target_w);
            input_channels.push_back(channel);
        }
        cv::split(padded, input_channels);

        predictor->Run();

        auto output_tensor = predictor->GetOutput(0);
        auto shape = output_tensor->shape();
        float *output_data = output_tensor->mutable_data<float>();

        int seq_len = shape[1];
        int num_classes = shape[2];

        // Словарь
        static std::vector<std::string> label_list = load_dict("ppocr_keys_v1.txt");

        std::string result;
        int last_idx = -1;
        std::cout << "Output shape: " << shape[0] << "x" << shape[1] << "x" << shape[2] << std::endl;
        for (int t = 0; t < seq_len; ++t)
        {
            int max_idx = 0;
            float max_val = -1.0f;

            for (int c = 0; c < num_classes; ++c)
            {
                float val = output_data[t * num_classes + c];
                if (val > max_val)
                {
                    max_val = val;
                    max_idx = c;
                }
            }
            std::cout << "Time step " << t << ": class=" << max_idx << ", value=" << max_val << std::endl;

            if (max_idx != 0 && max_idx <= (int)label_list.size() && max_idx != last_idx)
            {
                result += label_list[max_idx - 1];
            }
            last_idx = max_idx;
        }

        std::cout << "OCR result: " << result << std::endl;
        lpText = result;
    }

    return std::make_pair(lpText, lpContour);
}

int main()
{
    cv::Mat gray = cv::imread("images/2.jpeg", cv::IMREAD_GRAYSCALE);

    std::pair<std::__cxx11::string, std::vector<cv::Point>> text = findAndOCR(gray, 4, 5);
    std::cout << text.first << std::endl;
    return 0;
}