//栈  假设一切输入合理
#include <iostream>
#include <stdio.h>
#define max_int_size 40

//顺序存储结构
struct sqstack
{
    int data[max_int_size];
    int top;
};
//链式存储结构---双链表
struct nodestack
{
    int data;
    nodestack *front;
    nodestack *next;
};
typedef struct nodestack *nodestacks;

//顺序结构初始化
void initstack(sqstack &s)
{
    s.top = -1;
}
//链式结构初始化
void initstack(nodestacks &s)
{
    //s = new nodestack;
    s = (nodestack *)malloc(sizeof(nodestack));
    s->front = NULL;
    s->next = NULL;
}

//销毁链式结构的栈
void dropstack(nodestacks &s)
{
    nodestacks p, p1;
    p = s;
    while (p)
    {
        p = p->next;
        p1 = p;
        free(p);
    }
    s = NULL;
}

//入栈 s:栈  i：数值
//顺序结构
bool pop(sqstack &s, int i)
{
    if (s.top == max_int_size - 1)
        return false;
    s.top++;
    s.data[s.top] = i;
    return true;
}
//链式结构  == 链表头插法  
bool pop(nodestacks &s,int i)
{
    nodestacks p,q;
    p = s->next;
    q = new nodestack;
    q->data = i;
    q->next = p;
    p->front = q;
    s->next = q;
    return true;
}

//出栈 s:栈
//顺序结构
int push(sqstack &s){
    if(s.top == -1)
    return false;
    s.top--;
    return s.data[++s.top];
}
//链式结构  
int push(nodestacks &s)
{
    nodestacks p = s->next;
    int ans = p->data;
    s->next = p->next;
    p->next->front = s;
    free(p);
    return ans;
}

//返回栈顶元素
//顺序结构
int gettop(sqstack &s)
{
    return s.data[s.top];
}
//链式结构 
int gettop(nodestacks &s)
{
    return s->next->data;
}