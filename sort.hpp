#ifndef SORT_H_
#define SORT_H_

typedef int T;

/*
 * 全部实现升序排序
 * 排序函数的参数n全都表示数组元素个数（实际最大下标+1）
 * */

/****************** drivers *****************/
void swap(T* a, T* b) {
    T t = *a;
    *a = *b;
    *b = t;
}

/****************** quick sort *****************/
void quicksort(T* arr, int n) {
    if (arr = nullptr) return;
    _quicksort(arr, 0, n - 1);
}

void _quicksort(T* arr, int low, int high) {
    if (low >= high) return; // 临界条件，数组元素个数<= 1
    int mid = partition(T* arr, low, high);
    _quicksort(T* arr, low, mid - 1);
    _quicksort(T* arr, mid + 1, high);
}

/*
 * 默认选取最后一个元素作为主元
 * */
int partition(T* arr, int low, int high) {
    int i = low - 1, j = low;
    T meta = arr[high];
    while (j < high) {
        if (arr[j] < meta) {
            i++;
            swap(arr + i, arr + j);
        }
        j++;
    }
    swap(arr + i + 1, arr + high); // 不要忘记这一步
    return i + 1;
}

/****************** merge sort *****************/
void mergesort(T* arr, int n) {
    if (arr == nullptr) return;
    T* sorted_arr = new T[n];
    if (sorted_arr == nullptr) {
        cout << "内存分配失败\n";
        return;
    }
    _mergesort(arr, sorted_arr, 0, n - 1);
    delete [] sorted_arr;
}

void _mergesort(T* unsorted, T* sorted, int low, int high) {
    if (low >= high) return; // 临界条件，数组元素个数<= 1
    int mid = (low + high) / 2;
    _mergesort(unsorted, sorted, low, mid);
    _mergesort(unsorted, sorted, mid + 1, high);

    // 归并过程
    int left = low, right = mid + 1;
    int k = low;
    while (left <= mid && right <= high) {
        if (unsorted[left] < unsorted[right]) {
            sorted[k++] = unsorted[left++];
        } else {
            sorted[k++] = unsorted[right++];
        }
    }
    while (left <= mid) {
        sorted[k++] = unsorted[left++];
    }
    while (right <= high) {
        sorted[k++] = unsorted[right++];
    }
    for (int i = low; i <= high; ++i) {
        unsorted[i] = sorted[i];
    }
}


/****************** heap sort *****************/
void heapsort(T* arr, int n) {
    if (arr = nullptr) return;
    for (int i = n / 2; i >= 0; --i) { // 首先要建立最大堆
        perc_down(arr, i, n);
    }
    for (int i = n - 1; i > 0; --i) {
        swap(arr, arr + i); // 将最大值移到数组末尾
        perc_down(arr, 0, i - 1); // 现在arr[o]为一个新的值，需要进行下推
    }
}

/* 将pos位置的元素下推
 * @param pos 要下推的元素的位置
 * @param n 数组的大小
 * */
void perc_down(T* arr, int pos, int n) {
    T temp = arr[pos];
    int child = 2 * pos + 1;
    for ( ; child < n; // 左儿子非空结点
            pos = child, child = 2 * pos + 1) {
        // 存在右儿子且右儿子的值大于左儿子
        if (child < n - 1 && arr[child] < arr[child + 1])
            child++;
        if (temp < arr[child])
            arr[pos] = arr[child]; //较大的子结点的值要上推
        else
            break; // 下推结束
    }
    arr[pos] = temp;
}

#endif

