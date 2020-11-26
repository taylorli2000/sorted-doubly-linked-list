template <typename T>
class SortedList {
	struct Node {
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr) : data_(data), next_(next), prev_(prev) {}
	};
	Node* front_;
	Node* back_;
public:
	class const_iterator {
		friend class SortedList;
		Node* curr_;
		const SortedList* theList_;
		const_iterator(Node* curr, const SortedList* theList) : curr_(curr), theList_(theList) {}
	public:
		const_iterator() : curr_(nullptr), theList_(nullptr) {}
		//This function makes the const_iterator point to the next node.
		//It returns the updated const_iterator.
		const_iterator& operator++() {
			curr_ = curr_->next_;
			return *this;
		}
		//This function makes the const_iterator point to the next node.
		//It returns the original const_iterator.
		const_iterator operator++(int) {
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}
		//This function makes the const_iterator point to the previous node.
		//It returns the updated const_iterator.		
		const_iterator& operator--() {
			if (curr_ != nullptr) {
				curr_ = curr_->prev_;
			}
			else if (theList_ != nullptr) {
				curr_ = theList_->back_;
			}
			return *this;
		}
		//This function makes the const_iterator point to the previous node.
		//It returns the original const_iterator.
		const_iterator operator--(int) {
			const_iterator old = *this;
			if (curr_ != nullptr) {
				curr_ = curr_->prev_;
			}
			else if (theList_ != nullptr) {
				curr_ = theList_->back_;
			}
			return old;
		}
		//This function accepts a const_iterator object and compares the current object for equivalency.
		//It returns true if they are equal.
		bool operator==(const_iterator rhs) {
			return theList_ == rhs.theList_ && curr_ == rhs.curr_;
		}
		//This function accepts a const_iterator object and compares the current object for equivalency.
		//It returns true if they are not equal.
		bool operator!=(const_iterator rhs) {
			return !(*this == rhs);
		}
		//This function returns the data of the node as a const.
		const T& operator*() const {
			return curr_->data_;
		}
	};
	class iterator : public const_iterator {
		friend class SortedList;
		iterator(Node* curr, const SortedList* theList) : const_iterator(curr, theList) {}
	public:
		iterator() : const_iterator() {}
		//This function makes the iterator point to the next node.
		//It returns the updated iterator.
		iterator& operator++() {
			this->curr_ = this->curr_->next_;
			return *this;
		}
		//This function makes the iterator point to the next node.
		//It returns the original iterator.
		iterator operator++(int) {
			iterator old = *this;
			this->curr_ = this->curr_->next_;
			return old;
		}
		//This function makes the iterator point to the previous node.
		//It returns the updated iterator.
		iterator& operator--() {
			if (this->curr_ != nullptr) {
				this->curr_ = this->curr_->prev_;
			}
			else if (this->theList_ != nullptr) {
				this->curr_ = this->theList_->back_;
			}
			return *this;
		}
		//This function makes the iterator point to the previous node.
		//It returns the original iterator.
		iterator operator--(int) {
			iterator old = *this;
			if (this->curr_ != nullptr) {
				this->curr_ = this->curr_->prev_;
			}
			else if (this->theList_ != nullptr) {
				this->curr_ = this->theList_->back_;
			}
			return old;
		}
		//This function returns the data of the node.
		T& operator*() {
			return this->curr_->data_;
		}
		//This function returns the data of the node as a const.
		const T& operator*() const {
			return this->curr_->data_;
		}
	};
	SortedList();
	~SortedList();
	SortedList(const SortedList& rhs);
	SortedList& operator=(const SortedList& rhs);
	SortedList(SortedList&& rhs);
	SortedList& operator=(SortedList&& rhs);
	//This function returns an iterator with the node that contains the first piece of data.
	iterator begin() {
		return iterator(front_->next_, this);
	}
	//This function returns an iterator with the node after the last piece of data.
	iterator end() {
		return iterator(back_, this);
	}
	//This function returns a const_iterator with the node that contains the first piece of data.
	const_iterator cbegin() const {
		return const_iterator(front_->next_, this);
	}
	//This function returns an const_iterator with the node after the last piece of data.
	const_iterator cend() const {
		return const_iterator(back_, this);
	}
	iterator insert(const T& data);
	iterator search(const T& data);
	const_iterator search(const T& data) const;
	iterator erase(iterator it);
	iterator erase(iterator first, iterator last);
	bool empty() const;
	int size() const;
};
template <typename T>
SortedList<T>::SortedList() {
	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;
}
template <typename T>
SortedList<T>::~SortedList() {
	Node* temp;
	while (front_ != nullptr) {
		temp = front_->next_;
		delete front_;
		front_ = temp;
	}
}
//This function accepts a SortedList and creates a new SortedList by copying all resources from rhs.
template <typename T>
SortedList<T>::SortedList(const SortedList& rhs) : SortedList() {
	if (!rhs.empty()) {
		Node* nn = nullptr;
		for (const_iterator it = rhs.cbegin(); it != rhs.cend(); it++) {
			nn = new Node(it.curr_->data_, back_, back_->prev_);
			back_->prev_->next_ = nn;
			back_->prev_ = nn;
		}
	}
}
//This function accepts a SortedList and overwrites the current SortedList by copying all resources from rhs.
//It returns the current SortedList.
template <typename T>
SortedList<T>& SortedList<T>::operator=(const SortedList& rhs) {
	if (&rhs != this) {
		erase(begin(), end());
		Node* nn = nullptr;
		for (const_iterator it = rhs.cbegin(); it != rhs.cend(); it++) {
			nn = new Node(it.curr_->data_, back_, back_->prev_);
			back_->prev_->next_ = nn;
			back_->prev_ = nn;
		}
	}
	return *this;
}
//This function accepts a SortedList and creates a new SortedList by taking resources from rhs.
//It leaves rhs in an empty state.
template <typename T>
SortedList<T>::SortedList(SortedList&& rhs) {
	front_ = rhs.front_;
	rhs.front_ = nullptr;
	back_ = rhs.back_;
	rhs.back_ = nullptr;
}
//This function accepts a SortedList and overwrites the current SortedList by taking resources from rhs.
//It leaves rhs in an empty state.
//It returns the current SortedList.
template <typename T>
SortedList<T>& SortedList<T>::operator=(SortedList&& rhs) {
	erase(begin(), end());
	front_ = rhs.front_;
	rhs.front_ = nullptr;
	back_ = rhs.back_;
	rhs.back_ = nullptr;
	return *this;
}
//This function accepts T and creates a new node with T as data.
//The new node is inserted into the SortedList in order.
//It returns an interator to the new node.
template <typename T>
typename SortedList<T>::iterator SortedList<T>::insert(const T& data) {
	Node* nn = nullptr;
	if (empty()) {
		nn = new Node(data, back_, front_);
		front_->next_ = nn;
		back_->prev_ = nn;
	}
	else {
		bool found = false;
		for (iterator it = begin(); it != end() && found == false; it++) {
			if (data < it.curr_->data_) {
				nn = new Node(data, it.curr_, it.curr_->prev_);
				it.curr_->prev_->next_ = nn;
				it.curr_->prev_ = nn;
				found = true;
			}
		}
		if (found == false) {
			nn = new Node(data, back_, back_->prev_);
			back_->prev_->next_ = nn;
			back_->prev_ = nn;
		}
	}
	return iterator(nn, this);
}
//This function accepts T and searches the SortedList for T.
//If found, return an iterator to the matched node. If data is not found, return end().
template <typename T>
typename SortedList<T>::iterator SortedList<T>::search(const T& data) {
	iterator rc = end();
	for (iterator it = begin(); it != end() && rc == end(); it++) {
		if (*it == data) {
			rc = it;
		}
	}
	return rc;
}
//This function accepts T and searches the SortedList for T.
//If found, return a const_iterator to the matched node. If data is not found, return cend().
template <typename T>
typename SortedList<T>::const_iterator SortedList<T>::search(const T& data) const {
	const_iterator rc = cend();
	for (const_iterator it = cbegin(); it != cend() && rc == cend(); it++) {
		if (*it == data) {
			rc = it;
		}
	}
	return rc;
}
//This function accepts an iterator and erases the node pointed to by it.
//It returns an iterator with the next node in the SortedList. 
template <typename T>
typename SortedList<T>::iterator SortedList<T>::erase(iterator it) {
	if (it.curr_ != nullptr && it != end()) {
		it.curr_->next_->prev_ = it.curr_->prev_;
		it.curr_->prev_->next_ = it.curr_->next_;
		delete (it++).curr_;
	}
	return it;
}
//This function accepts two iterators and erases the nodes between first and last, excluding last.
//It returns the iterator last.
template <typename T>
typename SortedList<T>::iterator SortedList<T>::erase(iterator first, iterator last) {
	while (first != last && first.curr_ != nullptr) {
		first.curr_->prev_->next_ = first.curr_->next_;
		first.curr_->next_->prev_ = first.curr_->prev_;
		delete (first++).curr_;
	}
	return last;
}
//This functions checks for an empty state.
//It returns true if front_'s next_ points to back_;
template <typename T>
bool SortedList<T>::empty() const {
	return front_->next_ == back_;
}
//This function returns the size of the SortedList.
template <typename T>
int SortedList<T>::size() const {
	int rc = 0;
	for (const_iterator it = cbegin(); it != cend(); it++) {
		rc++;
	}
	return rc;
}
