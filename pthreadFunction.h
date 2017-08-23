#ifndef __PTHREAD_FUNCTION_H__
#define __PTHREAD_FUNCTION_H__

#include "functionInterface.h"
#include "utility.h"

class CPthreadFunction:public IFunctionInterface
{
public:
    enum EPTHREAD_SUB_FUNCTION
    {
        EPTHREAD_SUB_TYPE_SAMPLE = 1,
        EPTHREAD_INVALID_SUB_FUNCTION
    };
    CPthreadFunction(CUtility::SFunctionParam &sParam);
    
	static void initSubFunction(IFunctionInterface::MapFunctionStr &mSubFunctionStr);

    void run();
};

#endif

