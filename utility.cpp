#include "utility.h"
#include "functionInterface.h"

using namespace std;
class IFunctionInterface;

int CUtility::parseInputArgs(int argc, char* argv[], SFunctionParam &sParam)
{
    LOG_FUNC_BEGIN

    int ch = 0, iRet = -1;
    char szSubFunction[16];

    memset(szSubFunction, 0, sizeof(szSubFunction));
    memset(&sParam, 0, sizeof(SFunctionParam));
    opterr = 0;

    while((ch = getopt(argc, argv, "t:s:")) != -1)
    {
        switch(ch)
        {
            case 't':
                if(IFunctionInterface::s_mapFunctionStr.find(optarg) != IFunctionInterface::s_mapFunctionStr.end())
                    sParam.iFunction = IFunctionInterface::s_mapFunctionStr.at(optarg);
                else
                    return -1;
                break;
            case 's':
                strncpy(szSubFunction, optarg, sizeof(szSubFunction));
                break;
            default:
                return -1;
                break;
        }

    }
    if(sParam.iFunction == 0 || strlen(szSubFunction) == 0)
    {
        return iRet;
    }

    if(IFunctionInterface::s_mapSubFunctionStr.find(sParam.iFunction) != IFunctionInterface::s_mapSubFunctionStr.end())
    {
        IFunctionInterface::MapFunctionStr mapSubFunctionStr = IFunctionInterface::s_mapSubFunctionStr.at(sParam.iFunction);
        if(mapSubFunctionStr.find(szSubFunction) != mapSubFunctionStr.end())
        {
            sParam.iSubFunction = mapSubFunctionStr.at(szSubFunction);
            iRet = 0;
        }
        else
            iRet = -1;
    }
    else
        iRet = -1;

    LOG_FUNC_END
    return iRet;
}

void CUtility::printPassedTime(const struct timeval &tTvStart, const struct timeval &tTvEnd)
{
    time_t tPassedSec = tTvEnd.tv_sec - tTvStart.tv_sec;
    suseconds_t tPassedUsec = tTvEnd.tv_usec - tTvStart.tv_usec;
    if(tPassedUsec < 0)
    {
        tPassedSec -= 1;
        tPassedUsec += 1000000;
    }
    std::cout << "Time passed: " << tPassedSec << " s, " << tPassedUsec << " us." << std::endl;
}
