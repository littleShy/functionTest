#include "functionTest.h"

IFunctionInterface* CFunctionTest::createFunctionInstance(CUtility::SFunctionParam &sParam)
{
	LOG_FUNC_BEGIN
	IFunctionInterface *pFunction = NULL;
	try
	{
		switch(sParam.iFunction)
		{
			case IFunctionInterface::EMAIN_TYPE_PTHREAD:
				pFunction = new CPthreadFunction(sParam);
				break;
			case IFunctionInterface::EMAIN_TYPE_FILE:
				pFunction = new CFileFunction(sParam);
				break;
			case IFunctionInterface::EMAIN_TYPE_SORT:
				pFunction = new CSortFunction(sParam);
				break;
			case IFunctionInterface::EMAIN_TYPE_DATA_STRUCTURE:
				pFunction = new CDataStructure(sParam);
				break;
		}
	}
	catch(CFunctionException ex)
	{
		cout << "Catch CFunctionException, code: " << ex.getCode() << ", msg: " << ex.getMsg() << endl;
	}
	LOG_FUNC_END
	return pFunction;
}
