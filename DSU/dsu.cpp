#include <iostream>

class DSU {
public:
    void make_set(size_t i) {
        parent_[i] = i;
        rank_[i] = 0;
    }

    int find_set(size_t i) {
        if (i != parent_[i])
            parent_[i] = find(parent_[i]);
        return i;
    }

    bool union_sets(int a, int b) {
        int ra = find(a), rb = find(b);

        if (ra == rb)
            return false;

        if (rank_[ra] < rank_[rb]) {
            parent_[ra] = rb;
        } else if (rank_[rb] < rank_[ra]) {
            parent_[rb] = ra;
        } else {
            parent_[ra] = rb;
            ++rank_[rb];
        }

        return true;
    }

private:
    int parent_[100000];
    int rank_[100000];
};

int main() {

	return 0;
}

