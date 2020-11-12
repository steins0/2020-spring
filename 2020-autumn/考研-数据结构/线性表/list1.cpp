//顺序表  假设一切输入合理
#include <iostream>
#include <stdio.h>
#define max_int_size 40

using namespace std;

//结构体定义——静态
typedef struct sqllist
{
    int data[max_int_size];
    int lenth;
};
//结构体定义—-动态
typedef struct seqllist
{
    int *data;
    int now_lenth;  //动态表的当前长度
    int max_lenth;  //表的最大长度
};



//初始化--静态
void Initlist(sqllist &L){
    for (int i = 0; i < max_int_size; i++)
    {
        L.data[i] = 0;
    }
    L.lenth = 0;
}
//初始化--动态
void Initlist(seqllist &L)
{
    L.data = new int[max_int_size];
    //L.data = (int *)malloc(max_int_size*sizeof(int));
    L.now_lenth = 0;
    L.max_lenth = max_int_size;
}

//只能销毁结构体内的变量空间
void droplist(sqllist &L)
{
    delete L.data;
}
void droplist(seqllist &L)
{
    delete L.data;
}

//插入  i：插入数值  e：插入位置
//插入--静态
void insertlist(sqllist &L,int i,int e)
{
    for(int i = L.lenth;i >= e;i--)
    {
        L.data[i] = L.data[i-1];
    }
    L.data[e-1] = i;
    L.lenth++;
}
//插入--动态
void insertlist(seqllist &L,int i,int e)
{
    for(int i = L.now_lenth;i >= e;i--)
    {
        L.data[i] = L.data[i-1];
    }
    L.data[e-1] = i;
    L.now_lenth++;
}

//删除 位置为e的元素
//删除 静态
void deletelist(sqllist &L,int e)
{
    for (int i = L.lenth; i >= e; i++)
    {
        L.data[i-1] = L.data[i];
    }
    L.lenth--;
}
//删除 动态
void deletelist(seqllist &L,int e)
{
    for (int i = L.now_lenth; i >= e; i++)
    {
        L.data[i-1] = L.data[i];
    }
    L.now_lenth--;
}

//按值查找 值为val 返回位置
//按值查找 静态
int findbyvalue(sqllist &L,int val)
{
    for(int i= L.lenth;i>=0;i--)//倒叙查找
    {
        if (L.data[i] == val)
        {
            return i+1;
        }
    }
    return -1;
}
//按值查找 动态
int findbyvalue(seqllist &L,int val)
{
    for(int i= L.now_lenth;i>=0;i--)//倒叙查找
    {
        if (L.data[i] == val)
        {
            return i+1;
        }
    }
    return -1;
}

//按位查找 位为e 返回值
//按位查找 静态
int findbylocat(sqllist &L,int e)
{
    return L.data[e];
}
int findbylocat(seqllist &L,int e)
{
    return L.data[e];
}




