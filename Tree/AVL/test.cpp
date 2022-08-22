#include "tree2.h"
#include <cmath>
#include <cassert>

void TEST_HEIGHT() {
	AVLTree<int> tree;

	int n = 1e5;
	for(int i = 1; i <= n; ++i)
		tree.insert(rand()%n);

	assert(abs(log2(n) - tree.height()) >= 1);
	tree.print();
}
