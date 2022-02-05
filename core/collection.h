#pragma once

#include <array>
#include <map>
#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

#include "../core/test.h"

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

template <typename M>
bool ContainsKey(const M &map, const typename M::key_type &key) {
  return map.find(key) != map.end();
}

template <typename M>
typename M::mapped_type FindWithDefault(const M &map,
                                        const typename M::key_type &key,
                                        typename M::mapped_type default_value) {
  auto it = map.find(key);
  if (it != map.end())
    return it->second;
  return default_value;
}

template <typename M>
typename M::mapped_type *FindOrNull(M &map, const typename M::key_type &key) {
  auto it = map.find(key);
  if (it != map.end())
    return &it->second;
  return nullptr;
}

template <typename M>
const typename M::mapped_type *FindOrNull(const M &map,
                                          const typename M::key_type &key) {
  auto it = map.find(key);
  if (it != map.end())
    return &it->second;
  return nullptr;
}

template <typename M, typename = std::enable_if_t<
                          std::is_pointer<typename M::mapped_type>::value>>
typename M::mapped_type FindPtrOrNull(const M &map,
                                      const typename M::key_type &key) {
  auto it = map.find(key);
  if (it != map.end())
    return it->second;
  return nullptr;
}

template <typename M>
typename M::mapped_type::pointer
FindPtrOrNull(const M &map, const typename M::key_type &key) {
  // Implementation for unique_ptr values.
  auto it = map.find(key);
  if (it != map.end())
    return it->second.get();
  return nullptr;
}

//
// template <typename M, typename P>
// FindPtrOrNull(const M &map, const typename M::key_type &key)
//     ->typename M::mappped_type::pointer;

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
                     const std::function<R(const T &)> &fn) {
  std::vector<R> result;
  result.reserve(input.size());
  for (const T &item : input) {
    result.push_back(fn(item));
  }
  return result;
}

// -----------------------------------------------------------------------------

TEST(FindWithDefault) {
  std::map<int, int> m;
  m[10] = 10;
  EXPECT_EQ(FindWithDefault(m, 10, -1), 10);
  EXPECT_EQ(FindWithDefault(m, 12, -1), -1);
}

TEST(FindOrNullConst) {
  std::map<int, int> m;
  m[10] = 10;
  const int *p = FindOrNull(m, 10);
  EXPECT_TRUE(p != nullptr);
  EXPECT_EQ(*p, 10);
  EXPECT_TRUE(FindOrNull(m, 12) == nullptr);
}

TEST(FindOrNullMutable) {
  std::map<int, int> m;
  m[10] = 10;
  int *p = FindOrNull(m, 10);
  EXPECT_TRUE(p != nullptr);
  EXPECT_EQ(*p, 10);
  *p = 37;
  EXPECT_EQ(m.begin()->second, 37);
}

TEST(FindPtrOrNullRaw) {
  std::map<int, int *> m;
  int i = 10;
  m[10] = &i;
  const int *p = FindPtrOrNull(m, 10);
  EXPECT_TRUE(p != nullptr);
  EXPECT_EQ(*p, 10);
  EXPECT_TRUE(FindOrNull(m, 12) == nullptr);
}

TEST(FindPtrOrNullConstRaw) {
  std::map<int, const int *> m;
  int i = 10;
  m[10] = &i;
  const int *p = FindPtrOrNull(m, 10);
  EXPECT_TRUE(p != nullptr);
  EXPECT_EQ(*p, 10);
  EXPECT_TRUE(FindOrNull(m, 12) == nullptr);
}

TEST(FindPtrOrNullUnique) {
  std::map<int, std::unique_ptr<int>> m;
  m[10] = std::make_unique<int>(10);
  const int *p = FindPtrOrNull(m, 10);
  EXPECT_TRUE(p != nullptr);
  EXPECT_EQ(*p, 10);
  EXPECT_TRUE(FindOrNull(m, 12) == nullptr);
}
