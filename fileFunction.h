#ifndef __FILE_FUNCTION_H__
#define __FILE_FUNCTION_H__

#include "functionInterface.h"
#include "utility.h"

class CFileFunction : public IFunctionInterface
{
  public:
	CFileFunction(CUtility::SFunctionParam &sParam);
	enum EFILE_SUB_FUNCTION
	{
		EFILE_SUB_TYPE_LINK = 1,
		EFILE_INVALID_SUB_TYPE
	};

	static void initSubFunctionStr(IFunctionInterface::MapFunctionStr &mSubFunctionStr);
	void run();
};

#endif
