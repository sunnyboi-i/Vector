#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <numeric>
#include <stdexcept>

template <typename T>
class Vector {
 private:
  size_t m_size;
  size_t m_capacity;
  T* m_begin;
  T* m_end;

 public:
  Vector()
      : m_size{0},
        m_capacity{0},
        m_begin{nullptr},
        m_end{nullptr} {}

  Vector(size_t n, const T& value = T()) : m_size{n}, m_capacity{n} {
    m_begin = new T[m_size];
    for (size_t i = 0; i < m_size; ++i) {
      m_begin[i] = value;
    }
    m_end = m_begin + m_size;
  }

  Vector(std::initializer_list<T> lst)
      : m_size{lst.size()}, m_capacity{lst.size()} {
    m_begin = new T[m_size];
    size_t i = 0;
    for (auto& elem : lst) {
      m_begin[i++] = elem;
    }
    m_end = m_begin + m_size;
  }

  Vector(const Vector<T>& vec)
      : m_size{vec.m_size}, m_capacity{vec.m_capacity} {
    std::cout << "Copy ctor called\n";
    m_begin = new T[m_size];
    for (size_t i = 0; i < m_size; ++i) {
      m_begin[i] = vec.m_begin[i];
    }
    m_end = m_begin + m_size;
  }

  Vector(Vector<T>&& vec) noexcept
      : m_size{vec.m_size},
        m_capacity{vec.m_capacity},
        m_begin{vec.m_begin},
        m_end{vec.m_end} {
    std::cout << "Move ctor called\n";
    vec.m_begin = nullptr;
    vec.m_end = nullptr;
    vec.m_size = 0;
    vec.m_capacity = 0;
  }

  Vector<T>& operator=(const Vector& vec) {
    if (this == &vec) return *this;
    delete[] m_begin;
    m_size = vec.m_size;
    m_capacity = vec.m_capacity;
    m_begin = new T[m_size];
    for (size_t i = 0; i < m_size; ++i) {
      m_begin[i] = vec.m_begin[i];
    }
    m_end = m_begin + m_size;
    return *this;
  }

  Vector<T>& operator=(Vector&& vec) noexcept {
    delete[] m_begin;
    m_begin = vec.m_begin;
    m_end = vec.m_end;
    m_capacity = vec.m_capacity;
    m_size = vec.m_size;
    vec.m_begin = nullptr;
    vec.m_end = nullptr;
    vec.m_size = 0;
    vec.m_capacity = 0;
    return *this;
  }

  T& operator[](size_t pos) {
    return m_begin[pos];
  }

  const T& operator[](size_t pos) const {
    return m_begin[pos];
  }

  T& at(size_t pos) {
    if (pos >= m_size) {
      throw std::out_of_range("Index out of bounds");
    }
    return m_begin[pos];
  }

  const T& at(size_t pos) const {
    if (pos >= m_size) {
      throw std::out_of_range("Index out of bounds");
    }
    return m_begin[pos];
  }

  T& front() {
    if (m_size == 0) throw std::out_of_range("Vector is empty");
    return m_begin[0];
  }

  const T& front() const {
    if (m_size == 0) throw std::out_of_range("Vector is empty");
    return m_begin[0];
  }

  T& back() {
    if (m_size == 0) throw std::out_of_range("Vector is empty");
    return *(m_end - 1);
  }

  const T& back() const {
    if (m_size == 0) throw std::out_of_range("Vector is empty");
    return m_begin[m_size - 1];
  }

  T* data() { return m_begin; }
  const T* data() const { return m_begin; }
  bool empty() { return m_size == 0; }

  void clear() {
    for (size_t i = 0; i < m_size; ++i) {
      m_begin[i].~T();
    }
    m_size = 0;
    m_end = m_begin;
  }

  size_t max_size() const {
    return std::numeric_limits<size_t>::max() / sizeof(T);
  }

  void resize(size_t count, const T& val = T()) {
    if (count == m_size) {
      return;
    }
    if (count < m_size) {
      for (size_t i = count; i < m_size; i++) {
        m_begin[i].~T();
      }
    } else {
      reserve(count);
      for (size_t i = m_size; i < count; ++i) {
        m_begin[i] = T(val);
      }
    }
    m_size = count;
    m_end = m_begin + m_size;
  }

  void reserve(size_t n) {
    if (n <= m_capacity) return;
    T* auxiliary = new T[n];
    for (size_t i = 0; i < m_size; ++i) {
      auxiliary[i] = m_begin[i];
    }
    delete[] m_begin;
    m_begin = auxiliary;
    m_capacity = n;
    m_end = m_begin + m_size;
  }

  template <typename... Args>
  void emplace_back(Args&&... args) {
    if (m_size == m_capacity) {
      size_t new_capacity = (m_capacity == 0) ? 1 : 2 * m_capacity;
      reserve(new_capacity);
    }
    new (m_begin + m_size) T(std::forward<Args>(args)...);
    m_size += 1;
    m_end = m_begin + m_size;
  }

  void push_back(const T& value) {
    std::cout << "\npush back with lvalue called \n";
    if (m_size == m_capacity) {
      std::cout << "\nReallocation happened at size: " << m_size << '\n';
      size_t new_capacity = (m_capacity == 0) ? 1 : 2 * m_capacity;
      std::cout << "New capacity is now: " << new_capacity << '\n';
      reserve(new_capacity);
    }
    m_begin[m_size++] = value;
    m_end = m_begin + m_size;
  }

  void push_back(T&& value) {
    std::cout << "\npush back with rvalue called \n";
    if (m_size == m_capacity) {
      std::cout << "\nReallocation happened at size: " << m_size << '\n';
      size_t new_capacity = (m_capacity == 0) ? 1 : 2 * m_capacity;
      std::cout << "New capacity is now: " << new_capacity << '\n';
      reserve(new_capacity);
    }
    m_begin[m_size++] = std::move(value);
    m_end = m_begin + m_size;
  }

  void pop_back() {
    if (m_size == 0) {
      return;
    }
    m_begin[m_size - 1].~T();
    m_size -= 1;
    m_end = m_begin + m_size;
  }

  size_t size() const { return m_size; }
  size_t capacity() const { return m_capacity; }

  ~Vector() { delete[] m_begin; }

  template <typename U>
  friend std::ostream& operator<<(std::ostream& out, const Vector<U>& vec);
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& vec) {
  for (size_t i = 0; i < vec.m_size; ++i) {
    out << vec.m_begin[i] << ' ';
  }
  return out;
}

#endif