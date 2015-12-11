#include<stdio.h>
#include "node.h"

QueueList InitQueue()
{
 QueueList q=(Queue *)malloc(sizeof(Queue));
 QueueNode qn=(QueueNode)malloc(sizeof(QNode));
 q->first=qn;
 q->last=qn;
 return q;
}

QueueNumList InitNumQueue()
{
    QueueNumList q = (NumQueue*)malloc(sizeof(NumQueue));
    QueueNumNode qn = (NumNode)malloc(sizeof(NumNode));
    q->first = qn;
    q->last = qn;
    return q;
}

void enqueue(QueueList q,TreeNode *d)
{
  QueueList p=q;
  QueueNode Q=(QNode *)malloc(sizeof(QNode));
  Q->data=NULL;
  p->last->data=d;
  p->last->next=Q;
  p->last=Q;
}

void enqueue_int(QueueNumList q, int d)
{
    QueueNumList p = q;
    QueueNumNode Q = (NumNode*)malloc(sizeof(NumNode));
    Q->data = 0;
    p->last->data = d;
    p->last->next = Q;
    p->last = Q;
}

TreeNode *dequeue(QueueList q)
{
 if(q->first!=q->last)
 {
  TreeNode *tn = q->first->data;
  q->first=q->first->next;
  return tn;
 }
 else
 {
 return NULL;
 }
}

int dequeue_int(QueueNumList q)
{
    if(q->first != q->last)
    {
	int t = q->first->data;
	q->first = q->first->next;
	return t;
    }
    else
    {
        return 0;
    }
}
