#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "core/library.h"
#include "core/test.h"
#include "decks/bolas.h"
#include "decks/eld.h"
#include "decks/m20.h"
#include "decks/thb.h"
#include "search/task.h"

const Library &GetFormat() {
  // return kELD;
  // return kM20;
  return kTHB;
  // return kBolas;
}

const bool DEBUG_ON = false;

int main(int argc, char *argv[]) {
  // TEST(blah);
  TestRegistration::Singleton().RunTests();
  INFO << "Started program...\n";
  srand(4);
  // StepTwo();
  // StepThree();
  // StepFour();
  // RunBruteForceSearch();
  CompareParams(); // <-- THIS
  // CompareStrategies();
  return 0;
}
