
#include <iostream>
#include <ctime>
#include <fstream>

#include "MUSI6106Config.h"

#include "AudioFileIf.h"

using std::cout;
using std::endl;

// local function declarations
void    showClInfo ();

/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    std::string             sInputFilePath,                 //!< file paths
                            sOutputFilePath;

    long long               iInFileLength       = 0;        //!< length of input file

    clock_t                 time                = 0;

    float                   **ppfAudioData      = 0;

    CAudioFileIf            *phAudioFile        = 0;
    
    long long               blockLength         = 1024;

    showClInfo ();

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments
    sInputFilePath = argv[1];
    sOutputFilePath = argv[2];

    //////////////////////////////////////////////////////////////////////////////
    // open the input wave file
    CAudioFileIf::create(phAudioFile);
    phAudioFile->openFile(sInputFilePath, CAudioFileIf::kFileRead);
    CAudioFileIf::FileSpec_t fileSpecs;
    phAudioFile->getFileSpec(fileSpecs);
    phAudioFile->getLength(iInFileLength);

    //////////////////////////////////////////////////////////////////////////////
    // allocate memory
    time                    = clock();
    
    ppfAudioData = new float*[fileSpecs.iNumChannels];
    for (int i = 0; i < fileSpecs.iNumChannels; i++)
    {
        ppfAudioData[i] = new float[blockLength];
    }

    // get audio data and write it to the output file
    std::ofstream outputFileData;
    outputFileData.open(sOutputFilePath);
    for(int i = 0; i < 2; i ++)
    {
        
    }
    

    cout << "reading/writing done in: \t"    << (clock()-time)*1.F/CLOCKS_PER_SEC << " seconds." << endl;
    //////////////////////////////////////////////////////////////////////////////
    // get audio info and print it to stdout
    cout << "File Length: " << iInFileLength << endl;
    cout << "Format: " << fileSpecs.eFormat << endl;
    cout << "Bit stream Type " << fileSpecs.eBitStreamType << endl;
    cout << "Sample Rate " << fileSpecs.fSampleRateInHz << endl;
    cout << "Number of Channels " << fileSpecs.iNumChannels << endl;

    //////////////////////////////////////////////////////////////////////////////
    // do processing
    cout << "Hello there!" << endl << endl;

    //////////////////////////////////////////////////////////////////////////////
    // clean-up
    phAudioFile->destroy(phAudioFile);
    outputFileData.close();
    delete [] ppfAudioData;
    return 0;
    
}


void     showClInfo()
{
    cout << "GTCMT MUSI6106 Executable" << endl;
    cout << "(c) 2014-2018 by Alexander Lerch" << endl;
    cout  << endl;

    return;
}

