#ifndef __FUNCTION_INTERFACE_H__
#define __FUNCTION_INTERFACE_H__

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <map>
#include "utility.h"

using namespace std;

class IFunctionInterface
{
  public:
	enum EFUNCTION_TYPE
	{
		EPTHREAD_FUNCTION_TYPE = 1,
		EFILE_FUNCTION_TYPE,
		EINVALID_FUNCTION_TYPE
	};

	typedef map<string, int> MapFunctionStr;
	typedef MapFunctionStr::iterator IterFunctionStr;
	typedef map<int, MapFunctionStr> MapSubFunctionStr;
	typedef MapSubFunctionStr::iterator IterSubFunctionStr;

	static MapFunctionStr s_mapFunctionStr;
	static MapSubFunctionStr s_mapSubFunctionStr;

	IFunctionInterface(CUtility::SFunctionParam &sParam);

	static void initFunctionStr();

	static void usage();

	virtual void run() = 0;

  protected:
	int m_iFunctionType;
	int m_iSubFunctionType;
};

#endif
