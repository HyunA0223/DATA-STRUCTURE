#pragma once
typedef int element;	// 요소의 타입
typedef struct QueueNode {	// 큐의 노드의 타입 
	element item;
	struct QueueNode* link;
} QueueNode;
typedef struct {		// 큐 ADT 구현
	QueueNode* front, * rear;
} QueueType;