#include <stdio.h>
#include "functionInterface.h"
#include "pthreadFunction.h"
#include "fileFunction.h"

IFunctionInterface::MapFunctionStr IFunctionInterface::s_mapFunctionStr;
IFunctionInterface::MapSubFunctionStr IFunctionInterface::s_mapSubFunctionStr;

IFunctionInterface::IFunctionInterface(CUtility::SFunctionParam &sParam)
{
    m_iFunctionType = sParam.iFunction;
    m_iSubFunctionType = sParam.iSubFunction;
}

void IFunctionInterface::initFunctionStr()
{
    cout << "Init function type begin." << endl;
    // pthread function
    s_mapFunctionStr["pthread"] = EPTHREAD_FUNCTION_TYPE;
    // pthread sub function
    CPthreadFunction::initSubFunctionStr(s_mapSubFunctionStr[EPTHREAD_FUNCTION_TYPE]);

    // file function
    s_mapFunctionStr["file"] = EFILE_FUNCTION_TYPE;
    // file sub function
    CFileFunction::initSubFunctionStr(s_mapSubFunctionStr[EFILE_FUNCTION_TYPE]);
    
    cout << "Init function type end." << endl;
}

void IFunctionInterface::usage() 
{
    cout << "functionTest -t <value> -s <value>" << endl;
    cout << "\t-t optional value:" << endl;
    for (IterFunctionStr iter = s_mapFunctionStr.begin(); iter != s_mapFunctionStr.end(); iter++)
    {
        cout << "\t" << iter->first << endl;
        if(s_mapSubFunctionStr.find(iter->second) == s_mapSubFunctionStr.end())
        {
            THROW_FUNCTION_EXCEPTION(EERROR_NO_VALID_SUB_FUNCTION);
        }
        MapFunctionStr mapSubFunctionStr = s_mapSubFunctionStr.at(iter->second);
        
        cout << "\t\t-s optional value for '" << iter->first << "':" << endl;
        for(IterFunctionStr subIter=mapSubFunctionStr.begin();subIter!=mapSubFunctionStr.end();++subIter)
        {
            cout << "\t\t" << subIter->first << endl;
        }
    }
}
