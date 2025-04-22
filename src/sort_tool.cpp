// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
//  Modify     [2024/9/2 Meng-Chen Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#include<vector>
#include <random>
#include <limits>
#include <cmath>
using namespace std;
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    int n = data.size();   
    for(int j = 1; j<n; j++){
        int key = data[j];
        int i = j-1;
        while(i>=0 && data[i]>key){
            data[i+1] = data[i];
            i = i-1;
        }
        data[i+1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data,int f){
    QuickSortSubVector(data, 0, data.size() - 1, f);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS
    if(flag==0){
        if(low<high){
            int q = Partition(data, low, high);
            QuickSortSubVector(data, low, q-1, 0);
            QuickSortSubVector(data, q+1, high, 0);
        }
    }
    else if(flag==1){
        if(low<high){
            int q = RandomizedPartition(data, low, high);
            QuickSortSubVector(data, low, q-1, 1);
            QuickSortSubVector(data, q+1, high, 1);
        }
    }

}
int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    int i = low + rand() % (high-low+1);
    int temp = data[high];
    data[high] = data[i];
    data[i] = temp;
    return Partition(data, low, high);

}
int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    //high and low are only index
    int x = data[high];
    int i = low-1;
    for(int j = low; j< high; j++){
        if(data[j]<=x){
            i=i+1;
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }
    int temp2=data[i+1];
    data[i+1] = data[high];
    data[high] = temp2;

    return i+1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed

    if(low<high){
        int q = floor((low+high)/2);
        MergeSortSubVector(data, low, q);
        MergeSortSubVector(data, q+1, high);
        Merge(data, low, q, q+1, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n1 = middle1 - low + 1;//n1=6
    int n2= high - middle2 +1;//n2=6
    vector<int> L(n1+1,0);
    vector<int> N(n2+1,0);

    for(int i=0; i<n1; i++){
        L[i] = data[low+i];
    }
    for(int j = 0; j<n2; j++){
        N[j] = data[middle2+j];
    }

    L[n1] = numeric_limits<int>::max();
    N[n2] = numeric_limits<int>::max();

    int i = 0;
    int j = 0;

    for(int k = low; k<=high; k++){
        if(L[i]<=N[j]){
            data[k] = L[i];
            i++;
        }
        else{
            data[k] = N[j];
            j++;
        }
    }

}

// bottom-up style implementation of merge sort
void SortTool::BottomUpMergeSort(vector<int>& data) 
{
    int numGroup = data.size();   // total number of elements
    int groupMem = 1;             // size of the groups to be merged (starts with 1 element)

    // Loop until group size exceeds the number of elements
    while (groupMem < numGroup) {
        int i = 0;

        // Iterate through the array in steps of groupMem * 2
        while (i < numGroup) {
            int mid = i + groupMem - 1;
            int rightEnd = min(i + groupMem * 2 - 1, numGroup - 1);

            if (mid < rightEnd) {
                Merge(data, i, mid, mid + 1, rightEnd);
            }

            i = i + groupMem * 2;  // Move to the next pair of groups
        }

        groupMem = groupMem * 2;  // Double the group size for the next iteration
    }
}


// Heap sort method, be aware that you are NOT required to implement heap sort in PA1
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
}
