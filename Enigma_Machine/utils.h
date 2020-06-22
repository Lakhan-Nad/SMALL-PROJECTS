#ifndef INCLUDE_H_UTILS
#define INCLUDE_H_UTILS

#include <cstdlib>  // rand()

/*
 * Shuffles a array in place
 *
 * @params array and length of array
 *
 * @returns none
 */
void shuffle(int var[], int n) {
  int temp, random;
  for (int i = 0; i < n / 2; i++) {
    temp = var[i];
    random = std::rand() % n;
    var[i] = var[random];
    var[random] = temp;
  }
}

/*
 * Check if all numbers from 0:n-1 is present
 * in given array of size n
 *
 * @params array and size
 *
 * @returns boolean
 */
bool checkAllNumbers(const int arr[], int n) {
  int count = 0;
  int proxy[n] = {0};
  for (int i = 0; i < n; i++) {
    if (arr[i] >= 0 && arr[i] < n) {
      count += 1 - proxy[arr[i]];
      proxy[arr[i]] = 1;
    }
  }
  if (count != n) {
    return false;
  }
  return true;
}

/*
 * check for symmetry of array of size n with
 * elements in range 0:n-1
 *
 * if array of length n contains all elements from
 * 0:n-1 then it can be made a symmetrical array
 * arr[i] = j and arr[j] = i
 *
 * @params array and its size
 *
 * @returns boolean
 */
int checkSymmetry(const int arr[], int n) {
  int count = 0;
  int diff = 0;
  for (int i = 0; i < n; i++) {
    int a = arr[i];
    if (a >= 0 && a < n) {
      int b = arr[a];
      if (b == i) {
        count++;
      }
      if (a != b) {
        diff++;
      }
    }
    if (count != n) {
      return -1;
    }
  }
  return diff;
}

#endif