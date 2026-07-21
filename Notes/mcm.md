# Matrix Chain Multiplication (MCM) - Complete Notes

## Table of Contents
1. [Introduction to MCM](#introduction-to-mcm)
2. [Approach - Dynamic Programming](#approach---dynamic-programming)
3. [Code Breakdown](#code-breakdown)
4. [DP Table Explanation](#dp-table-explanation)
5. [Complete Example](#complete-example)
6. [Time & Space Complexity](#time--space-complexity)
7. [Important Notes](#important-notes)
8. [Common Mistakes to Avoid](#common-mistakes-to-avoid)

---

# Introduction to MCM

## What is Matrix Chain Multiplication?
**A problem of finding the cheapest order (parenthesization) to multiply a chain of matrices, without actually changing the final result.**

```cpp
int p[n+1];         // dimension array; matrix Ai has dimensions p[i-1] x p[i]
int m[n+1][n+1];    // DP table: m[i][j] = min cost to multiply Ai...Aj
int s[n+1][n+1];    // split table: best k to break the chain at
```

**Key Characteristics:**
- Matrix multiplication is associative — grouping doesn't change the result
- But grouping changes the **number of scalar multiplications** needed
- Goal: minimize total scalar multiplications, not compute the actual product
- The dimension array `p[]` has size `n+1` for `n` matrices

**Real-life Examples:**
- Optimizing chained operations in computer graphics pipelines
- Query optimization in databases (join order)
- Compiler optimization for expression evaluation order
- Any chained operation where grouping order affects computational cost

---

# Approach - Dynamic Programming

## 1. Brute Force (Why it's not used here)
**Try every possible way to parenthesize the chain and pick the cheapest**

- Number of ways to parenthesize `n` matrices follows the Catalan number, growing exponentially
- Extremely slow for even moderately large `n`
- This is why Dynamic Programming is used instead

---

## 2. Dynamic Programming (Used in this code)
**Build the table by chain length — solve small chains first, then use them to solve bigger chains**

```cpp
for (int d = 1; d <= n - 1; d++) {              // chain length
    for (int i = 1; i <= n - d; i++) {
        int j = i + d;
        int minVal = 1e9;
        for (int k = i; k <= j - 1; k++) {      // try every split point
            int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
            if (q < minVal) {
                minVal = q;
                s[i][j] = k;                     // remember best split
            }
        }
        m[i][j] = minVal;
    }
}
```

**Why use Dynamic Programming?**
- Every sub-chain `Ai...Aj` is solved exactly once and reused for larger chains
- Time complexity drops from exponential (Catalan number growth) to `O(n^3)`
- The `s[][]` table lets us reconstruct the actual optimal grouping afterward

---

# Code Breakdown

## 1. Taking Input
**Read number of matrices and their dimension array**

```cpp
int n;
cin >> n;              // number of matrices

int p[n+1];
for (int i = 0; i <= n; i++) cin >> p[i];   // dimension array
```

**Note:** For `n` matrices, `p[]` needs `n+1` values, since matrix `Ai` uses `p[i-1]` and `p[i]` as its dimensions.

---

## 2. Initializing the Tables
**Set diagonal to 0 (base case) and everything else to infinity**

```cpp
int m[n+1][n+1], s[n+1][n+1];

for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
        m[i][j] = (i == j) ? 0 : 1e9;
        s[i][j] = 0;
    }
}
```

**Time Complexity:** O(n²) for initialization

**Note:** `m[i][j] = 0` when `i == j` because multiplying a single matrix costs nothing. Infinity is used elsewhere so the first real comparison in the `min` search always succeeds.

---

## 3. Chain Length Loop (`d`)
**Solve smaller chains before bigger ones**

```cpp
for (int d = 1; d <= n - 1; d++) {
```

- `d` represents chain length (`j - i`)
- Starts at `d = 1` (2 matrices) and increases up to `d = n-1` (the full chain)
- This order matters because bigger chains depend on smaller chains already being solved

---

## 4. Split Point Loop (`k`) - The Core Recurrence
**Try every possible place to break the chain and keep the cheapest**

```cpp
for (int k = i; k <= j - 1; k++) {
    int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
    if (q < minVal) {
        minVal = q;
        s[i][j] = k;
    }
}
m[i][j] = minVal;
```

- `m[i][k]` → cost of multiplying the left part
- `m[k+1][j]` → cost of multiplying the right part
- `p[i-1]*p[k]*p[j]` → cost of multiplying the two resulting matrices together
- The loop checks every valid `k` and keeps the split with minimum total cost

**Time Complexity:** O(n) per `(i, j)` pair, so O(n³) overall

---

## 5. Printing the Tables
**Show both the cost table and the split table**

```cpp
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
        cout << m[i][j] << "\t";
    }
    cout << endl;
}
```

**Best Practice:** Printing `s[][]` alongside `m[][]` makes it possible to see exactly where each optimal chain was split.

---

## 6. Final Answer
**The cost of multiplying the entire chain**

```cpp
cout << "Minimum Cost: " << m[1][n] << endl;
```

**Time Complexity:** O(1) lookup, since it's already computed

---

# DP Table Explanation

## Table Reference

| `m[i][j]` means | Explanation |
|---|---|
| `i, j` | multiplying matrices `Ai` through `Aj` |
| value in cell | minimum scalar multiplications needed for that sub-chain |
| `s[i][j]` | the index `k` where the optimal split happens |

## Reading the Table

```cpp
m[i][j] = min over all k of ( m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j] )
```

The table is filled diagonal-by-diagonal, moving from short chains toward the full chain, since every cell depends on smaller sub-chains being solved first.

---

# Complete Example

## Example: Small MCM Run

# Dimensions p = [10, 20, 30, 40] (3 matrices: A1(10x20), A2(20x30), A3(30x40))

**Input:**
3
10 20 30 40

**Two possible groupings:**

| Order | Cost |
|---|---|
| `(A1 x A2) x A3` | 10×20×30 + 10×30×40 = 6000 + 12000 = **18000** |
| `A1 x (A2 x A3)` | 20×30×40 + 10×20×40 = 24000 + 8000 = 32000 |

**Output:**
Minimum Cost: 18000

**Explanation:** Grouping `(A1 x A2) x A3` needs fewer total scalar multiplications, so the algorithm picks that split.

---

# Time & Space Complexity

| Operation | Complexity |
|---|---|
| Filling the DP tables | O(n³) |
| Reading final answer | O(1) |
| Space used (two 2D tables) | O(n²) |

**Note:** Naive recursive solution without DP grows with the Catalan number (exponential). DP brings it down to `O(n³)` — polynomial.

---

# Important Notes

1. **1-Indexed Arrays:** Matrices are numbered `A1` to `An`, and `p[]` has `n+1` entries
2. **Bottom-Up by Chain Length:** The outer loop `d` ensures smaller sub-chains are always solved before bigger ones need them
3. **Optimal Substructure:** The best split of a chain depends only on the best splits of its two parts
4. **Overlapping Subproblems:** The same sub-chain `(i, j)` is reused across many larger chains — hence storing it in `m[][]`
5. **Cost Only, Not the Product:** This code computes the minimum multiplication cost, not the actual resulting matrix. Getting the actual parenthesization requires recursively reading `s[][]`

---

# Common Mistakes to Avoid

1. ❌ Forgetting `m[i][j] = 0` when `i == j` — this breaks every larger chain calculation built on top of it
2. ❌ Not initializing non-diagonal cells to a large value (infinity) before taking the minimum
3. ❌ Looping `i` and `j` directly instead of looping by chain length `d` — this can access cells that aren't filled yet
4. ❌ Using wrong dimension indices in `p[i-1]*p[k]*p[j]` — this is the most common source of wrong answers
5. ❌ Forgetting that `p[]` needs `n+1` values for `n` matrices, not `n`
