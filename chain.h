#ifndef __CHAIN_H__
#define __CHAIN_H__

#include "utility.h"
#include "linearList.h"
#include <iostream>

template <class T>
class CLinearList;
template <class T>
class ChainIterator;
template <class T>
class ChainNode;
template <class T>
class Chain
{
    friend class ChainIterator<T>;
public:
    Chain()
    {
        m_pHead = NULL;
        m_pTail = NULL;
    }
    ~Chain()
    {
        Erase();
    }
    int Length() const
    {
        int iLen = 0;
        ChainNode<T> *pNode = m_pHead;
        while(pNode)
        {
            ++iLen;
            pNode = pNode->m_pNext;
        }
        return iLen;
    }
    bool IsEmpty() const
    {
        return m_pHead == NULL;
    }
    bool Find(const int iIndex, T& outT) const
    {
        ChainNode<T> *pNode = m_pHead;
        int iTmpIndex = 1;
        while(pNode)
        {
            if(iTmpIndex == iIndex)
            {
                outT = pNode->m_data;
                return true;
            }
            pNode = pNode->m_pNext;
            iTmpIndex++;
        }
        return false;
    }
    int Search(const T& inT) const
    {
        ChainNode<T> *pNode = m_pHead;
        int iTmpIndex = 1;
        while(pNode)
        {
            if(pNode->m_data == inT)
                return iTmpIndex;
            pNode = pNode->m_pNext;
            iTmpIndex++;
        }
        return 0;
    }
    Chain<T>& Delete(const int iIndex, T& outT)
    {
        ChainNode<T> *pPreNode = NULL, *pTmpNode = pPreNode, *pCurNode = m_pHead;
        int iTmpIndex = 1;
        while(pCurNode)
        {
            if(iTmpIndex == iIndex)
            {
                outT = pCurNode->m_data;
                if(pPreNode)
                    pPreNode->m_pNext = pCurNode->m_pNext;
                else
                    m_pHead = pCurNode->m_pNext;
                if(!pCurNode->m_pNext)
                    m_pTail = pPreNode;
                delete pCurNode;
                return *this;
            }
            pPreNode = pCurNode;
            pCurNode = pCurNode->m_pNext;
            iTmpIndex++;
        }
        THROW_FUNCTION_EXCEPTION(EERROR_OUT_OF_BOUND);
    }
    Chain<T>& Insert(const int iIndex, const T& inT)
    {
        ChainNode<T> *pPreNode = NULL, *pCurNode = m_pHead;
        int iTmpIndex = 0;

        while(iTmpIndex < iIndex && pCurNode)
        {
            pPreNode = pCurNode;
            pCurNode = pCurNode->m_pNext;
            iTmpIndex++;
        }
        if(iIndex == iTmpIndex)
        {
            ChainNode<T> *pNode = new ChainNode<T>;
            pNode->m_data = inT;
            if(pPreNode)
                pPreNode->m_pNext = pNode;
            else
                m_pHead = pNode;
            pNode->m_pNext = pCurNode;
            if(pCurNode == NULL)
                m_pTail = pNode;
            return *this;
        }
        THROW_FUNCTION_EXCEPTION(EERROR_OUT_OF_BOUND);
    }
    Chain<T>& Insert(const T& inT)
    {
        ChainNode<T> *pNode = new ChainNode<T>;
        pNode->m_data = inT;
        if(m_pTail)
            m_pTail->m_pNext = pNode;
        m_pHead = m_pHead ? m_pHead : pNode;
        m_pTail = pNode;
        return *this;
    }

    void Erase()
    {
        ChainNode<T> *pNode = m_pHead;
        while(pNode)
        {
            ChainNode<T> *pTmpNode = pNode;
            pNode = pNode->m_pNext;
            delete pTmpNode;
        }
        m_pHead = NULL;
        m_pTail = NULL;
    }

    static Chain<T>* FromList(const CLinearList<T> &inList)
    {
        Chain<T>* pChain = new Chain<T>();
        int iListLen = inList.Length();
        T tValue;
        for(int i=1;i<=iListLen;++i)
        {
            inList.Find(i, tValue);
            pChain->Insert(tValue);
        }
        return pChain;
    }

    void OutPut(std::ostream &out) const
    {
        ChainNode<T> *pNode = m_pHead;
        cout << "Chain Length: " << Length() << std::endl;
        while(pNode)
        {
            out << pNode->m_data << " ";
            pNode = pNode->m_pNext;
        }
        cout << std::endl;
    }
private:
    ChainNode<T> *m_pHead;
    ChainNode<T> *m_pTail;
};

template <class T>
class ChainNode
{
    friend ChainIterator<T>;
    friend Chain<T>;
public:
    ChainNode()
    {
        m_pNext = NULL;
    }
private:
    T m_data;
    ChainNode<T>* m_pNext;
};

template <class T>
class ChainIterator
{
public:
    T* Initialize(const Chain<T> &inChain)
    {
        m_pLocation = inChain.m_pHead;
        return m_pLocation ? &m_pLocation->m_data : NULL;
    }
    T* Next()
    {
        if(m_pLocation)
            m_pLocation = m_pLocation->m_pNext;
        return m_pLocation ? &m_pLocation->m_data : NULL;
    }
private:
    ChainNode<T> *m_pLocation;
};

template<class T>
ostream& operator<<(ostream &out, const Chain<T> &inChain)
{
    inChain.OutPut(out);
    return out;
}
#endif
