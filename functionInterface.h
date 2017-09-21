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
		EMAIN_TYPE_PTHREAD = 1,
		EMAIN_TYPE_FILE,
		EMAIN_TYPE_SORT,
		EMAIN_TYPE_DATA_STRUCTURE,
		EINVALID_FUNCTION_TYPE
	};

	typedef map<string, int> MapFunctionStr;
	typedef MapFunctionStr::iterator IterFunctionStr;
	typedef map<int, MapFunctionStr> MapSubFunctionStr;
	typedef MapSubFunctionStr::iterator IterSubFunctionStr;
	
	static MapFunctionStr s_mapFunctionStr;
	static MapSubFunctionStr s_mapSubFunctionStr;

	IFunctionInterface(CUtility::SFunctionParam &sParam);

	static void initFunction();

	static void usage();

	virtual void run() = 0;

  protected:
	int m_iFunctionType;
	int m_iSubFunctionType;
};

#endif
