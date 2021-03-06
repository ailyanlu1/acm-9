#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
#define MAXM 10000000
#define MAXN 4096
using namespace std;
struct edge{
    int v, next;
}e[MAXM];
int eid, p[MAXN];
void insert(int x, int y)
{
    e[eid].v = y;
    e[eid].next = p[x];
    p[x] = eid++;
}
void mapinit()
{
    memset(p, -1, sizeof(p));
    eid = 0;
}
int x[MAXN], y[MAXN];
int n, m;
int dfn[MAXN], low[MAXN], stack[MAXN], belong[MAXN];
int bcnt, dindex = 0, top = 0;
bool instack[MAXN];
void tarjan(int v)
{
    instack[v] = true;
    stack[++top] = v;
    dfn[v] = low[v] = ++dindex;
    for (int i = p[v]; i != -1; i = e[i].next)
    {
        if (!dfn[e[i].v])
        {
            tarjan(e[i].v);
            low[v] = min(low[v], low[e[i].v]);
        }
        else if (instack[e[i].v])
        {
            low[v] = min(low[v], dfn[e[i].v]);
        }
    }
    int temp;
    if (dfn[v] == low[v])
    {
        bcnt++;
        do{
            temp = stack[top--];
            instack[temp] = false;
            belong[temp] = bcnt;
        }while (temp != v);
    }
}
void solve()
{
    memset(dfn, 0, sizeof(dfn));
    top = bcnt = dindex = 0;
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) tarjan(i);
}
bool inside(int a, int x, int y)
{
    return ((a >= x) && (a <= y)) || ((a >= y) && (a <= x));
}
void print_map()
{
    for (int i = 1; i <= n; ++i)
    {
        printf("%d:", i);
        for (int j = p[i]; j != -1; j = e[j].next)
            printf("");
    }
}
int main()
{
    mapinit();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
        scanf("%d%d", &x[i], &y[i]);
    for (int i = 1; i <= m; ++i)
        for (int j = i + 1; j <= m; ++j)
            if (inside(x[i], x[j], y[j]) ^ inside(y[i], x[j], y[j]))
            {
                insert(i, j + m);
                insert(i + m, j);
                insert(j, i + m);
                insert(j + m, i);
            }
    //printf("DONE\n");
    n = m * 2;
    //print_map();
    solve();
    //printf("DONE\n");
    bool flag = true;
    for (int i = 1; i <= m; ++i)
        if (belong[i] == belong[i + m])
        {
            flag = false;
            break;
        }
    if (flag) printf("panda is telling the truth...\n");
    else printf("the evil panda is lying again\n");
    return 0;
}
