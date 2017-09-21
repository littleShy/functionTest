#ifndef __DATA_STRUCTURE_H__
#define __DATA_STRUCTURE_H__

#include <unistd.h>
#include <stdio.h>
#include "functionInterface.h"
#include "utility.h"

class CDataStructure: public IFunctionInterface
{
public:
    enum EDSTRUCT_SUB_FUNCTION
    {
        EDSTRUCT_SUB_TYPE_LINEAR_LIST = 1,
        EDSTRUCT_SUB_TYPE_CHAIN,
        EDSTRUCT_SUB_TYPE_DOUBLE_CHAIN,
        EDSTRUCT_INVALID_SUB_TYPE
    };

    CDataStructure(CUtility::SFunctionParam &sParam);
    static void initSubFunction(IFunctionInterface::MapFunctionStr &mSubFunctionStr);
    void run();
private:
    typedef void (CDataStructure::*PFunc)();
    void testLinearList();
    void testChain();
    void testDoubleChain();

    static PFunc m_pDataFuncs[EDSTRUCT_INVALID_SUB_TYPE - 1];
    int    m_iDataStructureSubType;
};

#endif
