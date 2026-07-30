# 0/1 Knapsack Problem - Complete Notes

## Table of Contents
1. [Introduction to 0/1 Knapsack](#introduction-to-01-knapsack)
2. [Approach - Dynamic Programming](#approach---dynamic-programming)
3. [Code Breakdown](#code-breakdown)
4. [DP Table Explanation](#dp-table-explanation)
5. [Complete Example](#complete-example)
6. [Time & Space Complexity](#time--space-complexity)
7. [Important Notes](#important-notes)
8. [Common Mistakes to Avoid](#common-mistakes-to-avoid)

---

# Introduction to 0/1 Knapsack

## What is 0/1 Knapsack?
**A problem where we select items with given profit and weight to maximize profit without exceeding a given capacity, and each item can only be taken fully or not at all.**

```cpp
int p[n+1], wt[n+1];   // profit and weight of each item
int k[n+1][m+1];       // DP table: k[i][w] = max profit using first i items with capacity w
```

**Key Characteristics:**
- Items cannot be broken into fractions (0 or 1, not 0.5)
- Every item has a profit and a weight
- The bag has a fixed maximum capacity
- Goal: maximize total profit under the weight limit

**Real-life Examples:**
- Choosing items to pack for a trip with a weight limit
- Selecting projects to invest in with a fixed budget
- Cargo loading problems
- Resource allocation with a fixed budget/capacity

---

# Approach - Dynamic Programming

## 1. Brute Force (Why it's not used here)
**Try every possible subset of items and check which one fits and gives max profit**

- There are `2^n` subsets, so time complexity is exponential: `O(2^n)`
- Extremely slow for large `n`
- This is why we use Dynamic Programming instead

---

## 2. Dynamic Programming (Used in this code)
**Build a table bottom-up, where each cell stores the best answer for a subproblem**

```cpp
int k[n+1][m+1];

for(int i = 0; i <= n; i++) {
    for(int w = 0; w <= m; w++) {
        if(i == 0 || w == 0)
            k[i][w] = 0;                                       // base case
        else if (wt[i] <= w)
            k[i][w] = max(p[i] + k[i-1][w - wt[i]], k[i-1][w]); // take or skip
        else
            k[i][w] = k[i-1][w];                                // can't take, doesn't fit
    }
}
```

**Why use Dynamic Programming?**
- Avoids recomputation of the same subproblem again and again
- Every subproblem `k[i][w]` is solved exactly once and reused
- Time complexity drops from exponential to `O(n * m)`
- Easy to trace and print the whole table for understanding

---

# Code Breakdown

## 1. Taking Input
**Read number of items, capacity, and profit/weight of each item**

```cpp
int n, m;
cin >> n;   // number of items
cin >> m;   // knapsack capacity

int p[n+1], wt[n+1];

for(int i = 1; i <= n; i++) cin >> p[i];    // profits
for(int i = 1; i <= n; i++) cin >> wt[i];   // weights
```

**Note:** Arrays are 1-indexed (`i` starts from 1), index 0 is left unused so it lines up with the base case (`i == 0` means "no items").

---

## 2. Base Case
**When there are no items, or capacity is 0, profit must be 0**

```cpp
if(i == 0 || w == 0)
    k[i][w] = 0;
```

**Time Complexity:** O(1) per cell

**Note:** This is the foundation the whole table is built on - without this, the recurrence has nothing to build from.

---

## 3. Recurrence - Item Fits (`wt[i] <= w`)
**Decide whether taking the item is better than skipping it**

```cpp
k[i][w] = max(p[i] + k[i-1][w - wt[i]], k[i-1][w]);
```

- `p[i] + k[i-1][w - wt[i]]` → profit if we **take** item `i`: its own profit + best profit from remaining capacity using previous items
- `k[i-1][w]` → profit if we **skip** item `i`: same as without this item
- `max()` of both → the optimal decision for this cell

**Time Complexity:** O(1) per cell

---

## 4. Recurrence - Item Doesn't Fit (`wt[i] > w`)
**If the item's weight is more than current capacity, it cannot be taken**

```cpp
k[i][w] = k[i-1][w];
```

**Note:** No choice here — the only option is to skip the item.

---

## 5. Printing the DP Table
**Display how the table gets filled step by step**

```cpp
for (int i = 0; i <= n; i++) {
    cout << "i=" << i << " ";
    for (int w = 0; w <= m; w++) {
        cout << k[i][w] << "\t";
    }
    cout << endl;
}
```

**Best Practice:** Printing the full table while learning DP helps visualize exactly how bigger subproblems are built from smaller ones.

---

## 6. Final Answer
**The bottom-right corner of the table holds the answer**

```cpp
cout << "Maximum Profit: " << k[n][m] << endl;
```

**Time Complexity:** O(1) lookup, since it's already computed

---

# DP Table Explanation

## Table Reference

| `k[i][w]` means | Explanation |
|---|---|
| `i` (row) | using only the first `i` items |
| `w` (column) | capacity available |
| value in cell | best possible profit for that (items, capacity) combination |

## Reading the Table

```cpp
k[i][w] = max(p[i] + k[i-1][w - wt[i]], k[i-1][w]);
```

Every cell only depends on the **row above it** (`i-1`), meaning the table is built strictly bottom-up, row by row, from fewer items toward more items.

---

# Complete Example

## Example: Small Knapsack Run

Items: 1 2 3 4
Profit: 1 4 5 7
Weight: 1 2 4 5
Capacity (m): 4
**Input:**
4
4
1 4 5 7
1 2 4 5

**Output:**
Maximum Profit: 5

**Explanation:** Item 1 + Item 2 → weight = 1+2 = 3 (≤4), profit = 1+4 = 5. Item 3 alone also gives weight 4, profit 5. Both give the same maximum profit of 5.

---

# Time & Space Complexity

| Operation | Complexity |
|---|---|
| Filling the DP table | O(n × m) |
| Reading final answer | O(1) |
| Space used (2D table) | O(n × m) |

**Note:** Naive recursive solution without DP takes `O(2^n)` — exponential. DP brings it down to `O(n × m)` — polynomial.

---

# IMPORTANT NOTES

1. **1-Indexed Arrays:** `p[]`, `wt[]`, and the table are used with 1-based indexing to keep base case (`i==0`) clean
2. **Bottom-Up Only:** No recursion used here — the table is filled iteratively, row by row
3. **Optimal Substructure:** The best answer for `n` items is built from the best answers for fewer items
4. **Overlapping Subproblems:** The same `(i, w)` states are reused many times — that's exactly why we store them in a table instead of recomputing
5. **Space Can Be Optimized:** Since `k[i][w]` only depends on row `i-1`, this can be reduced to a 1D array — here it's kept 2D for clarity

---
# Common Mistakes to Avoid

1. ❌ Forgetting the base case (`i==0 || w==0`) — the whole table depends on it
2. ❌ Checking `wt[i] <= w` incorrectly (using `<` instead of `<=`) — off-by-one errors change the answer
3. ❌ Mixing up rows and columns while reading the table (`i` = items, `w` = capacity)
4. ❌ Assuming items can be split — this is strictly 0/1, not Fractional Knapsack
5. ❌ Not initializing arrays with `n+1` / `m+1` size — causes out-of-bound access since indexing starts at 1
