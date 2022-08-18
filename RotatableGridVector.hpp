#ifndef ROTATABLEGRIDVECTOR_HPP
#define ROTATABLEGRIDVECTOR_HPP

template <typename T>
class RotatableGridVector : public std::vector<std::vector<T>> {
    using std::vector<std::vector<T>>::vector;

    public:
        explicit RotatableGridVector(std::vector<std::vector<T>> &&rhs) : std::vector<std::vector<T>>(rhs) {}
};

#endif //ROTATABLEGRIDVECTOR_HPP
