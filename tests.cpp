#include <sstream>
#include <iostream>
#include <cassert>
#include "stdio.h"
//#include "functions.h"

using std::cout; using std::endl;

struct TestObjs {
  // add test objs
};

TestObjs *setup() {
  TestObjs *objs = new TestObjs;
  // initialize test objs
  return objs;
}

void cleanup(TestObjs *objs) {
}

void testPowerOfTwo();
// add more

int main(int argc, char *argv[]) {
  //TEST_INIT();
  // allow test name to be specified on the command line
  if (argc > 1) {
    //tctest_testname_to_execute = argv[1];
  }

  testPowerOfTwo();
  // add more



  //TEST_FINI();
}

void testPowerOfTwo() {
  // assert (0 == powerOfTwo(2));
  // assert (1 == powerOfTwo(3));
  // assert (0 == powerOfTwo(4));
  // assert (0 == powerOfTwo(1024));
  // assert (1 == powerOfTwo(-4));
  // assert (1 == powerOfTwo(-1025));
  // cout << "passed testPowerOfTwo" << endl;
}
