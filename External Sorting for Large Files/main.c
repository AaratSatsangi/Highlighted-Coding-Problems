#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define chunk_size 20000000 /// Integers


int number_of_integers,number_of_files;

void swap(int* a , int* b)
{
    if (*a != *b)
    {
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}

void heapify(int*arr , int n , int i)
{
    int largest = i;
    int left_child = 2*i + 1;
    int right_child = 2*i + 2;

    if (left_child < n &&  arr[left_child] > arr[largest])
        largest = left_child;
    if (right_child < n &&  arr[right_child] > arr[largest])
        largest = right_child;

    if (largest != i)
    {
        swap(&arr[i] , &arr[largest]);
        heapify(arr , n , largest);
    }
}

void heap_sort(int*arr , int n)
{
    /// Build MaxHeap

    int i;
    for (i = n/2 - 1 ; i >= 0 ; i--)
        heapify(arr , n , i);

    /// Remove one element from heap one by one

    for (i = n-1 ; i > 0 ; i--)
    {
        swap(&arr[i] , &arr[0]);
        heapify(arr , i , 0);
    }

}

int count_integers(FILE* fp_input)
{
    int a, count = 0;
    while(!feof(fp_input))
    {
        fscanf(fp_input , "%d" , &a);
        count++;
    }
    fseek(fp_input, 0 ,SEEK_SET);

    return count;
}

void split_sort_file(FILE* fp_input)
{
    FILE* fp_array[number_of_files];
    int tempNumberOfIntegers=number_of_integers;
    int i , j , n , a;

    ///Open Files for writing.
    char buffer[10];
    for(i = 0 ; i < number_of_files ; i++)
    {
        snprintf(buffer, sizeof(buffer),"%d.txt", i);
        fp_array[i] = fopen(buffer , "w");
    }


    int* arr;
    int check = 0;

    for(i = 0 ; i < number_of_files ; i++)
    {

        /// Determine number of integers left (MAX = 15 million)

        if(tempNumberOfIntegers >= chunk_size)
            {
                n = chunk_size;
                tempNumberOfIntegers -= chunk_size;
            }

        else
            {
                n = tempNumberOfIntegers;
                tempNumberOfIntegers = 0;
            }



        printf("\nnumber of integers left = %d\n" , tempNumberOfIntegers);
        /// Declare array for copying integers from file in heap.
        arr = (int*)malloc(n * sizeof(int));


        ///Put integers into array.
        for(j = 0 ; j < n ; j++)
        {
            fscanf(fp_input , "%d" , &a);
            arr[j] = a;
        }


        ///Sort Array
        printf("\nSORTING :: %d ",i);
        heap_sort(arr , n);
//        quick_sort(arr , 0 , n-1);
//        merge_sort(arr, 0 , n-1);
        printf("\nSORTED\n");


        ///Write sorted array into files
        for(j = 0 ; j < n ; j++)
        {
            fprintf(fp_array[i] , "%d\n",arr[j]);
            check++;
        }
        printf("Written :: %d , N = %d\n" , check,n);
        free(arr);
        fclose(fp_array[i]);
    }
   // free(fp_array);
}

int find_min_idx(int*arr , bool* flag_arr)
{
    int i, min, min_idx = -1;

    /// Set the min and min_idx from such a file which has not yet reached EOF.
    for (i = 0 ; i < number_of_files ; i++)
    {
        if(!flag_arr[i])
        {
            min = arr[i];
            min_idx = i;
            break;
        }
    }

    if (min_idx == -1)
        return -1;

    ///Calculate the minimum value and return its index
    for (i = 1 ; i < number_of_files ; i++)
    {
        if(arr[i] < min && !flag_arr[i])
        {
            min = arr[i];
            min_idx = i;
        }
    }
//    printf("\nIN find_min -- min_idx = %d , min - %d\n\n" , min_idx , min);
    return min_idx;
}

void k_way_merge(FILE** fp_in , FILE* fp_out)
{
    int i;

    int arr[number_of_files]; /// array to store integers from file and from which to get the minimum element from.
    bool flag_arr[number_of_files]; /// array to denote which file has reached its end.
//printf("Checkpoint 2 \n");
    for (i = 0 ; i < number_of_files ; i++)
    {
        flag_arr[i] = false;
        arr[i] = 0;
    }
//printf("Checkpoint 3 \n");
    int min_flag = -1; /// min_flag = -1 denotes the first call of this function.

    for (i = 0 ; i < number_of_integers ; i++)
    {
        /// Put value into array from which the last element was taken.
        if (min_flag != -1 && !feof(fp_in[min_flag]))
        {
            fscanf(fp_in[min_flag] , "%d" , arr+min_flag);
        }

        /// if that file has reached its end, then set the min_flag to true, which will indicate to not use that value.
        else if(min_flag != -1 && feof(fp_in[min_flag]))
        {
            flag_arr[min_flag] = true;
        }

        /// If its the first function call (i.e min_flag = -1) then put all the first elements from the files into array.
        else
        {
            printf("Checkpoint 4 \n");
            int a;
            for (int k = 0; k < number_of_files ; k++)
            {
                fscanf(fp_in[k] , "%d" , &a);
                arr[k] = a;
            }
        }

        min_flag = find_min_idx(arr , flag_arr);
       // printf("min = %d\n" , arr[min_flag]);
        fprintf(fp_out , "%d\n",arr[min_flag]);
    }
//    printf("Checkpoint 5 \n");
}

void merge_files()
{
  ///Open Files for reading.
    char buffer[10];
    int i;
    FILE* fp_in[number_of_files];
    for(i = 0 ; i < number_of_files ; i++)
    {
        snprintf(buffer, sizeof(buffer),"%d.txt", i);
        fp_in[i] = fopen(buffer , "r");

        if (fp_in[i] == NULL)
        {
            printf("----%s File Not Found!----\n" , buffer);
            return ;
        }
    }
printf("Checkpoint 1 \n");
    FILE* fp_out = fopen("out.txt" , "w");

    k_way_merge(fp_in , fp_out);
printf("Checkpoint 6 \n");
    fclose(fp_out);

    // for(i = 0 ; i < number_of_files ; i++)
    // {
    //     snprintf(buffer, sizeof(buffer),"%d.txt", i);
    //     remove(buffer);
    // }
}

int main()
{
    char file_name[50];
    printf("Enter File Name :: ");
    scanf("%[^\n]%*c", file_name);

    FILE *fp_input = fopen(file_name , "r");

    if (fp_input == NULL) {
        printf("File Not Found!\n");
        return -1;
    }

    fseek(fp_input ,0 , SEEK_END);
    int file_size = ftell(fp_input);
    printf("SIZE :: %d \n\n", file_size);

    fseek(fp_input ,0 , SEEK_SET);

    number_of_integers = count_integers(fp_input);
    printf("\nTotal Integers = %d\n" , number_of_integers);

    number_of_files = (number_of_integers+chunk_size-1)/chunk_size;
    printf("Number of Files :: %d\n" , number_of_files);

    printf("----- START!! ------\n\n");

    split_sort_file(fp_input);
     fclose(fp_input);
    // // free(fp_input);

    printf("\n\nMerging Files Now...\n\n");
    merge_files();
    printf("\n---------------COMPLETE-------------\n\n");

    return 0;
}
