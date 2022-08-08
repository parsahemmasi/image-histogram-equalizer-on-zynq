#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <hls_opencv.h>

#define INPUT_IMAGE_CORE "C:\\Users\\Parsa\\Desktop\\Python\\ExamplePicture.jpg"
#define OUTPUT_IMAGE_CORE "C:\\Users\\Parsa\\Desktop\\HLS_Adjusted_image.jpg"

typedef ap_axiu<8,2,5,6> uint8_side_channel;

void doHistStrech(hls::stream<uint8_side_channel> &inStream, hls::stream<uint8_side_channel> &outStream, unsigned char xMin, unsigned char xMax);

char outImage[400][400];

void saveImage(const std::string path, cv::InputArray inArr)
{
	double min;
	double max;
	cv::minMaxIdx(inArr, &min, &max);
	cv::Mat adjMap;
	cv::convertScaleAbs(inArr, adjMap, 255 / max);
	cv::imwrite(path, adjMap);
}

int main()
{
	printf("Load Image %s \n",INPUT_IMAGE_CORE);
	cv::Mat imageSrc;
	imageSrc = cv::imread(INPUT_IMAGE_CORE);
	cv::cvtColor(imageSrc,imageSrc,CV_BGR2GRAY);
	printf("Image Rows: %d  Cols: %d \n",imageSrc.rows,imageSrc.cols);

	hls::stream<uint8_side_channel> inputStream;
	hls::stream<uint8_side_channel> outputStream;

	cv::Mat imgCvOut(cv::Size(imageSrc.cols, imageSrc.rows), CV_8UC1, outImage, cv::Mat::AUTO_STEP);

	for(int idxRows = 0;idxRows<imageSrc.rows;idxRows++)
	{
		for(int idxCols=0;idxCols < imageSrc.cols;idxCols++)
		{
			uint8_side_channel valIn;
			valIn.data = imageSrc.at<unsigned char>(idxRows,idxCols);
			valIn.keep = 1;
			valIn.strb = 1;
			valIn.user = 1;
			valIn.id = 0;
			valIn.dest = 0;
			inputStream << valIn;
		}
	}

	doHistStrech(inputStream, outputStream, 0, 58);

	for(int idxRows = 0;idxRows<imageSrc.rows;idxRows++)
	{
		for(int idxCols=0;idxCols < imageSrc.cols;idxCols++)
		{
			uint8_side_channel valOut;
			outputStream.read(valOut);
			outImage[idxRows][idxCols] = valOut.data;
		}
	}

	saveImage(std::string(OUTPUT_IMAGE_CORE), imgCvOut);

	return 0;
}
