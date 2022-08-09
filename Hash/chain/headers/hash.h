#include "algs.h"
template <class T>
class Hash {
private:
    size_t size_;
    std::vector<std::vector<std::pair<std::string, T>>> table;

public:
    Hash() : size_{1} {
        table = std::vector<std::vector<std::pair<std::string, T>>>(size_);
    }

    explicit Hash(size_t size) : size_{size} {
        table = std::vector<std::vector<std::pair<std::string, T>>>(size_);
    }

    uint64_t hash_alg(std::string input) {
        float A = (quake3(5) - 1) / 2;
        int k = 1;
        size_t m = size_;

        for (char c_ : input) {
            k += c_;
        }

        return floor(m * (k * A - floor(k * A)));
    }

    T& get(std::string key) {
        uint64_t id_ = hash_alg(key) % size_;
        for (auto& it : table[id_]) {
            if (it.first == key) {
                return it.second;
            }
        }

        set(key, 0);
        return get(key);
    }

    void set(std::string key, T value) {
        uint64_t id_ = hash_alg(key) % size_;
        for (auto& it : table[id_]) {
            if (it.first == key) {
                it.second = value;
                return;
            }
        }

        id_ = hash_alg(key) % size_;
        table[id_].push_back(std::make_pair(key, value));
    }

    void remove(std::string key) {
        uint64_t id_ = hash_alg(key) % size_;
        size_t i = 0;
        for (auto& it : table[id_]) {
            if (it.first == key) {
                table.at(id_).erase(table.at(id_).begin() + i);
                return;
            }
            i++;
        }
    }

    size_t size() const {
        return size_;
    }
};
