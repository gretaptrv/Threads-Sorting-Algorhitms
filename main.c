#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

int length = 5;
pthread_t thread_id, thread_2id;

void *AlgorithmOne(void *vargp){ //thread_id function
	int *arrPtr = (int *)vargp;
	insertionSort(arrPtr);
	pthread_cancel(thread_2id); //terminates other thread
    printf("\n\n\n");
    printf("Insertion Sort Result: \n");
	for (int i = 0; i < length - 1; i++) {
        printf("%d, ", arrPtr[i]);
	}
	printf("%d", arrPtr[length - 1]);
}

void *AlgorithmTwo(void *vargp){
	int *arrPtr = (int *)vargp;
	cocktailShakerSort(arrPtr);
	//heapSort(arrPtr);
	//pthread_kill(thread_id);
	printf("\n\n\n");
	printf("Shaker Sort Result: \n");
	for (int i = 0; i < length - 1; i++) {
        printf("%d, ", arrPtr[i]);
	}
	printf("%d", arrPtr[length - 1]);
}

/*
void *sorting3(void *vargp) { //thread_2id function
    int *arrPtr = (int *)vargp;
    stoogeSort(arrPtr, 0, length - 1);
    pthread_cancel(thread_id);
    printf("\n\n\n");
	printf("Stooge Sort Result: \n");
	for (int i = 0; i < length - 1; i++) {
        printf("%d, ", arrPtr[i]);
	}
	printf("%d", arrPtr[length - 1]);
}
*/

void insertionSort(int *array) {
    for (int i = 1; i < length; i++) {
        int slider = array[i];
        int prev = i - 1;

        while (prev >= 0 && array[prev] > slider) {
            array[prev + 1] = array[prev];
            prev = prev - 1;
        }
        array[prev + 1] = slider;
    }
}

void cocktailShakerSort(int *array) {
    int result = cycle(array);
    while (result != 0) {
        cycle(array);
    }
}

int cycle(int *array) {
    if (forwardCycle(array) == 0) {
        return 0;
    }
    return backwardCycle(array);
}

int forwardCycle(int *array) {
    int tempHolder;
    int current = array[0];
    int counter = 0;

    for (int p = 1; p < length - 1; p++) {
        if (current > array[p]) {
            counter++;
            tempHolder = array[p];
            array[p] = current;
            current = tempHolder;
        } else {
            current = array[p];
        }
    }
    return counter;
}

int backwardCycle(int *array) {
    int tempHolder;
    int current = array[length - 2];
    int counter = 0;

    for (int p = length - 1; p >= 0; p--) {
        if (current < array[p]) {
            counter++;
            tempHolder = array[p];
            array[p] = current;
            current = tempHolder;
        } else {
            current = array[p];
        }
    }
    return counter;
}


/*
void heapify(int *array, int index) {
    int largest = index;
    int leftChildIndex = 2*index + 1;
    int rightChildIndex = 2*index + 2;
    if (array[leftChildIndex] > array[largest]) {
        largest = leftChildIndex;
    }
    if (array[rightChildIndex] > array[largest]) {
        largest = rightChildIndex;
    }

    if (largest != index) {
        int currRoot = array[index];
        array[index] = array[largest];
        array[largest] = currRoot;

        heapify(array, largest);
    }
}

void heapSort(int *array) {
    for (int i = length/2 - 1; i >= 0; i--) {
        heapify(array, i);
    }
    for (int i = length - 1; i > 0; i--) {
        int currRoot = array[0];
        array[0] = array[i];
        array[i] = currRoot;

        heapify(array, i);
    }
    //for (int i = 0; i < length; i ++) {
    //    printf("%d", array[i]);
    //}
}

void stoogeSort(int *array, int first, int second) {
    if (second <= first) {
        return;
    }

    if (array[first] > array[second]) {
        int tmp = array[first];
        array[first] = array[second];
        array[second] = tmp;
    }

    if ((second - first + 1) > 2) {
        int third = (second - first + 1)/3;
        stoogeSort(array, first, second - third);
        stoogeSort(array, first + third, second);
        stoogeSort(array, first, second - third);
    }
} */

int main(){
    FILE *myFile;
    myFile = fopen("numberArray.txt", "r");

    int *numbers = (int *)malloc((length)*sizeof(int));
    int i;

    if (myFile == NULL){
        printf("Error Reading File\n");
        exit (0);
    }

    for (i = 0; i < 5; i++){
        fscanf(myFile, "%d,", &numbers[i] );
    }

    fclose(myFile);

    int resultStatus;
    int resultStatus2;

	pthread_create(&thread_id, NULL, AlgorithmOne, (void *)numbers);
	pthread_create(&thread_2id, NULL, AlgorithmTwo, (void *)numbers);

	pthread_join(thread_id, &resultStatus);
	pthread_join(thread_2id, &resultStatus2);

    pthread_exit(0);
    pthread_exit(0);

    free (numbers);
    return 0;
}
