#include<iostream>
#include<vector>
#include<time.h>
#include<Windows.h>
using namespace std;



/*void test_1_wei_bag_problem() {
    vector<int> weight = { 1, 3, 4 };
    vector<int> value = { 15, 20, 30 };
    int bagWeight = 4;

    // 初始化
    vector<int> dp(bagWeight + 1, 0);
    for (int i = 0; i < weight.size(); i++) { // 遍历物品
        for (int j = bagWeight; j >= weight[i]; j--) { // 遍历背包容量
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    cout << dp[bagWeight] << endl;
}

void test_2_wei_bag_problem1() {
    vector<int> weight = { 1, 3, 4 };
    vector<int> value = { 15, 20, 30 };
    int bagWeight = 4;

    // 二维数组
    vector<vector<int>> dp(weight.size() + 1, vector<int>(bagWeight + 1, 0));

    // 初始化
    for (int j = weight[0]; j <= bagWeight; j++) {
        dp[0][j] = value[0];
    }

    // weight数组的大小 就是物品个数
    for (int i = 1; i < weight.size(); i++) { // 遍历物品
        for (int j = 0; j <= bagWeight; j++) { // 遍历背包容量
            if (j < weight[i]) dp[i][j] = dp[i - 1][j];
            else dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);

        }
    }

    cout << dp[weight.size() - 1][bagWeight] << endl;
}
*/
//#include <bits/stdc++.h>
//using namespace std;
int f[3000][3000];//状态函数f[i][j]表示第i件物品容量为j最大价值
int f2[3000];//状态函数f[j]表示第i件物品容量为j最大价值
int v[3000];
int w[300];
int choose[3000];
int cnt = 0;
int choose2[3000];
int cnt2 = 0;
string names[3000];
/*
函数功能：求0-1背包问题的最大价值
函数形参：物品数量和背包容量
函数返回值：返回最大值
*/
int fun(int n, int m)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (j < w[i])
                f[i][j] = f[i - 1][j];
            else
                f[i][j] = max(f[i - 1][j], f[i - 1][j - w[i]] + v[i]);
        }
    }

    return f[n][m];
}



int fun2(int n, int m)
{
    /*for (int i = 1; i <= n; i++)
    {
        for (int j = m; j >= w[i]; j--)//逆序 
        {
            f2[j] = max(f2[j], f2[j - w[i]] + v[i]);
        }
    }*/
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= w[i]; j--) {
            f2[j] = max(f2[j], f2[j - w[i]] + v[i]);
        }
    }

    return f2[m];
}


int main() {

    //功能测试
    int n, m;
    cout << "请输入物品数目：";
    cin >> n;
    cout << endl << "您输入的物品数目为 " << n << endl;

    cout << endl << "请输入背包最大重量: ";
    cin >> m;
    cout << endl << "您输入的背包最大重量为 " << m << endl;

    for (int i = 1; i <= n; i++) {
        cout << endl << "请依次输入第 " << i << " 件物品的名称、重量、价值: " << endl;
        cin >> names[i] >>  w[i] >> v[i];
    }
    cout << endl << "您输入的信息如下" << endl;
    cout << "名称       " << "重量        " << "价值        " << endl;
    for (int i = 1; i <= n; i++) {
        //cout << "请依次输入第 " << i << " 件物品的名称、重量、价值: " << endl;
        cout << names[i] << "          " << w[i] << "           " << v[i] << "            " << endl;
    }
    

    long long head, tail, freq;
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
    QueryPerformanceCounter((LARGE_INTEGER*)&head);
    int res = fun(n, m);
    QueryPerformanceCounter((LARGE_INTEGER*)&tail);
    cout << endl << "最大价值为 " << res << endl;
    
    int j = m;
    for (int i = n; i >= 1; i--) {
        if (f[i][j] != f[i - 1][j]) {
            j = j - w[i];
            choose[cnt++] = i;
        }
    }
    cout << "您的最优挑选方案如下：" << endl;
    cout << "共挑选 " << cnt << " 件物品" << endl;
    cout << "它们分别是 ";
    for (int i = cnt - 1; i >= 0; i--) {
        cout << names[choose[i]] << "  ";
    }

    cout << endl << "二维背包算法时间为 " << (tail - head) * 1000.0 / freq << "ms" << endl;

    cout << endl << "可优化为一维背包算法" << endl;

    QueryPerformanceCounter((LARGE_INTEGER*)&head);
    int res2 = fun2(n, m);
    QueryPerformanceCounter((LARGE_INTEGER*)&tail);

    j = m;
    for (int i = n; i >= 1; i--) {
        if (f[i][j] != f[i - 1][j]) {
            j = j - w[i];
            choose2[cnt2++] = i;

        }
    }
    cout << "最大价值为" << res2 << endl;
    cout << "您的最优挑选方案如下：" << endl;
    cout << "共挑选 " << cnt2 << " 件物品" << endl;
    cout << "它们分别是 ";
    for (int i = cnt2 - 1; i >= 0; i--) {
        cout << names[choose2[i]] << "  ";
    }
    cout << endl << "一维优化算法时间为 " << (tail - head) * 1000.0 / freq << "ms" << endl;
   


    cout << endl << "打印二维数组" << endl;
    for (int i = 0; i <= n; i++) {
        for (int k = 0; k <= m; k++) {
            cout << f[i][k] << " ";
        }
        cout << endl;
    }

    cout << endl << "打印一维数组" << endl;
    for (int i = 0; i <= m; i++)
        cout << f2[i] << " ";


    //时间复杂度测试
/*int n, m;
long long head, tail, freq;
QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
for (int k = 0; k < 10; k++) {
    cin >> n >> m;
    srand(time(NULL));
    for (int i = 1; i <= n; i++) {
        v[i] = rand() % 100;
        w[i] = rand() % 100;
    }
    cout << "n = " << n << " m = " << m;
    QueryPerformanceCounter((LARGE_INTEGER*)&head);
    fun(n, m);
    QueryPerformanceCounter((LARGE_INTEGER*)&tail);
    cout << endl << "二维背包算法时间为 " << (tail - head) * 1000.0 / freq << "ms" << endl;

    QueryPerformanceCounter((LARGE_INTEGER*)&head);
    fun2(n, m);
    QueryPerformanceCounter((LARGE_INTEGER*)&tail);
   // cout << "n = " << n << "m = " << m;
    cout <<  "一维背包算法时间为 " << (tail - head) * 1000.0 / freq << "ms" << endl << endl;
}
*/
    return 0;
}
