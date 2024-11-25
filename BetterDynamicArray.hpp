// Anther simple Dynamic array implementation, with a few improvements made
// Try to spot possible improvements.

#include <memory>
class DynamicArray {
private:
    std::unique_ptr<int[]> data;
    std::size_t capacity;
    std::size_t size;

    void resize(std::size_t new_capacity) {
        std::unique_ptr<int[]> new_data = std::make_unique<int[]>(new_capacity);

        for (std::size_t i = 0; i < size; ++i) {
            new_data[i] = std::move(data[i]);
        }

        data = std::move(new_data);
        capacity = new_capacity;
    }

public:
    DynamicArray() : data(nullptr), capacity(0), size(0) {}

    DynamicArray(std::initializer_list<int> init_list)
        : data(std::make_unique<int[]>(init_list.size())), capacity(init_list.size()), size(init_list.size()) {
        std::size_t index = 0;
        for (int value : init_list) {
            data[index++] = value;
        }
    }

    DynamicArray(const DynamicArray& other)
        : data(std::make_unique<int[]>(other.capacity)), capacity(other.capacity), size(other.size) {
        for (std::size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    DynamicArray(DynamicArray&& other) noexcept
        : data(std::move(other.data)), capacity(other.capacity), size(other.size) {
        other.capacity = 0;
        other.size = 0;
    }

    ~DynamicArray() = default; // Destructor is handled by unique_ptr

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            data = std::make_unique<int[]>(other.capacity);
            capacity = other.capacity;
            size = other.size;

            for (std::size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            capacity = other.capacity;
            size = other.size;

            other.capacity = 0;
            other.size = 0;
        }
        return *this;
    }

    void push_back(int value) {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    void pop_back() {
        if (size > 0) {
            --size;
        }
    }

    int get(std::size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void set(std::size_t index, int value) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        data[index] = value;
    }

    std::size_t get_size() const {
        return size;
    }

    std::size_t get_capacity() const {
        return capacity;
    }

    void shrink_to_fit() {
        if (capacity > size) {
            resize(size);
        }
    }

    // Operator Overloading
    int& operator[](std::size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const int& operator[](std::size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    bool operator==(const DynamicArray& other) const {
        if (size != other.size) {
            return false;
        }

        for (std::size_t i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const DynamicArray& other) const {
        return !(*this == other);
    }

    // Output stream operator for easy printing
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& vec) {
        os << "[";
        for (std::size_t i = 0; i < vec.size; ++i) {
            os << vec.data[i];
            if (i != vec.size - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

    // Iterator support
    int* begin() { return data.get(); }
    int* end() { return data.get() + size; }

    const int* begin() const { return data.get(); }
    const int* end() const { return data.get() + size; }
};
