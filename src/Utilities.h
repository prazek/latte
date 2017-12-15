#pragma once

template <typename T, typename From>
T* dyn_cast(From* param) {
  return dynamic_cast<T*>(param);
};

template <typename T, typename From>
const T* dyn_cast(const From &param) {
  return dynamic_cast<const T*>(&param);
}

template <typename T, typename From>
T* dyn_cast(From &param) {
  return dynamic_cast<T*>(&param);
}

template <typename T, typename From>
bool isa(From* param) {
  return dyn_cast<T>(param) != nullptr;
};

template <typename T, typename From>
bool isa(const From& param) {
  return dyn_cast<T>(param) != nullptr;
};


template <typename T, typename From>
T* cast(From* param) {
  assert(isa<T>(param));
  return dyn_cast<T>(param);
};

template <typename T, typename From>
const T& cast(const From &param) {
  assert(isa<T>(param));
  return *dyn_cast<T>(param);
}

template <typename T, typename From>
T& cast(From &param) {
  assert(isa<T>(param));
  return *dyn_cast<T>(param);
}




