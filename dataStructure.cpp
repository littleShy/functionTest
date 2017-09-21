#include "dataStructure.h"
#include "linearList.h"
#include "chain.h"
#include "doubleLinkedChain.h"

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
    mSubFunctionStr["doubleChain"] = EDSTRUCT_SUB_TYPE_DOUBLE_CHAIN;
    m_pDataFuncs[EDSTRUCT_SUB_TYPE_DOUBLE_CHAIN] = &CDataStructure::testDoubleChain;
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
    CLinearList<int> cList, cList2, cList3;
    int iRet, iObj, iIndex;
    int bFound;
    std::cout << cList << std::endl;
    cList.Insert(0, 1).Insert(1, 2).Insert(2, 3).Insert(3, 4).Insert(4, 5).Insert(5, 6);
    std::cout << cList << std::endl;
    
    cList2.Alternate(cList3, cList);
    std::cout << "cList2 [NULL+cList]: " << std::endl << cList2 << std::endl;
    
    cList3.ReInit();

    cList2.Alternate(cList, cList3);
    std::cout << "cList2 [cList+NULL]: " << std::endl << cList2 << std::endl;

    cList3.Insert(0, 11).Insert(1,22).Insert(2,33);
    std::cout << "cList3: " << std::endl << cList3 << std::endl;

    cList2.Alternate(cList3, cList);
    std::cout << "cList2 [cList3+cList]: " << std::endl << cList2 << std::endl;

    CLinearList<int> cList1(cList);
    std::cout << "cList1: " << std::endl << cList1 << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    if(cList1.Front())
        std::cout << "Current Index: " << cList1.CurrentIndex() << std::endl;
    for(int i=0;i<cList1.Length();++i)
    {
        std::cout << cList1.Current() << " ";
        if(!cList1.End())
            cList1.Next();
    }
    std::cout << std::endl;
    if(cList1.End())
        std::cout << "Current Index: " << cList1.CurrentIndex() << std::endl;
    for(int i=0;i<cList1.Length();++i)
    {
        std::cout << cList1.Current() << " ";
        if(!cList1.Front())
            cList1.Previous();
    }
    std::cout << std::endl << "---------------------------------------------" << std::endl;
    cList.Reverse();
    std::cout << "After Reverse: " << std::endl << cList << std::endl;
    cList.Half();
    std::cout << "After Half: " << std::endl << cList << std::endl;
    iIndex = 3;
    cList.Find(iIndex,iRet);
    std::cout << "Find index:" << iIndex << ", result: " << iRet << std::endl;
    iObj = 2;
    iIndex = cList.Search(iObj);
    std::cout << "Search " << iObj << " in Linear List result:" << iIndex << std::endl;
    iObj = 5;
    iIndex = cList.Search(iObj);
    std::cout << "Search " << iObj << " in Linear List result:" << iIndex << std::endl;
    cList.Delete(3, iRet);
    std::cout << "Delete index 3 " << cList << std::endl;
    cList.Reverse();
    std::cout << "After Reverse: " << std::endl << cList << std::endl;
    cList.Half();
    std::cout << "After Half: " << std::endl << cList << std::endl;
    cList.Delete(1, iRet);
    std::cout << "Delete index 1 " << cList << std::endl;

    
    Chain<int> chain;
    chain.Insert(0, 1).Insert(1, 2).Insert(2, 3).Insert(3, 4);
    cout << "Chain " << chain << endl;

    CLinearList<int> *pList = CLinearList<int>::FromChain(chain);
    cout << "Call FromChain(): " << *pList << endl;

    CLinearList<int> *pList1 = CLinearList<int>::FromChain1(chain);
    cout << "Call FromChain1(): " << *pList1 << endl;

    CATCH_FUNCTION_EXCEPTION
    CATCH_UNKNOW_EXCEPTION
    CATCH_EXCEPTION_END
    LOG_FUNC_END
}

void CDataStructure::testChain()
{
    LOG_FUNC_BEGIN
    CATCH_EXCEPTION_BEGIN
    Chain<int> chain;
    chain.Insert(0, 1).Insert(1, 2).Insert(2, 3).Insert(3, 4);
    cout << chain;
    int iIndex, iValue;
    bool bFlag = false;
    iIndex = 3;
    chain.Find(iIndex, iValue);
    cout << "Find " << iIndex << " in chain, result " << iValue << endl;
    iIndex = 5;
    bFlag = chain.Find(iIndex, iValue);
    
    cout << "Find " << iIndex << " in chain, result " << iValue << endl;
    iValue = 3;
    iIndex = chain.Search(iValue);
    cout << "Search " << iValue << " in chain, result: " << iIndex << endl;
    iIndex = 1;
    chain.Delete(iIndex, iValue);
    cout << "Delete index " << iIndex << " from chain." << endl;
    cout << chain;
    iIndex = 2;
    chain.Delete(iIndex, iValue);
    cout << "Delete index " << iIndex << " from chain." << endl;
    cout << chain;
    //index out of bound, exception!
    // iIndex = 10;
    // chain.Delete(iIndex, iValue);
    // cout << "Delete index " << iIndex << " from chain." << endl;
    // cout << chain;
    ChainIterator<int> cIter;
    int *pData = cIter.Initialize(chain);
    while(pData)
    {
        cout << *pData << " ";
        pData = cIter.Next();
    }

    CLinearList<int> cList;
    cList.Insert(0, 1).Insert(1, 2).Insert(2, 3).Insert(3, 4).Insert(4, 5).Insert(5, 6);
    std::cout << cList << std::endl;

    Chain<int>* pChain = Chain<int>::FromList(cList);
    cout << "Call FromList() " << *pChain << endl;

    CATCH_FUNCTION_EXCEPTION
    CATCH_UNKNOW_EXCEPTION
    CATCH_EXCEPTION_END
    LOG_FUNC_END
}


void CDataStructure::testDoubleChain()
{
    LOG_FUNC_BEGIN
    
    int iIndex, iValue;
    bool bFlag;
    CDoubleChain<int> chain;
    CDoubleChain<int> chain1(chain);
    cout << "chain1 " << chain1 << endl;
    chain.Insert(0, 0);
    cout << chain << endl;

    iIndex = 1;
    chain.Delete(iIndex, iValue);
    cout << "After delete index: " << iIndex << endl;
    cout << chain << endl;

    chain.Insert(0, 0).Insert(1, 1).Insert(2, 2).Insert(3, 3).Insert(4, 4);
    cout << chain << endl;

    CDoubleChain<int> chain2(chain);
    cout << "chain2 " << chain2 << endl;

    iIndex = 1;
    bFlag = chain.Find(iIndex, iValue);
    cout << "Find index " << iIndex << " in chain, ";
    if(bFlag)
        cout << "Found Result: " << iValue << endl;
    else
        cout << "Not Found!" << endl;
    
    
    iIndex = 5;
    bFlag = chain.Find(iIndex, iValue);
    cout << "Find index " << iIndex << " in chain, ";
    if(bFlag)
        cout << "Found Result: " << iValue << endl;
    else
        cout << "Not Found!" << endl;
    
    iValue = 3;
    iIndex = chain.Search(iValue);
    cout << "Search " << iValue << " in chain, ";
    if(iIndex)
        cout << "Found!, index is: " << iIndex << endl;
    else
        cout << "Not Found!" << endl;

    iIndex = 1;
    chain.Delete(iIndex, iValue);
    cout << "After delete index: " << iIndex << endl;
    cout << chain << endl;

    iIndex = 3;
    chain.Delete(iIndex, iValue);
    cout << "After delete index: " << iIndex << endl;
    cout << chain << endl;

    iIndex = 3;
    chain.Delete(iIndex, iValue);
    cout << "After delete index: " << iIndex << endl;
    cout << chain << endl;

    CLinearList<int> cList;
    cList.Insert(0, 1).Insert(1, 2).Insert(2, 3).Insert(3, 4).Insert(4, 5).Insert(5, 6);
    std::cout << cList << std::endl;

    CDoubleChain<int>* pChain = CDoubleChain<int>::FromList(cList);
    cout << "Call FromList(): " << *pChain << endl;
    delete pChain;

    LOG_FUNC_END
}
