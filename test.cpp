#include <iostream>
using namespace std;

#define MAX 20

int res_num;
// 因子暂存在res数组中
int res[MAX];
int p_res = 0;

// 将n进行分解
void resolve(int n);

int main() {
    while (1) {
        int n;
        cin >> n;
        resolve(n);
        cout << "total num of res:\t" << res_num << endl;
        res_num = 0;
    }
    return 0;
}

void resolve(int n) {
    if (n<=0) { // 出口
        //        for (int i=0; i<p_res; i++)
        //            cout << res[i] << " ";
        //        cout << endl;
        res_num++;
    }

    for (int i=1; i<=n; i++) {
        res[p_res] = i;
        p_res++;        // p_res++来顺次存储各个因子
        resolve(n-i);
        p_res--;        // 此行必须有，执行完上一行，下一次for循环即使第一个因子
    }
}