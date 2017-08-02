#include "fileFunction.h"

CFileFunction::PFileFunc CFileFunction::m_pFuncs[EFILE_INVALID_SUB_TYPE - 1] = {NULL};

CFileFunction::CFileFunction(CUtility::SFunctionParam &sParam) throw() : IFunctionInterface(sParam)
{
    if(sParam.iSubFunction >= EFILE_INVALID_SUB_TYPE)
    {
        THROW_FUNCTION_EXCEPTION(EERROR_INVALID_SUB_FUNCTION_TYPE);
    }
    m_iFileSubType = sParam.iSubFunction;
}

void CFileFunction::initSubFunctionStr(IFunctionInterface::MapFunctionStr &mSubFunctionStr)
{
    cout << "Init CFileFunction sub function begin." << endl;

    mSubFunctionStr["link"] = EFILE_SUB_TYPE_LINK;
    m_pFuncs[EFILE_SUB_TYPE_LINK] = &CFileFunction::testLink;
    mSubFunctionStr["fstat"] = EFILE_SUB_TYPE_FSTAT;
    m_pFuncs[EFILE_SUB_TYPE_FSTAT] = &CFileFunction::testFstat;

    cout << "Init CFileFunction sub function end." << endl;
}

void CFileFunction::run()
{
    cout << "CFileFunction run." << endl;

    if(NULL == m_pFuncs[m_iFileSubType])
    {
        THROW_FUNCTION_EXCEPTION(EERROR_INVALID_SUB_FUNCTION_TYPE);
    }
    (this->*m_pFuncs[m_iFileSubType])();

    cout << "CFileFunction run end." << endl;
}

void CFileFunction::testFstat()
{
    cout << "CFileFunction test fstat begin." << endl;

    cout << "CFileFunction test fstat end." << endl;
}

void CFileFunction::testLink()
{
    cout << "CFileFunction test link begin." << endl;

    cout << "CFileFunction test link end." << endl;
}
