#include "dataStructure.h"
#include "linearList.h"
// #include "chain.h"

CDataStructure::PFunc CDataStructure::m_pDataFuncs[EDSTRUCT_INVALID_SUB_TYPE - 1] = {NULL};

CDataStructure::CDataStructure(CUtility::SFunctionParam &sParam) : IFunctionInterface(sParam)
{
    if(sParam.iSubFunction >= EDSTRUCT_INVALID_SUB_TYPE)
    {
        THROW_FUNCTION_EXCEPTION(EERROR_INVALID_SUB_FUNCTION_TYPE);
    }
    m_iDataStructureSubType = sParam.iSubFunction;
}

void CDataStructure::initSubFunction(IFunctionInterface::MapFunctionStr &mSubFunctionStr)
{
    LOG_FUNC_BEGIN
    mSubFunctionStr["linearList"] = EDSTRUCT_SUB_TYPE_LINEAR_LIST;
    m_pDataFuncs[EDSTRUCT_SUB_TYPE_LINEAR_LIST] = &CDataStructure::testLinearList;
    mSubFunctionStr["chain"] = EDSTRUCT_SUB_TYPE_CHAIN;
    m_pDataFuncs[EDSTRUCT_SUB_TYPE_CHAIN] = &CDataStructure::testChain;
    LOG_FUNC_END
}

void CDataStructure::run()
{
    LOG_FUNC_BEGIN
    if(NULL == m_pDataFuncs[m_iDataStructureSubType])
        THROW_FUNCTION_EXCEPTION(EERROR_INVALID_SUB_FUNCTION_TYPE);
    CATCH_EXCEPTION_BEGIN
    (this->*m_pDataFuncs[m_iDataStructureSubType])();
    CATCH_FUNCTION_EXCEPTION
    CATCH_UNKNOW_EXCEPTION
    CATCH_EXCEPTION_END
    LOG_FUNC_END
}

void CDataStructure::testLinearList()
{
    LOG_FUNC_BEGIN
    CATCH_EXCEPTION_BEGIN
    CLinearList<int> cList(3);
    int iRet, iObj, iIndex;
    int bFound;
    std::cout << "Linear List:" << std::endl << cList << ", Length: " << cList.Length() << ", Size: " << cList.MaxSize() << std::endl;
    cList.Insert(1, 1);//.Insert(1, 2).Insert(2, 3).Insert(3, 4);
    std::cout << "Linear List:" << std::endl << cList << ", Length: " << cList.Length() << ", Size: " << cList.MaxSize() << std::endl;
    iIndex = 3;
    cList.Find(iIndex,iRet);
    std::cout << "Find index:" << iIndex << ", result: " << iRet << std::endl;
    iObj = 4;
    iIndex = cList.Search(iObj);
    std::cout << "Search " << iObj << " in Linear List result:" << iIndex << std::endl;
    iObj = 5;
    iIndex = cList.Search(iObj);
    std::cout << "Search " << iObj << " in Linear List result:" << iIndex << std::endl;
    cList.Delete(1, iRet);
    std::cout << "Linear List:" << std::endl << cList << ", Length: " << cList.Length() << ", Size: " << cList.MaxSize() << std::endl;
    cList.Delete(3, iRet);
    std::cout << "Linear List:" << std::endl << cList << ", Length: " << cList.Length() << ", Size: " << cList.MaxSize() << std::endl;
    cList.Delete(3, iRet);
    std::cout << "Linear List:" << std::endl << cList << ", Length: " << cList.Length() << ", Size: " << cList.MaxSize() << std::endl;    
    CATCH_FUNCTION_EXCEPTION
    CATCH_UNKNOW_EXCEPTION
    CATCH_EXCEPTION_END
    LOG_FUNC_END
}

void CDataStructure::testChain()
{
    LOG_FUNC_BEGIN

    LOG_FUNC_END
}
