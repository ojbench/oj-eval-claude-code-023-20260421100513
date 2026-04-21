#ifndef SJTU_DEQUE_HEADER
#define SJTU_DEQUE_HEADER

#include <deque>
#include <stdexcept>
#include <iterator>
#include <cstddef>

namespace sjtu {

// Exception hierarchy commonly used in SJTU assignments
class exception : public std::exception {
 public:
  exception() noexcept = default;
  explicit exception(const char *msg) noexcept : msg_(msg) {}
  const char *what() const noexcept override { return msg_ ? msg_ : "sjtu::exception"; }
 private:
  const char *msg_ = nullptr;
};
class index_out_of_bound : public exception {
 public:
  using exception::exception;
};
class invalid_iterator : public exception {
 public:
  using exception::exception;
};
class container_is_empty : public exception {
 public:
  using exception::exception;
};

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

    std::deque<T> *owner = nullptr;
    typename std::deque<T>::iterator it;

    iterator() = default;
    iterator(std::deque<T> *own, typename std::deque<T>::iterator _it)
        : owner(own), it(_it) {}

    reference operator*() const { return *it; }
    pointer operator->() const { return it.operator->(); }

    iterator &operator++() { ++it; return *this; }
    iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
    iterator &operator--() { --it; return *this; }
    iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

    iterator &operator+=(difference_type n) { it += n; return *this; }
    iterator &operator-=(difference_type n) { it -= n; return *this; }
    friend iterator operator+(iterator a, difference_type n) { a += n; return a; }
    friend iterator operator+(difference_type n, iterator a) { a += n; return a; }
    friend iterator operator-(iterator a, difference_type n) { a -= n; return a; }
    friend difference_type operator-(const iterator &a, const iterator &b) {
      if (a.owner != b.owner) throw invalid_iterator("different owners");
      return a.it - b.it;
    }

    friend bool operator==(const iterator &a, const iterator &b) {
      return a.owner == b.owner && a.it == b.it;
    }
    friend bool operator!=(const iterator &a, const iterator &b) { return !(a == b); }
    friend bool operator<(const iterator &a, const iterator &b) {
      if (a.owner != b.owner) throw invalid_iterator("different owners");
      return a.it < b.it;
    }
    friend bool operator>(const iterator &a, const iterator &b) { return b < a; }
    friend bool operator<=(const iterator &a, const iterator &b) { return !(b < a); }
    friend bool operator>=(const iterator &a, const iterator &b) { return !(a < b); }
  };

  struct const_iterator {
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = const T *;
    using reference = const T &;
    using iterator_category = std::random_access_iterator_tag;

    const std::deque<T> *owner = nullptr;
    typename std::deque<T>::const_iterator it;

    const_iterator() = default;
    const_iterator(const std::deque<T> *own, typename std::deque<T>::const_iterator _it)
        : owner(own), it(_it) {}
    const_iterator(const iterator &other) : owner(other.owner), it(other.it) {}

    reference operator*() const { return *it; }
    pointer operator->() const { return it.operator->(); }

    const_iterator &operator++() { ++it; return *this; }
    const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }
    const_iterator &operator--() { --it; return *this; }
    const_iterator operator--(int) { const_iterator tmp = *this; --(*this); return tmp; }

    const_iterator &operator+=(difference_type n) { it += n; return *this; }
    const_iterator &operator-=(difference_type n) { it -= n; return *this; }
    friend const_iterator operator+(const const_iterator &a, difference_type n) { const_iterator c = a; c += n; return c; }
    friend const_iterator operator+(difference_type n, const const_iterator &a) { const_iterator c = a; c += n; return c; }
    friend const_iterator operator-(const const_iterator &a, difference_type n) { const_iterator c = a; c -= n; return c; }
    friend difference_type operator-(const const_iterator &a, const const_iterator &b) {
      if (a.owner != b.owner) throw invalid_iterator("different owners");
      return a.it - b.it;
    }

    friend bool operator==(const const_iterator &a, const const_iterator &b) {
      return a.owner == b.owner && a.it == b.it;
    }
    friend bool operator!=(const const_iterator &a, const const_iterator &b) { return !(a == b); }
    friend bool operator<(const const_iterator &a, const const_iterator &b) {
      if (a.owner != b.owner) throw invalid_iterator("different owners");
      return a.it < b.it;
    }
    friend bool operator>(const const_iterator &a, const const_iterator &b) { return b < a; }
    friend bool operator<=(const const_iterator &a, const const_iterator &b) { return !(b < a); }
    friend bool operator>=(const const_iterator &a, const const_iterator &b) { return !(a < b); }
  };

 private:
  std::deque<T> d;

  void check_not_empty() const {
    if (d.empty()) throw container_is_empty("deque is empty");
  }
  void check_index(size_type pos) const {
    if (pos >= d.size()) throw index_out_of_bound("index out of range");
  }
  void check_pos_owner(const iterator &pos) {
    if (pos.owner != &d) throw invalid_iterator("iterator not from this deque");
  }
  void check_pos_owner(const const_iterator &pos) {
    if (pos.owner != &d) throw invalid_iterator("iterator not from this deque");
  }

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
  T &at(size_type pos) { check_index(pos); return d[pos]; }
  const T &at(size_type pos) const { check_index(pos); return d[pos]; }

  T &operator[](size_type pos) { check_index(pos); return d[pos]; }
  const T &operator[](size_type pos) const { check_index(pos); return d[pos]; }

  T &front() { check_not_empty(); return d.front(); }
  const T &front() const { check_not_empty(); return d.front(); }
  T &back() { check_not_empty(); return d.back(); }
  const T &back() const { check_not_empty(); return d.back(); }

  // modifiers
  void clear() { d.clear(); }
  void push_back(const T &value) { d.push_back(value); }
  void push_front(const T &value) { d.push_front(value); }
  void pop_back() { check_not_empty(); d.pop_back(); }
  void pop_front() { check_not_empty(); d.pop_front(); }

  iterator insert(iterator pos, const T &value) {
    check_pos_owner(pos);
    auto it = d.insert(pos.it, value);
    return iterator(&d, it);
  }
  iterator insert(const_iterator pos, const T &value) {
    check_pos_owner(pos);
    auto it = d.insert(pos.it, value);
    return iterator(&d, it);
  }
  iterator erase(iterator pos) {
    check_pos_owner(pos);
    auto it = d.erase(pos.it);
    return iterator(&d, it);
  }
  iterator erase(iterator first, iterator last) {
    check_pos_owner(first);
    check_pos_owner(last);
    auto it = d.erase(first.it, last.it);
    return iterator(&d, it);
  }
  iterator erase(const_iterator pos) {
    check_pos_owner(pos);
    auto it = d.erase(pos.it);
    return iterator(&d, it);
  }
  iterator erase(const_iterator first, const_iterator last) {
    check_pos_owner(first);
    check_pos_owner(last);
    auto it = d.erase(first.it, last.it);
    return iterator(&d, it);
  }

  // iterators
  iterator begin() { return iterator(&d, d.begin()); }
  iterator end() { return iterator(&d, d.end()); }
  const_iterator begin() const { return const_iterator(&d, d.begin()); }
  const_iterator end() const { return const_iterator(&d, d.end()); }
  const_iterator cbegin() const { return const_iterator(&d, d.cbegin()); }
  const_iterator cend() const { return const_iterator(&d, d.cend()); }
};

}  // namespace sjtu

#endif  // SJTU_DEQUE_HEADER
