#ifndef __DOUBLE_LINKED_CHAIN_H__
#define __DOUBLE_LINKED_CHAIN_H__

#include "utility.h"
#include "linearList.h"

template <class T>
class CDoubleChain;

template <class T>
class CDoubleNode
{
    friend class CDoubleChain<T>;
public:
    CDoubleNode()
    {
        m_pLeft = NULL;
        m_pRight = NULL;
    }
private:
    CDoubleNode<T> *m_pLeft;
    CDoubleNode<T> *m_pRight;
    T m_data;
};

template <class T>
class CDoubleChain
{
public:
    CDoubleChain()
    {
        m_pHead = NULL;
        m_pTail = NULL;
    }
    CDoubleChain(const CDoubleChain<T>& inChain)
    {
        CDoubleNode<T> *pNode = NULL, *pPreNode = NULL;
        m_pHead = NULL;
        int iLen = inChain.Length();
        T tValue;
        for(int i=1;i<=iLen;++i)
        {
            inChain.Find(i, tValue);
            pNode = new CDoubleNode<T>();
            pNode->m_data = tValue;
            if(pPreNode)
                pPreNode->m_pRight = pNode;
            else
                m_pHead = pNode;
            pNode->m_pLeft = pPreNode;
            pPreNode = pNode;
        }
        m_pHead = m_pHead ? m_pHead : pNode;
        m_pTail = pNode;
    }
    ~CDoubleChain()
    {
        
    }
    void Erase()
    {
        CDoubleNode<T> *pNode = m_pHead;
        while(pNode)
        {
            CDoubleNode<T> *pTmpNode = pNode;
            pNode = pNode->m_pRight;
            delete pTmpNode;
        }
        m_pHead = m_pTail = NULL;
    }
    int Length() const
    {
        CDoubleNode<T> *pNode = m_pHead;
        int iLen = 0;
        while(pNode)
        {
            ++iLen;
            pNode = pNode->m_pRight;
        }
        return iLen;
    }
    bool Find(const int iIndex, T &outT) const
    {
        if(iIndex <= 0)
            THROW_FUNCTION_EXCEPTION(EERROR_OUT_OF_BOUND);
        CDoubleNode<T> *pNode = m_pHead;
        int iTmpIndex = 1;
        while(iTmpIndex < iIndex && pNode)
        {
            pNode = pNode->m_pRight;
            ++iTmpIndex;
        }
        if(iTmpIndex == iIndex && pNode)
        {
            outT = pNode->m_data;
            return true;
        }
        else if(pNode == NULL || iTmpIndex > iIndex)
        {
            THROW_FUNCTION_EXCEPTION(EERROR_OUT_OF_BOUND);
        }
        return false;
    }
    int Search(const T& inT) const
    {
        CDoubleNode<T> *pNode = m_pHead;
        int iTmpIndex = 0;
        while(pNode)
        {
            ++iTmpIndex;
            if(pNode->m_data == inT)
                return iTmpIndex;
            pNode = pNode->m_pRight;
        }
        return 0;
    }
    CDoubleChain<T>& Delete(const int iIndex, T& outT)
    {
        if(iIndex <= 0)
            THROW_FUNCTION_EXCEPTION(EERROR_OUT_OF_BOUND);
        CDoubleNode<T> *pNode = m_pHead, *pPreNode = NULL;
        int iTmpIndex = 1;
        while(iTmpIndex < iIndex && pNode)
        {
            pPreNode = pNode;
            pNode = pNode->m_pRight;
            ++iTmpIndex;
        }
        if(iIndex == iTmpIndex && pNode)
        {
            CDoubleNode<T> *pNext = pNode->m_pRight;
            if(pPreNode)
                pPreNode->m_pRight = pNext;
            else
                m_pHead = pNext;
            if(pNext)
                pNext->m_pLeft = pPreNode;
            else
                m_pTail = pNext;
            delete pNode;
        }
        else
            THROW_FUNCTION_EXCEPTION(EERROR_OUT_OF_BOUND);
        return *this;
    }
    CDoubleChain<T>& Insert(const int iIndex, const T& inT)
    {
        if(iIndex < 0)
            THROW_FUNCTION_EXCEPTION(EERROR_OUT_OF_BOUND);
        CDoubleNode<T> *pNode = m_pHead, *pPreNode = NULL;
        int iTmpIndex = 0;
        while(iTmpIndex < iIndex && pNode)
        {
            pPreNode = pNode;
            pNode = pNode->m_pRight;
            ++iTmpIndex;
        }
        if(iTmpIndex == iIndex)
        {
            CDoubleNode<T> *pTmpNode = new CDoubleNode<T>();
            pTmpNode->m_data = inT;
            if(pPreNode)
                pPreNode->m_pRight = pTmpNode;
            else
                m_pHead = pTmpNode;
            if(pNode)
                pNode->m_pLeft = pTmpNode;
            else
                m_pTail = pTmpNode;
            pTmpNode->m_pLeft = pPreNode;
            pTmpNode->m_pRight = pNode;
        }
        return *this;
    }
    static CDoubleChain<T>* FromList(const CLinearList<T>& inList)
    {
        CDoubleChain<T>* pChain = new CDoubleChain<T>();
        int iListLen = inList.Length();
        T tValue;
        for(int i = 1; i<=iListLen; ++i)
        {
            inList.Find(i, tValue);
            pChain->Insert(i-1, tValue);
        }
        return pChain;
    }
    void Output(ostream& out) const
    {
        CDoubleNode<T>* pNode = m_pHead;
        while(pNode)
        {
            out << pNode->m_data << " ";
            pNode = pNode->m_pRight;
        }
    }
private:
    CDoubleNode<T>* m_pHead;
    CDoubleNode<T>* m_pTail;
};

template <class T>
ostream& operator<<(ostream &out, const CDoubleChain<T>& inChain)
{
    inChain.Output(out);
    return out;
}

#endif
