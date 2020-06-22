#include "utils.h"

/*
 * A class to represent the plugboard in Enigma
 *
 * Plugboards in enigma were like switched pairs
 * of characters and it switches two integers
 * For example A becomes G and G becomes A
 * while S remains S itself
 */
class Plugboard {
 private:
  int matches[26];
  static bool validWiring(const int[]);

 public:
  Plugboard();
  explicit Plugboard(const int[]);
  Plugboard(const Plugboard &) = delete;
  Plugboard(Plugboard &&) = delete;
  Plugboard &operator=(const Plugboard &);
  bool operator==(const Plugboard &);
  bool operator!=(const Plugboard &);
  int pass(int);
  void showMatches(int[]);
  void plugPair(int, int);
  void unplug(int);
  void randomSwitch(int);
  void resetAll();
};

/*
 * Default constructor makes no switching
 * i.e. pairs all character with themselves
 *
 * @constructor
 */
Plugboard::Plugboard() { resetAll(); }

/*
 * Make the required Connections
 * If given argument is not valid does nothing
 *
 * @parameterized constructor
 *
 * @param An array of size 26 with numbers 0-25 not to be reapeated
 * Array denotes the pairing of characters, it must be symmetrical
 * arr[23] = 2, then arr[2] must be 23
 */
Plugboard::Plugboard(const int pairs[]) {
  if (validWiring(pairs)) {
    for (int i = 0; i < 26; i++) {
      matches[i] = pairs[i];
    }
  }
}

/*
 * Function to return the paired cahracter
 *
 * @param an input integer
 *
 * @returns the paired integer
 */
int Plugboard::pass(int input) {
  input = input % 26;
  return matches[input];
}

/*
 * Pair the given two characters
 * If the given integers are already paired then remove
 * that pairing and make the intended pair
 *
 * @param two integers which should be paired
 * the range of integers should be 0-25
 */
void Plugboard::plugPair(int part1, int part2) {
  if (part1 >= 0 && part1 < 26 && part2 >= 0 && part2 < 26) {
    if (matches[part1] != part1) {
      matches[matches[part1]] = matches[part1];
    }
    if (matches[part2] != part2) {
      matches[matches[part2]] = matches[part2];
    }
    matches[part1] = part2;
    matches[part2] = part1;
  }
}

/*
 * An utility to unplug a pair
 *
 * @params the integer to unplug
 */
void Plugboard::unplug(int a) {
  if (a >= 0 && a < 26) {
    if (matches[a] != a) {
      int b = matches[a];
      matches[b] = b;
      matches[a] = a;
    }
  }
}

/*
 * An utility to show the current wiring of plugboard
 *
 * @param an integer array of size atleast 26
 *
 * The pairing is copied in the array in first 26 places
 */
void Plugboard::showMatches(int copy[]) {
  for (int i = 0; i < 26; i++) {
    copy[i] = matches[i];
  }
}

/*
 *Resets all integers to pair themselves
 */
void Plugboard::resetAll() {
  for (int i = 0; i < 26; i++) {
    matches[i] = i;
  }
}

/*
 * Performs random pairing of the plugboard
 *
 * @params no of pairs to be made
 *
 * @defaults no of pairs is 13
 */
void Plugboard::randomSwitch(int count = 13) {
  resetAll();
  count = count < 0 ? 13 : count > 13 ? 13 : count;
  int var[26];
  for (int i = 0; i < 26; i++) {
    var[i] = i;
  }
  shuffle(var, 26);
  for (int i = 0; i < count; i++) {
    matches[var[2 * i]] = var[2 * i + 1];
    matches[var[2 * i + 1]] = var[2 * i];
  }
}

/*
 * An utility to check that provided pairs is valid
 *
 * @static method
 *
 * @params an array of integers
 *
 * @returns true if valid false otherwise
 */
bool Plugboard::validWiring(const int pairs[]) {
  bool check1 = checkAllNumbers(pairs, 26);
  if (check1) {
    int check2 = checkSymmetry(pairs, 26);
    if (check2 != -1) {
      return true;
    }
  }
  return false;
}

/*
 * For copying two plugboard settings
 *
 * @param An instance of class whose contents
 * is to be copied
 */
Plugboard &Plugboard::operator=(const Plugboard &p) {
  for (int i = 0; i < 26; i++) {
    matches[i] = p.matches[i];
  }
  return *this;
}

/*
 * For comparing two plugboard settings
 *
 * @param An instance of class which should
 * be comapred
 *
 * @returns boolean for same or not
 */
bool Plugboard::operator==(const Plugboard &p) {
  for (int i = 0; i < 26; i++) {
    if (matches[i] != p.matches[i]) {
      return false;
    }
  }
  return true;
}

/*
 * For comparing two plugboard settings
 *
 * @param An instance of class which should
 * be comapred
 *
 * @returns boolean for diffrent or not
 */
bool Plugboard::operator!=(const Plugboard &p) {
  for (int i = 0; i < 26; i++) {
    if (matches[i] != p.matches[i]) {
      return true;
    }
  }
  return false;
}