#include <hls_stream.h>
#include <ap_axi_sdata.h>

typedef ap_axiu<8,2,5,6> uint8_side_channel;

void doHistStrech(hls::stream<uint8_side_channel> &inStream, hls::stream<uint8_side_channel> &outStream, unsigned char xMin, unsigned char xMax)
{
	#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS
	#pragma HLS INTERFACE s_axilite port=xMax bundle=CRTL_BUS
	#pragma HLS INTERFACE s_axilite port=xMin bundle=CRTL_BUS
	#pragma HLS INTERFACE axis port=outStream
	#pragma HLS INTERFACE axis port=inStream

	float xMax_minus_xMin = xMax - xMin;

	for(int idxPixel = 0;idxPixel < 400*400;idxPixel++)
	{
		#pragma HLS PIPELINE

		uint8_side_channel currPixelSideChannel = inStream.read();
		uint8_side_channel dataOutSideChannel;

		unsigned char x_t = currPixelSideChannel.data;

		float y_t_float = ((x_t - xMin) / (xMax_minus_xMin)) * 255;

		unsigned char y_t = y_t_float;

		dataOutSideChannel.data = y_t;
		dataOutSideChannel.keep = currPixelSideChannel.keep;
		dataOutSideChannel.strb = currPixelSideChannel.strb;
		dataOutSideChannel.user = currPixelSideChannel.user;
		dataOutSideChannel.last = currPixelSideChannel.last;
		dataOutSideChannel.id = currPixelSideChannel.id;
		dataOutSideChannel.dest = currPixelSideChannel.dest;

		outStream.write(dataOutSideChannel);
	}
}
