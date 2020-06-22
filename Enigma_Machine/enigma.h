#include "plugboard.h"
#include "reflector.h"
#include "roter.h"
#include "utils.h"

class Enigma {
 private:
  int noOfRoters;
  int noConfig;
  int *slots;
  Roter *rotors;
  Reflector *reflector;
  Plugboard *plugs;

  void freeAll();
  void init(int, int);
  void rotate();

 public:
  Enigma();
  explicit Enigma(int, int);
  Enigma(const Enigma &);
  Enigma(Enigma &&);
  ~Enigma();
  Enigma &operator=(const Enigma &);
  Enigma &operator=(Enigma &&);
  bool operator==(const Enigma &);
  int operate(int);
  void editRoter(int, int[], int);
  void editRoter(int, char[], int);
  void chooseRoters(int[]);
  void setOffset(int, int);
  void plug(int a, int b);
  void unplug(int a);
  void showPlugs();
  void showSlot();
};

Enigma::Enigma() { init(3, 5); }

Enigma::Enigma(int toUse, int total) {
  total = total < 0 ? 5 : (total < 10 ? total : 10);
  toUse = toUse < 0 ? 3 : (toUse < total ? toUse : total);
  init(toUse, total);
}

Enigma::Enigma(const Enigma &e) {
  init(e.noConfig, e.noOfRoters);
  *reflector = *(e.reflector);
  *plugs = *(e.plugs);
  for (int i = 0; i < noOfRoters; i++) {
    rotors[i] = e.rotors[i];
  }
  for (int i = 0; i < noConfig; i++) {
    slots[i] = e.slots[i];
  }
}

Enigma::Enigma(Enigma &&e) {
  init(e.noConfig, e.noOfRoters);
  *reflector = *(e.reflector);
  *plugs = *(e.plugs);
  for (int i = 0; i < noOfRoters; i++) {
    rotors[i] = e.rotors[i];
  }
  for (int i = 0; i < noConfig; i++) {
    slots[i] = e.slots[i];
  }
}

Enigma &Enigma::operator=(const Enigma &e) {
  if (&e == this) {
    return *this;
  }
  freeAll();
  init(e.noConfig, e.noOfRoters);
  *reflector = *(e.reflector);
  *plugs = *(e.plugs);
  for (int i = 0; i < noOfRoters; i++) {
    rotors[i] = e.rotors[i];
  }
  for (int i = 0; i < noConfig; i++) {
    slots[i] = e.slots[i];
  }
  return *this;
}

Enigma::~Enigma() { freeAll(); }

Enigma &Enigma::operator=(Enigma &&e) {
  if (&e == this) {
    return *this;
  }
  noOfRoters = e.noOfRoters;
  noConfig = e.noConfig;
  freeAll();
  rotors = e.rotors;
  slots = e.slots;
  plugs = e.plugs;
  reflector = e.reflector;
  e.rotors = nullptr;
  e.slots = nullptr;
  e.plugs = nullptr;
  e.reflector = nullptr;
  return *this;
}

bool Enigma::operator==(const Enigma &e) {
  bool rotorCount = noOfRoters == e.noOfRoters;
  bool configCount = noConfig == e.noConfig;
  if (rotorCount && configCount) {
    bool sameReflector = *(reflector) == *(e.reflector);
    bool samePlugSettings = *(plugs) == *(e.plugs);
    if (samePlugSettings && sameReflector) {
      for (int i = 0; i < noConfig; i++) {
        if (slots[i] != e.slots[i]) {
          return false;
        }
      }
      for (int i = 0; i < noOfRoters; i++) {
        if (rotors[i] != e.rotors[i]) {
          return false;
        }
      }
      return true;
    }
    return false;
  }
  return false;
}

void Enigma::freeAll() {
  delete rotors;
  delete slots;
  delete reflector;
  delete plugs;
}

void Enigma::init(int config, int count) {
  noOfRoters = count;
  noConfig = config;
  slots = new int[noConfig];
  rotors = new Roter[noOfRoters];
  reflector = new Reflector;
  plugs = new Plugboard;
  for (int i = 0; i < noConfig; i++) {
    slots[i] = i;
  }
}

void Enigma::rotate() {
  for (int i = 0; i < noConfig; i++) {
    rotors[slots[i]]++;
  }
}

int Enigma::operate(int input) {
  input %= 26;
  if (input < 0) {
    input += 26;
    input %= 26;
  }
  input = plugs->pass(input);
  for (int i = 0; i < noConfig; i++) {
    input = rotors[slots[i]].pass(input);
  }
  input = reflector->pass(input);
  for (int i = 0; i < noConfig; i++) {
    input = rotors[slots[noConfig - 1 - i]].pass(input, true);
  }
  input = plugs->pass(input);
  rotate();
  return input;
}

void Enigma::editRoter(int roterNo, int config[], int offset = 0) {
  roterNo %= noOfRoters;
  rotors[roterNo] = Roter(config, offset);
}

void Enigma::editRoter(int roterNo, char s[], int offset = 0) {
  roterNo %= noOfRoters;
  int config[26];
  for (int i = 0; i < 26; i++) {
    if (s[i] >= 'a' && s[i] <= 'z') {
      config[i] = s[i] - 'a';
    } else if (s[i] >= 'A' && s[i] <= 'Z') {
      config[i] = s[i] - 'A';
    } else {
      config[i] = i;
    }
  }
  rotors[roterNo] = Roter(config, offset);
}

void Enigma::chooseRoters(int slotConfig[]) {
  for (int i = 0; i < noConfig; i++) {
    slots[i] = slotConfig[i] % noOfRoters;
  }
}

void Enigma::setOffset(int configNo, int offset = 0) {
  configNo %= noConfig;
  offset %= 26;
  rotors[slots[configNo]].setOffset(offset);
}

void Enigma::plug(int part1, int part2) { plugs->plugPair(part1, part2); }

void Enigma::unplug(int part1) { plugs->unplug(part1); }

void Enigma::showPlugs() {
  std::cout << "The Paired Plugs: " << std::endl;
  int arr[26];
  plugs->showMatches(arr);
  for (int i = 0; i < 26; i++) {
    std::cout << (char)(i + 'A') << ":" << (char)(arr[i] + 'A') << " ";
  }
  std::cout << std::endl;
}

void Enigma::showSlot() {
  std::cout << "No of Roters: " << noOfRoters << std::endl;
  std::cout << "In Use: " << noConfig << std::endl;
  std::cout << "Config of Slots: ";
  for (int i = 0; i < noConfig; i++) {
    std::cout << slots[i] << " ";
  }
  std::cout << std::endl;
}