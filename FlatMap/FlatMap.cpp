#include <iostream>

// В этой задаче для простоты не требуется делать контейнер шаблонным,
// это допускается по желанию. Для нешаблонного решения,
// введем типы ключей и значений: ключом будет выступать строка (например, имя
// студента), значением - произвольная структура (например, численные
// характеристики студента).

// Ключ - типа string.
typedef std::string sKey;
// Значение - струкура с характеристиками ключа.
struct TValue {
  TValue () {
    Age = 0;
    Weight = 0;
  }
  
  TValue (const unsigned& age, const unsigned& weight) {
    Age = age;
      Weight = weight;
  }

  friend bool operator!=(const TValue &a, const TValue &b) {
    if (b.Age != a.Age || b.Weight != a.Weight) {
      return true;
    }
    return false;
  }
  friend bool operator==(const TValue &a, const TValue &b) {
    return !(a != b);
  }

  unsigned Age;
  unsigned Weight;
};
// Структура: Ключ, Значние.
struct TMapValue {
  TMapValue () {
    Key = sKey();
    Value = TValue();
  }

  TMapValue (const sKey& key, const TValue& val) {
    Key = key;
    Value = val;
  }

  friend bool operator!=(const TMapValue &a, const TMapValue &b) {
    if (a.Key != b.Key || a.Value != b.Value) {
      return true;
    }
    return false;
  }
  friend bool operator==(const TMapValue &a, const TMapValue &b) {
    return !(a != b);
  }

  sKey Key;
  TValue Value;
};

class TFlatMap {
public:
  TFlatMap ()
      : Capacity (DefaultCapacity), SizeArr (0) {
    Arr = new TMapValue[Capacity];
  };

  ~TFlatMap () {
    delete[] Arr;
  };

  TFlatMap (const TFlatMap& b) {
    Capacity = b.Capacity;
    SizeArr = b.SizeArr;
    Arr = new TMapValue[Capacity];

    std::copy(b.Arr, &(b.Arr[SizeArr]), Arr);
  };

  TFlatMap(TFlatMap &&b) noexcept {
    Capacity = b.Capacity;
    SizeArr = b.SizeArr;
    Arr = b.Arr;
    b.Arr = nullptr;
  }; 
  
  //+ Бинарный поиск по ключу. Возвращаемое значение - индекс в массиве.
  int BinarySearch (const sKey& key) const {
    int left = -1;
    int right = SizeArr;
    int mid;

    while (right - left > 1) {
      mid = (left + right) / 2;

      if (Arr[mid].Key < key) {
        left = mid;
      } 
      else {
        right = mid;
      }
    }

    return right;
  }
  //+ Обменивает значения двух флетмап.
  void swap(TFlatMap &b) {
    if (&b != this){
      TFlatMap tmp (std::move(*this));
      *this = std::move(b);
      b = std::move(tmp);
    }
  }
  //+
  TFlatMap &operator=(const TFlatMap &b) {
    if (&b != this) {
      SizeArr = b.SizeArr;
      Capacity = b.Capacity;

      delete[] Arr;
      Arr = new TMapValue[Capacity];
    
      std::copy(b.Arr, &(b.Arr[SizeArr]), Arr);
    }
    return *this;
  }
  //+
  TFlatMap &operator=(TFlatMap &&b) noexcept {
    if (&b != this) {
      SizeArr = b.SizeArr;
      Capacity = b.Capacity;

      delete[] Arr;
    
      Arr = b.Arr;
      b.Arr = nullptr;
    }
    return *this;
  }
  //+ Очищает контейнер.
  void clear() {
    delete[] Arr;
    Capacity = DefaultCapacity;
    Arr = new TMapValue[Capacity];
    SizeArr = 0;
  }
  //+ Удаляет элемент по заданному ключу. Возвращаемое значение - успешность удаления.
  bool erase(const sKey &k) {
    int index = BinarySearch (k);
      
    if (Arr[index].Key == k) {
      std::copy (&Arr[index + 1], &Arr[SizeArr], &Arr[index]);
      Arr[SizeArr - 1] = TMapValue ();
      --SizeArr;
      return true;
    }

    return false;
  }
  //+ Вставка в контейнер. Возвращаемое значение - успешность вставки.
  bool insert(const sKey &k, const TValue &v) {
    int index = BinarySearch (k);

    if (Arr[index].Key != k) {
      if (SizeArr == Capacity) {
        Capacity *= 2;
        TMapValue* newArr = new TMapValue[Capacity];
        std::copy(Arr, &Arr[SizeArr - 1], newArr);

        delete[] Arr;

        Arr = newArr;
      }
      
      std::copy_backward(&Arr[index], &Arr[SizeArr], &Arr[SizeArr + 1]); 
      Arr[index].Key = k;
      Arr[index].Value = v;
      ++SizeArr;
      return true;
    }

    return false;
  }
  //+ Проверка наличия значения по заданному ключу.
  bool contains(const sKey &k) const {
    int index = BinarySearch (k);

    return (Arr[index].Key == k);
  }
  //+ Возвращает значение по ключу. Небезопасный метод.
  // В случае отсутствия ключа в контейнере, вставляет в контейнер
  // значение, созданное конструктором по умолчанию и возвращает ссылку на него.
  TValue &operator[](const sKey &k) {
    int index = BinarySearch (k);

    if (Arr[index].Key != k){
      insert (k, TValue());
    }

    return Arr[index].Value;
  };

  //+ Возвращает значение по ключу. Бросает исключение при неудаче.
  TValue &at(const sKey &k) {
    int index = BinarySearch (k);
    
    if (Arr[index].Key == k){
      return Arr[index].Value;
    }
    else {
      throw std::invalid_argument("Not found arguments\n");
    }
  };
  // Возвращает значение по ключу. Бросает исключение при неудаче.
  const TValue &at(const sKey &k) const {
    int index = BinarySearch (k);
    
    if (Arr[index].Key == k){
      return Arr[index].Value;
    }
    else {
      throw std::invalid_argument("Not found arguments\n");
    }
  };
  //+
  size_t size() const {
    return SizeArr;
  };
  //+
  bool empty() const {
    return !SizeArr;
  };
  //+
  friend bool operator!=(const TFlatMap &a, const TFlatMap &b);
  //+
  friend bool operator==(const TFlatMap &a, const TFlatMap &b);
  // Выводит весь FlatMap в виде "Key: x Age: y Weight: z"
  void PrintMap () {
    for (int i = 0; i < SizeArr; ++i) {
      std::cout << "Key: " << Arr[i].Key << " Age: " << Arr[i].Value.Age << " Weight: " << Arr[i].Value.Weight << std::endl; 
    }
    std::cout << std::endl;
  }

private:
  TMapValue* Arr;
  static const int DefaultCapacity = 8;
  int Capacity;
  int SizeArr;
};
//+
int min (const int &a, const int &b) {
  return a < b? a : b;
}
//+
bool operator!=(const TFlatMap &a, const TFlatMap &b) {
  if (a.SizeArr != b.SizeArr) {
    return true;
  }

  for (int i = 0; i < a.SizeArr; ++i) {
    if (a.Arr[i] != b.Arr[i]) {
      return true;
    }
  }

  return false;
}
//+
bool operator==(const TFlatMap &a, const TFlatMap &b) {
  return !(a != b);
}