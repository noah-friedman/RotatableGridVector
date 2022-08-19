#ifndef ROTATABLEGRIDVECTOR_HPP
#define ROTATABLEGRIDVECTOR_HPP

#include <vector>
#include <utility>

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
            // Return if size = 0
            if (this->size() == 0)
                return;

            // (Re)set member variables
            this->position = {0, 0};
            this->null = {(size_t)-1, (size_t)-1};
            this->stored = {};
            this->total = {this->size(), this->at(0).size()};
            this->offset = 2;

            // Resize vectors if total.rows != total.cols
            if (this->total.rows > this->total.cols) {
                for (int row = 0; row < this->total.cols; row++)
                    this->at(row).resize(this->total.rows);

                /*
                 * When there are more rows than columns and there is insufficient space in the resized vectors to move the
                 * data in the square `total.min() x total.min()` without overwriting parts of itself prematurely, some
                 * preliminary 'chunks' must be moved beforehand.
                 */
                if (this->total.cols > (this->total.rows + 1) / 2) {
                    this->chunks = true;
                    size_t diff = this->total.rows - this->total.cols;
                    this->realCols = this->total.cols;
                    this->total.cols = this->total.rows;

                    // Move to begin of internal square
                    position = {diff, diff};
                    offset += diff;

#define CHUNK(ROW_FROM, ROW_TO, COL_FROM, COL_TO)                       \
for (size_t row = (ROW_FROM); row < (ROW_TO); row++) {                  \
    for (size_t col = (COL_FROM); col < (COL_TO); col++) {              \
        Coords dest = this->f(row, col);                                \
        std::swap(this->at(row)[col], this->at(dest.row)[dest.col]);    \
    }                                                                   \
} static_assert(true)

                    // Move chunks
                    CHUNK(0, diff, 0, this->realCols);
                    CHUNK(diff, this->total.rows, 0, diff);
                    CHUNK(this->total.rows - diff, this->total.rows, diff, this->realCols);
                }
            } else if (this->total.rows < this->total.cols)
                for (int i = 0; i < this->total.cols - this->total.rows; i++)
                    this->emplace_back(this->total.rows);

            while (true) {
                // Swap the value at `position` with `stored`
                this->swap(this->position);

                // Move all values within the square `total.min() x total.min()`
                if (this->null != Coords{(size_t)-1, (size_t)-1}) {
                    this->position = f(this->position);
                } else if (this->position.row >= (this->total.min() - 1) / 2)
                    break;
                else if (this->position.col == this->total.min() - offset) {
                    this->position.row++;
                    this->position.col = this->position.row;
                    this->offset++;
                } else
                    this->position.col++;

                if (this->total.rows > this->total.cols && !chunks)
                    std::swap(this->at(this->position.row)[this->position.col+this->total.rows-this->total.cols], stored);
            }

            if (this->realCols)
                this->total.cols = this->realCols;

            // Move all values outside the square (if any) and resize vectors
            if (this->total.rows < this->total.cols) {
                for (int row = 0; row < this->total.rows; row++) {
                    for (int col = this->total.rows; col < this->total.cols; col++) {
                        Coords dest = f(row, col);
                        this->at(dest.row)[dest.col] = this->at(row)[col];
                    }
                }

                for (int row = 0; row < this->total.cols; row++)
                    this->at(row).resize(this->total.rows);
            } else if (this->total.rows > this->total.cols) {
                if (!chunks) {
                    this-> realCols = this->total.cols;
                    this->total.cols = this->total.rows;

                    for (size_t row = this->realCols; row < this->total.rows; row++) {
                        for (size_t col = 0; col < this->realCols; col++) {
                            Coords dest = f(row, col);
                            this->at(dest.row)[dest.col] = this->at(row)[col];
                        }
                    }
                }

                this->resize(this->realCols);
            }
        }

    private:
        struct Coords {
            size_t row, col;

            bool operator==(const Coords &rhs) const {
                return this->row == rhs.row && this->col == rhs.col;
            }
        } position, null;
        T stored;
        struct {
            size_t rows, cols;

            size_t min() {
                return std::min(this->rows, this->cols);
            };
        } total;
        size_t realCols = 0;
        size_t offset = 2;
        bool chunks = false;

        Coords f(size_t row, size_t col) {
            return { col, (size_t)std::abs((int)row - (int)this->total.min() + 1) };
        }
        Coords f(Coords pos) {
            return f(pos.row, pos.col);
        }

        void swap(Coords pos) {
            if (pos == this->null)
                this->null = {(size_t)-1, (size_t)-1};
            else if (this->null == Coords{(size_t)-1, (size_t)-1})
                this->null = pos;
            std::swap(this->at(pos.row)[pos.col], stored);
        }
        void swap(size_t row, size_t col) {
            return this->swap(Coords{row, col});
        }
};

#endif //ROTATABLEGRIDVECTOR_HPP
