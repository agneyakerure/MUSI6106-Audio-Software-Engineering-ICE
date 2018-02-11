#if !defined(__CombFilter_hdr__)
#define __CombFilter_hdr__

#include "ErrorDef.h"

/*! \brief base class for the comb filter (FIR & IIR)
*/
class CCombFilterBase
{
public:
    CCombFilterBase (int iMaxDelayInFrames, int iNumChannels);
    virtual ~CCombFilterBase ();

    Error_t resetInstance ();

    Error_t setParam (CCombFilterIf::FilterParam_t eParam, float fParamValue);
    float   getParam (CCombFilterIf::FilterParam_t eParam) const;

    virtual Error_t process (float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames) = 0;

protected:
    CRingBuffer<float>  **m_ppCRingBuffer;  

    //m_afParam[0] = Gain
    //m_afParam[1] = Delay
    
    //m_aafParamRange[0][0] = Gain Min(m_afParam[0])
    //m_aafParamRange[0][1] = Gain Max(m_afParam[0])
    //m_aafParamRange[1][0] = Delay Min(m_afParam[1])
    //m_aafParamRange[1][1] = Delay Max(m_afParam[1])
    
    //All other -> Error
    
    float   m_afParam[CCombFilterIf::kNumFilterParams];
    float   m_aafParamRange[CCombFilterIf::kNumFilterParams][2];

    int     m_iNumChannels;

private:
    CCombFilterBase(const CCombFilterBase& that);

    bool    isInParamRange (CCombFilterIf::FilterParam_t eParam, float fValue);
};


/*! \brief FIR comb filter implementation
*/
class CCombFilterFir : public CCombFilterBase
{
public:
    CCombFilterFir (int iMaxDelayInFrames, int iNumChannels):CCombFilterBase(iMaxDelayInFrames, iNumChannels){};
    virtual ~CCombFilterFir (){};

    Error_t process (float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames) override;
};

/*! \brief IIR comb filter implementation
*/
class CCombFilterIir : public CCombFilterBase
{
public:
    CCombFilterIir (int iMaxDelayInFrames, int iNumChannels);
    virtual ~CCombFilterIir (){};

    Error_t process (float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames) override;
};

#endif // #if !defined(__CombFilter_hdr__)
