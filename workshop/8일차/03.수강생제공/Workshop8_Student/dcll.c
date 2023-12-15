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

	// todo: t ����� ����� �ʱ�ȭ �Ѵ�.

	return t;
}

//  d : �޸� ���� �Ҵ� ���� �Ϳ� ���ؼ� ������ ���
void destroyNode( Node* d ){
	// todo: �޸� ������ ������ �Ҵ� ���� ���� �޸𸮿� ���� free��

}

void _insertNode(Node *newnode, Node *P, Node *N) {
	newnode->prev = P;
	newnode->next = N;
	P->next = newnode;
	N->prev = newnode;
}

#define LOOPDCLL(C, H) for(C = H->next; C != H; C=C->next)

// SAry : key�� �Էµ� ��¥�� �ش��ϴ� ������ ��带 ������ �迭
// H : Head
// key : �˻��� ���� ��¥ (��, ��, ��)
int searchNodes(Node** SAry, Node* H, DateT key) {
	Node *C = NULL;  //  LOOP�� ���鼭 �� ��� ���忡 ����� �ӽ� ����
	DateT T;  				//  C->data.date�� �ӽ÷� ������ ����
    int cnt = 0;			//  �迭�� ����� ��� ����

	// todo: ��¥�� ���� �Ϳ� ���ؼ� SAry �迭�� ���� ��, �� ������ ��ȯ��

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
