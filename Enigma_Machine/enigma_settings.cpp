#include <iostream>

#include "enigma.h"

int main() {
  Enigma x(5, 10);
  x.setOffset(0, 1);
  x.setOffset(1, 2);
  x.setOffset(2, 5);
  x.setOffset(3, 5);
  x.setOffset(4, 6);
  x.plug(0, 25);
  x.plug(1, 24);
  x.plug(8, 20);
  int arr[60];
  for (int i = 0; i < 60; i++) {
    arr[i] = x.operate(i / 2);
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
  x.setOffset(0, 1);
  x.setOffset(1, 2);
  x.setOffset(2, 5);
  x.setOffset(3, 5);
  x.setOffset(4, 6);
  for (int i = 0; i < 60; i++) {
    std::cout << x.operate(arr[i]) << " ";
  }
  std::cout << std::endl;
  x.showPlugs();
  x.showSlot();
}