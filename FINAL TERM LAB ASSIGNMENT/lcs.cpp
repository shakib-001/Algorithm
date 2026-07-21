#include<iostream>
using namespace std;

int main() {
    int m, n;

    cout << "Enter length of first string: ";
    cin >> m;

    cout << "Enter length of second string: ";
    cin >> n;

    char x[m + 1], y[n + 1];
    int c[m + 1][n + 1];

    cout << "Enter first string (character by character):\n";
    for (int i = 1; i <= m; i++) {
        cin >> x[i];
    }

    cout << "Enter second string (character by character):\n";
    for (int j = 1; j <= n; j++) {
        cin >> y[j];
    }

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                c[i][j] = 0;
            else if (x[i] == y[j])
                c[i][j] = c[i - 1][j - 1] + 1;
            else
                c[i][j] = max(c[i - 1][j], c[i][j - 1]);
        }
    }

    cout << "\nDP Table (c[i][j]):\n";
    cout << "     ";
    for (int j = 0; j <= n; j++) {
        if (j == 0)
            cout << "0\t";
        else
            cout << y[j] << "\t";
    }
    cout << endl;

    for (int i = 0; i <= m; i++) {
        if (i == 0)
            cout << "0"<<"   ";
        else
            cout << x[i] << "   ";

        for (int j = 0; j <= n; j++) {
            cout << c[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\nLength of LCS: " << c[m][n] << endl;

    return 0;
}
