
// Simple implementation of a dynamic array
// Many possible improvements!
// Try to spot some.


class SimpleDynamicArray {
private:
    int* data;
    std::size_t capacity;
    std::size_t size;

    void resize(std::size_t new_capacity) {
        int* new_data = new int[new_capacity];

        for (std::size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    SimpleDynamicArray() : data(nullptr), capacity(0), size(0) {}

    ~SimpleDynamicArray() {
        delete[] data;
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
};

