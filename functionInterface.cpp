#include <stdio.h>
#include "functionInterface.h"
#include "pthreadFunction.h"
#include "fileFunction.h"
#include "sortFunction.h"

IFunctionInterface::MapFunctionStr IFunctionInterface::s_mapFunctionStr;
IFunctionInterface::MapSubFunctionStr IFunctionInterface::s_mapSubFunctionStr;

IFunctionInterface::IFunctionInterface(CUtility::SFunctionParam &sParam)
{
    m_iFunctionType = sParam.iFunction;
    m_iSubFunctionType = sParam.iSubFunction;
}

void IFunctionInterface::initFunction()
{
    LOG_FUNC_BEGIN
    // pthread function
    s_mapFunctionStr["pthread"] = EMAIN_TYPE_PTHREAD;
    // pthread sub function
    CPthreadFunction::initSubFunction(s_mapSubFunctionStr[EMAIN_TYPE_PTHREAD]);

    // file function
    s_mapFunctionStr["file"] = EMAIN_TYPE_FILE;
    // file sub function
    CFileFunction::initSubFunction(s_mapSubFunctionStr[EMAIN_TYPE_FILE]);

    // file function
    s_mapFunctionStr["sort"] = EMAIN_TYPE_SORT;
    // sort sub function
    CSortFunction::initSubFunction(s_mapSubFunctionStr[EMAIN_TYPE_SORT]);
    
    LOG_FUNC_END
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
