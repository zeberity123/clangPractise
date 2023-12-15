/*
 * dDCLL.c
 *
 *  Created on: 2015. 2. 6.
 *      Author: elayer
 */


#include "dcll.h"

void initDCLL(Node **H) {
	*H = (Node*)malloc(sizeof(Node));
	(*H)->next = *H;
	(*H)->prev = *H;
}
Node * createNode( T_DATA data ){
	Node *t = (Node*)malloc(sizeof(Node));

	// todo: t 노드의 멤버를 초기화 한다.
	t->data = data;
	t->next = NULL;
	t->prev = NULL;
	return t;
}

void destroyNode( Node* d ){
	// todo: 메모리 누수가 없도록 할당 받은 동적 메모리에 대해 free함
	free(d->data.note);
	free(d);
}

void _insertNode(Node *newnode, Node *P, Node *N) {
	newnode->prev = P;
	newnode->next = N;
	P->next = newnode;
	N->prev = newnode;
}

//#define LOOPDCLL(C, H) for(C = H->next; C != H; C=C->next)

int searchNodes(Node** SAry, Node* H, DateT key) {
	Node *C = NULL;
	DateT T;  //  C->data.date를 임시로 저장할 변수
    int cnt = 0;

	// todo: 날짜가 같은 것에 대해서 SAry 배열에 복사 후, 그 개수를 반환함
	LOOPDCLL(C, H) {
		T = C->data.date;
		if ( (T.day == key.day) && (T.month == key.month) && (T.year == key.year)) {
			SAry[cnt++] = C;
		}
	}
	return cnt;
}

void printList(Node * H) {
	Node *C = NULL;
	LOOPDCLL(C, H) {
		printf("%s ", C->data.note); fflush(stdout);
	}
	printf("\n");
	fflush(stdout);
}

void _deleteNode(Node *P, Node *N) {
	P->next = N;
	N->prev = P;
}


//#define LOOPDCLLSafe(C, N, H) for(C = H->next, N = C->next; \
//C != H; C = N, N=N->next)

void destroyDCLL(Node * H) {
	Node *C, *N;
	LOOPDCLLSafe(C, N, H)   {
		printf("delete : %s\n", C->data.note);
		deleteNode(C);
	}
}
