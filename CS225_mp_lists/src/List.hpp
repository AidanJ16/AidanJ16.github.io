/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = NULL;
    //head_->next = NULL;
    //head_->prev = NULL;

    tail_ = NULL;
    //tail_->next = NULL;
    //tail_->prev = NULL;

    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_, tail_);
}
/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(nullptr, tail_);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1
  while(head_ != NULL) {
    ListNode * tmp = head_;
    head_ = head_->next;
    delete tmp;
  }
  length_ = 0;
}


/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  // My own code for when given empty list
  if(head_ == NULL) {
    newNode->next = NULL;
    newNode->prev = NULL;
    head_ = newNode;
    tail_ = newNode;
    head_->next = NULL;
    head_->prev = NULL;
    tail_->next = NULL;
    tail_->prev = NULL;
    length_++;
    return;
  } else {
    newNode -> next = head_;
    head_->prev = newNode;
    newNode -> prev = NULL;
    head_ = newNode;
    length_++;
    return;
  }
  
  /*if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }*/

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  if(head_ == NULL) {
    newNode->next = NULL;
    newNode->prev = NULL;
    head_ = newNode;
    tail_ = newNode;
    head_->next = NULL;
    head_->prev = NULL;
    tail_->next = NULL;
    tail_->prev = NULL;
    length_++;
    return;
  } else {
    newNode->prev = tail_;
    newNode->next = NULL;
    tail_->next = newNode;
    tail_ = newNode;
    length_++;
    return;
  }
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in mp_lists part 1
  if(splitPoint >= length_) return NULL;
  if(splitPoint <= 0) return start;
  ListNode * curr = start;
  for (int i = 0; i < splitPoint; i++) {
    curr = curr->next;
  }
  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }
  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in part 1
  ListNode * toMove = head_->next;
  ListNode * track = head_;
  //std::cout << track->next << std::endl;
  while(toMove != NULL && toMove != tail_) {
    toMove->prev->next = toMove->next;
    toMove->next->prev = toMove->prev;

    toMove->next = NULL;
    toMove->prev = tail_;
    tail_->next = toMove;
    tail_ = toMove;
    //std::cout << track->next << std::endl;
    /*if(track->next == NULL) {
      break;
    }*/
    //std::cout << track->next << std::endl;
    track = track->next;
    toMove = track->next;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in mp_lists part 2
  //to perform reverse of nodes
  if(startPoint == NULL || endPoint == NULL) {
    return;
  }
  ListNode* tmp1 = NULL;
  ListNode* tmp2 = startPoint;
  //to save new start and end positions
  ListNode* new_end = startPoint;
  ListNode* new_start = endPoint;

  //to cover edge cases
  ListNode* previous = NULL;
  if(startPoint->prev != NULL) {
    previous = startPoint->prev;
  }
  ListNode* next = NULL;
  if(endPoint->next != NULL) {
    next = endPoint->next;
  }
  //performs the reverse
  while(tmp2 != endPoint) {
    tmp1 = tmp2->prev;
    tmp2->prev = tmp2->next;
    tmp2->next = tmp1;
    tmp2 = tmp2->prev;
  }
  tmp1 = endPoint->prev;
  endPoint->prev = endPoint->next;
  endPoint->next = tmp1;
  //now we can fix edge cases
  startPoint = new_start;
  endPoint = new_end;
  if(previous != NULL) {
    previous->next = startPoint;
  }
  startPoint->prev = previous;
  if(next != NULL) {
    next->prev = endPoint;
  }
  endPoint->next = next;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in mp_lists part 2
  if(n >= length_) {
    reverse();
    return;
  } 
  if(n == 0 || n == 1) {
    return;
  }
  else {
    ListNode* start = head_;
    ListNode* back = head_;
    int count = 0;
    while(start != NULL) {
      for(int i = 1; i < n; i++) {
        if(back->next != NULL) {
          back = back->next;
        }
      }
      
      reverse(start, back);
      if(start->prev == NULL) {
        head_ = start;
      }
      if(back->next == NULL) {
        tail_ = back;
      }
      start = back->next;
      back = back->next;
    }
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    if(tail_ != NULL) {
      while(tail_->next != NULL) {
        tail_ = tail_->next;
      }
    }
    length_ = length_ + otherList.length_;

    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in mp_lists part 2
    //edge cases
    if(first == NULL) {
      first = second;
      return first;
    }
    if(second == NULL) {
      return first;
    }
    //create new list to return
    //set our new list to the smallest val node
    ListNode* toRet = first;
    if(first->data < second->data) {
      toRet = first;
      first = first->next;
    } else {
      toRet = second;
      second = second->next;
    }
    //save start of our new list by creating tmp
    ListNode* tmp = toRet;
    //iterate until added one full list to our new list
    while(first != NULL && second != NULL) {
      //if first data smaller we add this node to tmp
      //iterate first
      if(first->data < second->data) {
        tmp->next = first;
        first->prev = tmp;
        first = first->next;
        //otherwise add second node to tmp
        //iterate second
      } else {
        tmp->next = second;
        second->prev = tmp;
        second = second->next;
      }
      //always adding a node so always iterate our list
      tmp = tmp->next;
    }
    //since we iterated through one or both lists
    //if a list is leftover we add the rest of it to our list
    if(first != NULL) {
      tmp->next = first;
      first->prev = tmp;
    }  
    if(second != NULL) {
      tmp->next = second;
      second->prev = tmp;
    }
    //set first to head of our new list and return
    first = toRet;
    return first;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in mp_lists part 2
  ListNode* tmp1 = start;
  ListNode* tmp2 = start->next;
  //base case, if no node given we return start no sorting needed
  //if one node its already sorted so return it
  if(start == NULL) return start;
  if(start->next == NULL) return start;

  //split into two linked lists using split function
  //rec2 will have more length if odd total length
  ListNode * rec2 = split(start, chainLength / 2);
  ListNode * rec1 = start;

  //find new lengths accordingly to even or odd numbered list
  int new_l1 = 0;
  int new_l2 = 0;
  if(chainLength % 2 == 0) {
    //if even they have equal length
    new_l1 = chainLength / 2;
    new_l2 = chainLength / 2;
  } else {
    //if odd rec2 gets longer length
    new_l2 = (chainLength / 2) + 1;
    new_l1 = (chainLength / 2);
  }
  //recursive call
  ListNode* base = mergesort(rec1, new_l1);
  ListNode* base2 = mergesort(rec2, new_l2);

  //sort all the divided lists
  return merge(base, base2);
}
