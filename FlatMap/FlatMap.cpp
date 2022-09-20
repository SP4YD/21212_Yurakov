#include <iostream>>
// В этой задаче для простоты не требуется делать контейнер шаблонным,
// это допускается по желанию. Для нешаблонного решения,
// введем типы ключей и значений: ключом будет выступать строка (например, имя
// студента), значением - произвольная структура (например, численные
// характеристики студента).
using namespace std;

typedef string sKey;
typedef struct TValue TValue;
typedef struct TMapValue TMapValue;

struct TValue {
  TValue () {
      Age = 0;
      Weight = 0;
  }
  TValue (const unsigned& age, const unsigned& weight) {
      Age = age;
      Weight = weight;
  }

  unsigned Age;
  unsigned Weight;
};

struct TMapValue {
  TMapValue () {
      Key = "";
  }
  TMapValue (const sKey& key, const TValue& val) {
      Key = key;
      Value = val;
  }

  sKey Key;
  TValue Value;
};

class FlatMap {
public:
  FlatMap ()
      : capacity (defaultCapacity), size (0) {
      arr = new TMapValue[capacity];
  };

  ~FlatMap () {
      delete[] arr;
  };

  FlatMap (const FlatMap& b) {
      capacity = b.capacity;
      size = b.size;
      arr = new TMapValue[capacity];

      for (int i = 0; i < size; ++i) {
          arr[i] = b.arr[i];
      }
  };

  FlatMap(FlatMap &&b); ///////////////////// Не понятно

  // Обменивает значения двух флетмап.
  // Подумайте, зачем нужен этот метод, при наличии стандартной функции
  // std::swap.
  void swap(FlatMap &b);

  FlatMap &operator=(const FlatMap &b);
  FlatMap &&operator=(FlatMap &&b);

  // Очищает контейнер.
  void clear();
  // Удаляет элемент по заданному ключу.
  bool erase(const Key &k);
  // Вставка в контейнер. Возвращаемое значение - успешность вставки.
  bool insert(const Key &k, const Value &v);

  // Проверка наличия значения по заданному ключу.
  bool contains(const Key &k) const;

  // Возвращает значение по ключу. Небезопасный метод.
  // В случае отсутствия ключа в контейнере, следует вставить в контейнер
  // значение, созданное конструктором по умолчанию и вернуть ссылку на него.
  Value &operator[](const Key &k);

  // Возвращает значение по ключу. Бросает исключение при неудаче.
  Value &at(const Key &k);
  const Value &at(const Key &k) const;

  size_t size() const;
  bool empty() const;

  friend bool operator!=(const FlatMap &a, const FlatMap &b);
  friend bool operator==(const FlatMap &a, const FlatMap &b);

private:
  TMapValue* arr;
  static const int defaultCapacity = 8;
  int capacity;
  int size;
};
