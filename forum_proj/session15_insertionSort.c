#include <stdio.h>
//swap function
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void insertionSort(int* intArr, int size) { 
    int i; int j; int k;
    for(i = 1; i < size; i++) {
        j = i;
        //if the counter has reached zero, then the swaps are considered done (it can't be done further).
        while(j > 0) {
            //if the current element is smaller than the previous one then swap, else break (it is in the correct relative position)
            //I have added some printf functions to show the process step by step.
            if(intArr[j] < intArr[j-1])  {
                printf("%d and %d swapped!\n", intArr[j-1], intArr[j]);
                swap(&intArr[j], &intArr[j-1]);
                printf("List now: ");
                for(k = 0; k < size; k++) {
                    printf("%d ", intArr[k]);
                }
                printf("\n");
            }

            else {
                printf("%d and %d not swapped!\n", intArr[j-1], intArr[j]);
                printf("\n");
                break;
            }
            printf("\n");
            j--;

        }
    }
}

int main() {
    int exampleList[] = {16, 11, 4, 18, 15}; // these could be of any size, but to be concise I chose 5 numbers.
    int arrSize = 5;
    
    //print initial list
    printf("Initial list: ");
    int i = 0;
    for(i = 0; i < arrSize; i++) {
        printf("%d ", exampleList[i]);
    }
    printf("\n\n");

    //sort
    insertionSort(exampleList, arrSize);

    //print sorted list
    printf("Sorted list: ");
    int j = 0;
    for(j = 0; j < arrSize; j++) {
        printf("%d ", exampleList[j]);
    }
    return 0;
}