#include <iostream>
using namespace std;

class safe_long_long_t {
private:
    long long value;
public:
    explicit safe_long_long_t (long long x) {
        this->value = x;
    }

    void operator = (const safe_long_long_t &a) {
        this->value = a.value;
    }

    safe_long_long_t operator + (const safe_long_long_t& a) {
        return safe_long_long_t (this->value + a.value);
    }

    safe_long_long_t operator - (const safe_long_long_t& a) {
        return safe_long_long_t (this->value - a.value);
    }

    safe_long_long_t operator * (const safe_long_long_t& a) {
        return safe_long_long_t (this->value * a.value);
    }

    safe_long_long_t operator / (const safe_long_long_t& a) {
        return safe_long_long_t (this->value / a.value);
    }

    safe_long_long_t operator % (const safe_long_long_t& a) {
        return safe_long_long_t (this->value % a.value);
    }
//префиксный инкремент
    safe_long_long_t& operator ++ () {
        this->value++;
        return *this;
    }
//постфиксный инкремент
    safe_long_long_t& operator ++ (int i) {
        safe_long_long_t oldValue(*this);
        this->value++;
        return oldValue;
    }
//префиксный декремент
    safe_long_long_t& operator -- () {
        this->value--;
        return *this;
    }
//постфиксный декремент
    safe_long_long_t& operator -- (int i) {
        safe_long_long_t oldValue(*this);
        this->value--;
        return oldValue;
    }

    bool operator == (const safe_long_long_t& a) {
        return (this->value == a.value);
    }

    bool operator != (const safe_long_long_t& a) {
        return (this->value != a.value);
    }

    bool operator > (const safe_long_long_t& a) {
        return (this->value > a.value);
    }

    bool operator < (const safe_long_long_t& a) {
        return (this->value < a.value);
    }

    bool operator >= (const safe_long_long_t& a) {
        return (this->value >= a.value);
    }

    bool operator <= (const safe_long_long_t& a) {
        return (this->value <= a.value);
    }


    friend ostream &operator << (ostream &out, const safe_long_long_t &a) {
        out << a.value;
        return out;
    };

    friend istream &operator >> (istream &in, safe_long_long_t &a)
    {
        in >> a.value;
        return in;
    };
};

class safe_c_array_t : public error_code {
private:
    int size;
    int* arr;
public:
    explicit safe_c_array_t (int n) {
        this->size = n;
        this->arr = new int [size];
    }

    safe_c_array_t (const safe_c_array_t& origin)
    {
        size = origin.size;
        arr = new int[size];
        for (int i = 0; i < size; i++)
            arr[i] = origin.arr[i];
    }
    void fill() {
        for (int i = 0; i < size; i++) {
            arr[i] = i;
        }
    }
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
    cout << a - b << endl << endl;

    safe_c_array_t arr = safe_c_array_t(9);
    safe_c_array_t arr_copy = safe_c_array_t(arr);
    arr.fill();
    arr_copy.fill();
    std::cout << arr[3]<< std::endl;
    std::cout << arr_copy[4];

    return 0;

}
