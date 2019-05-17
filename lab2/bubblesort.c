
// example: {1, 5, 2, 4, 3} -> {1, 2, 3, 4, 5}
void bubbleSort(int *arr, int size) 
{
    int i, j;

    for (i = size; i > 0; i--) {
        for (j = 0; j < i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
