#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <sys/time.h>

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
        static void printPassedTime(const struct timeval &tTvStart, const struct timeval &tTvEnd);
};

#define TIMER_BEGIN \
    struct timeval tTvStart, tTvEnd; \
    gettimeofday(&tTvStart, NULL);

#define TIMER_POINT \
    gettimeofday(&tTvEnd, NULL); \
    CUtility::printPassedTime(tTvStart, tTvEnd);

#define LOG_FUNC_BEGIN \
    std::cout << __FUNCTION__ << " begin." << std::endl;

#define LOG_FUNC_END \
    std::cout << __FUNCTION__ << " end." << std::endl;

#define ERROR_CODE_TO_MSG_INDEX(iCode)  (iCode - EERROR_MIN_ENUM)

#define THROW_FUNCTION_EXCEPTION(iCode) \
    do  \
    {   \
        throw CFunctionException((char*)szErrorMsg[ERROR_CODE_TO_MSG_INDEX(iCode)], iCode); \
    }while(0)

#define CATCH_EXCEPTION_BEGIN \
    try \
    {

#define CATCH_FUNCTION_EXCEPTION \
    }   \
    catch(CFunctionException e)    \
    {   \
        std::cout << "Catch exception, code: " << e.getCode() << ", msg: " << e.getMsg() << std::endl;

#define CATCH_UNKNOW_EXCEPTION \
    }   \
    catch(...)  \
    {   \
        std::cout << "Catch unknow exception!" << std::endl;

#define CATCH_EXCEPTION_END \
    }

enum ERROR_CODE
{
    EERROR_MIN_ENUM = 1001,
    EERROR_INVALID_FUNCTION_TYPE = 1001,
    EERROR_INVALID_SUB_FUNCTION_TYPE,
    EERROR_NO_VALID_SUB_FUNCTION,
    EERROR_OPEN_FILE_FAILED,
    EERROR_FUNCTION_FAILED = 1005,
    EERROR_OUT_OF_BOUND,
    EERROR_NO_MEM,
    EERROR_MAX_ENUM
};

const char szErrorMsg[EERROR_MAX_ENUM-1][64] = 
{
    "Invalid function type.",
    "Invalid sub function type.",
    "There is no valid sub function for current function.",
    "Open file failed.",
    "Function test failed.",
    "Index out of range.",
    "Memory not enough, alloc memory failed."
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
        char m_szErrorMsg[64];
        int m_iErrorCode;
};

#endif
