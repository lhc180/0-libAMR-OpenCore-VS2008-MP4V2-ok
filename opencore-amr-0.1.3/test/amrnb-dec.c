/* ------------------------------------------------------------------
 * Copyright (C) 2009 Martin Storsjo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 * -------------------------------------------------------------------
 */
//xx  ../encode-8k-1ch.amr  ../decode-8k-1ch.wav
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "wavwriter.h"
#include <interf_dec.h>

/* From WmfDecBytesPerFrame in dec_input_format_tab.cpp */
const int sizes[] = { 12, 13, 15, 17, 19, 20, 26, 31, 5, 6, 5, 5, 0, 0, 0, 0 };

//#define DISABLE_AMRNB_ENCODER
 

int main(int argc, char *argv[]) {
	
	FILE* in;
	char header[6];
	int n;
	void *wav;//
	void *amr;
	void *amrDecoder;

	
//lhc mp4 dec 1/4
FileWrapperPtr inputFile;

//	void* amrDecoder = (void*) malloc(sizeof(void *));
	//void* amrDecoder = NULL;

	
	fprintf(stderr, "AMR-NB  DEcode .amr file to .wav\n");

	if (argc < 1) {
		fprintf(stderr, "%s in.amr out.wav\n", argv[0]);
		return 1;
	}

//+++///////////////////////////////////////////////
	
//lhc mp4 open 2/4
  inputFile = FileWrapper_Open(argv[1]);
  if (inputFile == 0) {
    fprintf(stderr, "Failed to open bitstream file %s\n", argv[1]);
    return -1;
  } else if (!FileWrapper_IsMp4File(inputFile)) {
    fprintf(stderr, "Invalid input file %s\n", argv[1]);
    return -2;
  } else {
    fprintf(stderr, "Input bitstream file:\t%s\n", argv[1]);
  }

//+++///////////////////////////////=========////


//default
 // ../encode-8k-1ch.amr  ../decode-8k-1ch.wav
	in = fopen(argv[1], "rb");	
//in = fopen("encode-8k-1ch.amr", "rb");
	if (!in) {
		perror(argv[1]);
		return 1;
	}


	//check the file format
	n = fread(header, 1, 6, in);
	if (n != 6 || memcmp(header, "#!AMR\n", 6)) {
		fprintf(stderr, "Bad header\n");
		return 1;
	}


//ready output file 
//	wav = wav_write_open("decode-8k-1ch.wav", 8000, 16, 1);
	wav = wav_write_open(argv[2], 8000, 16, 1);
	if (!wav) {
		fprintf(stderr, "Unable to open %s\n", argv[2]);
		return 1;
	}



	//amr = Decoder_Interface_init();
	 //Decoder_Interface_init(amrDecoder);
	 amr =Decoder_Interface_init();


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	while (1) {

		uint8_t buffer[500], littleendian[320], *ptr;
		int size, i;
		int16_t outbuffer[160];


//default read frame to buffer
		/* Read the mode byte */
		n = fread(buffer, 1, 1, in);
		if (n <= 0)
			break;

		/* Find the packet size */
		size = sizes[(buffer[0] >> 3) & 0x0f];
		n = fread(buffer + 1, 1, size, in);
		if (n != size)
			break;
//default read data to buffer =============



		/* Decode the packet */
		//Decoder_Interface_Decode(amr, buffer, outbuffer, 0);
		//Decoder_Interface_Decode(amrDecoder, buffer, outbuffer, 0);
		Decoder_Interface_Decode(amr, buffer, outbuffer, 0);

		/* Convert to little endian and write to wav */
		ptr = littleendian;
		for (i = 0; i < 160; i++) {
			*ptr++ = (outbuffer[i] >> 0) & 0xff;
			*ptr++ = (outbuffer[i] >> 8) & 0xff;
		}

      //lhc wave
		wav_write_data(wav, littleendian, 320);
	}

 ///++++++++++++++++++++++++++++++
	//lhc 3gp exit

	//default
	fclose(in);




	 Decoder_Interface_exit(amr);
	//Decoder_Interface_exit(amrDecoder);
    
	//free(amrDecoder);
	//amrDecoder=NULL;


      //lhc wave
	wav_write_close(wav);

	fprintf(stderr, "Finished Decode \n");
	//getchar();
	return 0;
}

