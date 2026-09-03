#ifndef _SORT_H
#define _SORT_H

#ifdef __cplusplus
extern "C"{
#endif

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define D 5 //希尔排序增量，可自行定义

void Iterative_MergeSort(int* arr,int n);
void Non_Iterative_MergeSort(int* arr,int n);
void Heap_Sort(int *arr,int n);
void Quick_Sort(int* arr,int n);
void Hill_Sort(int* arr,int n);
void Mid_Insert_Sort(int* arr,int n);
void Direct_Insert_Sort(int* arr,int n);


#ifdef __cplusplus
}
#endif

#endif /*SORT_H*/