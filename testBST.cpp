#include "BST.h"
#include "BST.cpp"
int main() {
/*
1. In the main function create BST object of integers dynamically in the
heap.
2. Insert the following values to the created tree.
3. Create a second BST object of integers dynamically in the heap using
the copy constructor.
4. Delete the first created object.
5. Print the second object.
6. Call find_target method with the following values: 84, 43, 76, 143, 45.
7. Call and print the result of get_height method.
8. Delete the second object.
*/
BST<int>* binTree = new BST<int>;
binTree->insert(42);
binTree->insert(34);
binTree->insert(77);
binTree->insert(9);
binTree->insert(66);

BST<int>* binTreeCopy = new BST<int> (*binTree);
delete binTree;
binTreeCopy->print();
std::cout << "find_target(84) = " << binTreeCopy->find_target(84) << std::endl;
std::cout << "find_target(43) = " << binTreeCopy->find_target(43) << std::endl;
std::cout << "find_target(76) = " << binTreeCopy->find_target(76) << std::endl;
std::cout << "find_target(143) = " << binTreeCopy->find_target(143) << std::endl;
std::cout << "find_target(45) = " << binTreeCopy->find_target(45) << std::endl;


std::cout << "Tree's height is "<<binTreeCopy->get_height() << std::endl;

delete binTreeCopy;
return 0;
}