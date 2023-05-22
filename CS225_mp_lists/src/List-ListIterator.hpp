
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    // @TODO: graded in mp_lists part 1
    ListNode* position_;
    ListNode* tail;

  public:
    ListIterator() : position_(NULL), tail(NULL) { }
    ListIterator(ListNode* x, ListNode* y) : position_(x), tail(y) { }


    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in mp_lists part 1
        this->position_ = this->position_->next;
        return *(this);
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in mp_lists part 1
        ListNode* temp = this->position_;
        this->position_ = this->position_->next;
        return ListIterator(temp, tail);
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in mp_lists part 1
        if(this->position_ == NULL) {
            this->position_ = this->tail;
        } else {
            this->position_ = this->position_->prev;
        }
        return *(this);
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // @TODO: graded in mp_lists part 1
        ListNode* temp = this->position_;
        if(this->position_ == NULL) {
            this->position_ = this->tail;
            return ListIterator(temp, tail);
        } else {
            this->position_ = this->position_->prev;
        }
        return ListIterator(temp, tail);
    }

    bool operator!=(const ListIterator& rhs) {
        // @TODO: graded in mp_lists part 1
        return position_ != rhs.position_;
    }

    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
