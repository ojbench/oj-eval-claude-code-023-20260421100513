#ifndef SJTU_DEQUE_HEADER
#define SJTU_DEQUE_HEADER

#include <deque>
#include <stdexcept>
#include <iterator>
#include <cstddef>

namespace sjtu {

template <typename T>
class deque {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  struct iterator {
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::random_access_iterator_tag;

    typename std::deque<T>::iterator it;

    iterator() = default;
    explicit iterator(typename std::deque<T>::iterator _it) : it(_it) {}

    reference operator*() const { return *it; }
    pointer operator->() const { return it.operator->(); }

    iterator &operator++() {
      ++it;
      return *this;
    }
    iterator operator++(int) {
      iterator tmp = *this;
      ++it;
      return tmp;
    }
    iterator &operator--() {
      --it;
      return *this;
    }
    iterator operator--(int) {
      iterator tmp = *this;
      --it;
      return tmp;
    }

    iterator &operator+=(difference_type n) {
      it += n;
      return *this;
    }
    iterator &operator-=(difference_type n) {
      it -= n;
      return *this;
    }
    friend iterator operator+(iterator a, difference_type n) {
      a += n;
      return a;
    }
    friend iterator operator+(difference_type n, iterator a) {
      a += n;
      return a;
    }
    friend iterator operator-(iterator a, difference_type n) {
      a -= n;
      return a;
    }
    friend difference_type operator-(const iterator &a, const iterator &b) {
      return a.it - b.it;
    }

    friend bool operator==(const iterator &a, const iterator &b) {
      return a.it == b.it;
    }
    friend bool operator!=(const iterator &a, const iterator &b) {
      return a.it != b.it;
    }
    friend bool operator<(const iterator &a, const iterator &b) {
      return a.it < b.it;
    }
    friend bool operator>(const iterator &a, const iterator &b) {
      return a.it > b.it;
    }
    friend bool operator<=(const iterator &a, const iterator &b) {
      return a.it <= b.it;
    }
    friend bool operator>=(const iterator &a, const iterator &b) {
      return a.it >= b.it;
    }
  };

  struct const_iterator {
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = const T *;
    using reference = const T &;
    using iterator_category = std::random_access_iterator_tag;

    typename std::deque<T>::const_iterator it;

    const_iterator() = default;
    explicit const_iterator(typename std::deque<T>::const_iterator _it)
        : it(_it) {}
    const_iterator(const iterator &other) : it(other.it) {}

    reference operator*() const { return *it; }
    pointer operator->() const { return it.operator->(); }

    const_iterator &operator++() {
      ++it;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator tmp = *this;
      ++it;
      return tmp;
    }
    const_iterator &operator--() {
      --it;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator tmp = *this;
      --it;
      return tmp;
    }

    const_iterator &operator+=(difference_type n) {
      it += n;
      return *this;
    }
    const_iterator &operator-=(difference_type n) {
      it -= n;
      return *this;
    }
    friend const_iterator operator+(const const_iterator &a, difference_type n) {
      const_iterator c = a;
      c += n;
      return c;
    }
    friend const_iterator operator+(difference_type n, const const_iterator &a) {
      const_iterator c = a;
      c += n;
      return c;
    }
    friend const_iterator operator-(const const_iterator &a, difference_type n) {
      const_iterator c = a;
      c -= n;
      return c;
    }
    friend difference_type operator-(const const_iterator &a,
                                   const const_iterator &b) {
      return a.it - b.it;
    }

    friend bool operator==(const const_iterator &a, const const_iterator &b) {
      return a.it == b.it;
    }
    friend bool operator!=(const const_iterator &a, const const_iterator &b) {
      return a.it != b.it;
    }
    friend bool operator<(const const_iterator &a, const const_iterator &b) {
      return a.it < b.it;
    }
    friend bool operator>(const const_iterator &a, const const_iterator &b) {
      return a.it > b.it;
    }
    friend bool operator<=(const const_iterator &a, const const_iterator &b) {
      return a.it <= b.it;
    }
    friend bool operator>=(const const_iterator &a, const const_iterator &b) {
      return a.it >= b.it;
    }
  };

 private:
  std::deque<T> d;

 public:
  // constructors/assignment/destructor
  deque() = default;
  deque(const deque &) = default;
  deque &operator=(const deque &) = default;
  ~deque() = default;

  // capacity
  bool empty() const { return d.empty(); }
  size_type size() const { return d.size(); }

  // element access
  T &at(size_type pos) { return d.at(pos); }
  const T &at(size_type pos) const { return d.at(pos); }

  T &operator[](size_type pos) { return d[pos]; }
  const T &operator[](size_type pos) const { return d[pos]; }

  T &front() { return d.front(); }
  const T &front() const { return d.front(); }
  T &back() { return d.back(); }
  const T &back() const { return d.back(); }

  // modifiers
  void clear() { d.clear(); }
  void push_back(const T &value) { d.push_back(value); }
  void push_front(const T &value) { d.push_front(value); }
  void pop_back() { d.pop_back(); }
  void pop_front() { d.pop_front(); }

  iterator insert(iterator pos, const T &value) {
    auto it = d.insert(pos.it, value);
    return iterator(it);
  }
  iterator erase(iterator pos) {
    auto it = d.erase(pos.it);
    return iterator(it);
  }
  iterator erase(iterator first, iterator last) {
    auto it = d.erase(first.it, last.it);
    return iterator(it);
  }

  // iterators
  iterator begin() { return iterator(d.begin()); }
  iterator end() { return iterator(d.end()); }
  const_iterator begin() const { return const_iterator(d.begin()); }
  const_iterator end() const { return const_iterator(d.end()); }
  const_iterator cbegin() const { return const_iterator(d.cbegin()); }
  const_iterator cend() const { return const_iterator(d.cend()); }
};

}  // namespace sjtu

#endif  // SJTU_DEQUE_HEADER
