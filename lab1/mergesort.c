#include <stdlib.h>

void devide_and_conquer(int*, int, int, int*);
void merge(int*, int, int, int, int*);

void mergeSort(int* arr, int size) 
{
    /**
     * IN PLACE SORTING이 힘들기 때문에 TEMP ARRAY 변수 선언
     */
    int *temp = (int *) malloc(sizeof(int) * size);

    /**
     * MERGE SORT
     * - 최소 크기 배열로 나누는 작업은 devide 함수가 진행
     * - 합치는 작업은 merge 함수를 진행
     */
    devide_and_conquer(arr, 0, size - 1, temp);
}

void devide_and_conquer(int* arr, int p, int r, int* temp)
{
    int q;

    // 왼쪽 SUB ARRAY INDEX가 오른쪽 SUB ARRAY INDEX 범위를 침범하면 EARLY RETURN
    if (p >= r)
        return;

    // 범위 DEVIDE
    q = (p + r) / 2;

    /**
     * RECURSION
     * - 최소 범위가 될때 까지 나눈다.
     * - NESTED
     *      - 최소 범위 ARRAY 부터 SORTED ARRAY를 만들면서 합친다.
     */
    devide_and_conquer(arr, p, q, temp);
    devide_and_conquer(arr, q + 1, r, temp);

    // MERGE
    merge(arr, p, q, r, temp);
}

void merge(int* arr, int p, int q, int r, int* temp)
{
    int i, j, k;

    // 두 개의 SORTERD LIST에서 최소값을 뽑는 LOOP
    // MERGE를 실행할때 중간값이 LEFT에 포함되어있기 때문에 j = q + 1로 오른쪽 SUB ARRAY 범위로 보정한다.
    for (i = p, j = q + 1, k = p; (i <= q) && (j <= r);) {
        if (arr[i] < arr[j])
            temp[k++] = arr[i++];
        else 
            temp[k++] = arr[j++];
    }

    /**
     * 어느 한 쪽의 SORTED LIST가 모두 빠지면
     * 다른 한 쪽의 SORTED LIST의 나머지 ELEMENT 들을
     * 순서대로 뺄 수 있다.
     */
    while (i <= q) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];

    // MERGED ARRAY의 ELEMENT를 순서대로 SOURCE ARRAY에 할당한다.
    for (i = p; i <= r; i++)
        arr[i] = temp[i];
}