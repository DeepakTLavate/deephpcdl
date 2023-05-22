#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <omp.h>
     
    using namespace std;
     
    // Function to perform sequential bubble sort
    void sequential_bubble_sort(int arr[], int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
     
    // Function to perform parallel bubble sort
    void parallel_bubble_sort(int arr[], int n) {
        #pragma omp parallel
        {
            for (int i = 0; i < n - 1; i++) {
                int thread_num = omp_get_thread_num();
                int num_threads = omp_get_num_threads();
                for (int j = thread_num; j < n - i - 1; j += num_threads) {
                    if (arr[j] > arr[j + 1]) {
                        int temp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = temp;
                    }
                }
            }
        }
    }
     
    // Function to merge two sorted arrays
    void merge(int arr[], int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;
        int L[n1], R[n2];
        for (int i = 0; i < n1; i++) {
            L[i] = arr[l + i];
        }
        for (int j = 0; j < n2; j++) {
            R[j] = arr[m + 1 + j];
        }
        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
     
    // Function to perform sequential merge sort
    void sequential_merge_sort(int arr[], int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            sequential_merge_sort(arr, l, m);
            sequential_merge_sort(arr, m + 1, r);
            merge(arr, l, m, r);
        }
    }
     
    // Function to perform parallel merge sort
    void parallel_merge_sort(int arr[], int l, int r,int threads) {
        if (l < r) {
            int m = l + (r - l) / 2;
            if(threads>1 && r-l+1>=threads*1000){
                #pragma omp parallel sections
            {
                #pragma omp section
                {
                    parallel_merge_sort(arr, l, m,threads/2);
                }
                #pragma omp section
                {
                    parallel_merge_sort(arr, m + 1, r,threads- threads/2);
                }
            }
            }
            else{
                sequential_merge_sort(arr, l, m);
                sequential_merge_sort(arr, m + 1, r);
                merge(arr, l, m, r);
            }
        }
    }
     
    
    void printArr(int arr[],int n)
    {
        for(int i=0;i<n;i++)
        {
            cout<<arr[i]<<" ";
        }
    }
     
     
    // Example usage
    int main(){
        int n = 10;
        int arr[n];
        for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;
        sequential_bubble_sort(arr,n);
        cout<<"Sequential Bubble sort : ";
        printArr(arr,n);
        cout<<endl;

        for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;
        parallel_bubble_sort(arr,n);
        cout<<"Parallel Bubble Sort : ";
        printArr(arr,n);
        cout<<endl;

        for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;
        sequential_merge_sort(arr,0,n);
        cout<<"Sequential Merge Sort : ";
        printArr(arr,n);
        cout<<endl;

        for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;
        int threads = omp_get_max_threads();
        parallel_merge_sort(arr,0,n,threads);
        cout<<"Parallel Merge Sort : ";
        printArr(arr,n);
        


        return 0;
    }