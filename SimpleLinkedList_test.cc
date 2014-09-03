/*
 * SimpleLinkedList_test.cpp
 *
 * Test cases to test the SimpleLinkedList class
 *
 *  Created on: Sep 1, 2014
 *      Author: Brady Johnson
 */

#include "SimpleLinkedList.hh"
#include "TestUtils.hh"

// Test class used as the object to be stored in the Linked List
struct TestNode
{
  TestNode() : data_(-1) {}
  TestNode(int data) : data_(data) {}
  int data_;
};

// Simple internal method to check the expected size and empty()
bool checkSize(SimpleLinkedList<TestNode> &sll, uint32_t expectedSize)
{
  if(sll.size() != expectedSize)
  {
    return false;
  }

  if(expectedSize == 0)
  {
    return sll.empty();
  }
  else
  {
    return !sll.empty();
  }
}

// Forward declaration, implemented at the end, after all the tests
void getTests(test_utils::TestCaseList &tests);

int main(int argc, char **argv)
{
  test_utils::TestCaseList tests;

  getTests(tests);

  for(test_utils::TestCaseList::iterator testIter = tests.begin(); testIter != tests.end(); ++testIter)
  {
    test_utils::executeTest(*testIter);
  }
}


/********************************************************************
 *
 *                        Size tests
 *
 *******************************************************************/

bool TEST_size_empty()
{
  SimpleLinkedList<TestNode> sll;
  return sll.size() == 0;
}

bool TEST_size_notEmpty()
{
  SimpleLinkedList<TestNode> sll;
  TestNode tn;
  sll.append(tn);
  return sll.size() == 1;
}

bool TEST_empty_empty()
{
  SimpleLinkedList<TestNode> sll;
  return sll.empty() == true;
}

bool TEST_empty_notEmpty()
{
  SimpleLinkedList<TestNode> sll;
  TestNode tn;
  sll.append(tn);
  return sll.empty() == false;
}


/********************************************************************
 *
 *                        Modifier tests
 *
 *******************************************************************/

bool TEST_insert_emptyHead()
{
  SimpleLinkedList<TestNode> sll;
  TestNode tn1(1);
  sll.insert(tn1);

  if(!checkSize(sll, 1))
  {
    return false;
  }

  TestNode tn2(2);
  sll.insert(tn2);

  if(!checkSize(sll, 2))
  {
    return false;
  }

  // The only other way this test can fail is if an exception is thrown

  return true;
}

bool TEST_append_emptyTail()
{
  SimpleLinkedList<TestNode> sll;
  TestNode tn1;
  TestNode tn2;
  sll.append(tn1);
  sll.append(tn2);

  if(!checkSize(sll, 2))
  {
    return false;
  }

  return true;
}

bool TEST_pop_front_empty()
{
  try
  {
    SimpleLinkedList<TestNode> sll;
    sll.pop_front();

    // An exception should have been thrown
    return false;
  }
  catch(std::length_error &e)
  {
    // We're expecting this exception to be thrown
    return true;
  }
}

bool TEST_pop_front_notEmpty()
{
  SimpleLinkedList<TestNode> sll;
  TestNode tn1(1);
  TestNode tn2(2);
  sll.append(tn1);
  sll.append(tn2);

  sll.pop_front();
  if(!checkSize(sll, 1))
  {
    return false;
  }

  // Check that the correct node was removed
  if(sll.front().data_ != 2)
  {
    return false;
  }

  sll.pop_front();

  // It should be empty now
  if(!checkSize(sll, 0))
  {
    return false;
  }

  // Now that its empty, try to pop again
  try
  {
    sll.pop_front();

    // An exception should have been thrown
    return false;
  }
  catch(std::length_error &e)
  {
    // We're expecting this exception to be thrown
    return true;
  }
}

bool TEST_pop_back_empty()
{
  try
  {
    SimpleLinkedList<TestNode> sll;
    sll.pop_back();

    // An exception should have been thrown
    return false;
  }
  catch(std::length_error &e)
  {
    // We're expecting this exception to be thrown
    return true;
  }
}

bool TEST_pop_back_notEmpty()
{
  SimpleLinkedList<TestNode> sll;
  TestNode tn1(1);
  TestNode tn2(2);
  sll.append(tn1);
  sll.append(tn2);

  sll.pop_back();
  if(!checkSize(sll, 1))
  {
    return false;
  }

  // Check that the correct node was removed
  if(sll.back().data_ != 1)
  {
    return false;
  }

  sll.pop_back();

  // It should be empty now
  if(!checkSize(sll, 0))
  {
    return false;
  }

  // Now that its empty, try to pop again
  try
  {
    sll.pop_back();

    // An exception should have been thrown
    return false;
  }
  catch(std::length_error &e)
  {
    // We're expecting this exception to be thrown
    return true;
  }
}

bool TEST_reset()
{
  SimpleLinkedList<TestNode> sll;

  // nothing should happen
  sll.reset();

  TestNode tn1(1);
  sll.append(tn1);

  sll.reset();
  if(!checkSize(sll, 0))
  {
    return false;
  }

  return true;
}

/********************************************************************
 *
 *                        Accessor tests
 *
 *******************************************************************/

bool TEST_front_empty()
{
  try
  {
    SimpleLinkedList<TestNode> sll;
    TestNode tn = sll.front();

    // An exception should have been thrown
    return false;
  }
  catch(std::length_error &e)
  {
    // We're expecting this exception to be thrown
    return true;
  }
}

bool TEST_front_notEmpty()
{
  SimpleLinkedList<TestNode> sll;
  TestNode tn;
  sll.insert(tn);

  TestNode tn2 = sll.front();

  // front() should affect the list at all
  if(!checkSize(sll, 1))
  {
    return false;
  }

  return true;
}

bool TEST_back_empty()
{
  try
  {
    SimpleLinkedList<TestNode> sll;
    TestNode tn = sll.back();

    // An exception should have been thrown
    return false;
  }
  catch(std::length_error &e)
  {
    // We're expecting this exception to be thrown
    return true;
  }
}

bool TEST_back_notEmpty()
{
  SimpleLinkedList<TestNode> sll;
  TestNode tn;
  sll.insert(tn);

  TestNode tn2 = sll.back();

  // front() should affect the list at all
  if(!checkSize(sll, 1))
  {
    return false;
  }

  return true;
}


/********************************************************************
 *
 *                        Iterator tests
 *
 *******************************************************************/

bool TEST_begin_empty()
{
  try
  {
    SimpleLinkedList<TestNode> sll;
    SimpleLinkedList<TestNode>::iterator iter = sll.begin();

    // An exception should have been thrown
    return false;
  }
  catch(std::length_error &e)
  {
    // We're expecting this exception to be thrown
    return true;
  }
}

bool TEST_begin_emptyConst()
{
  try
  {
    SimpleLinkedList<TestNode> sll;
    SimpleLinkedList<TestNode>::const_iterator iter = sll.begin();

    // An exception should have been thrown
    return false;
  }
  catch(std::length_error &e)
  {
    // We're expecting this exception to be thrown
    return true;
  }
}

bool TEST_beginEnd_notEmpty()
{
  SimpleLinkedList<TestNode> sll;

  int iterCount(10);
  for(int i = 0; i < iterCount; ++i)
  {
    TestNode tn(i);
    sll.append(tn);
  }

  int counter(0);
  for(SimpleLinkedList<TestNode>::iterator iter = sll.begin(); iter != sll.end(); ++iter)
  {
    // Check that it iterates the list in order
    if(iter->data_ != counter++)
    {
      return false;
    }
  }

  // Check that it iterated all the way through the list
  if(counter != iterCount)
  {
    return false;
  }

  return true;
}

bool TEST_beginEnd_notEmptyConst()
{
  SimpleLinkedList<TestNode> sll;

  int iterCount(10);
  for(int i = 0; i < iterCount; ++i)
  {
    TestNode tn(i);
    sll.append(tn);
  }

  int counter(0);
  for(SimpleLinkedList<TestNode>::const_iterator iter = sll.begin(); iter != sll.end(); ++iter)
  {
    // Check that it iterates the list in order
    if(iter->data_ != counter++)
    {
      return false;
    }
  }

  // Check that it iterated all the way through the list
  if(counter != iterCount)
  {
    return false;
  }

  return true;
}

bool TEST_end_empty()
{
  try
  {
    SimpleLinkedList<TestNode> sll;
    SimpleLinkedList<TestNode>::iterator iter = sll.end();

    // An exception should have been thrown
    return false;
  }
  catch(std::length_error &e)
  {
    // We're expecting this exception to be thrown
    return true;
  }
}

bool TEST_end_emptyConst()
{
  try
  {
    SimpleLinkedList<TestNode> sll;
    SimpleLinkedList<TestNode>::const_iterator iter = sll.end();

    // An exception should have been thrown
    return false;
  }
  catch(std::length_error &e)
  {
    // We're expecting this exception to be thrown
    return true;
  }
}

/********************************************************************
 *
 *                        Reversal tests
 *
 *******************************************************************/

bool TEST_reverse_iterative_empty()
{
  try
  {
    SimpleLinkedList<TestNode> sll;
    sll.reverseIterative();

    // An exception should have been thrown
    return false;
  }
  catch(std::length_error &e)
  {
    // We're expecting this exception to be thrown
    return true;
  }
}

bool TEST_reverse_iterative_NotEmpty()
{
  SimpleLinkedList<TestNode> sll;

  // do a reverse with just one node
  TestNode tn0(0);
  sll.append(tn0);
  sll.reverseIterative();
  if(!checkSize(sll, 1))
  {
    return false;
  }

  // Populate the list with 10 Nodes, 1-9 (the first was added above)
  int iterCount(10);
  for(int i = 1; i < iterCount; ++i)
  {
    TestNode tn(i);
    sll.append(tn);
  }

  // reverse it, iteratively
  sll.reverseIterative();

  // Now check that the nodes have been reversed
  int counter(iterCount-1);
  for(SimpleLinkedList<TestNode>::iterator iter = sll.begin(); iter != sll.end(); ++iter)
  {
    // Check that it iterates the list in order
    if(iter->data_ != counter--)
    {
      return false;
    }
  }

  if(!checkSize(sll, iterCount))
  {
    return false;
  }

  return true;
}

bool TEST_reverse_recursive_empty()
{
  try
  {
    SimpleLinkedList<TestNode> sll;
    sll.reverseRecursive();

    // An exception should have been thrown
    return false;
  }
  catch(std::length_error &e)
  {
    // We're expecting this exception to be thrown
    return true;
  }
}

bool TEST_reverse_recursive_NotEmpty()
{
  SimpleLinkedList<TestNode> sll;

  // do a reverse with just one node
  TestNode tn0(0);
  sll.append(tn0);
  sll.reverseIterative();
  if(!checkSize(sll, 1))
  {
    return false;
  }

  if(!checkSize(sll, 1))
  {
    return false;
  }

  // Populate the list with 10 Nodes, 1-9 (the first was added above)
  int iterCount(10);
  for(int i = 1; i < iterCount; ++i)
  {
    TestNode tn(i);
    sll.append(tn);
  }

  // reverse it, recursively
  sll.reverseRecursive();

  // Now check that the nodes have been reversed
  int counter(iterCount-1);
  for(SimpleLinkedList<TestNode>::iterator iter = sll.begin(); iter != sll.end(); ++iter)
  {
    // Check that it iterates the list in order
    if(iter->data_ != counter--)
    {
      return false;
    }
  }

  if(!checkSize(sll, iterCount))
  {
    return false;
  }

  return true;
}


void getTests(test_utils::TestCaseList &tests)
{
  // Size tests
  ADD_TEST(&TEST_size_empty, tests);
  ADD_TEST(&TEST_size_notEmpty, tests);
  ADD_TEST(&TEST_empty_empty, tests);
  ADD_TEST(&TEST_empty_notEmpty, tests);

  // Modifier tests
  ADD_TEST(&TEST_insert_emptyHead, tests);
  ADD_TEST(&TEST_append_emptyTail, tests);
  ADD_TEST(&TEST_pop_front_empty, tests);
  ADD_TEST(&TEST_pop_front_notEmpty, tests);
  ADD_TEST(&TEST_pop_back_empty, tests);
  ADD_TEST(&TEST_pop_front_notEmpty, tests);
  ADD_TEST(&TEST_reset, tests);

  // Accessor tests
  ADD_TEST(&TEST_front_empty, tests);
  ADD_TEST(&TEST_front_notEmpty, tests);
  ADD_TEST(&TEST_back_empty, tests);
  ADD_TEST(&TEST_back_notEmpty, tests);

  // Iterator tests
  ADD_TEST(&TEST_begin_empty, tests);
  ADD_TEST(&TEST_begin_emptyConst, tests);
  ADD_TEST(&TEST_beginEnd_notEmpty, tests);
  ADD_TEST(&TEST_beginEnd_notEmptyConst, tests);
  ADD_TEST(&TEST_end_empty, tests);
  ADD_TEST(&TEST_end_emptyConst, tests);

  // Reversal Tests
  ADD_TEST(&TEST_reverse_iterative_empty, tests);
  ADD_TEST(&TEST_reverse_iterative_NotEmpty, tests);
  ADD_TEST(&TEST_reverse_recursive_empty, tests);
  ADD_TEST(&TEST_reverse_recursive_NotEmpty, tests);
}
