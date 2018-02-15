
#include <iostream>
#include <ctime>
#include <fstream>
#include <cmath>
#include <string.h>

#include "MUSI6106Config.h"

#include "AudioFileIf.h"
#include "CombFilterIf.h"
#include "Synthesis.h"

#define PI 3.14159265359
using namespace std;

// local function declarations
void    showClInfo ();
void    test1();                    //Test to see if delay size is longer than the input signal length, the output should be the same i.e. unaffected
void    test2();                    //Test to filter a sinewave with a filter of delay of 1 period and gain of -1 and see if output is zero. Tolerance = 0.0005
void    test3();                    //Test to check if IIR filter gives error on setting gain > 1.
/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    std::string                     sInputFilePath,                 //!< file paths
                                    sOutputFilePath;

    static const int                kBlockSize = 1024;
    float                           maxDelayTime = 1.0f;

    clock_t                         time = 0;

    float                           **ppfAudioData = 0;
    float                           **ppfOutputData = 0;

    CAudioFileIf                    *phAudioFile = 0,
                                    *phOutputFile = 0;
    
    //std::fstream                    hOutputFile;
    CAudioFileIf::FileSpec_t        stFileSpec;

    CCombFilterIf                   *pInstance = 0;
    
    
    std::string                     type;
    float                           delayTime;
    float                           gain;
    
    
    CCombFilterIf::create(pInstance);
    showClInfo();

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments
    //ORDER: Input File Path, Filter Type, Filter Delay, Filter Gain. Output Text File Path is same as input audio file path.
    if (argc == 1)
    {
        cout << "Running tests" << endl;
        test1();
        test2();
        test3();
        return 0;
    }
    else if (argc != 6)
    {
        cout << "Missing arguments!" << endl;
        return -1;
    }
    sInputFilePath = argv[1];
    sOutputFilePath = argv[2];
    type = argv[3];
    delayTime = stof(argv[4]);
    gain = stof(argv[5]);

    //////////////////////////////////////////////////////////////////////////////
    // open the input wave file
    CAudioFileIf::create(phAudioFile);
    CAudioFileIf::create(phOutputFile);
    
    phAudioFile->openFile(sInputFilePath, CAudioFileIf::kFileRead);
    
    if (!phAudioFile->isOpen())
    {
        cout << "Wave file open error!";
        return -1;
    }
    
    phAudioFile->getFileSpec(stFileSpec);
    phOutputFile->openFile(sOutputFilePath, CAudioFileIf::kFileWrite, &stFileSpec);

    //////////////////////////////////////////////////////////////////////////////
    // open the output text file
//    hOutputFile.open(sOutputFilePath.c_str(), std::ios::out);
//    if (!hOutputFile.is_open())
//    {
//        cout << "Text file open error!";
//        return -1;
//    }
    //(iFilterType ? CCombFilterIf::CombFilterType_t::kCombIIR : CCombFilterIf::CombFilterType_t::kCombFIR)
    //pInstance->init(CCombFilterIf::CombFilterType_t::kCombFIR, delayTime, stFileSpec.fSampleRateInHz, stFileSpec.iNumChannels);
    //////////////////////////////////////////////////////////////////////////////
    // allocate memory
    ppfAudioData = new float*[stFileSpec.iNumChannels];
    ppfOutputData = new float*[stFileSpec.iNumChannels];
    for (int i = 0; i < stFileSpec.iNumChannels; i++)
    {
        ppfAudioData[i] = new float[kBlockSize];
        ppfOutputData[i] = new float[kBlockSize];
    }
    
    if (type.compare("FIR") == 0){
        pInstance->init(CCombFilterIf::kCombFIR, maxDelayTime, stFileSpec.fSampleRateInHz, stFileSpec.iNumChannels);
        
    } else if (type.compare("IIR") == 0) {
        pInstance->init(CCombFilterIf::kCombIIR, maxDelayTime, stFileSpec.fSampleRateInHz, stFileSpec.iNumChannels);
    }

    time = clock();
    test1();
    test2();
    test3();
    //////////////////////////////////////////////////////////////////////////////
    // get audio data and write it to the output file
    pInstance->setParam(CCombFilterIf::kParamGain, gain);
    pInstance->setParam(CCombFilterIf::kParamDelay, delayTime);
    
    while (!phAudioFile->isEof())
    {
        long long iNumFrames = kBlockSize;
        phAudioFile-> readData(ppfAudioData, iNumFrames);
        pInstance -> process(ppfAudioData, ppfOutputData, iNumFrames);
        phOutputFile-> writeData(ppfOutputData, iNumFrames);
        
    }

    cout << "\nreading/writing done in: \t" << (clock() - time)*1.F / CLOCKS_PER_SEC << " seconds." << endl;

    //////////////////////////////////////////////////////////////////////////////
    // clean-up
    CAudioFileIf::destroy(phAudioFile);
    CAudioFileIf::destroy(phOutputFile);
    CCombFilterIf::destroy(pInstance);

    for (int i = 0; i < stFileSpec.iNumChannels; i++)
    {
        delete[] ppfAudioData[i];
        delete[] ppfOutputData[i];
    }
    delete[] ppfAudioData;
    delete[] ppfOutputData;
    ppfAudioData = 0;
    ppfOutputData = 0;
    return 0;
}

void genSineWave(float *wave, float amplitude,float frequency, float timeInSecs, float fs)
{
    for (int i = 0; i < timeInSecs*fs; i++)
    {
        wave[i] = amplitude*sin(2 * PI*i*frequency/fs);
    }
    return;
}

void test1()
{
//    static Error_t generateSine (float *pfOutBuf, float fFreqInHz, float fSampleFreqInHz, int iLength, float fAmplitude = 1.F, float fStartPhaseInRad = 0.F)

    float **sineWave, **outputFIR, **outputIIR;
    sineWave = new float*[1];
    sineWave[0] = new float[44100];
    CSynthesis::generateSine(sineWave[0], 300, 44100, 44100);
    
    outputFIR = new float*[1];
    outputFIR[0] = new float[44100];
    
    outputIIR = new float*[1];
    outputIIR[0] = new float[44100];
    
    bool failFlag = false;
    
    CCombFilterIf *pInstance = 0;
    
    CCombFilterIf::create(pInstance);
    pInstance->init(CCombFilterIf::kCombFIR, 2, 44100, 1);
    pInstance->setParam(CCombFilterIf::kParamDelay, 2);
    pInstance->process(sineWave, outputFIR, 44100);
    
    CCombFilterIf::destroy(pInstance);
    
    CCombFilterIf::create(pInstance);
    pInstance->init(CCombFilterIf::kCombIIR, 2, 44100, 1);
    pInstance->setParam(CCombFilterIf::kParamDelay, 2);
    pInstance->process(sineWave, outputIIR, 44100);
    
    
    for(int i = 0; i < 44100; i++)
    {
        if((sineWave[0][i] != outputFIR[0][i]) || (sineWave[0][i] != outputIIR[0][i]))
        {
            failFlag = true;
        }
        else
        {
            failFlag = false;
        }
    }
    
    if(failFlag)
    {
        cout<<"Test 1 Fail"<<endl;
    }
    else
    {
        cout<<"Test 1 Pass!"<<endl;
    }
    
    delete[] sineWave[0];
    delete[] outputFIR[0];
    delete[] outputIIR[0];
    delete[] sineWave;
    delete[] outputFIR;
    delete[] outputIIR;
    
    CCombFilterIf::destroy(pInstance);
    return;
}

void test2()
{
    float **sineWave, **outputFIR;
    sineWave = new float*[1];
    sineWave[0] = new float[44100];
    CSynthesis::generateSine(sineWave[0], 300, 44100, 44100);
    
    outputFIR = new float*[1];
    outputFIR[0] = new float[44100];
    
    bool failFlag = false;
    
    CCombFilterIf *pInstance = 0;
    
    CCombFilterIf::create(pInstance);
    pInstance->init(CCombFilterIf::kCombFIR, 2, 44100, 1);
    pInstance->setParam(CCombFilterIf::kParamDelay, 1/300);
    pInstance->setParam(CCombFilterIf::kParamGain, -1);
    pInstance->process(sineWave, outputFIR, 44100);
    
    for(int i = 0; i < 44100; i++)
    {
        if(outputFIR[0][i] > 0.00005)
        {
            failFlag = true;
        }
        else
        {
            failFlag = false;
        }
    }
    
    if(failFlag)
    {
        cout<<"Test 2 Fail"<<endl;
    }
    else
    {
        cout<<"Test 2 Pass!"<<endl;
    }
    
    delete[] sineWave[0];
    delete[] outputFIR[0];
    delete[] sineWave;
    delete[] outputFIR;
    
    CCombFilterIf::destroy(pInstance);
    return;
}

void test3()
{
    bool failFlag = false;
    CCombFilterIf *pInstance = 0;
    
    CCombFilterIf::create(pInstance);
    pInstance->init(CCombFilterIf::kCombIIR, 2, 44100, 1);
    if(pInstance->setParam(CCombFilterIf::kParamGain, 20) == kNoError)      //Check when gain exceeds limits
    {
        failFlag = true;
    }
    else
    {
        failFlag = false;
    }
    
    if(pInstance->setParam(CCombFilterIf::kParamGain, 0.7) == kNoError)     //Check when gain doesnt exceed limits
    {
        failFlag = false;
    }
    else
    {
        failFlag = true;
    }
    
    if(failFlag == true)
    {
        cout<<"Test3 Fail"<<endl;
    }
    else
    {
        cout<<"Test 3 Pass!"<<endl;
    }
    
    CCombFilterIf::destroy(pInstance);
    return;
}


void     showClInfo()
{
    cout << "GTCMT MUSI6106 Executable" << endl;
    cout << "(c) 2014-2018 by Alexander Lerch" << endl;
    cout  << endl;

    return;
}

