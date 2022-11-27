[![Actions Status](https://github.com/LevyMatan/Geeks4Geeks/workflows/MacOS/badge.svg)](https://github.com/LevyMatan/Geeks4Geeks/actions)
[![Actions Status](https://github.com/LevyMatan/Geeks4Geeks/workflows/Windows/badge.svg)](https://github.com/LevyMatan/Geeks4Geeks/actions)
[![Actions Status](https://github.com/LevyMatan/Geeks4Geeks/workflows/Ubuntu/badge.svg)](https://github.com/LevyMatan/Geeks4Geeks/actions)
[![Actions Status](https://github.com/LevyMatan/Geeks4Geeks/workflows/Style/badge.svg)](https://github.com/LevyMatan/Geeks4Geeks/actions)
[![Actions Status](https://github.com/LevyMatan/Geeks4Geeks/workflows/Install/badge.svg)](https://github.com/LevyMatan/Geeks4Geeks/actions)
[![codecov](https://codecov.io/gh/LevyMatan/Geeks4Geeks/branch/master/graph/badge.svg)](https://codecov.io/gh/LevyMatan/Geeks4Geeks)

# Geeks For Geeks - Problem of the Day

Here are a bunch of coding question solutions.

## Add Binary Strings

Given two binary strings A and B consisting of only 0s and 1s.
Find the resultant string after adding the two Binary Strings.
Note: The input strings may contain leading zeros but the output
string should not have any leading zeros.

### Example 1

```txt
Input:
A = "1101", B = "111"
Output: 10100
Explanation:
 1101
+ 111
10100
```

### Example 2

```txt
Input:
A = "10", B = "01"
Output: 11
Explanation:
  10
+ 01
  11
```

URL: https://practice.geeksforgeeks.org/problems/add-binary-strings3805/1

## Shenyrash and his Bits

Shreyansh has an integer N.
He is really curious about the binary representation of integers.
He sees that any given integer has a number of set bits.
Now he wants to find out that how many positive integers,
strictly less than N, have the same number of set bits as N.
He is a little weak in maths. Help him find the number of integers.
Note : Since N takes large values, brute force won't work.

### Example 1

```txt
        Input:
        N = 8
        Output: 3
        Explanation:
        Binary representation of 8 : 1000
        So the integers less than 8 with
        same number of set bits are : 4, 2, 1
        Hence, the result is 3.
```

### Example 2

```txt
        Input:
        N = 4
        Output: 2
        Explanation:
        Binary representation of 4 : 100
        So the integers less than 4 with
        same number of set bits are : 2, 1
        So, The result is 2.
```

        Expected Time Complexity: O(log(n))
        Expected Auxiliary Space: O(log(n)*log(n))


        Constraints :
        1 <= N <= 10^12

 URL: https://practice.geeksforgeeks.org/problems/shreyansh-and-his-bits1420/1
