
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

    clock_t                         time = 0;

    float                           **ppfAudioData = 0;
    float                           **ppfOutData = 0;

    CAudioFileIf                    *phAudioFile = 0;
    
    std::fstream                    hOutputFile;
    CAudioFileIf::FileSpec_t        stFileSpec;

    CCombFilterIf                   *pInstance = 0;
    
    std::string                     type;
    float                           delayTimeInSeconds = 0.0f;
    float                           maxDelayTimeInSeconds = 1.0f;
    float                           gain = 0.7f;
    
    CCombFilterIf::create(pInstance);
    showClInfo();

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments

    try
    {
        switch (argc)
        {
            case 1:
                cout << "Please enter arguments." << endl;
                exit(0);
                break;
            case 2:
                sInputFilePath = argv[1];
                sOutputFilePath = sInputFilePath + ".txt";
                delayTimeInSeconds = maxDelayTimeInSeconds;
                gain = 1.0f;
                break;
            case 3:
                sInputFilePath = argv[1];
                sOutputFilePath = sInputFilePath + ".txt";
                delayTimeInSeconds = maxDelayTimeInSeconds;
                type = string(argv[2]);
                gain = 1.0f;
                break;
            case 4:
                sInputFilePath = argv[1];
                sOutputFilePath = sInputFilePath + ".txt";
                type = string(argv[2]);
                delayTimeInSeconds = stof(argv[3]);
                gain = 1.0f;
                break;
            case 5:
                sInputFilePath = argv[1];
                sOutputFilePath = sInputFilePath + ".txt";
                type = string(argv[2]);
                delayTimeInSeconds = stof(argv[3]);
                gain = stof(argv[4]);
                break;
            default: cout << "Too many arguments." << endl;
                exit(0);
        }
    }
    catch (exception &exc)
    {
        cerr << "Invalid arguments passed." << endl;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    // open the input wave file
    CAudioFileIf::create(phAudioFile);

    phAudioFile->openFile(sInputFilePath, CAudioFileIf::kFileRead);
    if (!phAudioFile->isOpen())
    {
        cout << "Wave file open error!";
        return -1;
    }
    
    phAudioFile->getFileSpec(stFileSpec);

    //////////////////////////////////////////////////////////////////////////////
    // open the output text file
    hOutputFile.open(sOutputFilePath.c_str(), std::ios::out);
    if (!hOutputFile.is_open())
    {
        cout << "Text file open error!";
        return -1;
    }
    
    pInstance->init(CCombFilterIf::CombFilterType_t::kCombFIR, 0.5, stFileSpec.fSampleRateInHz, stFileSpec.iNumChannels);
    //////////////////////////////////////////////////////////////////////////////
    // allocate memory
    ppfAudioData = new float*[stFileSpec.iNumChannels];
    ppfOutData = new float*[stFileSpec.iNumChannels];
    for (int i = 0; i < stFileSpec.iNumChannels; i++)
    {
        ppfAudioData[i] = new float[kBlockSize];
        ppfOutData[i] = new float[kBlockSize];
    }

    time = clock();
    //////////////////////////////////////////////////////////////////////////////
    // get audio data and write it to the output file
    pInstance->init(CCombFilterIf::kCombFIR, 10.0f, 1.0f, 2);
    pInstance->setParam(CCombFilterIf::kParamGain, 0.5);
    
    while (!phAudioFile->isEof())
    {
        long long iNumFrames = kBlockSize;
        phAudioFile->readData(ppfAudioData, iNumFrames);

        cout << "\r" << "reading and writing";
        pInstance -> process (ppfAudioData, ppfOutData, iNumFrames);
        for (int i = 0; i < iNumFrames; i++)
        {
            for (int c = 0; c < stFileSpec.iNumChannels; c++)
            {
                hOutputFile << ppfAudioData[c][i] << "\t";
            }
            hOutputFile << endl;
        }
    }

    cout << "\nreading/writing done in: \t" << (clock() - time)*1.F / CLOCKS_PER_SEC << " seconds." << endl;

    //////////////////////////////////////////////////////////////////////////////
    // clean-up
    CAudioFileIf::destroy(phAudioFile);
    hOutputFile.close();

    for (int i = 0; i < stFileSpec.iNumChannels; i++)
    {
        delete[] ppfAudioData[i];
    }
    delete[] ppfAudioData;
    ppfAudioData = 0;

    return 0;

}


void     showClInfo()
{
    cout << "GTCMT MUSI6106 Executable" << endl;
    cout << "(c) 2014-2018 by Alexander Lerch" << endl;
    cout  << endl;

    return;
}

