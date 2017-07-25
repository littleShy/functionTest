#ifndef __FILE_FUNCTION_H__
#define __FILE_FUNCTION_H__

#include "functionInterface.h"

class CFileFunction: public IFunctionInterface
{
public:

	CFileFunction(int iFunctionType, int iSubFunctionType = 0): IFunctionInterface(iFunctionType, iSubFunctionType){}
	enum EFILE_SUB_FUNCTION
	{
		ELINK_FUNCTION
	};

	void usage()
	{
		cout << "CFileFunction usage: " << endl;
	}

	int run()
	{
		cout << "CFileFunction run." << endl;
		return 0;
	}	
};

#endif
