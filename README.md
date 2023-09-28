# Geeks For Geeks - Problem of the Day

[![Actions Status](https://github.com/LevyMatan/Geeks4Geeks/workflows/MacOS/badge.svg)](https://github.com/LevyMatan/Geeks4Geeks/actions)
[![Actions Status](https://github.com/LevyMatan/Geeks4Geeks/workflows/Windows/badge.svg)](https://github.com/LevyMatan/Geeks4Geeks/actions)
[![Actions Status](https://github.com/LevyMatan/Geeks4Geeks/workflows/Ubuntu/badge.svg)](https://github.com/LevyMatan/Geeks4Geeks/actions)
[![Actions Status](https://github.com/LevyMatan/Geeks4Geeks/workflows/Style/badge.svg)](https://github.com/LevyMatan/Geeks4Geeks/actions)
[![Actions Status](https://github.com/LevyMatan/Geeks4Geeks/workflows/Install/badge.svg)](https://github.com/LevyMatan/Geeks4Geeks/actions)
[![codecov](https://codecov.io/gh/LevyMatan/Geeks4Geeks/branch/master/graph/badge.svg)](https://codecov.io/gh/LevyMatan/Geeks4Geeks)

Here are a bunch of coding question solutions.

<details>
<summary><h2>Number of Enclaves</h2></summary>

- [Problem Statement](/include/number_of_enclaves/number_of_enclaves.md)
- [Solution](/source/number_of_enclaves.cpp)
- [Test](/test/number_of_enclaves_test.cpp)

</details>

<details>
<summary><h2>Catalan Number</h2></summary>

Given a number N. The task is to find the Nth catalan number.
The first few Catalan numbers for N = 0, 1, 2, 3, … are 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, …

Catalan Number for N is equal to the number of expressions containing N pairs of paranthesis that are correct matched, i.e., for each of the N '(' there exist N ')' on there right and vice versa.

Since answer can be huge return answer modulo 1e9+7.

### Example 1

```txt
Input:
N = 5
Output: 42
```

### Example 2

```txt
Input:
N = 4
Output: 14
```

</details>

## Flip Bits

Given an array A[] consisting of 0’s and 1’s. A flip operation is one in which you turn 1 into 0 and a 0 into 1. You have to do at most one “Flip” operation of any subarray. Formally, select a range (l, r) in the array A[], such that (0 ≤ l ≤ r < n) holds and flip the elements in this range to get the maximum ones in the final array. You can possibly make zero operations to get the answer.

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(1)

Constraints:
1 ≤ N ≤ 106
0 ≤ A[i] ≤ 1

### Examples

```txt
Input:
N = 5
A[] = {1, 0, 0, 1, 0} 
Output:
4
Explanation:
We can perform a flip operation in the range [1,2]
After flip operation array is : [ 1 1 1 1 0 ]
Count of one after fliping is : 4
[Note: the subarray marked in bold is the flipped subarray]
```

```txt
Input:
N = 7
A[] = {1, 0, 0, 1, 0, 0, 1}
Output:
6
Explanation:
We can perform a flip operation in the range [1,5]
After flip operation array is : [ 1 1 1 0 1 1 1]
Count of one after fliping is : 6
[Note: the subarray marked in bold is the flipped subarray]
```

## Add Binary Strings

Given two binary strings A and B consisting of only 0s and 1s.
Find the resultant string after adding the two Binary Strings.  
Note: The input strings may contain leading zeros but the output
string should not have any leading zeros.

### Examples

```txt
Input:
A = "1101", B = "111"
Output: 10100
Explanation:
 1101
+ 111
10100
```

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

### Examples

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

### Examples

```txt
Input:
n = 3
a[] = {1, 2, 3}
Output: 1 2 3
Explanation: In the given array every
element is non-negative.
```

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
