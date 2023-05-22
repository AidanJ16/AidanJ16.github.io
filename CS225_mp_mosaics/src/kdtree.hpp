/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>

using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
    /**
     * @todo Implement this function!
     */
    // edge cases
    if(curDim >= Dim) return false;
    if(curDim < 0) return false;
    // if less than in that dimension return true
    if(first[curDim] < second[curDim]) return true;
    // if equal must compare the points using <
    if(first[curDim] == second[curDim]) {
      if(first < second) return true;
      else return false;
    }
    // else we return false
    return false;
}

template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential)
{
    /**
     * @todo Implement this function!
     */
    // set up counts
    double count1 = 0;
    double count2 = 0;
    // calculate the distances squared
    for(int i =0; i < Dim; i++) {
      count1 += ((currentBest[i] - target[i]) * (currentBest[i] - target[i]));
      count2 += ((potential[i] - target[i]) * (potential[i] - target[i]));
    }
    // if distance squared for potential is less than distance squared for current we return true
    if(count2 < count1) return true;
    // if equal we compare points using <
    if(count2 == count1) {
      if(potential < currentBest) {
        return true;
      } else {
        return false;
      }
    }
    // else we return false
    return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     // check edge case that vector is empty
     if(newPoints.empty()) {
      size = 0;
      root = NULL;
      return;
     // otherwise we copy vector since const
     // set size and dim to 0
     // call helper function
     } else {
      vector<Point<Dim>> to_build = newPoints;
      to_build.assign(newPoints.begin(), newPoints.end());
      size = 0;
      int dim = 0;
      //no longer pass in root which we called node
      build_KDTree(to_build, root, dim, 0, to_build.size());
     }

}
template <int Dim>
void KDTree<Dim>::build_KDTree(vector<Point<Dim>>& vect, KDTreeNode*& node, int dim, int start, int end) {
  // base case
  if(start >= end) return;
  // calculate median (end -1) and create cmp using smallerDimVal
  int median = (end + start - 1) / 2;
  auto cmp = [di = dim](const Point<Dim> &lhs, const Point<Dim> &rhs){return smallerDimVal(lhs, rhs, di);};
  //cout << "After Select: around " << *(vect.begin() + median)  << endl;
  // call select on iterator begin and iterate appropriately for start, end, and median
  select(vect.begin() + start, vect.begin() + end, vect.begin() + median, cmp);
  // testing
  /*for (auto i : vect) {
    cout << i << " ";
  }
  cout << "\n";
  cout << "Center: " << *(vect.begin() + median)  << endl;*/
  // create new node based on median
  node = new KDTreeNode(vect[median]);
  // increase size
  size++;
  // recursive call on left and right with lower and upper half of vector
  build_KDTree(vect, node->left, (dim + 1) % Dim, start, median);
  build_KDTree(vect, node->right, (dim + 1) % Dim, median + 1, end);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   // call copy helper and copy size
   copy_tree(root, other->root);
   size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  // first call delete then copy, copy size, return tree
  delete_tree(root);
  copy_tree(root, rhs->root);
  size = rhs.size;
  return *this;
}
template <int Dim>
void KDTree<Dim>::copy_tree(KDTreeNode*& root, KDTreeNode*& o_root) {
  // edge case the o_root is NULL
  if(o_root == NULL) return;
  // otherwise we copy all nodes making new ones 
  root = new KDTreeNode(o_root);
  // recursive calls to copy left and right subtree
  copy_tree(root->left, o_root->left);
  copy_tree(root->right, o_root->right);
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  // call recursive destructor
  delete_tree(root);

}
template <int Dim>
void KDTree<Dim>::delete_tree(KDTreeNode*& to_del) {
  //base case if null no action
  if(to_del == NULL) return;
  //recursive call on left and right subtrees
  delete_tree(to_del->left);
  delete_tree(to_del->right);
  //make sure to delete root
  delete to_del;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    // edge case cant find nearest on empty tree
    if(root == NULL) return NULL;
    int dim = 0;
    // since query const copy the point
    Point<Dim> send = query;
    // find nearest using helper
    Point<Dim> ret = findNearest(root, send, dim);
    return ret;
}
template <int Dim>
Point<Dim> KDTree<Dim>::findNearest(KDTreeNode * node, Point<Dim>& query, int dim) const{
  if(node->left == NULL && node->right == NULL) {
    //attain leaf node as best
    return node->point;
  }
  // define closest to current node
  Point<Dim> closest = node->point;
  // if left query is smaller than node we recurse left, otherwise right
  if(smallerDimVal(query, node->point, dim)) {
    if(node->left != NULL) {
      closest = findNearest(node->left, query, (dim + 1) % Dim);
    }
  } else {
    if(node->right != NULL) {
      closest = findNearest(node->right, query, (dim + 1) % Dim);
    }
  }
  // now we find distance for current node and recursed node
  // if recursive calls failed then distances should be equal 
  int curr_dis = findDistance(node->point, query);
  int close_dis = findDistance(closest, query);
  // compare distances and update closest to node if node distance closer
  if(curr_dis < close_dis) {
    closest = node->point;
  }
  // if equal comapre points
  if(curr_dis == close_dis) {
      if(node->point < closest) {
        closest = node->point;
      }
  }
  // to check if we need to check other subtree we ignored in the recursive call
  // find distance between our current closest point and query
  close_dis = findDistance(closest, query);
  // find the split distance across current dimension
  int split = (node->point[dim] - query[dim]) * (node->point[dim] - query[dim]);
  
  Point<Dim> tmp_close;
  // if split distance is less or equal to closest distance we search that subtree
  if(close_dis >= split) {
    // if previously recursed left we go right, and vice versa
    if(smallerDimVal(query, node->point, dim)) {
      if(node->right != NULL) {
        // perform recursion on right subtree and update closest if needed
        tmp_close = findNearest(node->right, query, (dim + 1) % Dim);
        int tmp_close_dis = findDistance(tmp_close, query);
        if(tmp_close_dis < close_dis) {
          closest = tmp_close;
        }
        if(tmp_close_dis == close_dis) {
          if(tmp_close < closest) closest = tmp_close;
        }
      }
    } else {
      if(node->left != NULL) {
        // perform recursion on left subtree and update closest if needed
        tmp_close = findNearest(node->left, query, (dim + 1) % Dim);
        int tmp_close_dis = findDistance(tmp_close, query);
        if(tmp_close_dis < close_dis) {
        closest = tmp_close;
        }
        if(tmp_close_dis == close_dis) {
        if(tmp_close < closest) closest = tmp_close;
        }
      }
    }
  }
  // return closest point
  return closest;
}

template <int Dim>
int KDTree<Dim>::findDistance(Point<Dim>& one, Point<Dim>& two) const{
  int ret = 0;
  // calculate distance across all dimensions
  for(int i = 0; i < Dim; i++) {
    ret += ((one[i] - two[i]) * (one[i] - two[i]));
  }
  return ret;
}

template <typename RandIter, typename Comparator>
void select(RandIter start, RandIter end, RandIter k, Comparator cmp)
{
    /**
     * @todo Implement this function!
     */    
    // want to select first
    // then we partition
    // edge case, empty vector
    if(start == end) return;
    // base case
    if(start == end - 1) return;

    // find pivot index
    int pivot = std::distance(start, end - 1) / 2;
    
    // partition based on pivot index
    pivot = part(start, end, pivot, cmp);

    // find k index
    int pos_k = std::distance(start, k);
    
    // compare k index with pivot index
    // if == we found, if less recurse left, else recurse right
    if(pos_k == pivot) {
      return;
    }
    else if(pos_k < pivot) {
      
      select(start, start + pivot, k, cmp);
    } else {
      
      select(start + pivot + 1, end, k, cmp);
    }
}

template <typename RandIter, typename Comparator>
int part(RandIter start, RandIter end, int pivot, Comparator cmp) {
  // find pivot iterator
  auto pivot_itr = start;
  for(int i = 0; i < pivot; i++) pivot_itr++;
  
  // find last element iterator
  auto tmp_right = end;
  --tmp_right;
  
  //int val = *(pivot_itr);
  
  //swap pivot with end
  std::swap(*pivot_itr, *tmp_right);
  auto index = start;
  
  // partition around pivot, which is at last element (tmp_right)
  for(auto i = start; i != tmp_right; i++) {
    if(cmp(*i, *tmp_right)) {
      // swap i and index, increment index
      std::swap(*index, *i);
      //std::cout << "made it in" << *index << " " << *i << std::endl;
      index++;
    }
    //std::cout << *i << " i";
  }
  //std::cout << "done with i" << std::endl;
  //swap end (which is currently pivot) with the index
  std::swap(*tmp_right, *index);
  //std::cout << "test 1" << std::endl;
  int ret = std::distance(start, index);
  //std::cout << "test 2" << ret << std::endl;
  return ret;
}

// doesnt work for some reason?
template <typename RandIter, typename Comparator>
void swap(RandIter one, RandIter two) {
  auto tmp_one = *one;
  auto tmp_two = *two;
  *one = tmp_two;
  *two = tmp_one;
  return;
}
