/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    Node* to_ret = find(root, key);
    if(to_ret == NULL) {
        V ret = 0;
        return ret;
    }
    return to_ret->value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    //base
    if (subtree == NULL) return subtree;
    if (subtree->key == key) return subtree;
    //recursive step
    if(subtree->key < key) return find(subtree->right, key);
    return find(subtree->left, key);
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    insert(root, key, value);

}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL) {
        Node* temp = new Node(key, value);
        temp->left = NULL;
        temp->right = NULL;
        subtree = temp;
        return;
    }
   
    if (subtree->key == key) return;
    if (subtree->left == NULL && key < subtree->key) {
        
        Node* temp = new Node(key, value);
        subtree->left = temp;
        temp->left = NULL;
        temp->right = NULL;
        
        return;
    } else if (subtree->right == NULL && key > subtree->key){
       
        Node* temp = new Node(key, value);
        subtree->right = temp;
        temp->left = NULL;
        temp->right = NULL;
        
        return;
    }
    //recursive step
    if(subtree->key < key) {
        insert(subtree->right, key, value);
    } else {
        insert(subtree->left, key, value);
    }


}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    //Initialize pointers to firsts Left and Right Subtrees
    K first_key = first->key;
    V first_value = first->value;

    first->key = second->key;
    first->value = second->value;
    second->key = first_key;
    second->value  = first_value;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    
    Node* to_rem = find(root, key);
    std::cout << "did i make it here? ";
    remove(to_rem, key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here
    if(subtree == NULL) {
        return;
    }
    //Case 1: Zero Children
    if (subtree->left == NULL && subtree->right == NULL) {
        std::cout << "made it to delete";
        delete subtree;
        subtree = NULL;
        return;
    }
    //Case 2: Left Child Only Exists
    if (subtree->left !=  NULL && subtree->right == NULL) {
        swap(subtree, subtree->left);
        delete subtree;
        subtree = NULL;
        return;
    }
    //Case 3: Right Child Only Exists
    if (subtree->left == NULL && subtree->right != NULL) {
        swap(subtree, subtree->right);
        delete subtree;
        subtree = NULL;
        return;
    }
    if (subtree->left != NULL && subtree->right != NULL) {
        std::vector<K> inOrderTrav = getInorderTraversal();
        K IOP = K();
        for (unsigned int i = 0; i < inOrderTrav.size(); ++i) {
            if (inOrderTrav.at(i) < key) {
                IOP = inOrderTrav.at(i);
            } else if (inOrderTrav.at(i) == key) {
                break;
            }
        }
        Node* IOPnode = find(subtree, key);
        swap(subtree, subtree->left);
        delete subtree;
        return;
    }
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here

}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    return std::vector<int>();
}