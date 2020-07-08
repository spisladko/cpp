#include <iostream>


class int_list_t {
private:
    struct node_t {
		int value;
		node_t *next, *prev;

		node_t(int num) {
			value = num;
			prev = nullptr;
			next = nullptr;
		}
	};

    size_t size;
    node_t *head, *tail;

	node_t* get(const size_t pos) const {
		node_t* temp;
		if (pos >= size) {
			std::cout << "Index is out of range";
			exit(0);
		}
		if (pos <= size/2) {
            node_t temp = head;
            for (size_t i = 0; i < pos; i++) {
                temp = temp->next;
			}
		} else {
            node_t temp = tail;
            for (size_t i = size - 1; i > pos; i--) {
                temp = temp->prev;
            }
		}
	return temp;
	}

public:
    int_list_t() {
		head = tail = nullptr;
		size = 0;
	}

    int_list_t(const int_list_t &other) {
		head = tail = nullptr;
		size = 0;
		node_t* temp = other.head;
		while (temp != nullptr) {
			push_back(temp->value);
			temp = temp->next;
		}
	}

    int_list_t(size_t count, int value) {
		head = tail = nullptr;
		size = 0;
        for (size_t i = 0; i < count; i++) {
            push_back(value);
        }
    }

    ~int_list_t() {
    	clear();
    }

    int_list_t &operator=(const int_list_t &other){
		if(this == &other) {
			return *this;
		}
		int_list_t(other).swap(*this);
		return *this;
	}

    int &operator[](size_t pos) {
    	return get(pos)->value;
    }
    const int operator[](size_t pos) const {
    	return get(pos)->value;
    }

    int &back() {
    	return tail->value;
    }
    const int back() const {
    	return tail->value;
    }

    int &front() {
    	return head->value;
    }
    const int front() const {
    	return head->value;
    }

    void clear() {
		while (head) {
			tail = head->next;
			delete head;
			head = tail;
		}
		head = tail = nullptr;
		size = 0;

    }

    size_t get_size() const {
    	return size;
    }

	bool empty() const {
		return size == 0;
	}

    void insert(size_t pos, int new_val) {
		if (pos > size) {
			std::cout << "Index is out of range";
			exit(0);
		}
		if (pos == size) {
			push_back(new_val);
		} else if (pos == 0) {
			push_front(new_val);
		}
		int i = 1;
		node_t* Ins = head;
		Ins = get(pos)
		node_t* PrevIns = Ins->prev;
		node_t* temp = new node_t(new_val);
		if(PrevIns != 0 && size != 1)
			  PrevIns->next = temp;
		temp->next = Ins;
		temp->prev = PrevIns;
		Ins->prev = temp;
		size++;
	}

	void push_front(int new_val) {
		node_t* temp = new node_t(new_val);
		if (size == 0) {
			head = tail = temp;
		} else {
			head->prev = temp;
			temp->next = head;
			head = temp;
		}
		size++;
	}

	void push_back(int new_val) {
		node_t* temp = new node_t(new_val);
		if (size == 0) {
			head = tail = temp;
		} else {
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
		}
		size++;
	}

    void erase(size_t pos) {
		if (pos >= size) {
			std::cout << "Index is out of range";
			exit(0);
		}
        if (pos == 0) {
            pop_front();
        }
        else if(pos == size - 1) {
            pop_back();
        }
        else {
            node_t* temp = get(pos);
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete(temp);
            size--;
        }
	}

	void pop_front() {
		if (size == 1) {
			head = tail = nullptr;
			size = 0;
		} else {
			node_t* temp;
			temp->prev = 0;
			temp->value = head->value;
			temp->next = head;
			delete head;
			temp = head;
			size--;
		}
	}

	void pop_back() {
		if (size == 1) {
			head = tail = nullptr;
			size = 0;
		} else {
			node_t* temp;
			temp->next = 0;
			temp->value = tail->value;
			delete tail;
			temp = tail;
			size--;
		}
	}

    int_list_t splice(size_t start_pos, size_t count) {
        if (start_pos > size || start_pos + count > size) {
            std::cout << "Index is out of range";
            exit(0);
        }
        int_list_t result = int_list_t();
        node_t *temp = get(start_pos);
        result.head = temp;
        for (size_t i = 0; i < count; i++) {
            temp = temp->next;
        }
        result.tail = temp->prev;
        result.head->prev->next = result.tail->next;
        result.tail->next->prev = result.head->prev;
        result.head->prev = nullptr;
        result.tail->next = nullptr;
        result.size = count;
        size -= count;
        return result;
    }
    int_list_t &merge(int_list_t &other) {
        if (head == nullptr){
            head = other.head;
            tail = other.tail;
            return *this;
        }
        tail->next = other.head;
        other.head->prev = tail;
        tail = other.tail;
        size += other.get_size();
        other.tail = nullptr;
        other.head = nullptr;
        other.size = 0;
        return *this;
    }

    void reverse() {
        node_t* temp = head;
        while (temp != nullptr) {
            std::swap(temp->next, temp->prev);
            temp = temp->prev;
        }
        std::swap(head, tail);
	}

    void swap(int_list_t &other) {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size, other.size);
    }

private:
    friend std::istream &operator>>(std::istream &stream, int_list_t &list);
    friend std::ostream &operator<<(std::ostream &stream, const int_list_t &list);
};

std::istream &operator>>(std::istream &stream, int_list_t &list) {
	int temp;
	while (stream >> temp) {
		list.push_back(temp);
	}
	return stream;
}

std::ostream &operator<<(std::ostream &stream, const int_list_t &list) {
    auto temp = list.head;
    while (temp != nullptr) {
        stream << temp->value;
        if (temp->next != nullptr) {
            stream << ", ";
        }
        temp = temp->next;
    }
    return stream;
<<<<<<< HEAD
}
=======
}
>>>>>>> 593eed6953b53884936e59edaaa4bcaec1606f39
