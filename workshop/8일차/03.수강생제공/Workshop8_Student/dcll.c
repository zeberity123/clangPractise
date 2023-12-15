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

	return t;
}

//  d : 메모리 동적 할당 받은 것에 대해서 해제할 노드
void destroyNode( Node* d ){
	// todo: 메모리 누수가 없도록 할당 받은 동적 메모리에 대해 free함

}

void _insertNode(Node *newnode, Node *P, Node *N) {
	newnode->prev = P;
	newnode->next = N;
	P->next = newnode;
	N->prev = newnode;
}

#define LOOPDCLL(C, H) for(C = H->next; C != H; C=C->next)

// SAry : key로 입력된 날짜에 해당하는 스케줄 노드를 저장할 배열
// H : Head
// key : 검색에 사용될 날짜 (년, 월, 일)
int searchNodes(Node** SAry, Node* H, DateT key) {
	Node *C = NULL;  //  LOOP을 돌면서 각 노드 저장에 사용할 임시 변수
	DateT T;  				//  C->data.date를 임시로 저장할 변수
    int cnt = 0;			//  배열에 저장된 노드 개수

	// todo: 날짜가 같은 것에 대해서 SAry 배열에 복사 후, 그 개수를 반환함

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


#define LOOPDCLLSafe(C, N, H) for(C = H->next, N = C->next; \
C != H; C = N, N=N->next)

void destroyDCLL(Node * H) {
	Node *C, *N;
	LOOPDCLLSafe(C, N, H)   {
		printf("delete : %s\n", C->data.note);
		deleteNode(C);
	}
}
