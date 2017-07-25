#include <iostream>
using namespace std;

class CUnility
{
    public:
        struct SFunctionParam
        {
            int iFunction;
            int iSubFunction;
        };
        static int parseInputArgs(int argc, char* argv[], SFunctionParam &sParam)
        {
            int ch = 0, iRet = 0;
            opterr = 0;
            while((ch = getopt(argc, argv, "t:s:")) != -1)
            {
                switch(ch)
                {
                    case 't':
                        if(s_mFunctionStr.find(optarg) != s_mFunctionStr.end())
                            sParam.iFunction = s_mFunctionStr.at(optarg);
                        else
                            iRet = -1;
                        break;
                    case 's':
                        if(s_mFunctionSub.find(optarg) != s_mFunctionSub.end())
                            sParam.iSubFunction = s_mFunctionSub.at(optarg);
                        else
                            iRet = -1;
                        break;
                    default:
                        iRet = -1;
                        cout << "Invalid option: " << ch << endl;
                        break;
                }
            }
            return iRet;
        }

};
