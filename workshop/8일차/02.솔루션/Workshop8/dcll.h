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



typedef struct     //  ��¥ ����ü
{
	int year;			// ��
	int month;		// ��
	int day;				// ��
}DateT;

typedef struct     // ������ ����ü
{
	int num;       	// ���
	DateT date;
	int startT;			// ���� �ð�  ( 0 ~ 23 �Է�)
	int endT;           // ���� �ð�  (0 ~ 23 �Է�)
	char *note;      	// ������ ����
} Schedule;

typedef Schedule T_DATA;

typedef struct _Node {
    T_DATA data;
	struct _Node *prev;
	struct _Node *next;
} Node;
typedef Node* NodeP;
Node *Head;              				// ����Ʈ�� ��� ������

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
int searchNodes(Node** SAry, Node* H, DateT key); // �߰�
void printList(Node * H);
void _deleteNode(Node *P, Node *N);
void updateNode(Node *f, T_DATA newvalue);
#endif /* DCLL_H_ */
