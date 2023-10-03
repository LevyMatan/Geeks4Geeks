# Roman Number to Integer

Given a string in roman number format (s) your task is to convert it to an integer.  
Various symbols and their values are given below.

- I: 1
- V: 5
- X: 10
- L: 50
- C: 100
- D: 500
- M: 1000

## Example 1

```txt
Input:
s = V
Output: 5
```

## Example 2

```txt
Input:
s = III 
Output: 3
```

## Your Task

Complete the function romanToDecimal() which takes a string as input parameter and returns the equivalent decimal number.

Expected Time Complexity: O(|S|), |S| = length of string S.
Expected Auxiliary Space: O(1)

Constraints:
1<=roman no range<=3999

## Solution

### Idea

First lets talk about the rules of roman number.  
Lets try and write the number 1990 as a roman number:  
M = 1000, CM = 900, XC = 90 and IX = 9.
Writing it out would look like MCMXC.  

We add the values of the symbols from left to right.
If the symbol on the left is smaller than the symbol on the right, we subtract the left symbol from the right symbol.
If the symbol on the left is greater than or equal to the symbol on the right, we add the left symbol to the total.
