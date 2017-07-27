#include "pthreadFunction.h"

using namespace std;
CPthreadFunction::CPthreadFunction(CUtility::SFunctionParam &sParam): IFunctionInterface(sParam)
{

}

void CPthreadFunction::initSubFunctionStr(IFunctionInterface::MapFunctionStr &mSubFunctionStr)
{
    cout << "Init CPthreadFunction sub function." << endl;
    mSubFunctionStr["sample"] = EPTHREAD_SUB_TYPE_SAMPLE;
}
void CPthreadFunction::run()
{
    cout << "Pthread function run..." << endl;
}
