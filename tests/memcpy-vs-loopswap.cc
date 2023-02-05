/**
 * Performance test for memcpy vs loop + std::swap
 * - we got an array of uint64_t with size SIZE
 * - we want to double the size of the array
 *   to do so, we need to copy the data to a new array
 *   - then we need to free the old array from memory
 *   - then we can allocate a new array with double the size
 *   - then we can copy the data back to the new array
 *
 * - this test compares the performance of memcpy vs loop + std::swap
 * - the result is that memcpy is faster than loop + std::swap by ~30%
 */

#include <algorithm>
#include <iostream>
#include <chrono>

#define SIZE 1E9

int main()
{
    uint64_t *data = new uint64_t[SIZE];
    for (uint64_t i = 0; i < SIZE; i++)
        data[i] = i;

    // memcpy
    auto t1 = std::chrono::high_resolution_clock::now();
    uint64_t *memcpyd = new uint64_t[SIZE * 2];
    memcpy(memcpyd, data, sizeof(uint64_t) * SIZE);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Using memcpy: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;
    for (uint64_t i = 0; i < SIZE; i++)
        if (memcpyd[i] != data[i])
            std::cout << "Error: " << memcpyd[i] << " != " << data[i] << std::endl;
    delete[] memcpyd;

    // loop + std::swap
    t1 = std::chrono::high_resolution_clock::now();
    uint64_t *swapd = new uint64_t[SIZE * 2];
    for (uint64_t i = 0; i < SIZE; i++)
        std::swap(swapd[i], data[i]);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Using loop + std::swap: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;
    for (uint64_t i = 0; i < SIZE; i++)
        if (swapd[i] != i)
            std::cout << "Error: " << swapd[i] << " != " << data[i] << std::endl;
    delete[] swapd;

    delete[] data;
    return 0;
}