#pragma once

#include <algorithm>
#include <functional>
#include <mutex>
#include <numeric>
#include <unordered_map>
#include <vector>

namespace shashki {

/**
 * Returns the index permutation which would sort the elements of `xs` into
 * order
 */
template <typename T>
std::vector<size_t> arg_sort(const T* xs, const size_t n,
                             const bool asc = true) {
  std::vector<size_t> idx(n);
  std::iota(idx.begin(), idx.end(), 0);

  std::function<bool(size_t, size_t)> comp;
  if (asc)
    comp = [&xs](size_t i1, size_t i2) { return xs[i1] < xs[i2]; };
  else
    comp = [&xs](size_t i1, size_t i2) { return xs[i1] > xs[i2]; };

  std::stable_sort(idx.begin(), idx.end(), comp);

  return idx;
}

/**
 * Returns the index permutation which would sort the elements of `xs` into
 * order
 */
template <typename T>
std::vector<size_t> arg_sort(const std::vector<T>& xs, const bool asc = true) {
  return arg_sort(xs.data(), xs.size(), asc);
}

/**
 * Elementary but thread-safe map
 */
template <typename K, typename V, typename M = std::unordered_map<K, V>>
class ConcurrentMap {
 public:
  ConcurrentMap() {}
  ConcurrentMap& operator=(ConcurrentMap&) = delete;

  void set(const K& key, V&& value) {
    const std::lock_guard<std::mutex> lk(mtx);
    data[key] = value;
  }

  V& get(const K& key) {
    const std::lock_guard<std::mutex> lk(mtx);
    return data[key];
  }

 private:
  std::mutex mtx;
  M data;
};

}  // namespace shashki
