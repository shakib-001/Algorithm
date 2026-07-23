# Longest Common Subsequence (LCS) - Complete Notes

## Table of Contents
1. [Introduction to LCS](#introduction-to-lcs)
2. [Approach - Dynamic Programming](#approach---dynamic-programming)
3. [Code Breakdown](#code-breakdown)
4. [DP Table Explanation](#dp-table-explanation)
5. [Complete Example](#complete-example)
6. [Time & Space Complexity](#time--space-complexity)
7. [Important Notes](#important-notes)
8. [Common Mistakes to Avoid](#common-mistakes-to-avoid)

---

# Introduction to LCS

## What is LCS?
**LCS is the longest sequence of characters that appears, in the same relative order, in both given strings (not necessarily contiguous).**

```cpp
char x[m+1], y[n+1];   // input strings
int c[m+1][n+1];       // DP table: c[i][j] = LCS length of x[1..i] and y[1..j]
```

**Key Characteristics:**
- A subsequence keeps relative order but does not need to be contiguous
- Different from "Substring" (which must be contiguous)
- There can be more than one valid LCS of the same length
- Both strings are compared character by character

**Real-life Examples:**
- Diff tools (comparing two versions of a file)
- DNA sequence comparison in bioinformatics
- Spell-checking / auto-correction
- Version control systems (git diff)

---

# Approach - Dynamic Programming

## 1. Brute Force (Why it's not used here)
**Try every possible subsequence of one string and check if it exists in the other**

- Number of subsequences of a string of length `m` is `2^m`
- Time complexity becomes exponential: `O(2^min(m,n))`
- Not practical for long strings

---

## 2. Dynamic Programming (Used in this code)
**Build a table bottom-up, comparing characters of both strings pair by pair**

```cpp
int c[m+1][n+1];

for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
        if (i == 0 || j == 0)
            c[i][j] = 0;                              // base case
        else if (x[i] == y[j])
            c[i][j] = c[i - 1][j - 1] + 1;             // characters matched
        else
            c[i][j] = max(c[i - 1][j], c[i][j - 1]);   // characters mismatched
    }
}
```

**Why use Dynamic Programming?**
- Same `(i, j)` subproblem would be computed repeatedly otherwise
- Each subproblem is solved once and reused across the table
- Time complexity reduces from exponential to `O(m * n)`
- Printing the full table makes match/mismatch decisions easy to trace

---

# Code Breakdown

## 1. Taking Input
**Read both strings and store them 1-indexed**

```cpp
int m, n;
cin >> m >> n;

char x[m+1], y[n+1];
for(int i = 1; i <= m; i++) cin >> x[i];
for(int j = 1; j <= n; j++) cin >> y[j];
```

**Note:** Index 0 is left unused on purpose, so `i == 0` / `j == 0` cleanly represents "empty string" for the base case.

---

## 2. Base Case
**If either string is empty, there can be no common subsequence**

```cpp
if (i == 0 || j == 0)
    c[i][j] = 0;
```

**Time Complexity:** O(1) per cell

**Note:** This fills the entire first row and first column of the table with zeros.

---

## 3. Recurrence - Characters Match (`x[i] == y[j]`)
**If the current characters are the same, they must be part of the LCS**

```cpp
c[i][j] = c[i - 1][j - 1] + 1;
```

- The matched character is counted (`+1`)
- The rest of the LCS comes from the diagonal cell, i.e., both strings shortened by one character

**Time Complexity:** O(1) per cell

---

## 4. Recurrence - Characters Mismatch (`x[i] != y[j]`)
**If the current characters differ, one of them must be excluded**

```cpp
c[i][j] = max(c[i - 1][j], c[i][j - 1]);
```

- `c[i-1][j]` → result if we drop the current character of `x`
- `c[i][j-1]` → result if we drop the current character of `y`
- `max()` of both → best possible LCS length ignoring one mismatched character

**Time Complexity:** O(1) per cell

---

## 5. Printing the DP Table
**Display the table with both strings as row/column headers**

```cpp
for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
        cout << c[i][j] << "\t";
    }
    cout << endl;
}
```

**Best Practice:** Watching how the table fills up makes it clear exactly where the length increases (matches) and where it just carries forward (mismatches).

---

## 6. Final Answer
**The bottom-right cell holds the LCS length of the full strings**

```cpp
cout << "LCS Length: " << c[m][n] << endl;
```

**Time Complexity:** O(1) lookup, since it's already computed

---

# DP Table Explanation

## Table Reference

| `c[i][j]` means | Explanation |
|---|---|
| `i` (row) | first `i` characters of string `x` |
| `j` (column) | first `j` characters of string `y` |
| value in cell | LCS length between those two prefixes |

## Reading the Table

```cpp
if (x[i] == y[j]) c[i][j] = c[i-1][j-1] + 1;
else              c[i][j] = max(c[i-1][j], c[i][j-1]);
```

Diagonal moves in the table represent matched characters; horizontal/vertical moves represent skipped (mismatched) characters.

---

# Complete Example

## Example: Small LCS Run

x = "ABC"
y = "AC"

**Table:**

| | 0 | A | C |
|---|---|---|---|
| **0** | 0 | 0 | 0 |
| **A** | 0 | 1 | 1 |
| **B** | 0 | 1 | 1 |
| **C** | 0 | 1 | 2 |

**Input:**
3 2
A B C
A C
**Output:**
LCS Length: 2
