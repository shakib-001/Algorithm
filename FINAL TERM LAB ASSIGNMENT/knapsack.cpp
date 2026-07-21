#include<iostream>
using namespace std;

int main(){
    int n, m;

    cout << "Enter number of items: ";
    cin >> n;

    cout << "Enter maximum capacity of knapsack: ";
    cin >> m;

    int p[n+1], wt[n+1];
    int k[n+1][m+1];

    cout << "Enter profits of items:\n";
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    cout << "Enter weights of items:\n";
    for(int i = 1; i <= n; i++) {
        cin >> wt[i];
    }

    for(int i = 0; i <= n; i++) {
        for(int w = 0; w <= m; w++) {
            if(i == 0 || w == 0)
                k[i][w] = 0;
            else if (wt[i] <= w)
                k[i][w] = max(p[i] + k[i-1][w - wt[i]], k[i-1][w]);
            else
                k[i][w] = k[i-1][w];
        }
    }

    cout << "\nDP Table (k[i][w]):\n";
    cout << "     ";
    for (int w = 0; w <= m; w++) {
        cout << w << "\t";
    }
    cout << endl;

    for (int i = 0; i <= n; i++) {
        cout << "i=" << i << " ";
        for (int w = 0; w <= m; w++) {
            cout << k[i][w] << "\t";
        }
        cout << endl;
    }

    cout << "\nMaximum Profit: " << k[n][m] << endl;

    return 0;
}
