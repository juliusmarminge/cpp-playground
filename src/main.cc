// Copyright 2023 julius0216@outlook.com

#include <iostream>
#include "vector.hh"

int main()
{
    Vector<int> vector;
    for (int i = 0; i < 100; i++)
        vector.push_back(i * 2);

    std::cout << "Size    : " << vector.size() << std::endl;
    std::cout << "Cap     : " << vector.capacity() << std::endl;
    std::cout << "Vec[10] : " << vector.at(10) << std::endl;
    return 0;
}
