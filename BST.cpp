#include "BST.h"
#include "BTNode.h"
#include <__config>
#include <iostream>
template <typename T>
BST<T>::BST() : root (nullptr){}

// DESTRUCTOR FOR ASSIGNMENT 4
template <typename T>
BST<T>::~BST(){
    destroyTree(root);
}

// helper function for destructor
template <typename T>
void BST<T>::destroyTree(BTNode<T>* node){
    if(!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// COPY CONSTRUCTOR ASSIGNMENT 4
template <typename T>
BST<T>::BST(const BST<T>& other){
    this->root = copyNode(this->root,other.root);
}

//helper function for copy constructor
template <typename T>
BTNode<T>* BST<T>::copyNode(BTNode<T>* thisNode, BTNode<T>* otherNode){
    if (!otherNode) return nullptr;
    if (!thisNode) thisNode = new BTNode<T>(otherNode->data, copyNode(nullptr, otherNode->left), copyNode(nullptr, otherNode->right));
    return thisNode;
}

// FIND TARGET FUNCTION ASSIGNMENT 4
template <typename T>
bool BST<T>::find_target(const T& val) const{
    return find_target_helper(val, root);
}

// helper function for FIND TARGETR FUNCTION
template <typename T>
bool BST<T>::find_target_helper(const T& val, BTNode<T>* node) const{
    if (!node) return false;
    T difference = val - node->data;
    if (node->data == difference) return false;
    BTNode<T>* dummy = node;
    while(dummy){
        if(dummy->data == difference) return true;
        else if (difference < dummy->data) dummy = dummy->left;
        else if (difference > dummy->data) dummy = dummy->right;
    }
    return find_target_helper(val, node->left) || find_target_helper(val, node->right);
}

// FIND HEIGHT FUNCTION ASSIGNMENT 4
template <typename T>
int BST<T>::get_height() const{
    return longest_path(root);
}

// helper function for height assignment 4
template <typename T>
int BST<T>::longest_path(BTNode<T>* node) const{
    if (!node) return 0;
    int left = longest_path(node->left) + 1;
    int right = longest_path(node->right) + 1;

    if(left > right) return left;
    return right;
}

template <typename T>
bool BST<T>::empty() const {
return (root == nullptr);
}
template <typename T>
void BST<T>::insert(const T& val) {
//empty tree
if (empty()) {
root = new BTNode<T>(val);
}
else {
BTNode<T>* cur = root, *prev = root;
while (cur) {
prev = cur;
if (val < cur->data) {
cur = cur->left;
}
else {
cur = cur->right;
}
}
//cur is nullptr, prev is a parent of cur
if (val < prev->data) {
prev->left = new BTNode<T>(val);
}
else {
prev->right = new BTNode<T>(val);
}
}
}
template <typename T>
void BST<T>::preorder(BTNode<T>* node) const {
if (!node) {
return;
}
else {
std::cout << node->data << ' ';
preorder(node->left);
preorder(node->right);
}
}
template <typename T>
void BST<T>::preorder() const {
std::cout << "Preorder:\t\t[";
preorder(root);
std::cout << "]\n";
}
template <typename T>
void BST<T>::inorder(BTNode<T>* node) const {
if (!node) {
return;
}
else {
inorder(node->left);
std::cout << node->data << ' ';
inorder(node->right);
}
}
template <typename T>
void BST<T>::inorder() const {
std::cout << "Inorder:\t\t[";
inorder(root);
std::cout << "]\n";
}
template <typename T>
void BST<T>::postorder(BTNode<T>* node) const {
if (!node) {
return;
}
else {
postorder(node->left);
postorder(node->right);
std::cout << node->data << ' ';
}
}
template <typename T>
void BST<T>::postorder() const {
std::cout << "Postorder:\t\t[";
postorder(root);
std::cout << "]\n";
}
template <typename T>
void BST<T>::print() const {
print("", root, false);
}
template <typename T>
void BST<T>::print(const std::string& prefix, const BTNode<T>* node, bool isRight)
const {
if (node != nullptr) {
std::cout << prefix;
std::cout << (isRight ? "R--" : "L--");
//print the value of the node
std::cout << node->data << std::endl;
//enter the next tree level
print(prefix + " ", node->right, true);
print(prefix + " ", node->left, false);
}
}
template <typename T>
const T& BST<T>::get_min() const {
if (empty()) {
throw std::string("Empty tree\n");
}
else {
BTNode<T>* cur = root;
while (cur->left) {
cur = cur->left;
}
return cur->data;
}
}
template <typename T>
const T& BST<T>::get_min(BTNode<T>* node) const {
if (empty()) {
throw std::string("Empty tree\n");
}
else {
BTNode<T>* cur = node;
while (cur->left) {
cur = cur->left;
}
return cur->data;
}
}
template <typename T>
BTNode<T>* BST<T>::search(const T& val) {
BTNode<T>* node = root;
while (node) {
if (node->data == val) {
return node;
}
else if (val < node->data) {
node = node->left;
}
else if (val > node->data) {
node = node->right;
}
}
return nullptr;
}
template <typename T>
BTNode<T>* BST<T>::search_parent(const T& val) {
if(root->data == val) { //root doesn't have a parent
return nullptr;
}
BTNode<T>* node = root;
BTNode<T>* prev = root;
while (node) {
if (node->data == val) {
return prev;
}
else if (val < node->data) {
prev = node;
node = node->left;
}
else if (val > node->data) {
prev = node;
node = node->right;
}
}
return nullptr;
}
template <typename T>
void BST<T>::delete_node(const T& val) {
if (empty()) {
return;
}
BTNode<T>* node = search(val);
if (!node) {
throw std::string("No node to delete\n");
}
BTNode<T>* parent = search_parent(val);
if (!node->left && !node->right) { //leaf node
delete_leaf(node, parent);
}
else if (!node->left || !node->right) { //one kid
delete_one_child(node, parent);
}
else { //has two children
delete_two_children(node);
}
}
template <typename T>
void BST<T>::delete_leaf(BTNode<T>* child, BTNode<T>* parent) {
if (!child) {
throw std::string ("Delete leaf: no node to delete\n");
}
if (!parent) { //root which is a leaf node
delete root;
root = nullptr;
return;
}
else if (parent->left == child) { //left kid
parent->left = nullptr;
}
else if (parent->right == child) { //right kid
parent->right = nullptr;
}
else {
throw std::string("Delete leaf: impossible to delete\n");
}
delete child;
}
template <typename T>
void BST<T>::delete_one_child(BTNode<T>* child, BTNode<T>* parent) {
if (!child) {
throw std::string("Delete one child: no node to delete");
}
else if (child->left && child->right) {
throw std::string("Delete one child: node has two children");
}
if (child == root) {
BTNode<T>* to_delete = root;
root = (root->left) ? root->left : root->right;
delete to_delete;
return;
}
if(child->right && !child->left) { //right kid
if (parent->right == child) { //right child of a parent
parent->right = child->right;
}
else if (parent->left == child) { //left child of a parent
parent->left = child->right;
}
}
else if (!child->right && child->left) {
if (parent->right == child) { //right child of a parent
parent->right = child->left;
}
else if (parent->left == child) { //left child of a parent
parent->left = child->left;
}
}
else {
throw std::string("Delete one child: node has no children");
}
//release the memory
delete child;
}
template <typename T>
void BST<T>::delete_two_children(BTNode<T>* node) {
if (!node) {
throw std::string("Delete two children: no node to delete");
}
else if (!node->right || !node->left) {
throw std::string("Delete two children: node has less than two children");
}
T min_node_value = get_min(node->right);
BTNode<T>* min_node = search(min_node_value);
if (!min_node->left && !min_node->right) {
delete_leaf(min_node, search_parent(min_node_value));
}
else if (!min_node->left || !min_node->right) {
delete_one_child(min_node, search_parent(min_node_value));
}
node->data = min_node_value;
}