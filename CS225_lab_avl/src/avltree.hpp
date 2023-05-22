/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* tmp1 = t->right;
    Node* tmp2 = tmp1->left;
    tmp1->left = t;
    t->right = tmp2;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = tmp1;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* tmp1 = t->left;
    Node* tmp2 = tmp1->right;
    tmp1->right = t;
    t->left = tmp2;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = tmp1;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree == NULL) return;
    if(subtree->right == NULL && subtree->left == NULL) return;
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if(balance == -2) {
        //std::cout << "rotating in rebalance" << std::endl;
        int r_h = heightOrNeg1(subtree->left->right);
        int l_h = heightOrNeg1(subtree->left->left);
        int l_bal = r_h - l_h;
        if(l_bal < 0) rotateRight(subtree);
        else rotateLeftRight(subtree);
    } else if(balance == 2) {
        //std::cout << "rotating in rebalance" << std::endl;
        int r_h = heightOrNeg1(subtree->right->right);
        int l_h = heightOrNeg1(subtree->right->left);
        int r_bal = r_h - l_h;
        if(r_bal > 0) rotateLeft(subtree);
        else rotateRightLeft(subtree);
    }
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL) {
        subtree = new Node(key, value);
        return;
    }
    else if(key == subtree->key) {
        subtree->value = value;
        return;
    }
    else if (key < subtree->key) {
        insert(subtree->left, key, value);
    }
    else if (key > subtree->key) {
        insert(subtree->right, key, value);
    }
    //std::cout << "I am rebalancing" << std::endl;
    rebalance(subtree);
    //subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* pre = subtree->left;
            while(pre->right != NULL) {
                pre = pre->right;
            }
            subtree->value = pre->value;
            subtree->key = pre->key;
            remove(subtree->left, pre->key);
        } else {
            /* one-child remove */
            // your code here
            if(subtree->right != NULL) {
                Node * to_del = subtree;
                subtree = subtree->right;
                delete to_del;
            } else {
                Node * to_del = subtree;
                subtree = subtree->left;
                delete to_del;
            }
        }
        // your code here
    }
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
    rebalance(subtree);
}
