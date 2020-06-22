#include "utils.h"

/*
 * A Reflector is special part aof Enigma
 *
 * The decoding works because of this very
 * part of enigma. When the signal travels
 * to all of the rotors it hits reflector from
 * where it returns and take up a new journey
 *
 * Its very interesting to note that no character
 * ever returns itself in enigma because a
 * reflectors input never return itself as
 * output.
 */
class Reflector {
 private:
  int config[26];
  static bool validMatch(int[]);

 public:
  Reflector();
  explicit Reflector(int[]);
  Reflector(const Reflector &) = delete;
  Reflector(Reflector &&) = delete;
  Reflector &operator=(const Reflector &);
  bool operator==(const Reflector &);
  bool operator!=(const Reflector &);
  int pass(int);
  void randomMatches();
};

/*
 * Initialize the Reflector with random inputs
 *
 * @default constructor
 */
Reflector::Reflector() { randomMatches(); }

/*
 * Initialize a reflector with give I/O map
 *
 * @parameterized constructor
 *
 * @param takes the I/O map for Reflector
 * The I/O map must be symmetrical
 */
Reflector::Reflector(int arr[]) {
  if (validMatch(arr)) {
    for (int i = 0; i < 26; i++) {
      config[i] = arr[i];
    }
  } else {
    randomMatches();
  }
}

/*
 * Gives the output for given input to Reflector
 *
 * @param the input integer
 *
 * @returns the output of the Reflector
 */
int Reflector::pass(int a) {
  a = (a + 26) % 26;
  return config[a];
}

/*
 * An utility to check if given
 * I/O map is valid or not
 *
 * @params integer array for mapping of pairs
 *
 * @return true if valid false otherwise
 */
bool Reflector::validMatch(int arr[]) {
  bool check1 = checkAllNumbers(arr, 26);
  if (check1) {
    int check2 = checkSymmetry(arr, 26);
    if (check2 == 13) {
      return true;
    }
  }
  return false;
}

/*
 * Creates a random matching pairing or I/O map
 */
void Reflector::randomMatches() {
  int var[26];
  for (int i = 0; i < 26; i++) {
    var[i] = i;
  }
  shuffle(var, 26);
  for (int i = 0; i < 13; i++) {
    config[var[2 * i]] = var[2 * i + 1];
    config[var[2 * i + 1]] = var[2 * i];
  }
}

/*
 * For copying one reflector settings to other
 *
 * @params The instance which needs to be copied
 *
 * @returns a reference to this object
 */
Reflector &Reflector::operator=(const Reflector &r) {
  for (int i = 0; i < 26; i++) {
    config[i] = r.config[i];
  }
  return *this;
}

/*
 * For comparing two Reflector instances
 * for equality
 *
 * @param the instance which is to be compared
 *
 * @returns true if same false otherwise
 */
bool Reflector::operator==(const Reflector &r) {
  for (int i = 0; i < 26; i++) {
    if (config[i] != r.config[i]) {
      return false;
    }
  }
  return true;
}

/*
 * For comparing two Reflector instances
 * for inequality
 *
 * @param the instance which is to be compared
 *
 * @returns true if different false otherwise
 */
bool Reflector::operator!=(const Reflector &r) {
  for (int i = 0; i < 26; i++) {
    if (config[i] != r.config[i]) {
      return true;
    }
  }
  return false;
}