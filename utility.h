#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <iostream>
#include "functionInterface.h"

using namespace std;

class CUtility
{
    public:
        struct SFunctionParam
        {
            int iFunction;
            int iSubFunction;
        };
        static int parseInputArgs(int argc, char* argv[], SFunctionParam &sParam)
        {
            int ch = 0, iRet = 0;
            opterr = 0;
            while((ch = getopt(argc, argv, "t:s:")) != -1)
            {
                switch(ch)
                {
                    case 't':
                        if(IFunctionInterface::s_mFunctionStr.find(optarg) != IFunctionInterface::s_mFunctionStr.end())
                            sParam.iFunction = IFunctionInterface::s_mFunctionStr.at(optarg);
                        else
                            iRet = -1;
                        break;
                    case 's':
                        if(IFunctionInterface::s_mSubFunctionStr.find(optarg) != IFunctionInterface::s_mSubFunctionStr.end())
                            sParam.iSubFunction = IFunctionInterface::s_mSubFunctionStr.at(optarg);
                        else
                            iRet = -1;
                        break;
                    default:
                        iRet = -1;
                        cout << "Invalid option: " << ch << endl;
                        break;
                }
            }
            return iRet;
        }

};

#endif

