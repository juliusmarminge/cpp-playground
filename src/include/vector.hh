#ifndef VECTOR_HH
#define VECTOR_HH

#include <iostream>

#define DEFAULT_CAPACITY 10
#define GROWTH_FACTOR 1.5

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

    T *m_data;
    int m_size;
    int m_capacity;
};

/**************************************************
 * Memory allocation / reallocation / destruction *
 **************************************************/

// Reallocate memory to fit more elements
template <typename T>
void Vector<T>::realloc()
{
    // Allocate a temporary copy
    T *copy = new T[m_size];
    memcpy(copy, m_data, sizeof(T) * m_size);

    // Free the currently allocated memory and reallocate more
    delete[] m_data;
    m_capacity *= GROWTH_FACTOR;
    m_data = new T[m_capacity];

    // Copy the elements over to the new, bigger allocated memory
    memcpy(m_data, copy, sizeof(T) * m_size);
    delete[] copy;
}

template <typename T>
Vector<T>::Vector() : m_size(0), m_capacity(DEFAULT_CAPACITY)
{
    m_data = new T[m_capacity];
}

template <typename T>
Vector<T>::~Vector()
{
    if (m_data != nullptr)
    {
        delete[] m_data;
        m_data = nullptr;
        m_size = 0;
    }
}

/**************************************************
 *                   Operators                    *
 **************************************************/

template <typename T>
T &Vector<T>::operator[](int index) const
{
    if (index < 0 || index >= m_size)
        throw "Out of range";
    return m_data[index];
}

/**************************************************
 *                Getter methods                  *
 **************************************************/

template <typename T>
int Vector<T>::size() const
{
    return m_size;
}

template <typename T>
int Vector<T>::capacity() const
{
    return m_capacity;
}

template <typename T>
T &Vector<T>::at(int index) const
{
    if (index < 0 || index >= m_size)
        throw "Out of range";
    return m_data[index];
}

template <typename T>
bool Vector<T>::empty() const
{
    return m_size == 0;
}

template <typename T>
T &Vector<T>::front() const
{
    return m_data[0];
}

template <typename T>
T &Vector<T>::back() const
{
    return m_data[m_size - 1];
}

template <typename T>
const T *Vector<T>::data() const
{
    return m_data;
}

/**************************************************
 *       Methods that mutates the vector          *
 **************************************************/

template <typename T>
void Vector<T>::push_back(const T &object)
{
    if (m_size >= m_capacity)
        realloc();
    m_data[m_size++] = object;
}

#endif // VECTOR_HH