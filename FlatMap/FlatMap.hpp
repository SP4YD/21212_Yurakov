#pragma once

#include <iostream>

// Key - type string
typedef std::string sKey;
// Value - structure with key characteristics
struct TValue {
  // Construct empty Value with age = 0, weight = 0
  TValue ();
  // Construct empty Value with the given input values
  TValue (const size_t& age, const size_t& weight);

  friend bool operator!=(const TValue &a, const TValue &b);
  friend bool operator==(const TValue &a, const TValue &b);

  size_t Age;
  size_t Weight;
};

class TFlatMap {
public:
  // Construct empty FlatMap with 
  // Capacity = Default Capacity, Size Array = 0
  // Memory is allocated for an array
  TFlatMap ();
  // The allocated memory is deleted
  ~TFlatMap ();
  // Copy constructor
  TFlatMap (const TFlatMap& b);
  // Move constructor
  TFlatMap(TFlatMap &&b) noexcept;
  // Binary search by key. The return value is the index in the array
  size_t BinarySearch (const sKey& key) const;
  // Exchanges the values of two FlamtMap with std::move
  void swap(TFlatMap &b);
  
  TFlatMap &operator=(const TFlatMap &b);
  TFlatMap &operator=(TFlatMap &&b) noexcept; 
  // Cleans the container
  void clear();

  // Deletes an element by the specified key. The return value is the success of the deletion
  bool erase(const sKey &k);
  // Inserting into the container. The return value is the success of the insertion
  bool insert(const sKey &k, const TValue &v);
  // Checking for the presence of a value for a given key
  bool contains(const sKey &k) const;
  // Returns the value by key. Unsafe method
  // If there is no key in the container, inserts the value created 
  // by the default constructor into the container and returns a reference to it
  TValue &operator[](const sKey &k);
  // Returns the value by key. Throws an exception on failure
  TValue &at(const sKey &k);
  // Returns the value by key. Throws an exception on failure
  const TValue &at(const sKey &k) const;
  // Returns the number of elements in the FlatMap at the moment
  size_t size() const;
  // Returns true if size == 0 else return fasle
  bool empty() const;

  friend bool operator!=(const TFlatMap &a, const TFlatMap &b);
  friend bool operator==(const TFlatMap &a, const TFlatMap &b);
  
private:
  // Structure: Key, Value.
  struct TMapValue {
    // Construct empty MapValue with default Key and Value
    TMapValue ();
    // Construct empty MapValue with the given input values
    TMapValue (const sKey& key, const TValue& val);

    bool operator!=(const TMapValue &a);

    sKey Key;
    TValue Value;
  };

  TMapValue* Arr;
  static const size_t DefaultCapacity = 8;
  size_t Capacity;
  size_t SizeArr;
};