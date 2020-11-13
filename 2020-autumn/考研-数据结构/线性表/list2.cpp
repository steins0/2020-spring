//链表  假设一切输入合理
#include <iostream>
#include <stdio.h>
#define max_int_size 40

//单链表
struct Lnode
{
    int data;
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
//带头节点
void Initlist(Lnolist &L)
{
    L = (Lnode *)malloc(sizeof(Lnode));
    L->next = NULL;
}
//不带头节点
void Initlist2(Lnolist &L)
{
    L = (Lnode *)malloc(sizeof(Lnode));
    L = NULL;
}

//单链表创建(头插法) 数组长度为N
void CreateList_L_Front(Lnolist &L, int a[], int n)
{
    Lnolist p;
    int i;
    L = (Lnode *)malloc(sizeof(Lnode)); // 创建立头结点
    L->next = NULL;
    for (int num = n - 1; num >= 0; num--)
    {
        p = new Lnode;     // 创建新结点
        p->data = a[num];  // 赋元素值
        p->next = L->next; // 插入在两节点之间
        L->next = p;       //L指向p
    }
}
//单链表创建(尾插法) 数组长度为N
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
        q->next = p;                        // 插入在尾结点之后
        q = p;                              // q指向新的表尾
    }
    q->next = NULL; // 表尾结点next域置空
}

//后续只对含头节点的结构代码
//销毁单链表
void droplist(Lnolist &L)
{
    Lnolist p, p1;
    p = L;
    while (p) //遍历完整个单链表
    {
        p1 = p;
        p = p->next;
        free(p1);
    }
    L = NULL;
}

//插入数据  i为位置 e为值
bool insertlist(Lnolist &L, int i, int e)
{
    Lnolist p, s;
    int j = 1;
    for(p = L;j<i;j++)
    {
        if (p->next == NULL)
        {
            break;
        }
        p = p->next;
    }
    if (j != i )
        return false; // i的位置不合理
    if ((s = (Lnode *)malloc(sizeof(Lnode))) == NULL)
        exit(1); // 存储分配失败
    s->data = e;
    s->next = p->next;
    p->next = s; // 插入新结点
    return true;
}

