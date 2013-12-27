
@echo off

echo .
echo ========================================
echo LHC WAVE TO AMR PACK MP4 TEST===========
echo ========================================




echo .
echo amrNB-Enc=========================== 

 
amrNB-Enc-3gp.exe -r 12200  test-8k-1ch.wav  Enc-amrnb-8k.mp4

echo Encode success======================= 



echo .
echo amrNB-Dec============================ 

 
amrNB-Dec-3gp.exe   Enc-amrnb-8k.mp4  Dec-amrnb-8k.wav

echo Decode success======================= 

echo .

pause
