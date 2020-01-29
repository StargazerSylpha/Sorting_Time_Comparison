/*
 * Project:EG-P291
 * !!! Do not open this cpp file in vc6.0 directly !!!
 * 
 * Environment:
 * Visual Studio Code for macOS 1.41.0
 * Extensions:
 * C/C++ 0.26.2
 * Code Runner 0.9.15
 * 
 * Create: 20191212 14:20
 * Made by Sylpha（Zhao Lu）in WJCYTU.
 * Blog:{base64|aHR0cHM6Ly9zeWxwaGEubmV0}
 * 
 * Ver 0.5 20200129 23:33
 * Debug.
 * 
 * Ver 0.4 20191217 10:07
 * Debug,and you can input number array by yourself.
 * 
 * Ver 0.3 20191216 19:28
 * Swap func can be used.
 * 
 * Ver 0.2 20191216 14:37
 * Merge sort debug.
 * 
 * Ver 0.1 20191216 11:41
 * Code and debug.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#define MAXSIZE 10001      //允许的数组大小最大值，由于内存原因目前最大可以到10w，再往上报错
#define NUMLIM 99       //自动生成数据最大值，可以尝试万级别，但相应的排序时间会成倍增加
#define ARROUT 1        //数组输出控制 1开启，0关闭
#define CLEAR system("clear");
typedef long int DATATYPE;

using namespace std;

//-------------------生成随机数------------------

DATATYPE getRandNum(DATATYPE _low,DATATYPE _high)       //获取datatype类型的随机数，传入参数为要获得的随机数的最小值和最大值
{
    DATATYPE randNum;
    srand(rand());      //置随机数种子
    //https://www.jb51.net/article/170295.htm
    randNum = rand() % (_high - _low + 1) + _low;       //获得指定范围内随机数的运算公式
    return randNum;
}

//------------------检验func:test---------------

bool checkArray(DATATYPE _array[], int _low, int _high)     //返回值类型为boolean的函数，传入参数包括排序完成的数、下标起始值、下标最大值
{
    int i;
    for (i = _low; i < _high - 1; i++)      //令i为下标的最低位，最大为下标的最高位-1，逐渐递增
    {
        if (_array[i] > _array[i + 1])      //因为完成的数组为递增的数组，所以这里判断前一位是否大于后一位
        {
            return false;       //大于则返回false，显示数组内有错误
        }
    }
    return true;    //否则返回true，表示数组排序正确
}

//----------------交换函数----------------

void swap(DATATYPE &a, DATATYPE &b)         //交换函数，传入参数为两个datatype变量的地址
{
    DATATYPE tmp;
    tmp = a;
    a = b;
    b = tmp;
}

//----------------冒泡排序----------------

void bubbleSort(DATATYPE _bubbleSortArray[], int _n)        //冒泡排序函数，传入参数为欲排序的数组 和 该数组的大小
{
    int i, j;
    //DATATYPE tmp;
    for (i = _n - 2; i >= 0; i--)       //外层变量控制每趟比较的最大下标
    {   
        for (j = 0; j <= i; j++)            //控制每次相邻元素比较的下标
        {
            if (_bubbleSortArray[j] > _bubbleSortArray[j + 1])      //如果左边元素比右边元素大，则交换
            {
                //tmp = _bubbleSortArray[j + 1];
                //_bubbleSortArray[j + 1] = _bubbleSortArray[j];
                //_bubbleSortArray[j] = tmp;
                swap(_bubbleSortArray[j + 1], _bubbleSortArray[j]);     //交换函数
            }
        }
    }

    cout << "冒泡排序";
    if(ARROUT)      //定义的输出控制常量，值为true或者1时允许输出排序后的变量
    {   
        cout << "后 序列：";
        for (i = 0; i < _n; i++)
        {
            cout << _bubbleSortArray[i] << " ";   //注释掉本行以屏蔽冒泡排序输出
        }
    }
    cout << endl;
    

    if (checkArray(_bubbleSortArray, 0, _n - 1))       //检查排序后的数组是否正确
        cout << "结果正确";
    else
        cout << "结果错误";
}

void bubbleSortTime(DATATYPE _bubbleSortArray[], int _n)    //_n：数组大小
{
    clock_t t;
    t = clock();
    bubbleSort(_bubbleSortArray, _n);
    t = clock() - t;
    //cout << " 耗时：" << (((float)t) / CLOCKS_PER_SEC) << endl;
    printf(" 耗时：%lf秒\n", ((double)t) / CLOCKS_PER_SEC);
    cout << "----------" << endl;
}

//--------------------快速排序-----------------------

int quickSortPart(DATATYPE _quickSortArray[], int _min, int _max)   //快排分块，_min 数组起始下标，_max 数组最大下标
{
    int i = _min, j = _max;
    DATATYPE tmp = _quickSortArray[i];
    while (i < j)
    {
        while (j > i && _quickSortArray[j] >= tmp)
            j--;
        _quickSortArray[i] = _quickSortArray[j];
        while (i < j && _quickSortArray[i] <= tmp)
            i++;
        _quickSortArray[j] = _quickSortArray[i];
    }
    _quickSortArray[i] = tmp;
    return i;
}

void quickSort(DATATYPE _quickSortArray[], int _min, int _max) //快排递归，_min 数组起始下标，_max 数组最大下标
{
    int i;
    if (_min < _max)
    {
        i = quickSortPart(_quickSortArray, _min, _max);
        quickSort(_quickSortArray, _min, i - 1);
        quickSort(_quickSortArray, i + 1, _max);
    } 
}

void quickSortTime(DATATYPE _quickSortArray[], int _n)      //求快速排序的绝对执行时间，传入参数为需要排序的数组，以及数组的大小
{
    clock_t t;      //定义时间类型t,clock_t是一个long int类型
    int j;
    t = clock();    //clock函数记录当前时间到t
    quickSort(_quickSortArray, 0, _n - 1);      //进行一次快速排序
    t = clock() - t;        //获取当前时间，并减去t之前记录的时间，得到程序绝对执行的时间并写入到t

    cout << "快速排序";
    if(ARROUT)      //判断数组输出标记是否打开，为真则输出排序后的数组
    {   
        cout << "后 序列：";
        for (j = 0; j < _n; j++)
        {   
            cout << _quickSortArray[j] << " ";    //注释掉本行以屏蔽快速排序输出
        }
    }
    cout << endl;
    

    if (checkArray(_quickSortArray, 0, _n - 1))     //检查数组排序是否正确的函数，传入参数为排序后的数组、下标起始值、下标最大值
        cout << "结果正确";
    else
        cout << "结果错误";

    printf(" 耗时：%lf秒\n", ((double)t) / CLOCKS_PER_SEC);          //以浮点型输出绝对执行时间，clocks_per_sec是一秒钟内cpu运行的时钟周期数
    cout << "----------" << endl;
}

//-----------------------直接插入排序---------------------

void insertSort(DATATYPE _insertSortArray[], int _n)        //直接插入排序的函数，传入参数为待排序的数组，以及数组的大小_n
{
    int i, j;
    DATATYPE tmp;       //定义临时变量tmp

    for (i = 1; i < _n; i++)
    {
        if (_insertSortArray[i] < _insertSortArray[i - 1])      //如果后一项小于前一项
        {
            tmp = _insertSortArray[i];      //挑出小的一方
            for (j = i - 1; j >= 0 && _insertSortArray[j] > tmp; j--)       //以较小一项的前一项开始，设定条件进行循环
            {
                _insertSortArray[j + 1] = _insertSortArray[j];      //进行交换
            }
            _insertSortArray[j + 1] = tmp;
        }
    }
}

void insertSortTime(DATATYPE _insertSortArray[], int _n)
{
    clock_t t;
    int j;
    t = clock();
    insertSort(_insertSortArray, _n);
    t = clock() - t;

    cout << "直接插入排序";
    if(ARROUT)
    {   
        cout << "后 序列：";
        for (j = 0; j < _n; j++)
        {   
            cout << _insertSortArray[j] << " ";      //注释掉本行以屏蔽快速排序输出
        }
    }
    cout << endl;
    

    if (checkArray(_insertSortArray, 0, _n - 1))
        cout << "结果正确";
    else
        cout << "结果错误";

    printf(" 耗时：%lf秒\n", ((double)t) / CLOCKS_PER_SEC);
    cout << "----------" << endl;
}

//-----------------------简单选择排序---------------------

void selectSort(DATATYPE _selectSortArray[], int _n)
{
    int i, j, k;
    int m;
    //DATATYPE tmp;
    for (i = 0; i < _n - 1; i++)
    {
        k = i;
        for (j = i + 1; j < _n; j++)
        {
            if (_selectSortArray[j] < _selectSortArray[k])
                k = j;
        }
        if (k != i)
        {
            //tmp = _selectSortArray[i];
            //_selectSortArray[i] = _selectSortArray[k];
            //_selectSortArray[k] = tmp;
            swap(_selectSortArray[i], _selectSortArray[k]);
        }
    }
}

void selectSortTime(DATATYPE _selectSortArray[], int _n)
{
    clock_t t;
    int j;
    t = clock();
    selectSort(_selectSortArray, _n);
    t = clock() - t;

    cout << "简单选择排序";
    if(ARROUT)
    {   
        cout << "后 序列：";
        for (j = 0; j < _n; j++)
        {   
            cout << _selectSortArray[j] << " ";      //注释掉本行以屏蔽快速排序输出
        }
    }
    cout << endl;
    

    if (checkArray(_selectSortArray, 0, _n - 1))
        cout << "结果正确";
    else
        cout << "结果错误";

    printf(" 耗时：%lf秒\n", ((double)t) / CLOCKS_PER_SEC);
    cout << "----------" << endl;
}

//-----------------------折半插入排序---------------------

void binaryInsertSort(DATATYPE _binaryInsertSortArray[], int _n)
{
    int i, j, low, high, mid;
    DATATYPE tmp;
    for (i = 1; i < _n; i++)
    {
        if (_binaryInsertSortArray[i] < _binaryInsertSortArray[i - 1])
        {
            tmp = _binaryInsertSortArray[i];
            low = 0;
            high = i - 1;
            while (low <= high)
            {
                mid = (low + high) / 2;
                if (tmp < _binaryInsertSortArray[mid])
                    high = mid - 1;
                else
                    low = mid + 1;
            }

            for (j = i - 1; j >= high + 1; j--)
                _binaryInsertSortArray[j + 1] = _binaryInsertSortArray[j];
            _binaryInsertSortArray[high + 1] = tmp;
        }
    }
}

void binaryInsertSortTime(DATATYPE _binaryInsertSortArray[], int _n)
{
    clock_t t;
    int j;
    t = clock();
    binaryInsertSort(_binaryInsertSortArray, _n);
    t = clock() - t;

    cout << "折半插入排序";
    if(ARROUT)
    {   
        cout << "后 序列：";
        for (j = 0; j < _n; j++)
        {   
            cout << _binaryInsertSortArray[j] << " ";      //注释掉本行以屏蔽快速排序输出
        }
    }
    cout << endl;
    

    if (checkArray(_binaryInsertSortArray, 0, _n - 1))
        cout << "结果正确";
    else
        cout << "结果错误";

    printf(" 耗时：%lf秒\n", ((double)t) / CLOCKS_PER_SEC);
    cout << "----------" << endl;
}

//-----------------------希尔排序---------------------

void shellSort(DATATYPE _shellSortArray[], int _n)
{   
    //https://blog.csdn.net/qq_39207948/article/details/80006224
    int i, j, d;
    DATATYPE tmp;
    d = _n / 2;

    while (d > 0)
    {
        for (i = d; i < _n; i++)
        {
            tmp = _shellSortArray[i];
            j = i - d;

            while (j >= 0 && tmp < _shellSortArray[j])
            {
                _shellSortArray[j + d] = _shellSortArray[j];
                j -= d;
            }
            _shellSortArray[j + d] = tmp;
        }
        d /= 2;
    }
}

void shellSortTime(DATATYPE _shellSortArray[], int _n)
{
    clock_t t;
    int j;
    t = clock();
    shellSort(_shellSortArray, _n);
    t = clock() - t;

    cout << "希尔排序";
    if(ARROUT)
    {   
        cout << "后 序列：";
        for (j = 0; j < _n; j++)
        {   
            cout << _shellSortArray[j] << " ";      //注释掉本行以屏蔽快速排序输出
        }
    }
    cout << endl;
    

    if (checkArray(_shellSortArray, 0, _n - 1))
        cout << "结果正确";
    else
        cout << "结果错误";

    printf(" 耗时：%lf秒\n", ((double)t) / CLOCKS_PER_SEC);
    cout << "----------" << endl;
}

//-----------------------堆排序---------------------

/*
递增排序用到最大堆：结点元素不小于其孩子
完全二叉树特性：左边子节点位置 = 2 * 当前父节点的位置 + 1
            右边子节点位置 = 2 * 当前父节点的位置 + 2（即左子节点 + 1）
*/

void heapSortSift(DATATYPE _heapSortArray[], int _low, int _high)       //堆排序筛选
{
    int parent = _low;
    int lchild = 2 * parent;      //parent：父结点，lchild：parent的左孩子
    DATATYPE tmp = _heapSortArray[parent];
    while (lchild <= _high)
    {
        if (lchild < _high && _heapSortArray[lchild] < _heapSortArray[lchild + 1])
            lchild++;   //rightChild较大，指向rightChild

        if (tmp < _heapSortArray[lchild])   //parent结点小于其孩子中较大的一方
        {
            _heapSortArray[parent] = _heapSortArray[lchild];    //较大child移到parent节点
            parent = lchild;    //修改值，使其向下继续筛选
            lchild = 2 * parent;
        }
        else
            break;      //如果parent结点>=最大child，筛选结束
    }
    _heapSortArray[parent] = tmp;   //被筛选值放入最终位置
}

void heapSort(DATATYPE _heapSortArray[], int _n)    //堆排序
{
    int i;
    for (i = _n / 2; i >= 1; i--)
        heapSortSift(_heapSortArray, i, _n);    //循环建立初始堆
    for (i = _n; i >= 2; i--)
    {
        //DATATYPE tmp;
        //tmp = _heapSortArray[1];
        //_heapSortArray[1] = _heapSortArray[i];
        //_heapSortArray[i] = tmp;    //将最后的元素与根[1]号元素交换
        swap(_heapSortArray[1], _heapSortArray[i]);
        heapSortSift(_heapSortArray, 1, i - 1);
    }
}

void heapSortTime(DATATYPE _heapSortArray[], int _n)
{
    clock_t t;
    int j;
    t = clock();
    heapSort(_heapSortArray, _n);
    t = clock() - t;

    cout << "堆排序";
    if(ARROUT)
    {   
        cout << "后 序列：";
        for (j = 1; j < _n + 1; j++)
        {   
            cout << _heapSortArray[j] << " ";      //注释掉本行以屏蔽快速排序输出
        }
    }
    cout << endl;
    

    if (checkArray(_heapSortArray, 1, _n))
        cout << "结果正确";
    else
        cout << "结果错误";

    printf(" 耗时：%lf秒\n", ((double)t) / CLOCKS_PER_SEC);
    cout << "----------" << endl;
}

//-----------------------二路归并排序---------------------

void merge(DATATYPE _mergeSortArray[], int _low, int _mid, int _high)   //归并_mergeSortArray[_low...._high]
{
    DATATYPE *msArray;
    int i = _low, j = _mid + 1, k = 0;
    msArray = (DATATYPE *)malloc((_high - _low + 1) * sizeof(DATATYPE));
    while (i <= _mid && j <= _high)
    {
        if (_mergeSortArray[i] < _mergeSortArray[j])
        {
            msArray[k] = _mergeSortArray[i];
            i++;
            k++;
        }
        else
        {
            msArray[k] = _mergeSortArray[j];
            j++;
            k++;
        }
    }
    while (i <= _mid)
    {
        msArray[k] = _mergeSortArray[i];
        i++;
        k++;
    }
    while (j <= _high)
    {
        msArray[k] = _mergeSortArray[j];
        j++;
        k++;
    }
    for (k = 0, i = _low; i <= _high; k++, i++)
        _mergeSortArray[i] = msArray[k];
    free(msArray);
}

void mergePass(DATATYPE _mergeSortArray[], int _length, int _n)
{
    int i;
    for (i = 0; i + 2 * _length - 1 < _n; i = i + 2 * _length)
        merge(_mergeSortArray, i, i + _length - 1, i + 2 * _length - 1);
    if (i + _length - 1 < _n - 1)
        merge(_mergeSortArray, i, i + _length - 1, _n - 1);
}

void mergeSort(DATATYPE _mergeSortArray[], int _n)
{
    int length;
    for (length = 1; length < _n; length = 2 * length)
        mergePass(_mergeSortArray, length, _n);
}

void mergeSortTime(DATATYPE _mergeSortArray[], int _n)
{
    clock_t t;
    int j;
    t = clock();
    mergeSort(_mergeSortArray, _n + 1);
    t = clock() - t;

    cout << "二路归并排序";
    if(ARROUT)
    {   
        cout << "后 序列：";
        for (j = 1; j < _n + 1; j++)
        {   
            cout << _mergeSortArray[j] << " ";      //注释掉本行以屏蔽快速排序输出
        }
    }
    cout << endl;
    

    if (checkArray(_mergeSortArray, 1, _n))
        cout << "结果正确";
    else
        cout << "结果错误";

    printf(" 耗时：%lf秒\n", ((double)t) / CLOCKS_PER_SEC);
    cout << "----------" << endl;
}

int main(void)
{
    int i, j, n, type;      //解除1
    //n = MAXSIZE; //!!!!!!!
    //n = 10;
    cout << "----------" << endl
         << "本程序运行较慢，请耐心等待。" << endl
         << "如遇到每次生成随机数组相同，请尝试重新编译或者重新打开程序。" << endl
         << "数据大小范围：1~" << NUMLIM << endl
         << "----------" << endl;
    
    cout << "请输入选项前序号选择功能：" << endl
         << "1.系统自动生成随机数进行排序" << endl
         << "2.自行输入随机数进行排序" << endl;
    cin >> type;
    if (type != 1 && type != 2)
    {
        cout << "功能选择错误！" << endl;
        return 0;
    }

    CLEAR
    cout << "----------" << endl
         << "请输入需要排序的数组的大小：(>0 && < " << MAXSIZE << ")" << endl;
    cin >> n;
    CLEAR
    /*
        if(n % 2 != 0)
        {
            cout << "数组大小需为双数，请重新设置！" << endl;
            return 0;
        }
        */

    if (n > MAXSIZE)
    {
        cout << "数组大小超过限制，请重新输入！" << endl;
        return 0;
    }
    if (n <= 0)
    {
        cout << "输入错误，请重新输入！" << endl;
        return 0;
    }
    DATATYPE dataArray[MAXSIZE]; //
    if(type == 1)
    {
        //----生成随机数组----
        
        cout << "----------" << endl
             << "功能1：" << endl;
        
        for (j = 0; j < 3; j++)
            for (i = 0; i < n; i++)
            {
                dataArray[i] = getRandNum(1, NUMLIM);
            }

        cout << "原序列：";
        if (ARROUT)
        {
            for (i = 0; i < n; i++)
            {
                cout << dataArray[i] << " "; //注释掉本行以屏蔽原序列输出
            }
        }
        else
            cout << "已隐藏" << endl;

        cout << endl
            << "----------" << endl;
    }
    else if (type == 2)
    {
        cout << "----------" << endl
             << "功能2：" << endl
             << "请输入大小为" << n << "的需要排序的数组：" << endl;
        
        dataArray[0] = 0;
        for (i = 0; i < n; i++)
        {
            cin >> dataArray[i];
        }
        cout << "----------" << endl;
        
    }
    

    //----填充冒泡排序用数组----
    DATATYPE bubbleSortArray[MAXSIZE];
    
    for (i = 0; i < n; i++)
    {
        bubbleSortArray[i] = dataArray[i];
    }

    //----填充快速排序用数组----
    DATATYPE quickSortArray[MAXSIZE];
    
    for (i = 0; i < n; i++)
    {
        quickSortArray[i] = dataArray[i];
    }

    //----填充直接插入排序用数组----
    DATATYPE insertSortArray[MAXSIZE];
    
    for (i = 0; i < n; i++)
    {
        insertSortArray[i] = dataArray[i];
    }

    //----填充简单选择排序用数组----
    DATATYPE selectSortArray[MAXSIZE];
    
    for (i = 0; i < n; i++)
    {
        selectSortArray[i] = dataArray[i];
    }

    //----填充折半插入排序用数组----
    DATATYPE binaryInsertSortArray[MAXSIZE];
    
    for (i = 0; i < n; i++)
    {
        binaryInsertSortArray[i] = dataArray[i];
    }

    //----填充希尔排序用数组----
    DATATYPE shellSortArray[MAXSIZE];
    
    for (i = 0; i < n; i++)
    {
        shellSortArray[i] = dataArray[i];
    }
    
    //----填充堆排序用数组----
    DATATYPE heapSortArray[MAXSIZE];
    
    for (i = 0; i < n; i++)
    {   
        //https://jianshu.com/p/0d383d294a80
        //https://www.cnblogs.com/Java3y/p/8639937.html
        heapSortArray[i + 1] = dataArray[i];
    }

    //----填充二路归并排序用数组----
    DATATYPE mergeSortArray[MAXSIZE];
    
    for (i = 0; i < n; i++)
    {   
        mergeSortArray[i] = dataArray[i];
    }

    //----冒泡排序----
    bubbleSortTime(bubbleSortArray,n);

    //----快速排序----
    quickSortTime(quickSortArray, n);

    //----直接插入排序----
    insertSortTime(insertSortArray, n);

    //----简单选择排序----
    selectSortTime(selectSortArray, n);

    //----折半插入排序----
    binaryInsertSortTime(binaryInsertSortArray, n);

    //----希尔排序----
    shellSortTime(shellSortArray, n);

    //----堆排序----
    heapSortTime(heapSortArray, n);

    //----二路归并排序----
    mergeSortTime(mergeSortArray, n);

    cout << "运行完成" << endl
         << "----------" << endl;
    return 0;
}
