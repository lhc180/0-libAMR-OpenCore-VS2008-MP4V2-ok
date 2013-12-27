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
#include <cstdlib>
#include <string>

#include <stdio.h>
#include <string.h>

#include "wavwriter.h"
#include <interf_dec.h>

//lhc mp4
#include "mp4v2.h" 

/* From WmfDecBytesPerFrame in dec_input_format_tab.cpp */
const int sizes[] = { 12, 13, 15, 17, 19, 20, 26, 31, 5, 6, 5, 5, 0, 0, 0, 0 };

//#define DISABLE_AMRNB_ENCODER
 

int main(int argc, char *argv[]) {
	
	FILE* inAmrfile;
	char header[6];
	int n;
	void *outWavfile;//
	void *amr;
	void *amrDecoder;

	
//lhc mp4 dec 1/4
    uint8_t* pConfig;
	uint32_t configSize = 0;
	MP4FileHandle mp4File;

    MP4TrackId video_trackId ;
    MP4TrackId audio_trackId ;

	uint8_t video_profileLevel;   
	uint8_t audio_profileLevel;
    uint32_t timeScale ;

	MP4Duration trackDuration;
	MP4SampleId numSamples;
	uint32_t maxSampleSize;

	MP4Timestamp sampleTime;
	MP4Duration sampleDuration;
	MP4Duration sampleRenderingOffset;
	bool isSyncSample;

	uint8_t* pSample = (uint8_t*)malloc(maxSampleSize);
	uint32_t sampleSize;


//	void* amrDecoder = (void*) malloc(sizeof(void *));
	//void* amrDecoder = NULL;

	
	fprintf(stderr, "AMR-NB  DEcode .amr file to .wav\n");

	if (argc < 1) {
		fprintf(stderr, "%s in.amr out.wav\n", argv[0]);
		return 1;
	}

//+++///////////////////////////////////////////////
	
//lhc mp4 open 2/4
	// open the mp4 file, and read meta-info
	  mp4File = MP4Read("vid_demo_1.mp4");	
 
	// get a handle on the first video track
	  audio_trackId = MP4FindTrackId(mp4File, 0, "audio", 0);
	  video_trackId = MP4FindTrackId(mp4File, 0, "video", 0);
  
	  audio_profileLevel = MP4GetAudioProfileLevel(mp4File);
	  video_profileLevel = MP4GetVideoProfileLevel(mp4File); 

	// gather the crucial track information 

	  //timeScale = MP4GetTrackTimeScale(mp4File, video_trackId);
	  timeScale = MP4GetTrackTimeScale(mp4File, audio_trackId);
	// note all times and durations 
	// are in units of the track time scale

	  trackDuration = MP4GetTrackDuration(mp4File, audio_trackId);
	  numSamples = MP4GetTrackNumberOfSamples(mp4File, audio_trackId);
	  maxSampleSize = MP4GetTrackMaxSampleSize(mp4File, audio_trackId);
	
	MP4GetTrackESConfiguration(mp4File, audio_trackId, &pConfig, &configSize);

	// done with our copy of ES configuration
	free(pConfig);

	//+++///////////////////////////////=========////

	for (MP4SampleId sampleId = 1; sampleId <= numSamples; sampleId++) {

		// give ReadSample our own buffer, and let it know how big it is
		sampleSize = maxSampleSize;

        // read next sample from video track
		MP4ReadSample(mp4File, audio_trackId, sampleId, 
					&pSample, &sampleSize );

		// read next sample from video track
		//MP4ReadSample(mp4File, audio_trackId, sampleId, 
		//	&pSample, &sampleSize,
		//	&sampleTime, &sampleDuration, &sampleRenderingOffset, 
		//	&isSyncSample);

		// convert timestamp and duration from track time to milliseconds
		//uint64_t myTime = MP4ConvertFromTrackTimestamp(mp4File, audio_trackId, 
		//	sampleTime, MP4_MSECS_TIME_SCALE);

		//uint64_t myDuration = MP4ConvertFromTrackDuration(mp4File, audio_trackId,
		//	sampleDuration, MP4_MSECS_TIME_SCALE);

		// decode frame and display it
	}

	// close mp4 file
	MP4Close(mp4File);


//default
 // ../encode-8k-1ch.amr  ../decode-8k-1ch.wav
	inAmrfile = fopen(argv[1], "rb");	
//in = fopen("encode-8k-1ch.amr", "rb");
	if (!inAmrfile) {
		perror(argv[1]);
		return 1;
	}


	//check the file format
	n = fread(header, 1, 6, inAmrfile);
	if (n != 6 || memcmp(header, "#!AMR\n", 6)) {
		fprintf(stderr, "Bad header\n");
		return 1;
	}


//ready output file 
//	wav = wav_write_open("decode-8k-1ch.wav", 8000, 16, 1);
	outWavfile = wav_write_open(argv[2], 8000, 16, 1);
	if (!outWavfile) {
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
		n = fread(buffer, 1, 1, inAmrfile);
		if (n <= 0)
			break;

		/* Find the packet size */
		size = sizes[(buffer[0] >> 3) & 0x0f];
		n = fread(buffer + 1, 1, size, inAmrfile);
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
		wav_write_data(outWavfile, littleendian, 320);
	}

 ///++++++++++++++++++++++++++++++
	//lhc 3gp exit

	//default
	fclose(inAmrfile);




	 Decoder_Interface_exit(amr);
	//Decoder_Interface_exit(amrDecoder);
    
	//free(amrDecoder);
	//amrDecoder=NULL;


      //lhc wave
	wav_write_close(outWavfile);

	fprintf(stderr, "Finished Decode \n");
	//getchar();
	return 0;
}

