#include "FlatMap.hpp"
#define Multiplier_Capacity 2

TValue::TValue () {
  Age = 0;
  Weight = 0;
}

TValue::TValue (const size_t& age, const size_t& weight) {
  Age = age;
  Weight = weight;
}

bool operator!=(const TValue &a, const TValue &b) {
  return (b.Age != a.Age || b.Weight != a.Weight);
}
bool operator==(const TValue &a, const TValue &b) {
  return !(a != b);
}

TFlatMap::TMapValue::TMapValue() {
  Key = sKey();
  Value = TValue();
}

TFlatMap::TMapValue::TMapValue(const sKey& key, const TValue& val) {
  Key = key;
  Value = val;
}

bool TFlatMap::TMapValue::operator==(const TFlatMap::TMapValue &a) {
  return (a.Key == Key && a.Value == Value);
}

TFlatMap::TFlatMap ()
    : Capacity (DefaultCapacity), SizeArr (0) {
  Arr = new TMapValue[Capacity];
}

TFlatMap::~TFlatMap () {
  delete[] Arr;
}

TFlatMap::TFlatMap (const TFlatMap& b) {
  Capacity = b.Capacity;
  SizeArr = b.SizeArr;
  Arr = new TMapValue[Capacity];

  std::copy(b.Arr, &(b.Arr[SizeArr]), Arr);
}

TFlatMap::TFlatMap(TFlatMap &&b) noexcept {
  Capacity = b.Capacity;
  SizeArr = b.SizeArr;
  Arr = b.Arr;
  b.Arr = nullptr;
}

size_t TFlatMap::BinarySearch (const sKey& key) const {
  long long left = -1;
  long long right = SizeArr;
  long long mid;

  while (right > left + 1) {
    mid = left + (right - left) / 2;

    if (Arr[mid].Key < key) {
      left = mid;
    } 
    else {
      right = mid;
    }
  }

  return right;
}

void TFlatMap::swap(TFlatMap &b) {
  if (&b != this){
    TFlatMap tmp (std::move(*this));
    *this = std::move(b);
    b = std::move(tmp);
  }
}

TFlatMap& TFlatMap::operator=(const TFlatMap &b) {
  if (&b != this) {
    SizeArr = b.SizeArr;
    Capacity = b.Capacity;

    delete[] Arr;
    Arr = new TMapValue[Capacity];

    std::copy(b.Arr, &(b.Arr[SizeArr]), Arr);
  }
  return *this;
}

TFlatMap& TFlatMap::operator=(TFlatMap &&b) noexcept {
  if (&b != this) {
    SizeArr = b.SizeArr;
    Capacity = b.Capacity;

    delete[] Arr;

    Arr = b.Arr;
    b.Arr = nullptr;
  }
  return *this;
}

void TFlatMap::clear() {
  delete[] Arr;
  Capacity = DefaultCapacity;
  Arr = new TMapValue[Capacity];
  SizeArr = 0;
}

bool TFlatMap::erase(const sKey &k) {
  size_t index = BinarySearch (k);

  if (Arr[index].Key == k) {
    std::copy (&Arr[index + 1], &Arr[SizeArr], &Arr[index]);
    Arr[SizeArr - 1] = TMapValue ();
    --SizeArr;
    return true;
  }

  return false;
}

bool TFlatMap::insert(const sKey &k, const TValue &v) {
  size_t index = BinarySearch (k);

  if (Arr[index].Key != k) {
    if (SizeArr == Capacity) {
      Capacity *= Multiplier_Capacity;
      TMapValue* newArr = new TMapValue[Capacity];
      std::copy(Arr, &Arr[SizeArr], newArr);

      delete[] Arr;

      Arr = newArr;
    }

    std::copy_backward(&Arr[index], &Arr[SizeArr], &Arr[SizeArr + 1]);
    Arr[index] = TMapValue(k,v);
    ++SizeArr;
    return true;
  }

  return false;
}

bool TFlatMap::contains(const sKey &k) const {
  size_t index = BinarySearch (k);

  return (Arr[index].Key == k);
}

TValue& TFlatMap::operator[](const sKey &k) {
  size_t index = BinarySearch (k);

  if (Arr[index].Key != k){
    insert (k, TValue());
  }

  return Arr[index].Value;
}

TValue& TFlatMap::at(const sKey &k) {
  size_t index = BinarySearch (k);

  if (Arr[index].Key != k) {
    throw std::invalid_argument("Not found arguments\n");

  }
  return Arr[index].Value;
}

const TValue& TFlatMap::at(const sKey &k) const {
  size_t index = BinarySearch (k);

  if (Arr[index].Key != k) {
    throw std::invalid_argument("Not found arguments\n");
  }
  return Arr[index].Value;
}

size_t TFlatMap::size() const {
  return SizeArr;
}

bool TFlatMap::empty() const {
  return !SizeArr;
}

bool operator!=(const TFlatMap &a, const TFlatMap &b) {
  return !(a == b);
}
bool operator==(const TFlatMap &a, const TFlatMap &b) {
  if (a.SizeArr != b.SizeArr) {
    return false;
  }

  return std::equal (a.Arr, &a.Arr[a.SizeArr], b.Arr, &b.Arr[b.SizeArr]);
}