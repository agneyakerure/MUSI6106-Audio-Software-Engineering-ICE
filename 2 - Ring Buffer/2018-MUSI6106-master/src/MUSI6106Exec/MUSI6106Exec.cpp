
#include <iostream>
#include <ctime>

#include "MUSI6106Config.h"

#include "AudioFileIf.h"
#include "RingBuffer.h"

using std::cout;
using std::endl;

// local function declarations
void    showClInfo ();

int     test1(CRingBuffer<float> *pCRingBuffer, float *pfTestSignal, int bufferLength, int testSignalLength);
int     test2(CRingBuffer<float> *pCRingBuffer, float *pfTestSignal, int bufferLength, int testSignalLength);
int     test3(CRingBuffer<float> *pCRingBuffer, float *pfTestSignal, int bufferLength, int testSignalLength);
int     test4(CRingBuffer<float> *pCRingBuffer, float *pfTestSignal, int bufferLength, int testSignalLength);
int     test5(CRingBuffer<float> *pCRingBuffer, float *pfTestSignal, int bufferLength, int testSignalLength);

/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    // You don't need to use an audio file this time, though you can try if you want.
    // std::string             sInputFilePath,                 //!< file paths
    //                         sOutputFilePath;
    // static const int        kBlockSize          = 1024;
    // float                   **ppfAudioData      = 0;
    // CAudioFileIf            *phAudioFile        = 0;
    // CAudioFileIf::FileSpec_t stFileSpec;
    // long long               iInFileLength       = 0;        //!< length of input file

    clock_t                 time                = 0;

    CRingBuffer<float>      *pCRingBuffer       = 0;
    float                   *pfTestSignal       = 0;
    float                   fGain               = 1.f;
    int                     bufferLength        = atoi(argv[1]);
    int                     testSignalLength    = atoi(argv[2]);
    int                     failFlag            = 0;

    showClInfo ();

    //////////////////////////////////////////////////////////////////////////////
    // allocate memory
    time                    = clock();
    pCRingBuffer = new CRingBuffer<float>(bufferLength);
    pfTestSignal = new float[testSignalLength];

    // fill the test signal (e.g., a unit impulse)
    for (int i=0; i < testSignalLength; i++)
    {
        pfTestSignal[i] = i;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    // do processing and tests
    if(test1(pCRingBuffer, pfTestSignal, bufferLength, testSignalLength) != 0)
    {
        failFlag = 1;
    }
    else
    {
        failFlag = 0;
    }
    
    if(test2(pCRingBuffer, pfTestSignal, bufferLength, testSignalLength) != 0)
    {
        failFlag = 1;
    }
    else
    {
        failFlag = 0;
    }
    
    if(test3(pCRingBuffer, pfTestSignal, bufferLength, testSignalLength) != 0)
    {
        failFlag = 1;
    }
    else
    {
        failFlag = 0;
    }
    
    if(test4(pCRingBuffer, pfTestSignal, bufferLength, testSignalLength) != 0)
    {
        failFlag = 1;
    }
    else
    {
        failFlag = 0;
    }
    
    if(test5(pCRingBuffer, pfTestSignal, bufferLength, testSignalLength) != 0)
    {
        failFlag = 1;
    }
    else
    {
        failFlag = 0;
    }
    

    if(failFlag == 0)
    {
        cout << "All functions successfully implemented!" << "\n" <<endl;
    }
    else
    {
        cout << "Unsuccessful" << "\n" <<endl;
    }
    cout << "processing done in: \t"    << (clock()-time)*1.F/CLOCKS_PER_SEC << " seconds." << endl;

    //////////////////////////////////////////////////////////////////////////////
    // clean-up
    delete pCRingBuffer;
    delete [] pfTestSignal;
    
    return 0;
}

int test1(CRingBuffer<float> *pCRingBuffer, float *pfTestSignal, int bufferLength, int testSignalLength)
{
    float writeVal = 66.66;
    pCRingBuffer->put(writeVal);
    float readVal = pCRingBuffer->get();
    //cout<<"\n"<<readVal<<"\n";
    if(readVal == writeVal)
    {
        cout << "Test 1: Success" << endl;
        return 0;
    }
    else
    {
        cout << "Test 1: Failure" << endl;
        return -1;
    }
}

int test2(CRingBuffer<float> *pCRingBuffer, float *pfTestSignal, int bufferLength, int testSignalLength)
{
    int indexArray[5] = {512, -10, 1000, -444, 2.5};
    int resultArray[5] = {0, 502, 488, 68, 2};
    for(int i = 0; i < 5; i++)
    {
        pCRingBuffer->setWriteIdx(indexArray[i]);
        int index = pCRingBuffer->getWriteIdx();
        if(index != resultArray[i])
        {
            cout << "Test 2: Failure" << endl;
            return -1;
        }
    }
    cout << "Test 2: Success" << endl;
    return 0;
}

int test3(CRingBuffer<float> *pCRingBuffer, float *pfTestSignal, int bufferLength, int testSignalLength)
{
    int indexArray[5] = {512, -10, 1000, -444, 2.5};
    int resultArray[5] = {0, 502, 488, 68, 2};
    for(int i = 0; i < 5; i++)
    {
        pCRingBuffer->setReadIdx(indexArray[i]);
        int index = pCRingBuffer->getReadIdx();
        if(index != resultArray[i])
        {
            cout << "Test 3: Failure" << endl;
            return -1;
        }
    }
    cout << "Test 3: Success" << endl;
    return 0;
}

int test4(CRingBuffer<float> *pCRingBuffer, float *pfTestSignal, int bufferLength, int testSignalLength)
{
    for(int i = 0; i < testSignalLength; i++)
    {
        pCRingBuffer->putPostInc(pfTestSignal[i]);
        int input = pCRingBuffer->getPostInc();
        if(input != pfTestSignal[i])
        {
            cout << "Test 4: Failure" << endl;
            return -1;
        }
    }
    cout << "Test 4: Success" << endl;
    return 0;
}

int test5(CRingBuffer<float> *pCRingBuffer, float *pfTestSignal, int bufferLength, int testSignalLength)
{
    int indexArray[5] = {512, -10, 1000, -444, 2.5};
    int resultArray[5] = {0, 502, 488, 68, 2};

    for(int i = 0;i < bufferLength; i++)
    {
        pCRingBuffer->putPostInc(pfTestSignal[i]);
    }
    for(int i = 0; i < 5; i++)
    {
        float val = pCRingBuffer->get(indexArray[i]);
        if(val != pfTestSignal[resultArray[i]])
        {
            cout << "Test 5: Failure" << endl;
            return -1;
        }
    }
    cout << "Test 5: Success" << endl;
    return 0;
}


void     showClInfo()
{
    cout << "GTCMT MUSI6106 Executable" << endl;
    cout << "(c) 2014-2018 by Alexander Lerch" << endl;
    cout  << endl;

    return;
}

