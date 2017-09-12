#ifndef __LINEAR_LIST_H__
#define __LINEAR_LIST_H__

#include "utility.h"
#include <iostream>

using namespace std;

template <class T>
class CLinearList
{
public:
    CLinearList(int iSize = 10)
    {
        m_pElement = new T[iSize];
        m_iMaxSize = iSize;
        m_iSize = 0;
    }
    ~CLinearList()
    {
        delete []m_pElement;
    }

    //删除iIndex位置元素，保存到outT中，返回修改后的线性表
    CLinearList<T>& Delete(int iIndex, T &outT);
    //在iIndex后插入元素inT，返回修改后的线性表
    CLinearList<T>& Insert(int iIndex, const T &inT);

    //空TRUE 
    bool IsEmpty() const {return m_iSize == 0;}
    int  MaxSize() const {return m_iMaxSize;}
    //返回表中元素个数
    int  Length() const {return m_iSize;}
    //查找iIndex位置元素，放入outT中，如果没查到返回false
    bool Find(const int iIndex, T &outT) const;
    //返回inT位置，若不存在返回0
    int  Search(const T &inT) const;

    void OutPut(std::ostream & out)const ;
private:
    T*  expandSize();
    int m_iMaxSize;
    int m_iSize;
    T*  m_pElement;
};

template <class T>
CLinearList<T>& CLinearList<T>::Delete(int iIndex, T &outT)
{
    if(Find(iIndex, outT))
    {
        for(int i=iIndex-1; i<m_iSize; ++i)
            m_pElement[i] = m_pElement[i+1];
        m_iSize--;
    }
    else
        THROW_FUNCTION_EXCEPTION(EERROR_OUT_OF_BOUND);
}

template <class T>
CLinearList<T>& CLinearList<T>::Insert(int iIndex, const T &inT)
{
    if(iIndex < 0 || iIndex > m_iSize)
        THROW_FUNCTION_EXCEPTION(EERROR_OUT_OF_BOUND);
    if(m_iSize == m_iMaxSize)
    {
        expandSize();
    }
    int i=m_iSize;
    for(; i > iIndex; --i)
        m_pElement[i] = m_pElement[i-1];
    m_pElement[i]=inT;
    m_iSize++;
    return *this;
}

template <class T>
bool CLinearList<T>::Find(const int iIndex, T &outT) const
{
    if(iIndex > m_iSize || iIndex < 1)
        return false;
    outT = m_pElement[iIndex-1];
    return true;
}

template <class T>
int CLinearList<T>::Search(const T &inT) const
{
    for(int i=0;i<m_iSize;++i)
    {
        if(m_pElement[i] == inT)
            return i + 1;
    }
    return 0;
}

template <class T>
void CLinearList<T>::OutPut(ostream& out) const
{
    for(int i=0;i<m_iSize;++i)
        out << m_pElement[i] << " ";
}

template <class T>
T* CLinearList<T>::expandSize()
{
    T* pNewEle = new T[m_iMaxSize*2];
    for(int i=0;i<m_iSize;++i)
        pNewEle[i] = m_pElement[i];
    delete []m_pElement;
    m_iMaxSize *= 2;
    m_pElement = pNewEle;
    return m_pElement;
}

template <class T>
ostream& operator<<(ostream &out, CLinearList<T> &inT)
{
    inT.OutPut(out);
    return out;
}


template <class T>
ostream& operator<<(ostream &out, CLinearList<T> &inT);
#endif
