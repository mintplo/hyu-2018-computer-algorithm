#include <stdio.h>
#include <stdlib.h>

/**
 * countSort Implementing Function
 * 
 * 전제 조건: Input 값중에 0은 없다고 가정하였다.
 * 0이 있다면 0을 포함한 배열을 만들어야하기 때문에 size + 1 만큼의 배열을 만들어야 한다.
 */
void countSort(int* arr, int size)
{
    int i;
    // 카운팅, 결과 임시 저장을 위한 배열 선언
    int* counting = (int *) malloc(sizeof(int) * size);
    int* resultArr = (int *) malloc(sizeof(int) * size);

    // 실제 Number Counting 단계에서 += 1 연산을 위해
    // 카운팅 배열의 초기 값을 모두 0으로 초기화 해야한다.
    for (i = 0; i <= size - 1; i++) {
        counting[i] = 0;
    }

    /**
     * Number Counting For-loop
     * 
     * 이슈:
     * 1. 0을 고려하지 않고 입력값은 1부터 있다고 가정
     * 2. 하지만 배열의 인덱스는 0부터 시작, 배열의 인덱스 0을 1로 고려하기 위한 인덱스 조작이 필요
     */
    for (i = 0; i <= size - 1; i++) {
        // (arr[i] - 1) 배열의 인덱스 0을 1로 고려
        counting[arr[i] - 1] += 1;
    }

    // 카운팅된 배열을
    // 다음 배열의 원소 값 = (이전 배열 원소값 + 다음 배열의 원소값) 순차적으로 연산.
    for (i = 0; i < size - 1; i++) {
        counting[i + 1] += counting[i];
    }

    // 카운팅된 배열이 실제 그 숫자의 Index Offset Range로 환산되었다면
    // (arr 배열에 정렬된 배열로 넣기 전) 임시로 정렬된 결과를 담을 배열에 저장하기 위한 과정이 필요하다.
    for (i = size - 1; i >= 0; i--) {
        // (arr[i] - 1) 배열의 인덱스 0을 1로 고려
        // counting offset 역시 index가 0부터 시작하는 개념이 고려되지 않았기 때문에 -1로 보정한다.
        resultArr[counting[arr[i] - 1] - 1] = arr[i];
        // (arr[i] - 1) 배열의 인덱스 0을 1로 고려
        counting[arr[i] - 1] -= 1;
    }

    // 임시로 저장한 결과 배열을 arr 배열로 옮김
    for (i = 0; i <= size - 1; i++) {
        arr[i] = resultArr[i];
    }
}
