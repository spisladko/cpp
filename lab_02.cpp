#include <iostream>
using namespace std;

class safe_long_long_t {
private:
    long long value;
public:
    explicit safe_long_long_t (long long x) {
        value = x;
    }

    safe_long_long_t operator=(const safe_long_long_t &a) {
        value = a.value;
<<<<<<< HEAD
        return *this;
    }

    safe_long_long_t &operator+=(const safe_long_long_t& a) {
        value += a.value;
        return *this;
    }

    safe_long_long_t &operator-=(const safe_long_long_t& a) {
        value -= a.value;
        return *this;
    }

    safe_long_long_t &operator*=(const safe_long_long_t& a) {
        value *= a.value;
        return *this;
    }

    safe_long_long_t &operator/=(const safe_long_long_t& a) {
        value /= a.value;
        return *this;
    }

    safe_long_long_t &operator%=(const safe_long_long_t& a) {
        value %= a.value;
        return *this;
    }

=======
		return *this;
    }

	safe_long_long_t &operator+=(const safe_long_long_t& a) {
		value += a.value;
		return *this;
	}

	safe_long_long_t &operator-=(const safe_long_long_t& a) {
		value -= a.value;
		return *this;
	}
	
	safe_long_long_t &operator*=(const safe_long_long_t& a) {
		value *= a.value;
		return *this;
	}
	
	safe_long_long_t &operator/=(const safe_long_long_t& a) {
		value /= a.value;
		return *this;
	}
	
	safe_long_long_t &operator%=(const safe_long_long_t& a) {
		value %= a.value;
		return *this;
	}
	
>>>>>>> 2cb76aa16d70ddd015ab59dc5e4a3d920c94a5cd
//префиксный инкремент
    safe_long_long_t& operator++() {
        value++;
        return *this;
    }
//постфиксный инкремент
    safe_long_long_t operator++(int i) {
<<<<<<< HEAD
        safe_long_long_t oldValue = *this;
        ++*this;
=======
        safe_long_long_t oldValue(value);
        value++;
>>>>>>> 2cb76aa16d70ddd015ab59dc5e4a3d920c94a5cd
        return oldValue;
    }
//префиксный декремент
    safe_long_long_t& operator--() {
<<<<<<< HEAD
        --value;
=======
        value--;
>>>>>>> 2cb76aa16d70ddd015ab59dc5e4a3d920c94a5cd
        return *this;
    }
//постфиксный декремент
    safe_long_long_t operator--(int i) {
<<<<<<< HEAD
        safe_long_long_t oldValue = *this;
        --*this;
=======
        safe_long_long_t oldValue(value);
        value--;
>>>>>>> 2cb76aa16d70ddd015ab59dc5e4a3d920c94a5cd
        return oldValue;
    }

    friend ostream &operator<<(ostream &out, const safe_long_long_t &a) {
        out << a.value;
        return out;
    };

    friend istream &operator>>(istream &in, safe_long_long_t &a) {
        in >> a.value;
        return in;
    };
<<<<<<< HEAD

    friend bool operator==(const safe_long_long_t& a, const safe_long_long_t& b);
    friend bool operator>(const safe_long_long_t& a, const safe_long_long_t& b);
    friend bool operator<(const safe_long_long_t& a, const safe_long_long_t& b);
    friend bool operator>=(const safe_long_long_t& a, const safe_long_long_t& b);
    friend bool operator<=(const safe_long_long_t& a, const safe_long_long_t& b);
=======
	
	friend bool operator==(const safe_long_long_t& a, const safe_long_long_t& b); 
	friend bool operator>(const safe_long_long_t& a, const safe_long_long_t& b);
	friend bool operator<(const safe_long_long_t& a, const safe_long_long_t& b);
	friend bool operator>=(const safe_long_long_t& a, const safe_long_long_t& b);
	friend bool operator<=(const safe_long_long_t& a, const safe_long_long_t& b);
>>>>>>> 2cb76aa16d70ddd015ab59dc5e4a3d920c94a5cd
};

safe_long_long_t operator+(safe_long_long_t a, const safe_long_long_t& b) {
    return (a += b);
}

safe_long_long_t operator-(safe_long_long_t a, const safe_long_long_t& b) {
    return (a -= b);
}

safe_long_long_t operator*(safe_long_long_t a, const safe_long_long_t& b) {
    return (a *= b);
}

safe_long_long_t operator/(safe_long_long_t a, const safe_long_long_t& b) {
    return (a /= b);
}

safe_long_long_t operator%(safe_long_long_t a, const safe_long_long_t& b) {
    return (a %= b);
}

bool operator==(const safe_long_long_t& a, const safe_long_long_t& b) {
    return (a.value == b.value);
}

bool operator!=(const safe_long_long_t& a, const safe_long_long_t& b) {
    return !(a == b);
}

bool operator>(const safe_long_long_t& a, const safe_long_long_t& b) {
    return (a.value > b.value);
}

bool operator<(const safe_long_long_t& a, const safe_long_long_t& b) {
    return !((a > b)||(a == b));
}

bool operator>=(const safe_long_long_t& a, const safe_long_long_t& b) {
    return ((a > b)||(a == b));
}

bool operator<=(const safe_long_long_t& a, const safe_long_long_t& b) {
    return !(a > b);
}


class safe_c_array_t : public error_code {
private:
    int size;
    int* arr;
public:
    explicit safe_c_array_t (int n) {
        size = n;
        arr = new int[size];
    }
<<<<<<< HEAD

    safe_c_array_t &operator=(const safe_c_array_t& arr2) {
        if (this != &arr2) {
                    delete[] arr;
                    size = arr2.size;
                    arr = new int[size];
                    for (int i = 0; i < size; i++) {
                        arr[i] = arr2.arr[i];
                    }
            }
        return *this;
    }

=======
	
	safe_c_array_t &operator=(const safe_c_array_t& arr2) {
		for (int i = 0; i < size; i++) {
			arr[i] = arr2.arr[i];
		}
	}
			
>>>>>>> 2cb76aa16d70ddd015ab59dc5e4a3d920c94a5cd
    safe_c_array_t (const safe_c_array_t& origin) {
        size = origin.size;
        arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = origin.arr[i];
<<<<<<< HEAD
        }
    }

=======
		}
		return *this;
    }
	
>>>>>>> 2cb76aa16d70ddd015ab59dc5e4a3d920c94a5cd
    void fill() {
        for (int i = 0; i < size; i++) {
            arr[i] = i;
        }
    }
<<<<<<< HEAD

=======
	
>>>>>>> 2cb76aa16d70ddd015ab59dc5e4a3d920c94a5cd
    int &operator[](int k) {
        return arr[k];
    }

    ~safe_c_array_t () {
        delete[]arr;
    }

};


int main() {
    safe_long_long_t a(5);
    safe_long_long_t b(10);
    cout << a + b << endl;
    cout << a * b << endl;
    cout << a / b << endl;
    cout << a - b << endl;
    cout << a-- << ' ' << --a << endl << endl;

    safe_c_array_t arr = safe_c_array_t(9);
    safe_c_array_t arr_copy = safe_c_array_t(arr);
    arr.fill();
    arr_copy.fill();
    std::cout << arr[3]<< std::endl;
    std::cout << arr_copy[4];

    return 0;

}
