#ifndef VECTOR_HH
#define VECTOR_HH

#include <iostream>

#define DEFAULT_CAPACITY 10

template <typename T>
class Vector
{
public:
    Vector();                       // Default constructor
    ~Vector();                      // Destructor
    Vector(const Vector<T> &other); // Copy constructor
    Vector(Vector<T> &&other);      // Move constructor

    Vector<T> &operator=(const Vector<T> &other);     // Copy assignment
    Vector<T> &operator=(Vector<T> &&other) noexcept; // Move assignment
    bool operator==(const T &rhs) const;              // Equality operator
    bool operator!=(const T &rhs) const;              // Inequality operator
    T &operator[](int index) const;                   // Index operator

    int size() const;
    int capacity() const;
    bool empty() const;
    T &at(int index) const;
    T &front() const;
    T &back() const;
    const T *data() const;

    void insert(int index, const T &object);
    void push_back(const T &object);
    void clear();
    void erase(int index);
    void pop_back();

private:
    void realloc();

    const double m_GROWTH_FACTOR = 1.5;
    T *m_elements;
    int m_size;
    int m_capacity;
};

template <typename T>
Vector<T>::Vector() : m_size(0), m_capacity(DEFAULT_CAPACITY)
{
    m_elements = new T[m_capacity];
}

template <typename T>
Vector<T>::~Vector()
{
    delete m_elements;
    m_size = 0;
}

#endif // VECTOR_HH