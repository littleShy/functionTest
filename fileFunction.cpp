#include "fileFunction.h"

CFileFunction::CFileFunction(CUtility::SFunctionParam &sParam): IFunctionInterface(sParam)
{

}

void CFileFunction::initSubFunctionStr(IFunctionInterface::MapFunctionStr &mSubFunctionStr)
{
    cout << "Init CFileFunction sub function." << endl;
    mSubFunctionStr["link"] = EFILE_SUB_TYPE_LINK;
}

void CFileFunction::run()
{
    cout << "CFileFunction run." << endl;
}
