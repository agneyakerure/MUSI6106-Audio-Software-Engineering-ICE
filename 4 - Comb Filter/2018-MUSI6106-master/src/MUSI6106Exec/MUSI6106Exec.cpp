
#include <iostream>
#include <ctime>
#include <fstream>
#include <cmath>
#include <string.h>

#include "MUSI6106Config.h"

#include "AudioFileIf.h"
#include "CombFilterIf.h"

using namespace std;

// local function declarations
void    showClInfo ();

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


void     showClInfo()
{
    cout << "GTCMT MUSI6106 Executable" << endl;
    cout << "(c) 2014-2018 by Alexander Lerch" << endl;
    cout  << endl;

    return;
}

