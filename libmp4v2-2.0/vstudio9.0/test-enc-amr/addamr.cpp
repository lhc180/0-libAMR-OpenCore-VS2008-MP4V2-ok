#include "mp4v2.h"
#include <cstdlib>
#include <string>

/*

    MP4FileHandle MP4CreateEx (const char* fileName,
                               uint32_t  flags,
                               int add_ftyp,
                               int add_iods,
                               char* majorBrand,
                               uint32_t minorVersion,
                               char** supportedBrands,
                               uint32_t supportedBrandsCount)
*/
int main(int argc, char** argv)
{

	MP4FileHandle mp4file;

	MP4TrackId   audioAmrNb;
	MP4TrackId   audioAmrWb;
	MP4TrackId   audioAac;

/*Create */ 
	mp4file =MP4Create("test-Enc-amr.mp4", 0);
    //mp4file = MP4CreateEx("test.mp4", 9, 0, 1, 1, 0, 0, 0 ); 

	MP4SetTimeScale(mp4file, 90000); 
 
/*Set video*/ 
//video = MP4AddH263VideoTrack(mp4, 90000, 0, 176, 144, 0, 0, 0, 0); 
 
/*   
//Set audio aac 
       audioAac = MP4AddAudioTrack(mp4file, 48000, 1024, MP4_MPEG4_AUDIO_TYPE);
      if (audioAac == MP4_INVALID_TRACK_ID)
      {
          printf("add audio track failed.\n");
          return 1;
      }
      MP4SetAudioProfileLevel(mp4file, 0x2);
 */

//Set audio AMR
	  /*
	  
    MP4TrackId MP4AddAmrAudioTrack(
        MP4FileHandle hFile,
        uint32_t timeScale,
        uint16_t modeSet,
        uint8_t modeChangePeriod,
        uint8_t framesPerSample,
        bool isAmrWB)
		*/
   audioAmrNb = MP4AddAmrAudioTrack(mp4file, 8000, 0, 0, 1, 0); 
     // audioAmrWb = MP4AddAmrAudioTrack(mp4file, 8000, 0, 0, 1, true);
 
/*Write file// 
do 
{ 
		 
		if(...) 
		{ 
		//enc audio data to amr/
		... 
		MP4WriteSample(mp4,audio,len,buf,160,1); 
		 
		} 
		else 
		{ 
		//enc vidoe data to h263/
		... 
		MP4WriteSample(mp4,video , len buf, 90000/fps, 1); 
		} 
		 
}while(1) 
 */


MP4Close(mp4file, 0); 
 
 printf( "Create file %s finished\n", "test-Enc-amr.mp4" );
 //printf( "test create file %s finished\n", argv[1] );

//exit(0);
 
 
}

