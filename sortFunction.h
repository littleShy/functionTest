#ifndef __SORT_FUNCTION_H__
#define __SORT_FUNCTION_H__

#include "functionInterface.h"
#include "utility.h"

class CSortFunction: public IFunctionInterface
{
public:
    CSortFunction(CUtility::SFunctionParam &sParam) throw();
    enum{
        //插入排序-直接排序 (Straight Insertion Sort)
        ESORT_SUB_TYPE_STRAIGHT_INSERT = 1,
        //插入排序—希尔排序(Shell`s Sort)
        ESORT_SUB_TYPE_SHELL,
        //选择排序—简单选择排序(Simple Selection Sort)
        ESORT_SUB_TYPE_SIMAPLE_SELECT,
        //选择排序—堆排序(Heap Sort)
        ESORT_SUB_TYPE_HEAP,
        //交换排序—冒泡排序(Bubble Sort)
        ESORT_SUB_TYPE_BUBBLE = 5,
        //交换排序—快速排序(Quick Sort)
        ESORT_SUB_TYPE_QUICK,
        //归并排序(Merge Sort)
        ESORT_SUB_TYPE_MERGE,
        //桶排序/基数排序(Radix Sort)
        ESORT_SUB_TYPE_RADIX = 8,
        ESORT_INVALID_SUB_TYPE
    };
    static void initSubFunction(IFunctionInterface::MapFunctionStr &mSubFunctionStr);
    void run();

private:
    typedef void (CSortFunction::*PFunc)(int *, int);
    static PFunc m_pSortFuncs[ESORT_INVALID_SUB_TYPE-1];

    void StraightInsertSort(int iArray[], int n);
    void ShellSort(int iArray[], int n);
    void SimpleSelectionSort(int iArray[], int n);
    void HeapSort(int iArray[], int n);
    void BubbleSort(int iArray[], int n);
    void QuickSort(int iArray[], int n);
    void MergeSort(int iArray[], int n);
    void RadixSort(int iArray[], int n);

    void _Merge(int iArray[], int left, int mid, int right);
    void _MergeRecursion(int iArray[], int left, int right);
    void _MergeIteration(int iArray[], int len);
    void print(int iArray[], int n);
    void swap(int iArray[], int i, int j);

    int m_iSortSubType;
};

#endif
