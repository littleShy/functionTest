#ifndef __FUNCTION_TEST_H__
#define __FUNCTION_TEST_H__
#include "inc.h"
class CFunctionTest
{
public:
    static IFunctionInterface* createFunctionInstance(CUtility::SFunctionParam &sParam);
};

#endif
