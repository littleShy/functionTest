#include "functionTest.h"
using namespace std;

int main(int argc, char * argv[])
{
	cout << "Test start..." << endl;
	CUtility::SFunctionParam sParam;
	IFunctionInterface::initFunction();

	if(CUtility::parseInputArgs(argc, argv, sParam) != 0)
	{
		IFunctionInterface::usage();
		return -1;
    }
    
    IFunctionInterface *pFunction = CFunctionTest::createFunctionInstance(sParam);
    if(NULL ==pFunction)
    {
        cout << "Create Function failed!" << endl;
        return -1;
    }
	try
	{
        pFunction->run();
	}
	catch(CFunctionException ex)
	{
		cout << "Catch CFunctionException, code: " << ex.getCode() << ", msg: " << ex.getMsg() << endl;
    }
    catch(...)
    {
        cout << "Catch Unknow exception." << endl;
    }
	cout << "Test end." << endl;
	return 0;
}
