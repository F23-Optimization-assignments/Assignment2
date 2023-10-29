#ifndef ASSIGNMENT1_VECTOR_OPS_H
#define ASSIGNMENT1_VECTOR_OPS_H

#include <iostream>
#include <vector>

class VectorException : public std::exception {
private:
    const char* msg;
public:
    explicit VectorException(const char* msg) : std::exception(), msg(msg) { }
    [[nodiscard]] const char * what() const noexcept override {
        return msg;
    }
};

template<typename T>
void print_vector(const std::vector<T> &vec) {
    for (const T &elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

template<typename T>
T dot_product(const std::vector<T>& a, const std::vector<T>& b) {
    if (a.size() != b.size()) {
        throw VectorException("incompatible vectors' sizes for dot product");
    }
    T res;
    for (size_t idx = 0; idx < a.size(); ++idx) {
        res += a[idx] * b[idx];
    }
    return res;
}

template<typename T>
std::vector<T> subtraction(const std::vector<T>& a, const std::vector<T>& b) {
    if (a.size() != b.size()) {
        throw VectorException("incompatible vectors' sizes for dot product");
    }
    std::vector<T> vec(a.size());
    for (size_t idx = 0; idx < a.size(); ++idx) {
        vec[idx] = a[idx] - b[idx];
    }
    return vec;
}

template<typename T>
std::vector<T> multiply(const T& coefficient, const std::vector<T>& b) {
    std::vector<T> res(b.size());
    for (size_t idx = 0; idx < b.size(); ++idx) {
        res[idx] = coefficient * b[idx];
    }
    return res;
}

#endif //ASSIGNMENT1_VECTOR_OPS_H
