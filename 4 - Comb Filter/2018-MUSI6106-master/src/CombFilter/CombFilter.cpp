
// standard headers
#include <limits>

// project headers
#include "MUSI6106Config.h"

#include "ErrorDef.h"
#include "Util.h"
#include "RingBuffer.h"

#include "CombFilterIf.h"
#include "CombFilter.h"


CCombFilterBase::CCombFilterBase( int iMaxDelayInFrames, int iNumChannels ) :
    m_ppCRingBuffer(0),
    m_iNumChannels(iNumChannels)
{

    assert(iMaxDelayInFrames > 0);
    assert(iNumChannels > 0);

}

CCombFilterBase::~CCombFilterBase()
{
    if(m_ppCRingBuffer)
    {
        for (int i = 0; i < m_iNumChannels; i++)
        {
            delete m_ppCRingBuffer[i];
        }
    }
    delete [] m_ppCRingBuffer;
}

Error_t CCombFilterBase::resetInstance()
{
    for(int i = 0; i < CCombFilterIf::kNumFilterParams; i++)
    {
        m_afParam[i] = 0;
        for(int j = 0; j < 2; j ++)
        {
            m_aafParamRange[i][j] = 0;
        }
    }
    
    for(int i = 0; i < m_iNumChannels; i++)
    {
        m_ppCRingBuffer[i]->reset();
    }
    
    return kNoError;
}

Error_t CCombFilterBase::setParam( CCombFilterIf::FilterParam_t eParam, float fParamValue )
{
    if (!isInParamRange(eParam, fParamValue))
        return kFunctionInvalidArgsError;

    switch (eParam)
    {
        case CCombFilterIf::kParamGain:
            m_afParam[0] = fParamValue;
            break;
            
        case CCombFilterIf::kParamDelay:
            m_afParam[1] = fParamValue;
            break;
            
        default:
            return kFunctionIllegalCallError;
    }
    return kNoError;
}

float CCombFilterBase::getParam( CCombFilterIf::FilterParam_t eParam ) const
{
    switch (eParam)
    {
        case CCombFilterIf::kParamGain:
            return m_afParam[0];
            
        case CCombFilterIf::kParamDelay:
            return m_afParam[1];
            
        default:
            return kFunctionIllegalCallError;
    }
    return 0;
}

bool CCombFilterBase::isInParamRange( CCombFilterIf::FilterParam_t eParam, float fValue )
{
    if (fValue < m_aafParamRange[eParam][0] || fValue > m_aafParamRange[eParam][1])
    {
        return false;
    }
    else
    {
        return true;
    }
}

Error_t CCombFilterFir::process( float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames )
{
    for(int i = 0; i < m_iNumChannels; i++)
    {
        for(int j = 0; j < iNumberOfFrames; j++)
        {
            m_ppCRingBuffer[i]->putPostInc(ppfInputBuffer[i][j]);
            ppfOutputBuffer[i][j] = ppfInputBuffer[i][j] + (m_afParam[0] * m_ppCRingBuffer[i]->getPostInc());
        }
    }
    return kNoError;
}


CCombFilterIir::CCombFilterIir (int iMaxDelayInFrames, int iNumChannels) : CCombFilterBase(iMaxDelayInFrames, iNumChannels)
{
    m_aafParamRange[0][0] = -1.0f;
    m_aafParamRange[0][1] = 1.0f;
}

Error_t CCombFilterIir::process( float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames )
{
    for(int i = 0; i < m_iNumChannels; i++)
    {
        for(int j = 0; j < iNumberOfFrames; j++)
        {
            ppfOutputBuffer[i][j] = ppfInputBuffer[i][j] + (m_afParam[0] * m_ppCRingBuffer[i]->getPostInc());
            m_ppCRingBuffer[i]->putPostInc(ppfOutputBuffer[i][j]);
        }
    }
    return kNoError;
}
