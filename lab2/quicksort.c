#include <stdlib.h>
#include <time.h>

void swap(int*, int, int);
void doQuickSort(int*, int, int);
int doPartitioning(int*, int, int);

void quickSort(int* arr, int size) 
{
    // Initial Doing Quicksort Function
    doQuickSort(arr, 0, size - 1);
}

/**
 * 요소들간의 자리를 변경하기 위한 Swap Function
 */
void swap(int* arr, int source, int target)
{
    int temp = arr[source];
    arr[source] = arr[target];
    arr[target] = temp;
}

/**
 * QuckSorting function
 */
void doQuickSort(int* arr, int p, int r)
{
    int q;
    if (p < r) {
        // 파티셔닝 이후 pivot 인덱스의 값을 받는다.
        q = doPartitioning(arr, p, r);

        // 기준이 된 pivot 인덱스의 양쪽으로 다시 Quick Sorting (Recursion)
        doQuickSort(arr, p, q - 1);
        doQuickSort(arr, q + 1, r);
    }
}

/**
 * Randomized Quick Sorting 을 위한 Partition Function
 * 
 * Output:
 * p(pivot)을 기준으로 좌측은 pivot보다 작거나 같은 원소
 * 우측은 pivot보다 큰 원소
 * 
 * Problem:
 * Quick Sort는 Sorted Order List, Reserved Sorted Order List를 대상으로
 * Pivot을 특정한 값으로 고정시킬 경우 (좌측 또는 우측 맨 끝) 이미 정렬된 리스트를 순차적으로
 * 다시 정렬하게 된다. => O(n^2)의 Worst Case
 * 
 * Solved:
 * 요소를 무작위로 뽑아 Pivot을 만든다면 이미 정렬된 리스트여도 비슷한 O를 보장한다.
 */
int doPartitioning(int* arr, int p, int q)
{
    int randomPicked, x, i = p, j = p + 1;

    // timestamp 값을 기반으로 난수를 초기화하면 실행해도 계속 똑같은 값을 반환하는 rand를 어느 정도 난수화 시킬수 있다.
    srand(time(NULL));
    // p와 q가 range를 나타내는 인덱스이기 때문에 random index도 그 안에서 뽑아야한다.
    randomPicked = ((rand() % (q - p + 1))) + p;

    // 무작위로 뽑은 값을 pivot을 위해 맨 앞으로 보낸다.
    x = arr[randomPicked];
    swap(arr, p, randomPicked);

    // 기존 Quick Sort 로직과 똑같다.
    // count(q-p) 만큼 돌면서 pivot보다 작거나 같은 요소가 있다면 좌측으로 보낸다.
    for (; j <= q; j++) {
        if (arr[j] <= x) {
            swap(arr, ++i, j);
        }
    }

    // 최종적으로 pivot보다 작은 요소중 제일 큰 인덱스 값으로 pivot이 바뀌면서 기준이 된다.
    swap(arr, p, i);

    // pivot 인덱스 값을 리턴
    return i;
}
