#include "sortFunction.h"

CSortFunction::PFunc CSortFunction::m_pSortFuncs[ESORT_INVALID_SUB_TYPE - 1] = {NULL};

CSortFunction::CSortFunction(CUtility::SFunctionParam &sParam) throw() : IFunctionInterface(sParam)
{
    if(sParam.iSubFunction >= ESORT_INVALID_SUB_TYPE)
    {
        THROW_FUNCTION_EXCEPTION(EERROR_INVALID_SUB_FUNCTION_TYPE);
    }
    m_iSortSubType = sParam.iSubFunction;
}

void CSortFunction::initSubFunction(IFunctionInterface::MapFunctionStr &mSubFunctionStr)
{
    LOG_FUNC_BEGIN
    mSubFunctionStr["straight"] = ESORT_SUB_TYPE_STRAIGHT_INSERT;
    m_pSortFuncs[ESORT_SUB_TYPE_STRAIGHT_INSERT] = &CSortFunction::StraightInsertSort;
    mSubFunctionStr["shell"] = ESORT_SUB_TYPE_SHELL;
    m_pSortFuncs[ESORT_SUB_TYPE_SHELL] = &CSortFunction::ShellSort;
    mSubFunctionStr["simple"] = ESORT_SUB_TYPE_SIMAPLE_SELECT;
    m_pSortFuncs[ESORT_SUB_TYPE_SIMAPLE_SELECT] = &CSortFunction::SimpleSelectionSort;
    mSubFunctionStr["heap"] = ESORT_SUB_TYPE_HEAP;
    m_pSortFuncs[ESORT_SUB_TYPE_HEAP] = &CSortFunction::HeapSort;
    mSubFunctionStr["bubble"] = ESORT_SUB_TYPE_BUBBLE;
    m_pSortFuncs[ESORT_SUB_TYPE_BUBBLE] = &CSortFunction::BubbleSort;
    mSubFunctionStr["quick"] = ESORT_SUB_TYPE_QUICK;
    m_pSortFuncs[ESORT_SUB_TYPE_QUICK] = &CSortFunction::QuickSort;
    mSubFunctionStr["merge"] = ESORT_SUB_TYPE_MERGE;
    m_pSortFuncs[ESORT_SUB_TYPE_MERGE] = &CSortFunction::MergeSort;
    mSubFunctionStr["radix"] = ESORT_SUB_TYPE_RADIX;
    m_pSortFuncs[ESORT_SUB_TYPE_RADIX] = &CSortFunction::RadixSort;
    LOG_FUNC_END
}

void CSortFunction::run()
{
    LOG_FUNC_BEGIN
    if(NULL == m_pSortFuncs[m_iSubFunctionType])
    {
        THROW_FUNCTION_EXCEPTION(EERROR_INVALID_SUB_FUNCTION_TYPE);
    }

    int iArray[] = {8,3,4,5,0,6,7,1,2,9};
    cout << "before sort:" << endl;
    int len = sizeof(iArray) / sizeof(int);
    print(iArray, len);
    (this->*m_pSortFuncs[m_iSortSubType])(iArray, len);
    cout << "after sort:" << endl;
    print(iArray, len);

    LOG_FUNC_END
}

void CSortFunction::swap(int iArray[], int i, int j)
{
    int iTmp = iArray[i];
    iArray[i] = iArray[j];
    iArray[j] = iTmp;
}

void CSortFunction::print(int iArray[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << iArray[i] << " ";
    }
    cout << endl;
}
/********************************************************************
*
*                            直接插入排序
*   从第一个元素开始，可以认为是已经排序的元素，取出下一个元素，从后往前扫描
* 已排序的元素序列，如果该元素(已排序)大于此元素，则把该元素移到下一个位置，
* 重复比较移动已排序的元素序列，直到没有元素大于此元素。将新元素插入到当前位
* 置。然后继续取未排序序列的下一个元素，循环以上步骤。
*
* 数据结构 ---------- 数组
* 最差时间复杂度 ---- 最坏情况为输入序列是降序排列的,此时时间复杂度O(n^2)
* 最优时间复杂度 ---- 最好情况为输入序列是升序排列的,此时时间复杂度O(n)
* 平均时间复杂度 ---- O(n^2)
* 所需辅助空间 ------ O(1)
* 稳定性 ------------ 稳定
*
*********************************************************************/
void CSortFunction::StraightInsertSort(int iArray[], int n)
{
    LOG_FUNC_BEGIN
    
    for(int i=1;i<n;++i)
    {
        int iTmpI = iArray[i];
        int j=i-1;
        while(j >= 0 && iTmpI < iArray[j])
        {
            iArray[j+1] = iArray[j--];
        }
        iArray[j+1] = iTmpI;
    }
    
    LOG_FUNC_END
}

/********************************************************************
*
*                            希尔排序
*   希尔排序，也叫递减增量排序，是插入排序的一种更高效的改进版本。希尔排序是
* 不稳定的排序算法。
*   希尔排序是基于插入排序的以下两点性质而提出改进方法的：
*   1. 插入排序在对几乎已经排好序的数据操作时，效率高，即可以达到线性排序的
*      效率
*   2. 但插入排序一般来说是低效的，因为插入排序每次只能将数据移动一位
*   希尔排序通过将比较的全部元素分为几个区域来提升插入排序的性能。这样可以让
* 一个元素可以一次性地朝最终位置前进一大步。然后算法再取越来越小的步长进行排
* 序，算法的最后一步就是普通的插入排序，但是到了这步，需排序的数据几乎是已排
* 好的了（此时插入排序较快）。
*
* 数据结构 ---------- 数组
* 最差时间复杂度 ---- 根据步长序列的不同而不同。已知最好的为O(n(logn)^2)
* 最优时间复杂度 ---- O(n)
* 平均时间复杂度 ---- 根据步长序列的不同而不同。
* 所需辅助空间 ------ O(1)
* 稳定性 ------------ 不稳定
*
*********************************************************************/
void CSortFunction::ShellSort(int iArray[], int n)
{
    LOG_FUNC_BEGIN
    
    int m = 0;
    while(m <= n)
    {
        m = 3 * m + 1;
    }

    while( m >= 1)
    {
        StraightInsertSort(iArray + m - 1, n - m + 1);
        m = (m - 1) / 3;
    }
    
    LOG_FUNC_END
}

/********************************************************************
*
*                            选择排序
*   初始时，在序列中找到最小(大)的元素，放到序列的起始位置作为已排序的序列。
* 然后再从未排序的序列中取出最小(大)的元素，放到已排序的序列末尾，以此类推，
* 直到所有的元素排序完毕
*
*   选择排序是不稳定的排序算法，不稳定发生在最小元素与A[i]交换的时刻。
* 比如序列：{ 5, 8, 5, 2, 9 }，一次选择的最小元素是2，然后把2和第一个5进行
* 交换，从而改变了两个元素5的相对次序。
*
* 数据结构 ---------- 数组
* 最差时间复杂度 ---- O(n^2)
* 最优时间复杂度 ---- O(n^2)
* 平均时间复杂度 ---- O(n^2)
* 所需辅助空间 ------ O(1)
* 稳定性 ----------- 不稳定
*
*********************************************************************/
void CSortFunction::SimpleSelectionSort(int iArray[], int n)
{
    LOG_FUNC_BEGIN
    
    for(int i=0;i<n;++i)
    {
        int min = i;
        for(int j=i+1;j<n;++j)
        {
            if(iArray[j] < iArray[min])
                min = j;
        }
        if(min != i)
        {
            swap(iArray, i, min);
        }
    }
    
    LOG_FUNC_END
}
/********************************************************************
*
*                            堆排序
*   堆排序是利用堆这种数据结构所设计的排序算法。堆是一种近似于完全二叉树(所有
* 的叶节点)的结构。并满足性质：以最大堆为例其父节点的值总大于它的孩子节点。
*
*   由输入的无需数组构造一个最大堆，作为初始的无序区。把堆顶元素(最大值)和堆
* 尾元素互换。把堆(无序区)的尺寸缩小1，调用heapify(A, 0)从新的堆顶元素开始进
* 行调整。重复以上步骤直到堆尺寸为1。
*
* 最差时间复杂度 ---- O(nlogn)
* 最优时间复杂度 ---- O(nlogn)
* 平均时间复杂度 ---- O(nlogn)
* 所需辅助空间 ------ O(1)
* 稳定性 ------------ 不稳定
*
*********************************************************************/
void CSortFunction::HeapSort(int iArray[], int n)
{
    LOG_FUNC_BEGIN
    

    LOG_FUNC_END
}
/********************************************************************
*
*                            冒泡排序
*   比较每一对相邻的元素，如果前者比后者大，则调换两个元素的位置，比较完后，
* 最后一个元素就是最大的。重复以上步骤比较移动每一对相邻的元素，除了最后一个
* 元素，直到没有一对元素可比较为止
*
* 数据结构 ---------- 数组
* 最差时间复杂度 ---- O(n^2)
* 最优时间复杂度 ---- 如果能在内部循环第一次运行时,使用一个旗标来表示有无需
*                   要交换的可能,可以把最优时间复杂度降低到O(n)
* 平均时间复杂度 ---- O(n^2)
* 所需辅助空间 ------ O(1)
* 稳定性 ------------ 稳定
*
*********************************************************************/
void CSortFunction::BubbleSort(int iArray[], int n)
{
    LOG_FUNC_BEGIN
    
    for(int i = 0; i < n - 1; ++i)
    {
        for(int j = 0; j < n - i - 1; ++j)
        {
            if(iArray[j] > iArray[j+1])
            {
                swap(iArray, j, j+1);
            }
        }
    }
    
    LOG_FUNC_END
}
/********************************************************************
*
*                            快速排序
*   快速排序采用分治策略把一个序列分为两个子序列。
*   从序列中挑出一个元素，作为基准(pivot)。把所有比基准小的元素放在基准前面
* 比基准大的元素放在基准后面，这个成为分区操作。对每个分区递归的执行以上步骤
* 递归结束条件是序列大小为0,或1。
*
* 数据结构 --------- 数组
* 最差时间复杂度 ---- 每次选取的基准都是最大（或最小）的元素，导致每次只划分
*                    出了一个分区，需要进行n-1次划分才能结束递归，时间复杂
*                    度为O(n^2)
* 最优时间复杂度 ---- 每次选取的基准都是中位数，这样每次都均匀的划分出两个分
*                    区，只需要logn次划分就能结束递归，时间复杂度为O(nlogn)
* 平均时间复杂度 ---- O(nlogn)
* 所需辅助空间 ------ 主要是递归造成的栈空间的使用(用来保存left和right等局部
*                    变量)，取决于递归树的深度，一般为O(logn)，最差为O(n)
* 稳定性 ---------- 不稳定
*
*********************************************************************/
void CSortFunction::QuickSort(int iArray[], int n)
{
    LOG_FUNC_BEGIN
    
    _QuickSort(iArray, 0, n - 1);
    
    LOG_FUNC_END
}
void CSortFunction::_QuickSort(int iArray[], int left, int right)
{
    if(left >= right)
        return;
    int iPivotIndex = _QuickPartition(iArray, left, right);
    _QuickSort(iArray, left, iPivotIndex - 1);
    _QuickSort(iArray, iPivotIndex + 1, right);
}
int CSortFunction::_QuickPartition(int iArray[], int left, int right)
{
    // 这里每次都选择最后一个元素作为基准
    //tail为小于基准的子数组最后一个元素的索引
    int iPivot = right, tail = left -1;
    for(int i=left;i<right;++i)
    {
        // 把小于等于基准的元素放到前一个子数组末尾
        if(iArray[i] < iArray[iPivot])
        {
            swap(iArray, ++tail, i);
        }
    }
    // 最后把基准放到前一个子数组的后边，剩下的子数组既是大于基准的子数组
    // 该操作很有可能把后面元素的稳定性打乱，所以快速排序是不稳定的排序算法
    swap(iArray, tail + 1, right);
    return tail + 1;
}
/********************************************************************
*
*                            归并排序
*   申请空间，大小为两个已经排序的序列之和，该空间用来存放已经排序的序列。设
* 两个指针，最初指向两个已排序的序列的起始位置。比较两个指针指向的元素，选择
* 相对小的元素放入合并空间中，并移动指针到下个位置。重复上述步骤，直到某一个
* 序列达到末尾，然后直接把另外一个序列合并至空间末尾。
*
* 数据结构 ---------- 数组
* 最差时间复杂度 ---- O(nlogn)
* 最优时间复杂度 ---- O(nlogn)
* 平均时间复杂度 ---- O(nlogn)
* 所需辅助空间 ------ O(n)
* 稳定性 ------------ 稳定
*
*********************************************************************/
void CSortFunction::MergeSort(int iArray[], int n)
{
    LOG_FUNC_BEGIN
    int *pTmpArray = new int[n];
    memcpy(pTmpArray, iArray, sizeof(int) * n);

    cout << "Recursion sort >>>\t";
    print(pTmpArray, n);
    _MergeRecursion(pTmpArray, 0, n - 1);
    cout << "After recursion sort:\t";
    print(pTmpArray, n);

    cout << "\n==========================================\n\n";

    cout << "Iteration sort >>>\t";
    print(iArray, n);
    _MergeIteration(iArray, n);
    cout << "After iteratioin sort:\t";
    print(iArray, n);
    
    delete pTmpArray;
    LOG_FUNC_END
}

void CSortFunction::_Merge(int iArray[], int left, int mid, int right)
{
    int i = left,j = mid + 1, index = 0, len = right - left + 1;
    int *pTmpSorted = new int[len];
    while(i <= mid && j <= right)
    {
        pTmpSorted[index++] = iArray[i] <= iArray[j] ? iArray[i++] : iArray[j++];
    }
    while(i <= mid)
    {
        pTmpSorted[index++] = iArray[i++];
    }
    while(j <= right)
    {
        pTmpSorted[index++] = iArray[j++];
    }
    for(int n=0;n<len;++n)
    {
        iArray[left++] = pTmpSorted[n];
    }
    delete pTmpSorted;
}
void CSortFunction::_MergeRecursion(int iArray[], int left, int right)
{
    if(left == right)
        return;
    int mid = (left + right) / 2;
    _MergeRecursion(iArray, left, mid);
    _MergeRecursion(iArray, mid + 1, right);
    _Merge(iArray, left, mid, right);
}
void CSortFunction::_MergeIteration(int iArray[], int len)
{
    int left, mid, right;
    for(int i=1;i<len;i*=2)
    {
        left = 0;
        while(left + i < len)
        {
            mid = left + i - 1;
            right = mid + i < len ? mid + i : len - 1;
            _Merge(iArray, left, mid, right);
            left = right + 1;
        }
    }
}

void CSortFunction::RadixSort(int iArray[], int n)
{
    LOG_FUNC_BEGIN
    
    
    
    LOG_FUNC_END
}

