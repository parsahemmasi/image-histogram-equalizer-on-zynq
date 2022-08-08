#include <hls_stream.h>
#include <ap_axi_sdata.h>

typedef ap_axiu<8,2,5,6> uint8_side_channel;

void doHist(hls::stream<uint8_side_channel> &inStream, int histo[256])
{
	#pragma HLS INTERFACE bram port=histo
	#pragma HLS INTERFACE axis port=inStream
	#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS

	for(int idxHist = 0;idxHist<256;idxHist++)
	{
		#pragma HLS PIPELINE
		histo[idxHist] = 0;
	}

	for(int idxPixel = 0;idxPixel<400*400;idxPixel++)
	{
		uint8_side_channel currPixelSideChannel = inStream.read();
		histo[currPixelSideChannel.data]++;
	}
}
