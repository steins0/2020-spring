//链表  假设一切输入合理
#include <iostream>
#include <stdio.h>
#define max_int_size 40

//双链表
struct Lnode
{
    int data;
    Lnode *front;
    Lnode *next;
};
typedef struct Lnode *Lnolist; //定义结构体的指针类型
//方法二
// typedef struct Lnode
// {
//     int data;
//     Lnode *next;
// }Lnode，*Lnolist;

//初始化
//带头节点(即第一个节点无数据)
void Initlist(Lnolist &L)
{
    L = (Lnode *)malloc(sizeof(Lnode));
    L->next = NULL;
    L->front = NULL;
}
//不带头节点
void Initlist2(Lnolist &L)
{
    L = (Lnode *)malloc(sizeof(Lnode));
    L = NULL;
}

//双链表创建(头插法) 数组长度为N
void CreateList_L_Front(Lnolist &L, int a[], int n)
{
    Lnolist p;
    int i;
    L = (Lnode *)malloc(sizeof(Lnode)); // 创建立头结点
    L->next = NULL;
    L->next = NULL;
    for (int num = n - 1; num >= 0; num--)
    {
        p = new Lnode;     // 创建新结点
        p->data = a[num];  // 赋元素值
        p->next = L->next; // 插入在两节点之间
        p->next->front = p; //下一节点的头指向p
        L->next = p;       //L指向p
        p->front = L; //p的头指向L
    }
}
//双链表创建(尾插法) 数组长度为N
void CreateList_L_Rear(Lnolist &L, int a[], int n)
{
    Lnolist p, q;
    int i;
    L = (Lnode *)malloc(sizeof(Lnode)); // 创建立头结点
    q = L;                              // q始终指向尾结点，开始时尾结点也是头结点
    for (i = 0; i < n; i++)
    {
        p = (Lnolist)malloc(sizeof(Lnode)); // 创建新结点
        p->data = a[i];                     // 赋元素值
        p->front = q;
        q->next = p;                        // 插入在尾结点之后
        q = p;                              // q指向新的表尾
    }
    q->next = NULL; // 表尾结点next域置空
}

//后续操作基本和单链表差不多