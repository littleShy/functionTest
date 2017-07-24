#ifndef __FUNCTION_INTERFACE_H__
#define __FUNCTION_INTERFACE_H__

#include "inc.h"

class IFunctionInterface
{
public:
	enum EFUNCTION_TYPE
	{
		EPTHREAD_TYPE,
		EFILE_TYPE,
		EINVALID_TYPE
	};

	typedef std::map<int, string> MapFunctionStr;
	typedef MapFunctionStr::iterator IterFunctionStr;
	
	static MapFunctionStr s_mFunctionStr;
	
	IFunctionInterface(int iFunctionType, int iSubFunctionType = 0)
	{
		m_iFunctionType = iFunctionType;
		m_iSubFunctionType = iSubFunctionType;
	}

	static void initFunctionStr()
	{
		s_mFunctionStr[EPTHREAD_TYPE] = "pthread";
		s_mFunctionStr[EFILE_TYPE] = "file";
	}
	
	virtual void  usage() = 0;
	virtual int run() = 0;
protected:
	int m_iFunctionType;
	int m_iSubFunctionType;
};

#endif

