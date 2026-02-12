#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

/*
    k: number of eggs
    n: number of floors
    Returns: minimum trials in worst case
*/

// recursive approach
// Time: O(2^n), Space: O(n)
int eggDropRecursive(int k, int n) {
    if (n <= 1) return n;
    if (k == 1) return n;

    int minTrials = INT_MAX;
    for (int i = 1; i <= n; i++) {
        int res = 1 + max(eggDropRecursive(k - 1, i - 1), eggDropRecursive(k, n - i));
        minTrials = min(minTrials, res);
    }
    return minTrials;
}

// dp iterative
// Time: O(k*n^2), Space: O(k*n)
int eggDropDp(int k, int n) {
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= k; i++) {
        dp[i][0] = 0;
        dp[i][1] = 1;
    }
    for (int j = 1; j <= n; j++) {
        dp[1][j] = j;
    }

    for (int i = 2; i <= k; i++) {
        for (int j = 2; j <= n; j++) {
            dp[i][j] = INT_MAX;
            for (int x = 1; x <= j; x++) {
                int breaks = dp[i - 1][x - 1];
                int survives = dp[i][j - x];
                int worst_case = 1 + max(breaks, survives);
                dp[i][j] = min(dp[i][j], worst_case);
            }
        }
    }
    return dp[k][n];
}

// dp + binary optimisation
// Time: O(k*n*log(n)), Space: O(k*n)
int eggDropDpBinary(int k, int n) {
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= k; i++) {
        dp[i][0] = 0;
        dp[i][1] = 1;
    }
    for (int j = 1; j <= n; j++) {
        dp[1][j] = j;
    }

    for (int i = 2; i <= k; i++) {
        for (int j = 2; j <= n; j++) {
            dp[i][j] = INT_MAX;
            int left = 1;
            int right = j;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                int breaks = dp[i - 1][mid - 1];
                int survives = dp[i][j - mid];
                int worst_case = 1 + max(breaks, survives);
                
                dp[i][j] = min(dp[i][j], worst_case);
                
                if (breaks < survives) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
    }
    return dp[k][n];
}

int main() {
    int n = 10; // floors
    int k = 2;  // eggs
    
    cout << "Eggs: " << k << ", Floors: " << n << endl;
    cout << "Recursive: " << eggDropRecursive(k, n) << endl;
    cout << "DP Iterative: " << eggDropDp(k, n) << endl;
    cout << "DP Binary Search: " << eggDropDpBinary(k, n) << endl;
    
    // Test case 2: 100 floors, 2 eggs (Classic)
    n = 100; k = 2;
    cout << "\nEggs: " << k << ", Floors: " << n << endl;
    // cout << "Recursive: (Skipped for performance)" << endl; 
    cout << "DP Iterative: " << eggDropDp(k, n) << endl;
    cout << "DP Binary Search: " << eggDropDpBinary(k, n) << endl;

    return 0;
}