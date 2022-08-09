#include "algs.h"
template <class T>
class Hash {
private:
    size_t size_;
    std::vector<std::pair<std::string, T>> table;

public:
    Hash() : size_{1} {
        table = std::vector<std::pair<std::string, T>>(size_, {"", NULL});
    }

    explicit Hash(size_t size) : size_{size} {
        table = std::vector<std::pair<std::string, T>>(size_, {"", NULL});
    }

    uint64_t extra_hash_alg(std::string input) {
        float A = (quake3(5) - 1) / 2;
        int k = 0;
        size_t m = size_;

        for (char c_ : input) {
            k += c_;
        }

        return floor(m * (k * A - floor(k * A)));
    }

    uint64_t hash_alg(std::string input, int i) {
        return (extra_hash_alg(input) + i) % size_;
    }

    T& get(std::string key) {
        int i = 0;
        int j = hash_alg(key, i);
        while (table[j].second != NULL && table[j].first != "" || i != size_) {
            if (table[j].first == key) {
                return table[j].second;
            }
            i++;
            j = hash_alg(key, i);
        }
        return (*table.end()).second;
    }

    void set(std::string key, T value) {
        int i = 0;
        while (i != size_) {
            int j = hash_alg(key, i);
            if (table[j].second == NULL && table[j].first == "") {
                table[j] = {key, value};
                return;
            } else {
                i++;
            }
        }
        throw std::runtime_error("hash table overflow");
    }

    /*
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
    */
    size_t size() const {
        return size_;
    }

    void print_all() {
        for (auto it : table) {
            std::cout << it.second << " ";
        }
        std::cout << "\n";
    }
};
