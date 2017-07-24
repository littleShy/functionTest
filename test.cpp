#include "inc.h"
using namespace std;

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

int parseInputArgs(int argc, char* argv[])
{
	int ch = 0, iRet = -1;
	opterr = 0;
	char szFunction[16], szSubFunction[16];
	memset(szFunction, 0, sizeof(szFunction));
	memset(szSubFunction, 0, sizeof(szSubFunction));
	while((ch = getopt(argc, argv, "t:s:")) != -1)
	{
		switch(ch)
		{
			case 't':
		}
	}
	return EINVALID_TYPE;
}

void usage()
{

}


int main(int argc, char * argv[])
{

	return 0;
}
