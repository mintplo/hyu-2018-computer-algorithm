#include <stdio.h>

void max_heapify(int*, int, int);
void build_max_heap(int*, int);
void swap(int*, int , int);

void heapSort(int* arr, int size)
{   
    /**
     * t_size 변수는 ARRAY의 인덱스가 0부터 시작하기 때문에 보정을 위해 선언
     */
    int i, j, t_size = size - 1;

    /**
     * 오름차순 정렬을 위해 MAX HEAP 트리를 만든다.
     */
    build_max_heap(arr, t_size);

    /**
     * 만들어진 HEAP TREE를 바탕으로 ASCENDING HEAP SORT를 진행한다.
     */
    for (i = t_size; i >= 1; i--) {
        swap(arr, 0, t_size);
        max_heapify(arr, 0, --t_size);
    }
}

/**
 * heapSort 함수와 max_heapify 함수 내에서 중복으로 사용하는 SWAP 함수 선언
 */
void swap(int* arr, int a, int b) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void max_heapify(int* arr, int parent, int size)
{
    /**
     * 배열의 인덱스가 0부터 시작하기 때문에
     * LEFT = parent + 1
     * RIGHT = parent + 2
     */
    int max = parent;
    int left =  (parent * 2) + 1;
    int right = (parent * 2) + 2;

    /**
     * 전 이중 트리가 아니기 때문에 CHILD가 존재하는지 확인하는 조건식을 넣어야 함.
     * PARENT, LEFT CHILD, RIGHT CHILD 중 가장 큰 값을 확인하는 로직은 IF문을 두번 수행하여
     * 최고값을 정한다.
     */
    if ((left <= size) && (arr[parent] < arr[left])) {
        max = left;
    }

    if ((right <= size) && (arr[max] < arr[right])) {
        max = right;
    }

    if (max != parent) {
        swap(arr, parent, max);
        max_heapify(arr, max, size);
    }
}

void build_max_heap(int* arr, int size)
{
    /**
     * CHILD 바로 위에 있는 PARENT NODE부터 BOTTOM - UP 으로 HEAPIFY를 진행하며
     * 배열의 인덱스가 0부터 시작하기 때문에 아래와 같은 연산을 한다.
     */
    int i = (int)((size - 1) / 2);

    for (; i >= 0; i--)
        max_heapify(arr, i, size);
}
