#include<iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of matrices: ";
    cin >> n;

    int p[n + 1];

    cout << "Enter the dimensions (size " << n + 1 << "):\n";
    for (int i = 0; i <= n; i++) {
        cin >> p[i];
    }

    int m[n + 1][n + 1];
    int s[n + 1][n + 1];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                m[i][j] = 0;
            else
                m[i][j] = 1e9;
            s[i][j] = 0;
        }
    }

    int q;

    for (int d = 1; d <= n - 1; d++) {
        for (int i = 1; i <= n - d; i++) {
            int j = i + d;
            int minVal = 1e9;
            for (int k = i; k <= j - 1; k++) {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < minVal) {
                    minVal = q;
                    s[i][j] = k;
                }
            }
            m[i][j] = minVal;
        }
    }

    cout << "\nCost Table (m[i][j]):\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i > j)
                cout << "-\t";
            else
                cout << m[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\nSplit Table (s[i][j]):\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i >= j)
                cout << "-\t";
            else
                cout << s[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\nMinimum number of multiplications: " << m[1][n] << endl;

    return 0;
}
