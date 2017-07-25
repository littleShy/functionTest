#ifndef __FUNCTION_INTERFACE_H__
#define __FUNCTION_INTERFACE_H__

#include <iostream>
#include <unistd.h>
#include <map.h>

class IFunctionInterface
{
public:
	enum EFUNCTION_TYPE
	{
		EPTHREAD_TYPE,
		EFILE_TYPE,
		EINVALID_FUNCTION_TYPE
	};

	typedef std::map<string, int> MapFunctionStr;
	typedef MapFunctionStr::iterator IterFunctionStr;

	static MapFunctionStr s_mFunctionStr;
	MapFunctionStr s_mSubFunctionStr;

	IFunctionInterface(int iFunctionType, int iSubFunctionType = 0)
	{
		m_iFunctionType = iFunctionType;
		m_iSubFunctionType = iSubFunctionType;
	}

	void initFunctionStr()
	{
		// pthread function
		s_mFunctionStr["pthread"] = EPTHREAD_TYPE;

		// file function
		s_mFunctionStr["file"] = EFILE_TYPE;
	}
	
	void usage()
	{
		cout << "\t-t <value>" << endl;
		for(IterFunctionStr iter=s_mFunctionStr.begin();iter<s_mFunctionStr.size();iter++)
			cout << "\t\t" << iter.first << endl;
	}
	virtual int run() = 0;
protected:
	int m_iFunctionType;
	int m_iSubFunctionType;
};

#endif

