#include "pthreadFunction.h"

using namespace std;
CPthreadFunction::CPthreadFunction(CUtility::SFunctionParam &sParam): IFunctionInterface(sParam)
{

}

void CPthreadFunction::initSubFunction(IFunctionInterface::MapFunctionStr &mSubFunctionStr)
{
    cout << "Init CPthreadFunction sub function begin." << endl;
    mSubFunctionStr["sample"] = EPTHREAD_SUB_TYPE_SAMPLE;
    cout << "Init CPthreadFunction sub function end." << endl;
}

void CPthreadFunction::run()
{
    cout << "Pthread function run begin." << endl;
    cout << "Pthread function run end." << endl;
}
