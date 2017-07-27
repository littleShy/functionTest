#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <iostream>
#include <string.h> 

class CUtility
{
    public:
        struct SFunctionParam
        {
            SFunctionParam()
            {
                iFunction = 0;
                iSubFunction = 0;
            }
            int iFunction;
            int iSubFunction;
        };
        static int parseInputArgs(int argc, char* argv[], SFunctionParam &sParam);
};

class CFunctionException
{
    public:
        CFunctionException(char *szMsg, int iCode)
        {
            strncpy(m_szErrorMsg, szMsg, sizeof(m_szErrorMsg));
            m_iErrorCode = iCode;
        }
        inline char *getMsg(){return m_szErrorMsg;}
        inline int getCode(){return m_iErrorCode;}
    private:
        char m_szErrorMsg[32];
        int m_iErrorCode;
};

#endif
