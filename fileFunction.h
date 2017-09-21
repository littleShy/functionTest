#ifndef __FILE_FUNCTION_H__
#define __FILE_FUNCTION_H__

#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include <stdio.h>
#include "functionInterface.h"
#include "utility.h"

class CFileFunction : public IFunctionInterface
{
	public:
        CFileFunction(CUtility::SFunctionParam &sParam);
        enum EFILE_SUB_FUNCTION
        {
            EFILE_SUB_TYPE_LINK = 1,
            EFILE_SUB_TYPE_STAT,
            EFILE_INVALID_SUB_TYPE
        };

        static void initSubFunction(IFunctionInterface::MapFunctionStr &mSubFunctionStr);
        void run();

        private:
        typedef void (CFileFunction::*PFunc)();
        void testStat();
        void testLink();

        static PFunc m_pFileFuncs[EFILE_INVALID_SUB_TYPE - 1];
        int m_iFileSubType;
};

#endif
