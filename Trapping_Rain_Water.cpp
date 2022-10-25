// C++ implementation of the problem trapping rain water
  
#include <bits/stdc++.h>
using namespace std;
  

int maxWater(int arr[], int n)
{
    
    int res = 0;
  
    
    for (int i = 1; i < n - 1; i++) {
  
        // Find the maximum element on its left
        int left = arr[i];
        for (int j = 0; j < i; j++)
            left = max(left, arr[j]);
  
        // Find the maximum element on its right
        int right = arr[i];
        for (int j = i + 1; j < n; j++)
            right = max(right, arr[j]);
  
        // Update the maximum water
        res = res + (min(left, right) - arr[i]);
    }
  
    return res;
}
  

int main()
{
    int arr[] = { 1, 3, 0, 5, 1, 4, 1, 6, 2, 3, 0, 4 };
    int n = sizeof(arr) / sizeof(arr[0]);
  
    cout << maxWater(arr, n);
  
    return 0;
}
