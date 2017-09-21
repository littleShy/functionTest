#include "fileFunction.h"

CFileFunction::PFunc CFileFunction::m_pFileFuncs[EFILE_INVALID_SUB_TYPE - 1] = {NULL};

CFileFunction::CFileFunction(CUtility::SFunctionParam &sParam) : IFunctionInterface(sParam)
{
    if(sParam.iSubFunction >= EFILE_INVALID_SUB_TYPE)
    {
        THROW_FUNCTION_EXCEPTION(EERROR_INVALID_SUB_FUNCTION_TYPE);
    }
    m_iFileSubType = sParam.iSubFunction;
}

void CFileFunction::initSubFunction(IFunctionInterface::MapFunctionStr &mSubFunctionStr)
{
    cout << "Init CFileFunction sub function begin." << endl;

    mSubFunctionStr["link"] = EFILE_SUB_TYPE_LINK;
    m_pFileFuncs[EFILE_SUB_TYPE_LINK] = &CFileFunction::testLink;
    mSubFunctionStr["stat"] = EFILE_SUB_TYPE_STAT;
    m_pFileFuncs[EFILE_SUB_TYPE_STAT] = &CFileFunction::testStat;

    cout << "Init CFileFunction sub function end." << endl;
}

void CFileFunction::run()
{
    cout << "CFileFunction run." << endl;

    if(NULL == m_pFileFuncs[m_iFileSubType])
    {
        THROW_FUNCTION_EXCEPTION(EERROR_INVALID_SUB_FUNCTION_TYPE);
    }
    (this->*m_pFileFuncs[m_iFileSubType])();

    cout << "CFileFunction run end." << endl;
}

void CFileFunction::testStat()
{
    cout << "CFileFunction test stat begin." << endl;
    char szFile[32] = "test.xml";
    struct stat sStat;
    int fd = open(szFile, O_CREAT | O_RDWR);
    if(fd < 0)
    {
        perror("Open file failed.");
        THROW_FUNCTION_EXCEPTION(EERROR_OPEN_FILE_FAILED);
    }
    if(fstat(fd, &sStat) != 0)
    {
        THROW_FUNCTION_EXCEPTION(EERROR_FUNCTION_FAILED);
    }

    //st_mode
    cout << "File (" << szFile << ") mode is: ";
    switch(sStat.st_mode)
    {
        case S_IFMT:
            cout << "S_IFMT" << endl;
            break;
        case S_IFSOCK:
            cout << "S_IFSOCK" << endl;
            break;
        case S_IFLNK:
            cout << "S_IFLNK" << endl;
            break;
        case S_IFREG:
            cout << "S_IFREG" << endl;
            break;
        case S_IFBLK:
            cout << "S_IFBLK" << endl;
            break;
        case S_IFDIR:
            cout << "S_IFDIR" << endl;
            break;
        case S_IFCHR:
            cout << "S_IFCHR" << endl;
            break;
        case S_IFIFO:
            cout << "S_IFIFO" << endl;
            break;
        default:
            cout << "Un Know file mode." << endl;
            break;
    }

    cout << "inode:\t" << sStat.st_ino << endl;
    cout << "dev:\t" << sStat.st_dev << endl;
    cout << "rdev:\t" << sStat.st_rdev << endl;
    cout << "nlink:\t" << sStat.st_nlink << endl;
    cout << "uid:\t" << sStat.st_uid << endl;
    cout << "gid:\t" << sStat.st_gid << endl;
    cout << "size:\t" << sStat.st_size << endl;
    cout << "atime:\t" << sStat.st_atime << endl;
    cout << "mtime:\t" << sStat.st_mtime << endl;
    cout << "ctime:\t" << sStat.st_ctime << endl;
    cout << "blksize:\t" << sStat.st_blksize << endl;
    cout << "blocks:\t" << sStat.st_blocks << endl;

    cout << "CFileFunction test stat end." << endl;
}

void CFileFunction::testLink()
{
    cout << "CFileFunction test link begin." << endl;
    cout << "Waiting for development." << endl;
    cout << "CFileFunction test link end." << endl;
}
