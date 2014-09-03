/*
 * TestUtils.hh
 *
 * Simple testing framework
 *
 *  Created on: Sep 1, 2014
 *      Author: Brady Johnson
 */


#include <list>
#include <string>
#include <iostream>

using namespace std;

namespace test_utils {

void logFail(const string &test, const string &msg = string(""))
{
  cout << "Test Failure: " << test;
  if(!msg.empty())
  {
    cout << ", " << msg;
  }
  cout << endl;
}

void logPass(const string &test)
{
  cout << "Test Passed: " << test << endl;
}

typedef bool (*TEST_FUNC_POINTER)();

struct TestCase
{
  TestCase(const string &name, TEST_FUNC_POINTER test) : test_(test)
  {
	  if(name[0] == '&')
	  {
		  testName_ = name.substr(1);
	  }
  }
  string testName_;
  TEST_FUNC_POINTER test_;
};

typedef list<TestCase> TestCaseList;

#define ADD_TEST(test, testList) { test_utils::TestCase tc(#test, test); testList.push_back(tc); }

bool executeTest(TestCase &tc)
{
  try
  {
    bool result = (tc.test_)();
    if(result)
    {
      logPass(tc.testName_);
    }
    else
    {
      logFail(tc.testName_);
    }

    return result;
  }
  catch(std::exception &e)
  {
    logFail(tc.testName_, e.what());
    return false;
  }
  catch(...)
  {
    logFail(tc.testName_, "caught unexpected exception");
    return false;
  }
}

};
