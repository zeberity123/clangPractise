/*
 * dcll.h
 *
 *  Created on: 2015. 2. 6.
 *      Author: elayer
 */

#ifndef DCLL_H_
#define DCLL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_SZ  20



typedef struct     //  날짜 구조체
{
	int year;			// 년
	int month;		// 월
	int day;				// 일
}DateT;

typedef struct     // 스케줄 구조체
{
	int num;       	// 사번
	DateT date;
	int startT;			// 시작 시간  ( 0 ~ 23 입력)
	int endT;           // 종료 시간  (0 ~ 23 입력)
	char *note;      	// 스케줄 내용
} Schedule;

typedef Schedule T_DATA;

typedef struct _Node {
    T_DATA data;
	struct _Node *prev;
	struct _Node *next;
} Node;
typedef Node* NodeP;
Node *Head;              				// 리스트의 헤드 포인터

#define LOOPDCLL(C, H) for(C = H->next; C != H; C=C->next)
#define LOOPDCLLSafe(C, N, H) for(C = H->next, N = C->next; \
C != H; C = N, N=N->next)
#define deleteNode(T) _deleteNode(T->prev, T->next); destroyNode(T)
#define insertAfterNode(newnode, T) _insertNode(newnode, T, T->next)
#define insertBeforeNode(newnode, T) _insertNode(newnode, T->prev, T)

void initDCLL(Node **H);
void destroyDCLL(Node * H);

Node* createNode( T_DATA data );
void destroyNode(Node *d );
void _insertNode(Node *newnode, Node *P, Node *N);
int searchNodes(Node** SAry, Node* H, DateT key); // 추가
void printList(Node * H);
void _deleteNode(Node *P, Node *N);
void updateNode(Node *f, T_DATA newvalue);
#endif /* DCLL_H_ */
