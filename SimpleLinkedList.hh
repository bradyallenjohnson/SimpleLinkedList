/*
 * SimpleLinkedList.hh
 *
 *  Created on: Sep 1, 2014
 *      Author: Brady Johnson
 */

#ifndef SIMPLELINKEDLIST_HH_
#define SIMPLELINKEDLIST_HH_

#include <stdexcept>
#include <stdint.h>

/**
 * A simple single LinkedList with minimal functionality
 */
template <class T>
class SimpleLinkedList
{
private:
  /**
   * Internal class used to store the data in the Linked List
   */
  struct ListNode
  {
    ListNode() : next_(NULL) {}
    ListNode(const T &data) : data_(data), next_(NULL) {}
    T data_;
    ListNode *next_;
  };

  /**
   * Internal class used to iterate the Linked List
   */
  class ListIterator
  {
  public:
    ListIterator() : node_(NULL) {}
    ListIterator(ListNode *node) : node_(node) {}
    ListIterator& operator=(ListIterator arg) {node_ = arg.node_; return *this;}
    bool operator==(ListIterator rhs) const { return rhs.node_ == node_; }
    bool operator!=(ListIterator rhs) const { return rhs.node_ != node_; }
    T * operator->() { return &(node_->data_); }
    T const * operator->() const { return &(node_->data_); }
    T & operator*()  { return node_->data_; }
    T operator*() const { return node_->data_; }
    void increment()
    {
      if(node_->next_ == NULL || node_ == SimpleLinkedList::endSentinel.node_)
      {
        node_ = SimpleLinkedList::endSentinel.node_;
      }
      else
      {
        node_ = node_->next_;
      }
    }
    ListIterator operator++() { ListIterator retval(*this); increment(); return retval; }
    ListIterator operator++(int unused) {increment(); return *this;}
  private:
    ListNode *node_;
  };

public:
  typedef ListIterator iterator;
  typedef ListIterator const_iterator;

  SimpleLinkedList() :
    head_(NULL),
    tail_(NULL),
    size_(0)
  {
  }

  ~SimpleLinkedList()
  {
  }

  /*
   * Applying the "Rule of 3": since the dtor is not implemented, no need to impl the copy ctor nor assign operator
   */

  /**
   * Return an iterator to the beginning of the Linked List.
   * If the list is empty, an std::length_error exception will be thrown.
   */
  SimpleLinkedList::iterator begin() { emptyException(); return ListIterator(head_); }
  SimpleLinkedList::const_iterator begin() const { emptyException(); return ListIterator(head_); }

  /**
   * Return an iterator indicating the end of the Linked List has been reached
   * If the list is empty, an std::length_error exception will be thrown.
   */
  SimpleLinkedList::iterator end() { emptyException(); return endSentinel; }
  SimpleLinkedList::const_iterator end() const { emptyException(); return endSentinel; }

  /**
   * Return the number of elements in the linked list
   */
  inline uint32_t size() const { return size_; }

  /**
   * Return true if the list is empty, false otherwise
   */
  inline bool empty() const { return size_ == 0; }

  /**
   * Insert a data node into the head of the Linked List
   */
  void insert(T data)
  {

    if(empty())
    {
      append(data);
      return;
    }

    ListNode *newNode(new ListNode(data));
    newNode->next_ = head_;
    head_ = newNode;
    ++size_;
  }

  /**
   * Append a data node onto the end of the Linked List
   */
  void append(T data)
  {
    ListNode *newNode(new ListNode(data));
    if(empty())
    {
      head_ = newNode;
      tail_ = newNode;
    }
    else
    {
      tail_->next_ = newNode;
      tail_ = newNode;
    }
    size_++;
  }

  /**
   * Remove the node from the head of the Linked list
   * If the list is empty, an std::length_error exception will be thrown.
   */
  void pop_front()
  {
      emptyException();

      if(size() == 1)
      {
        delete head_;
        head_ = tail_ = NULL;
        size_ = 0;
        return;
      }

      ListNode *node(head_->next_);
      delete head_;
      head_ = node;
      size_--;
  }

  /**
   * Remove the node from the tail of the Linked list
   * If the list is empty, an std::length_error exception will be thrown.
   */
  void pop_back()
  {
      emptyException();

      if(size() == 1)
      {
        pop_front();
        return;
      }

      // Iterate to the penultimate node
      ListNode *node(head_);
      while(node->next_ != tail_)
      {
        node = node->next_;
      }
      delete tail_;
      tail_ = node;
      size_--;
  }

  /* For a more complex version, the following two should be implemented
  void insert(iterator iter, T data);
  void remove(iterator iter);
  */

  /**
  * Release the LinkedList resources, emptying the list
  */
  void reset()
  {
    // remove all the nodes
    while(!empty())
    {
      pop_front();
    }
  }

  /**
   * Return the first node in the Linked List without modifying the list.
   * If the list is empty, an std::length_error exception will be thrown.
   */
  inline T front() { emptyException(); return head_->data_; }

  /**
   * Return the last node in the Linked List without modifying the list
   * If the list is empty, an std::length_error exception will be thrown.
   */
  inline T back() { emptyException(); return tail_->data_; }

  /**
   * Reverse the order of all the Nodes in the Linked List iteratively
   * Algorithmic complexity = O(n), No extra memory is used
   * If the list is empty, an std::length_error exception will be thrown.
   */
  void reverseIterative()
  {
    emptyException();
    if(size() == 1)
    {
      // nothing to be done
      return;
    }

    tail_ = head_;
    ListNode *newHead(head_);

    while(head_ != NULL)
    {
      ListNode *node = head_;
      head_ = node->next_;
      node->next_ = newHead;
      newHead = node;
    }

    head_ = newHead;
    tail_->next_ = NULL;
  }

  /**
   * Reverse the order of all the Nodes in the Linked List recursively.
   * Algorithmic complexity = O(n), The only memory used is the stack needed to recurse.
   * If the list is empty, an std::length_error exception will be thrown.
   */
  void reverseRecursive()
  {
    emptyException();
    if(size() == 1)
    {
      // nothing to be done
      return;
    }

    ListNode *node = head_;
    ListNode *newHead;
    ListNode *newTail;
    reverseRecursiveInternal(node, newHead, newTail);
    head_ = newHead;
    tail_ = newTail;
  }

private:

  /**
   * Internal method that actually performs the recursion to reverse the list
   */
  void reverseRecursiveInternal(ListNode *node, ListNode *&head, ListNode *&tail)
  {
    // recursion exit condition
    if(node->next_ == NULL)
    {
      head = node;
      tail = node;
      return;
    }

    reverseRecursiveInternal(node->next_, head, tail);

    tail->next_ = node;
    tail = node;
    node->next_ = NULL;
  }

  /**
   * Internal method to check if the Linked List is empty.
   * Throws a std::length_error exception if it is empty
   */
  void emptyException() const
  {
    if(empty())
    {
      throw std::length_error("the list is empty");
    }
  }

  static ListIterator endSentinel;
  ListNode *head_;
  ListNode *tail_;
  uint32_t size_;
};

template <class T>
typename SimpleLinkedList<T>::ListIterator SimpleLinkedList<T>::endSentinel = SimpleLinkedList<T>::ListIterator(new ListNode());

#endif /* SIMPLELINKEDLIST_HH_ */
