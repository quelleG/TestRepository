// 1.编程实现顺序表的基本操作

#include<stdio.h>
#include "stdafx.h"
#include "malloc.h"
#include <conio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE  10 // 存储空间的初始分配量
#define LISTINCREMENT  10  // 分配增量
typedef char ElemType;     // 顺序表中存放的是整数
typedef struct{
	ElemType *elem;        // 存储空间基址
	int length;            // 当前长度
	int listsize;          // 当前分配的存储容量
}SqList;

void InitList(SqList &L){
	// 建立一个空的顺序表L
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (L.elem){
		L.length = 0;
		L.listsize = LIST_INIT_SIZE;
	}
}

void CreateSqList(SqList &L){
	// 初始条件：顺序表L已存在
	// 操作结果：将元素依次加入顺序表L
	int i = 0;
	while (true){
		char a,c;
		a = getchar();
		c = getchar();
		if (a != '?')
			L.elem[i] = a;
		else
			break;
		i++;
		L.length++;
		if (L.length >= L.listsize){
			L.elem = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT)*sizeof(ElemType));
			L.listsize += LISTINCREMENT;
		}
	}
}

void ListInsert(SqList &L, int i, ElemType e){
	// 初始条件：顺序表L已存在，1<=i<=ListLength(L)+1
	// 操作结果：在顺序表L中第i个位置之前插入新的数据元素e，表长加1
	ElemType *p, *q;
	if (i<1 || i>L.length + 1)
		printf("ERROR");
	if (L.length >= L.listsize){
		L.elem = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT)*sizeof(ElemType));
		L.listsize += LISTINCREMENT;
	}
	q = &(L.elem[i - 1]);
	for (p = &(L.elem[L.length - 1]); p >= q; --p)
		*(p + 1) = *p;
	*q = e;
	++L.length;
}

void ListDelete(SqList &L, int i, ElemType &e){
	// 初始条件：顺序表L已存在，1<=i<=ListLength(L)
	// 操作结果：删除顺序表L的第i个数据元素，并用e返回其值
	ElemType *p;
	if (i<1 || i>L.length + 1)
		printf("ERROR");
	e = L.elem[i - 1];
	for (p = &L.elem[i - 1]; p <= &L.elem[L.length - 1]; p++)
		*(p - 1) = *p;
	--L.length;
}

void PrintList(SqList L){
	// 初始条件：顺序表L已存在
	// 操作结果：打印顺序表
	int i;
	for (i = 0; i < L.length-1; i++)
		printf("%c -> ", L.elem[i]);
	printf("%c", L.elem[i]);
}

int Locate(SqList L, ElemType e){
	// 初始条件：顺序表L已存在
	// 操作结果：若顺序表L中存在数据元素e，则返回e在顺序表L中第一次出现的位序;否则返回0
	int i, result = 0;
	for (i = 0; i < L.length; i++){
		if (L.elem[i] == e){
			result = i + 1;
			break;
		}
	}
	return result;
}

void SearchByLocation(SqList L, int i, ElemType &e){
	// 初始条件：顺序表L已存在
	// 操作结果：若顺序表L中存在位序i，则返回位序i的元素e,否则返回0
	e =  L.elem[i - 1];
	L.length++;
}

int ListLength(SqList L){
	// 初始条件：顺序表L已存在
	// 操作结果：返回顺序表L的表长
	return L.length;
}

int main(){
	SqList L;
	int n, i;
	ElemType e;

	InitList(L);
	printf("Please input the element of list,(Use space to split，end with a '?'): "); 
	CreateSqList(L);

	printf("The elements of this list are: ");
	PrintList(L);
	printf("\n");

	printf("The length of this list is: %d\n", ListLength(L));

	printf("Please input a element which is you want to search: ");
	scanf_s("%c", &e);
	printf("The element you are input is: %c\n", e);
	printf("The location where the element is queried from the list is: %d\n", Locate(L, e));
	
	printf("Please input the location where you want to search: ");
	scanf_s("%d", &i);
	SearchByLocation(L, i, e);
	printf("The element that is searched from the list is: %c\n", e);

	printf("The length of this list is: %d\n", ListLength(L));
	printf("Please input the element and the location where you want the element insert.(Use space to split): ");
	e = getchar();
	scanf_s("%d",&i);
	ListInsert(L, i, e);
	printf("The elements of this list are: ");
	PrintList(L);
	printf("\n");

	printf("Please input the location of element which is you want to remove: ");
	scanf_s("%d", &i);
	printf("The location you are input is: %d\n", i);
	ListDelete(L, i, e);
	printf("The element that is removed from the list is: %c\n", e);
	printf("The elements of this list are: ");
	PrintList(L);
	printf("The length of this list is: %d\n", ListLength(L));
	
	printf("Press any key to end...\n");
	char ch = getchar();
	
	return 0;
}
