#include "utils.h"

/*
 * A class to implement a rotor in Enigma
 *
 * Rotor is a mechanical wheel that has an input
 * and a output connection.
 * The rotor can also rotate and provide
 * a different mapping every time
 */
class Roter {
 private:
  int config[26];
  int offset;
  static bool checkValidConfig(const int[]);

 public:
  Roter();
  explicit Roter(const int[], int);
  Roter(const Roter &) = delete;
  Roter(Roter &&) = delete;
  Roter &operator=(const Roter &);
  bool operator==(const Roter &);
  bool operator!=(const Roter &);
  void operator++();
  void operator--();
  void operator++(int);
  void operator--(int);
  void rotate(int);
  int pass(int, bool);
  void setOffset(int);
  void setConfig(int[]);
  void randomRoter();
  int getOffset();
  void getConifg(int[]);
};

/*
 * Initialize a Rotor with random value
 * for input output connection
 *
 * @default constructor
 */
Roter::Roter() { randomRoter(); }

/*
 * Initialize a rotor with I/O and offset
 *
 * @parameterized constructor
 *
 * @params integer array denoting the I/O map
 * the ith integer denotes that for input i
 * the output is that integer. Offset denotes the
 * start rotor starts position
 *
 * @restrictions the I/O map should be size 26 and
 * contains all the integers from 0-25
 */
Roter::Roter(const int arr[], int pos = 0) {
  pos = pos < 0 ? 0 : (pos % 26);
  if (checkValidConfig(arr)) {
    for (int i = 0; i < 26; i++) {
      config[i] = arr[i];
    }
  } else {
    randomRoter();
  }
}

/*
 * Rotates the rotor by given position
 *
 * @params the positions to rotate
 * +ve for right and -ve for left
 */
void Roter::rotate(int x) {
  offset += x;
  offset %= 26;
  if (offset < 0) {
    offset += 26;
    offset %= 26;
  }
}

/*
 * Gives output for given input
 *
 * @params input integer and bool to denote direction
 * true for backward and false otherwise
 *
 * @defaults the default direction is
 * assumed to be forward
 *
 * @returns the output of Rotor
 */
int Roter::pass(int input, bool backward = false) {
  if (!backward) {
    input += offset;
    input %= 26;
    return config[input];
  } else {
    int i;
    for (i = 0; i < 26; i++) {
      if (config[i] == input) {
        break;
      }
    }
    i += 26 - offset;
    i %= 26;
    return i;
  }
}

/*
 * To set offset of the Rotor
 *
 * @param integer denoting offset
 */
void Roter::setOffset(int position) {
  position %= 26;
  if (position < 0) {
    position += 26;
    position %= 26;
  }
  offset = position;
}

/*
 * Sets the configuration if valid
 * @params A integer array of Configuration
 */
void Roter::setConfig(int arr[]) {
  if (checkValidConfig(arr)) {
    for (int i = 0; i < 26; i++) {
      config[i] = arr[i];
    }
  }
}

/*
 * To check if given I/O map is valid
 *
 * @param an array denoting I/O map
 *
 * @returns boolean config is valid or not
 */
bool Roter::checkValidConfig(const int arr[]) {
  return checkAllNumbers(arr, 26);
}

/*
 * A utility to randomly map I/O
 */
void Roter::randomRoter() {
  offset = rand() % 26;
  for (int i = 0; i < 26; i++) {
    config[i] = i;
  }
  shuffle(config, 26);
}

/*
 * Returns the configuration array
 *
 * @params An array to copy config
 */
void Roter::getConifg(int copy[]) {
  for (int i = 0; i < 26; i++) {
    copy[i] = config[i];
  }
}

/*
 * Returns the offset
 *
 * @returns offset value
 */
int Roter::getOffset() { return offset; }

/*
 * For copying a rotor settings
 *
 * @params The Rotor instance that should be
 * copied
 *
 * @returns a reference to this object
 */
Roter &Roter::operator=(const Roter &r) {
  offset = r.offset;
  for (int i = 0; i < 26; i++) {
    config[i] = r.config[i];
  }
  return *this;
}

/*
 * To check if two rotor instances are same
 *
 * @param the instance from which comparison
 * is to be made
 *
 * @returns boolean weather two Rotors are equal
 * or not
 */
bool Roter::operator==(const Roter &r) {
  if (offset == r.offset) {
    for (int i = 0; i < 26; i++) {
      if (config[i] != r.config[i]) {
        return false;
      }
    }
    return true;
  }
  return false;
}

/*
 * To check if two rotor instances are different
 *
 * @param the instance from which comparison
 * is to be made
 *
 * @returns boolean weather two Rotors are inequal
 * or not
 */
bool Roter::operator!=(const Roter &r) {
  if (offset != r.offset) {
    for (int i = 0; i < 26; i++) {
      if (config[i] == r.config[i]) {
        return false;
      }
    }
    return true;
  }
  return false;
}

/*
 * @overload to rotate forward by one position
 * @prefix increament
 */
void Roter::operator++() { this->rotate(1); }

/*
 * @overload to rotate backward by one position
 * @prefix decreament
 */
void Roter::operator--() { this->rotate(-1); }

/*
 * @overload to rotate forward by one position
 * @postfix increament
 */
void Roter::operator++(int) { this->rotate(1); }

/*
 * @overload to rotate backward by one position
 * @postfix decreament
 */
void Roter::operator--(int) { this->rotate(-1); }
