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
//xx  ../encode-8k-1ch.mp4 ../decode-8k-1ch.wav
#include <cstdlib>
#include <string>

#include <stdio.h>
#include <string.h>

#include "wavwriter.h"
#include <interf_dec.h>

//lhc mp4
#include "mp4v2.h" 

//#define DISABLE_AMRNB_ENCODER
 

int main(int argc, char *argv[]) {
	
 
	void *outWavfile;
	int16_t outWavBuf[160];
	void *amrDecoder; 

	
//lhc mp4 dec 1/4
   // uint8_t* pConfig;
	//uint32_t configSize = 0;
	MP4FileHandle mp4File;

    //MP4TrackId video_trackId ;
    MP4TrackId audio_trackId ;

	//uint8_t video_profileLevel;   
	//uint8_t audio_profileLevel;
    uint32_t timeScale ;

	MP4Duration trackDuration;
	MP4SampleId numSamples;
	uint32_t maxSampleSize;

	//MP4Timestamp sampleTime;
	//MP4Duration sampleDuration;
	//MP4Duration sampleRenderingOffset;
	//bool isSyncSample;

	uint8_t* pSample;
	uint32_t sampleSize;

 
	fprintf(stderr, "AMR-NB  DEcode .amr file to .wav\n");

	if (argc < 1) {
		fprintf(stderr, "%s in.amr out.wav\n", argv[0]);
		return 1;
	}

//+++///////////////////////////////////////////////
	
//lhc mp4 open 2/4
	// open the mp4 file, and read meta-info
	  mp4File = MP4Read(argv[1]);	
 
	// get a handle on the first video track
	  audio_trackId = MP4FindTrackId(mp4File, 0, "audio", 0);
	//video_trackId = MP4FindTrackId(mp4File, 0, "video", 0);
  
	 // audio_profileLevel = MP4GetAudioProfileLevel(mp4File);
	 // video_profileLevel = MP4GetVideoProfileLevel(mp4File); 

	// gather the crucial track information 

	  //timeScale = MP4GetTrackTimeScale(mp4File, video_trackId);
	  timeScale = MP4GetTrackTimeScale(mp4File, audio_trackId);
	// note all times and durations 
	// are in units of the track time scale

	  trackDuration = MP4GetTrackDuration(mp4File, audio_trackId);
	  numSamples = MP4GetTrackNumberOfSamples(mp4File, audio_trackId);
	  maxSampleSize = MP4GetTrackMaxSampleSize(mp4File, audio_trackId);
	
	  pSample = (uint8_t*)malloc(maxSampleSize);


//ready output file 
//	wav = wav_write_open("decode-8k-1ch.wav", 8000, 16, 1);
	outWavfile = wav_write_open(argv[2], 8000, 16, 1);
	if (!outWavfile) {
		fprintf(stderr, "Unable to open %s\n", argv[2]);
		return 1;
	}

	 amrDecoder =Decoder_Interface_init();

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for (MP4SampleId sampleId = 1; sampleId <= numSamples; sampleId++)  {


// give ReadSample our own buffer, and let it know how big it is
		sampleSize = maxSampleSize;

        // read next sample from video track
		MP4ReadSample(mp4File, audio_trackId, sampleId, 
					&pSample, &sampleSize );


		/* Decode the packet */ 
		Decoder_Interface_Decode(amrDecoder, pSample, outWavBuf, 0);

		wav_write_data(outWavfile, (char*)outWavBuf, 320);


	}
 

	// close mp4 file
	MP4Close(mp4File);
	Decoder_Interface_exit(amrDecoder);
	wav_write_close(outWavfile);

	fprintf(stderr, "Finished Decode \n");

	//getchar();
	return 0;
}

