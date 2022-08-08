#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <hls_opencv.h>

#include <hls_stream.h>
#include <ap_axi_sdata.h>

typedef ap_axiu<8,2,5,6> uint8_side_channel;

void doHist(hls::stream<uint8_side_channel> &inStream, int histo[256]);

#define INPUT_IMAGE_CORE "C:\\Users\\Parsa\\Desktop\\Python\\ExamplePicture.jpg"
#define FILE_HISTOGRAM "Hist.txt"

char outImage[400][400];
int histo[256];
int lutMult[256];

void saveHistogram(const char* filename,int *histPointer)
{
	FILE *pfile;
	pfile = fopen(filename,"w");
	if(pfile != NULL)
	{
		for(int idx = 0;idx<256;idx++)
		{
			fprintf(pfile,"Bin[%d]=%d\n",idx,histPointer[idx]);
		}
	}
}

int main()
{
	printf("Load Image %s \n",INPUT_IMAGE_CORE);
	cv::Mat imageSrc;
	imageSrc = cv::imread(INPUT_IMAGE_CORE);
	cv::cvtColor(imageSrc, imageSrc, CV_BGR2GRAY);
	printf("Image Rows : %d  Cols: %d ",imageSrc.rows, imageSrc.cols);

	hls::stream<uint8_side_channel> inputStream;

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
	doHist(inputStream,histo);
	saveHistogram(FILE_HISTOGRAM,histo);

	return 0;
}
