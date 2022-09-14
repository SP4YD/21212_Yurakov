#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

// Управление сложностью - мощный баз ворд

/*int main ()
{
    FILE* f = fopen ("input.txt", "r");
    if (f == NULL) {
        printf ("ERROR");
        return 0;
    }

    size_t arr_size = 0; // сколько прочитано интов
    size_t capacity = 12; // ёмкость выделенной памяти в элемент

    int* arr = (int*)malloc (sizeof (*arr) * capacity);

    while (fscanf (f, "%d", arr + arr_size) == 1) {
        arr_size++;
        if (arr_size == capacity) {
            capacity *= 2;
            int* tmp = (int *) realloc (arr, sizeof (*arr) * capacity);
            if (tmp == NULL) {
                break;
            }
            arr = tmp;
        }
        //arr = realloc (arr, sizeof(*arr) * (i + 1)); // потеряем память
    }

    for (int i = 0; i < arr_size; ++i) {
        printf ("%d ", *(arr + i));
    }

    free (arr);
    fclose (f);

    return 0;
}*/

class Array {
public:
    Array ()
        : capacity (defaultCapacity) {
        arr = (int*)malloc (capacity * sizeof (*arr));
    }
    Array (size_t initial_capacity)
        : capacity (initial_capacity) {
        arr = (int*)malloc (capacity * sizeof (*arr));
    }
    Array (const Array& copy) {
        size = copy.size;
        capacity = copy.capacity;
        arr = (int*)malloc (capacity * sizeof (*arr));

        for (int i = 0; i < size; ++i) {
            arr[i] = copy.arr[i];
        }

        capacity = copy.capacity;
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
    void insert (unsigned int pos, int value) {
        pos += 1;
        if (pos > size + 1) {
            cout << "Error: out of range" << endl;
        } else {
            if (pos == size + 1) {
                push_back (value);
            } else {
                memmove (arr + pos, arr + pos - 1, (size - pos + 1) * sizeof (int));
                arr[pos - 1] = value;
                ++size;
            }
        }
    }
    void print () {
        for (int i = 0; i < size; ++i) {
            cout << arr[i] << ' ';
        }
    }
    int operator[] (const int pos) {
        return arr[pos];
    }
    Array& operator= (const Array& tmp) {
        if (this != &tmp) {
            free (arr);
            capacity = tmp.capacity;
            size = tmp.size;
            arr = (int*)malloc (capacity * sizeof (*arr));
            for (int i = 0; i < size; ++i) {
                arr[i] = tmp.arr[i];
            }
        }
        return *this;
    }
private:
    int* arr = nullptr;
    size_t size = 0ull;
    size_t capacity = 0ull;
    static const int defaultCapacity = 12;
};

int main () {
    Array A;

    FILE* f = fopen ("input.txt", "r");

    if (f == NULL) {
        printf ("ERROR");
        return 0;
    }

    int tmp = 0;
    while (fscanf (f, "%d", &tmp) == 1) {
        A.push_back (tmp);
    }

    Array B = A;

    A.insert (4, 100);
    B.insert (4, 200);

    A.print ();
    cout << endl;
    B.print ();

    cout << endl << "A[4] = " << A[4] << endl << "B[4] = " << B[4] << endl;

    return 0;
}