//队列  假设一切输入合理
#include <iostream>
#include <stdio.h>
#define max_int_size 40

//顺序存储结构
struct sqqueue
{
    int data[max_int_size];
    int top,end;
};
//链式存储结构---双链表
struct nodequeue
{
    int data;
    nodequeue *end;
    nodequeue *next;
};
typedef struct nodequeue *nodequeues;

//顺序结构初始化
void initstack(sqqueue &s)
{
    s.end=0;
    s.top=0;
}

//链式结构初始化
void initstack(nodequeues &s)
{
    s = new nodequeue;
    s->end =  NULL;
    s->next = NULL;
}

//销毁链式结构的队列
void dropqueue(nodequeues &s)
{
    nodequeues p,q;
    p = s->next;
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
}

//入队 s:栈  i：数值
//顺序结构
bool enqueue(sqqueue &s, int i)
{
    if (s.end == max_int_size - 1)
        return false;
    s.end++;
    s.data[s.end] = i;
    return true;
}
//链式结构  == 链表尾插法  
bool enqueue(nodequeues &s,int i)
{
    nodequeues p;
    p = new nodequeue;
    p->data = i;
    p->next = NULL;  //设置新节点
    s->end->next = p; //新节点加至最后
    s->end = p; // 尾指针更新
    return true;
}

//出队 s:队列
//顺序结构
int outqueue(sqqueue &s)
{
    if (s.end == 0)
    {
        return false;
    }
    s.end--;
    return s.data[++s.end];
}
//链式结构
int outqueue(nodequeue &s)
{
    if(s.end ==NULL)
    return false;
    int i =s.end->data;
    nodequeues p = s.next;
    while (p->next != s.end)
    {
        p = p->next;
    }
    s.end = p;
    return i;
}

//返回队头元素
//顺序结构
int gettop(sqqueue &s)
{
    if (s.end == 0)
    {
        return false;
    }
    return s.data[s.end];
}
//链式结构
int gettop(nodequeue &s)
{
    return s.end->data;
}