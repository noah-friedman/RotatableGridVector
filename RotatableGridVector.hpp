#ifndef ROTATABLEGRIDVECTOR_HPP
#define ROTATABLEGRIDVECTOR_HPP

template <typename T>
class RotatableGridVector : public std::vector<std::vector<T>> {
    using std::vector<std::vector<T>>::vector;

    public:
        /**
         * A move constructor to allow conversion between this class and its parent class.
         * @param rhs The data to be moved into this object.
         */
        explicit RotatableGridVector(std::vector<std::vector<T>> &&rhs) : std::vector<std::vector<T>>(rhs) {}

        /**
         * Rotates the contents of this object 90º clockwise.
         * @warning Behaviour is undefined when the internal vectors do not all have the same length.
         */
        void rotate() {
            throw std::runtime_error("not yet implemented");
        }
};

#endif //ROTATABLEGRIDVECTOR_HPP
