//KMP
#include <iostream>
#include <string>
// pat 表示模式串，txt 表示文本串
//长度为 M，长度为 N。KMP
//算法是在 txt 中查找子串 pat，如果存在，返回这个子串的起始索引，否则返回 -1。

using namespace std;
//暴力算法
int search(string pat, string txt)
{
    int n1 = pat.length();
    int n2 = txt.length();
    for (int i = 0; i <= n2 - n1; i++)
    {
        int j;
        for (j = 0; j < n2; j++)
        {
            if (pat[j] != txt[i + j])
                break;
        }
        if (j == n1)
            return i;
    }
    return -1;
}

//KMP

int search(string pat, string txt, int next[])
{
    int i = 1, j = 1;
    int n1 = pat.length();
    int n2 = txt.length();
    while (i <= pat.length() && j <= txt.length())
    {
        if (j == 0 || pat[i] == txt[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
}

//求next
void next(string pat, int *next)
{
    int len = pat.length();
    next[0] = 1;
    int k = 0;
    int j = 1;
    while (j < len - 1)
    {
        if (k == 0 || pat[j] == pat[k])
        {
            k++;
            j++;
            next[k] = j;
        }
        else
        {
            k = next[k];
        }
    }
}

//next优化
void getnextval(string pat, int *next, int *nextval)
{
    int len = pat.length();
    next[0] = 1;
    int k = 0;
    int j = 1;
    while (j < len - 1)
    {
        if (k == 0 || pat[j] == pat[k])
        {
            k++;
            j++;
            next[k] = j;
        }
        else
        {
            k = next[k];
        }
    }
    for (j = 2; j <= pat.length(); j++)
    {
        if (pat[next[j]] == pat[j])
            nextval[j] = nextval[next[j]];
        else
            nextval[j] = next[j];
    }
}