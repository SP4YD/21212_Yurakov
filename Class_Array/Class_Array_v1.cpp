#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

class Array {
public:
    Array () 
        : capacity (defaultCapacity) {
        arr = (int*)malloc (capacity * sizeof (*arr));
    }
    Array (size_t initial_capacity) 
        : capacity(initial_capacity){
        arr = (int*) malloc (capacity * sizeof (*arr));
    }
    ~Array () {
        free (arr);
    }
    void push_back (int X) {
        if (size == capacity) {
            capacity *= 2;
            int* tmp = (int*)realloc (arr, capacity * sizeof (*arr));
            if (tmp == NULL) {
                cout << "Error";
                return;
            }
            arr = tmp;
        }
        arr[size++] = X;
    }
    void print () {
        for (int i = 0; i < size; ++i) {
            cout << arr[i] << ' ';
        }
    }
private:
    int* arr = nullptr;
    size_t size = 0ull;
    size_t capacity = 0ull;
    static const int defaultCapacity = 12;
};

int main () {
    Array a, b;

    FILE* f = fopen ("input.txt", "r");

    if (f == NULL) {
        printf ("ERROR");
        return 0;
    }

    int tmp = 0;
    while (fscanf (f, "%d", &tmp) == 1) {
        a.push_back (tmp);
    }

    a.print();

    return 0;
}