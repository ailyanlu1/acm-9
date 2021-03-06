#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define eps 1e-5
#define INF 1e20
#define MAXN 1024
#define sqr(x) (x)*(x)
using namespace std;
double a[MAXN][MAXN], b[MAXN][MAXN], x[MAXN], y[MAXN], z[MAXN];
int n;
double low, up;
bool init()
{
    scanf("%d", &n);
    if (!n) return false;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lf%lf%lf", &x[i], &y[i], &z[i]);
        for (int j = 1; j < i; ++j)
        {
            a[i][j] = a[j][i] = sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j]));
            b[i][j] = b[j][i] = fabs(z[i] - z[j]);
        }
    }
    low = INF, up = 0;
    return true;
}
double d[MAXN];
bool vst[MAXN];
int pre[MAXN];
double prim(int st, double r)
{
    for (int i = 1; i <= n; ++i) d[i] = INF;
    memset(vst, false, sizeof(vst));
    d[st] = 0;
    double s1 = 0, s2 = 0;
    for (int i = 1; i <= n; ++i)
    {
        double m1 = INF;
        int m2 = -1;
        for (int j = 1; j <= n; ++j)
            if ((d[j] < m1) && !vst[j]){
                m1 = d[j];
                m2 = j;
            }
        s1 += b[pre[m2]][m2];
        s2 += a[pre[m2]][m2];
        vst[m2] = true;
        for (int j = 1; j <= n; ++j)
            if (!vst[j] && (b[m2][j] - r * a[m2][j] < d[j])){
                d[j] = b[m2][j] - r * a[m2][j];
                pre[j] = m2;
            }
    }
    return s1 / s2;
}
double solve()
{
    up = 0;
    while (1){
        low = prim(1, up);
        if (fabs(low - up) < eps) return up;
        up = low;
    }
}
int main()
{
    while (init())
    {
        printf("%.3f\n", solve());
    }
    return 0;
}
