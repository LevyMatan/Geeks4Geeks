# Geeks For Geeks - Problem of the Day

[![Actions Status](https://github.com/LevyMatan/Geeks4Geeks/workflows/MacOS/badge.svg)](https://github.com/LevyMatan/Geeks4Geeks/actions)
[![Actions Status](https://github.com/LevyMatan/Geeks4Geeks/workflows/Windows/badge.svg)](https://github.com/LevyMatan/Geeks4Geeks/actions)
[![Actions Status](https://github.com/LevyMatan/Geeks4Geeks/workflows/Ubuntu/badge.svg)](https://github.com/LevyMatan/Geeks4Geeks/actions)
[![Actions Status](https://github.com/LevyMatan/Geeks4Geeks/workflows/Style/badge.svg)](https://github.com/LevyMatan/Geeks4Geeks/actions)
[![Actions Status](https://github.com/LevyMatan/Geeks4Geeks/workflows/Install/badge.svg)](https://github.com/LevyMatan/Geeks4Geeks/actions)
[![codecov](https://codecov.io/gh/LevyMatan/Geeks4Geeks/branch/master/graph/badge.svg)](https://codecov.io/gh/LevyMatan/Geeks4Geeks)

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

URL: <https://practice.geeksforgeeks.org/problems/add-binary-strings3805/1>  
:rocket: [Solution](/source/add_binary_strings.cpp)

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

URL: <https://practice.geeksforgeeks.org/problems/shreyansh-and-his-bits1420/1>  
:rocket: [Solution](/source/shenyrash_and_his_bits.cpp)

## Maximum Subarray

Find out the maximum sub-array of non negative numbers from an array.

The sub-array should be contiguous i.e., a sub-array created by choosing the second and
fourth element and skipping the third element is invalid.

Maximum sub-array is defined in terms of the sum of the elements in the sub-array.
Sub-array A is greater than sub-array B if sum(A) > sum(B).

```txt
a = [1, 2, 5, -7, 2, 3]
The two sub-arrays are [1, 2, 5] [2, 3].
The answer is [1, 2, 5] as its sum is larger than [2, 3]
```

NOTE: If there is a tie, then compare with segment's length and return segment which has
maximum length. If there is still a tie, then return the segment with minimum starting index. If
no such subarray is present return "-1"

### Example 1

```txt
Input:
n = 3
a[] = {1, 2, 3}
Output: 1 2 3
Explanation: In the given array every
element is non-negative.
```

### Example 2

```txt
Input:
n = 2
a[] = {-1, 2}
Output: 2
Explanation: The only subarray [2] is
the answer.
```

Your Task:  
Complete the function findSubarray() which takes the array a and the size of the array, n,  
as input parameters and returns an array representing the answer. If there is no subarray return  
an array of length 1 containing -1 only. You don't to print answer or take inputs.  

Expected Time Complexity: O(N)  
Expected Auxiliary Space: O(1)  

Constraints:  
1 ≤ N ≤ 105  
-105 ≤ A[i] ≤ 105  

URL: <https://practice.geeksforgeeks.org/problems/maximum-sub-array5443/1>  
:rocket: [Solution](/source/maximum_sub_array.cpp)
