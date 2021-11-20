#pragma once

template <typename T> using Predicate = std::function<bool(const T &)>;

template <typename T> Predicate<T> IsElement(const T &elem) {
  return [&elem](const T &other) { return elem == other; };
}

template <typename T>
int Find(const std::vector<T> &vec, const Predicate<T> &pred) {
  for (int i = 0; i < vec.size(); ++i) {
    if (pred(vec[i])) {
      return i;
    }
  }
  return -1;
}

template <typename T>
bool Contains(const std::vector<T> &vec, const Predicate<T> &pred) {
  return Find<T>(vec, pred) >= 0;
}

template <typename T>
bool ContainsItem(const std::vector<T> &vec, const T &item) {
  return Find<T>(vec, [&](const T &value) { return value == item; }) >= 0;
}

template <typename K, typename V>
bool ContainsKey(const std::unordered_map<K, V> &map, const K &key) {
  return map.find(key) != map.end();
}

template <typename K, typename V, typename M>
V FindWithDefault(const M &map, const K &key, V default_value) {
  auto it = map.find(key);
  if (it != map.end())
    return it->second;
  return default_value;
}

template <typename T> void AddN(std::vector<T> &vec, size_t n, T value) {
  vec.insert(vec.end(), n, value);
}

template <typename T>
T *MoveItem(int i, std::vector<T> &from, std::vector<T> &to) {
  int last = from.size() - 1;
  if (i < 0 || i > last) {
    // ERROR << "Cannot move item: " << i << " last: " << last << "\n";
    return nullptr;
  }
  to.push_back(std::move(from[i]));
  from[i] = std::move(from[last]);
  from.pop_back();
  return &to.back();
}

template <typename T, typename R>
std::vector<R> MapFn(const std::vector<T> &input,
                     std::function<R(const T &)> fn) {
  std::vector<R> result;
  result.reserve(input.size());
  for (const T &item : input) {
    result.push_back(fn(item));
  }
  return result;
}
