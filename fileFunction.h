#ifndef __FILE_FUNCTION_H__
#define __FILE_FUNCTION_H__

#include<sys/stat.h>
#include<unistd.h>
#include <stdio.h>
#include "functionInterface.h"
#include "utility.h"

class CFileFunction : public IFunctionInterface
{
	public:
        CFileFunction(CUtility::SFunctionParam &sParam) throw();
        enum EFILE_SUB_FUNCTION
        {
            EFILE_SUB_TYPE_LINK = 1,
            EFILE_SUB_TYPE_FSTAT,
            EFILE_INVALID_SUB_TYPE
        };

        static void initSubFunctionStr(IFunctionInterface::MapFunctionStr &mSubFunctionStr);
        void run();

	private:
        void testFstat();
        void testLink();

        typedef void (CFileFunction::*PFileFunc)();
        static PFileFunc m_pFuncs[EFILE_INVALID_SUB_TYPE - 1];
        int m_iFileSubType;
};

#endif
