#ifndef __LINEAR_LIST_H__
#define __LINEAR_LIST_H__

#include "utility.h"
#include "chain.h"
#include <iostream>

using namespace std;

template <class T>
class CLinearList
{
public:
    CLinearList()
    {
        m_iMaxSize = 0;
        ReInit();
    }

    CLinearList(const CLinearList<T> &inT)
    {
        m_iCurrent = inT.CurrentIndex();
        m_iMaxSize = inT.MaxSize();
        m_iSize = inT.Length();
        m_pElement = new T[m_iMaxSize];
        for(int i=1;i<=m_iSize;++i)
        {
            inT.Find(i, m_pElement[i-1]);
        }
    }

    CLinearList<T>& operator=(const CLinearList<T>& inT)
    {
        if(this == &inT)
            return *this;
        if(m_iMaxSize != 0)
        {
            delete []m_pElement;
        }
        m_iCurrent = inT.CurrentIndex();
        m_iMaxSize = inT.MaxSize();
        m_iSize = inT.Length();
        m_pElement = new T[m_iMaxSize];
        for(int i=1;i<=m_iSize;++i)
        {
            inT.Find(i, m_pElement[i-1]);
        }
    }

    ~CLinearList()
    {
        delete []m_pElement;
    }

    void ReInit()
    {
        if(m_iMaxSize != 0)
            delete [] m_pElement;
        m_pElement = new T[1];
        if(NULL == m_pElement)
            THROW_FUNCTION_EXCEPTION(EERROR_NO_MEM);
        m_iMaxSize = 1;
        m_iSize = 0;
        m_iCurrent = 1;
    }

    //删除iIndex位置元素，保存到outT中，返回修改后的线性表
    CLinearList<T>& Delete(int iIndex, T &outT)
    {
        if(Find(iIndex, outT))
        {
            if((m_iSize-1) <= m_iMaxSize/2 && (m_iMaxSize != 1))
                reduceSize();
            for(int i=iIndex-1; i<m_iSize; ++i)
                m_pElement[i] = m_pElement[i+1];
            m_iSize--;
        }
        else
            THROW_FUNCTION_EXCEPTION(EERROR_OUT_OF_BOUND);
    }

    //在iIndex后插入元素inT，返回修改后的线性表
    CLinearList<T>& Insert(int iIndex, const T &inT)
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

    //反转线性表元素
    CLinearList<T>& Reverse()
    {
        for(int i=0;i<m_iSize/2;++i)
        {
            T tTmp = m_pElement[i];
            m_pElement[i] = m_pElement[m_iSize-i-1];
            m_pElement[m_iSize-i-1] = tTmp;
        }
        return *this;
    }

    /*
        截断成原来长度的一半
        如果X.length的初始值为7，且X.element[]=[2,13,4,5,17,8,29]，则执行X.Half()后，
        X.length的值为4，且X.element[]=[2,4,17,29];如果X.length的初始值为4，且X.element[]=
        [2,13,4,5]，则执行X.Half()后，X.length的值为2，且X.element[]=[2,4]。如果X开始时是空表，
        则执行X.Half()后，X仍然为空表。
    */
    CLinearList<T>& Half()
    {
        int iHalfSize = (m_iSize+1)/2;
        for(int i=2;i<m_iSize;i+=2)
        {
            m_pElement[i/2] = m_pElement[i];
        }
        m_iSize = iHalfSize;
        if((m_iSize-1) <= m_iMaxSize/2 && (m_iMaxSize != 1))
            reduceSize();
        Reset();
        return *this;
    }
    //组合inTA和inTB，两个线性表元素交替出现，第一个是inTA的第一个元素，当其中一个线性表
    //元素没有时直接把另外一个线性表剩余元素拼接过来
    void Alternate(const CLinearList<T> &inTA, const CLinearList<T> &inTB)
    {
        int iAIndex = 1,iBIndex = 1, iALen = inTA.Length(), iBLen = inTB.Length();
        int i = 0, iMinSize, iFinalSize = iALen + iBLen;
        ReInit();
        if(inTA.Length() == 0 && inTB.Length() == 0)
        {
            return;
        }
        if(inTA.Length() == 0)
        {
            *this = inTB;
            return;
        }
        else if(inTB.Length() == 0)
        {
            *this = inTA;
            return;
        }
        iFinalSize = iALen + iBLen;
        iMinSize = iALen < iBLen ? iALen : iBLen;
        T tmpT;
        for(;i<iMinSize*2;++i)
        {
            if(i%2 == 0)
                inTA.Find(iAIndex++, tmpT);
            else
                inTB.Find(iBIndex++, tmpT);
            Insert(i, tmpT);
        }
        if(iAIndex > inTA.Length())
        {
            for(;iBIndex<=inTB.Length();++iBIndex,++i)
            {
                inTB.Find(iBIndex, tmpT);
                Insert(i, tmpT);
            }
        }
        else
        {
            for(;iAIndex<=inTA.Length();++iAIndex,++i)
            {
                inTA.Find(iAIndex, tmpT);
                Insert(i, tmpT);
            }
        }
    }

    static CLinearList<T>* FromChain(const Chain<T>& inChain)
    {
        CLinearList<T> *pList = new CLinearList<T>();
        int iChainLen = inChain.Length();
        T tValue;
        for(int i=1; i<=iChainLen; ++i)
        {
            inChain.Find(i, tValue);
            pList->Insert(i-1, tValue);
        }
        return pList;
    }
    static CLinearList<T>* FromChain1(const Chain<T>& inChain)
    {
        CLinearList<T> *pList = new CLinearList<T>();
        ChainIterator<T> chainIter;
        T* pTValue = chainIter.Initialize(inChain);
        int iIndex = 0;
        while(pTValue)
        {
            pList->Insert(iIndex, *pTValue);
            pTValue = chainIter.Next();
            ++iIndex;
        }
        return pList;
    }

    //空TRUE 
    bool IsEmpty() const {return m_iSize == 0;}
    bool End() const 
    {
        if(m_iSize == 0)
            return true;
        return m_iCurrent == m_iSize;
    }
    bool Front() const 
    {
        if(m_iSize == 0)
            return true;
        return m_iCurrent == 1;
    }
    int  MaxSize() const {return m_iMaxSize;}
    int  CurrentIndex() const {return m_iCurrent;}
    //返回表中元素个数
    int  Length() const {return m_iSize;}
    //查找iIndex位置元素，放入outT中，如果没查到返回false
    bool Find(const int iIndex, T &outT) const
    {
        if(iIndex > m_iSize || iIndex < 1)
            return false;
        outT = m_pElement[iIndex-1];
        return true;
    }
    //返回inT位置，若不存在返回0
    int  Search(const T &inT) const
    {
        for(int i=0;i<m_iSize;++i)
        {
            if(m_pElement[i] == inT)
                return i + 1;
        }
        return 0;
    }
    //重置m_iCurrent为1
    void Reset(){m_iCurrent = 1;}
    
    //返回线性表inT的当前元素
    T& Current() const
    {
        return m_pElement[m_iCurrent-1];
    }
    void Previous()
    {
        if(m_iCurrent-1 < 1)
            THROW_FUNCTION_EXCEPTION(EERROR_OUT_OF_BOUND);
        m_iCurrent--;
    }
    void Next()
    {
        if(m_iCurrent+1 > m_iSize)
            THROW_FUNCTION_EXCEPTION(EERROR_OUT_OF_BOUND);
        m_iCurrent++;
    }

    void OutPut(std::ostream & out)const
    {
        out << "LiearList Max Size: " << m_iMaxSize << ", used: " << m_iSize << ", Current Index: " << m_iCurrent << endl;
        for(int i=0;i<m_iSize;++i)
            out << m_pElement[i] << " ";
    }

private:
    T*  expandSize()
    {
        reAllocMem(m_iMaxSize*2);
    }

    T* reduceSize()
    {
        reAllocMem(m_iMaxSize/2);
    }

    T* reAllocMem(const int iReSize)
    {
        T* pNewEle = new T[iReSize];
        if(NULL == pNewEle)
            THROW_FUNCTION_EXCEPTION(EERROR_NO_MEM);
        for(int i=0;i<m_iSize;++i)
            pNewEle[i] = m_pElement[i];
        delete []m_pElement;
        m_iMaxSize = iReSize;
        m_pElement = pNewEle;
        return m_pElement;
    }
    
    int m_iMaxSize;
    int m_iSize;
    int m_iCurrent;
    T*  m_pElement;
};

template <class T>
ostream& operator<<(ostream &out, CLinearList<T> &inT)
{
    inT.OutPut(out);
    return out;
}

template <class T>
void Reverse(CLinearList<T> &inT)
{
    inT.Reverse();
}

#endif
