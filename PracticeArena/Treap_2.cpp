
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <sstream>

using namespace std;

#pragma region TreeDebug
template <typename T>
class TreeDebug
{
public:
    /// @brief prints the tree to the console in NLR order
    /// @param node must have a toString() method
    /// @param rootIndex
    /// @param prefix
    /// @return
    static stringstream debugTree(shared_ptr<T> node, int rootIndex = 1, string prefix = "")
    {
        stringstream ss;
        string unitPrefix = "       ";
        if (!node)
        {
            ss << prefix << "#" << to_string(rootIndex) << "-> |()" << endl;
            return ss;
        }
        ss << prefix + "#" + to_string(rootIndex) + (rootIndex & 1 ? "_R-> " : "_L-> ") << "Node = " << node->toString() << endl;

        ss << debugTree(node->leftChild, rootIndex << 1, prefix + unitPrefix).str();
        ss << debugTree(node->rightChild, (rootIndex << 1) + 1, prefix + unitPrefix).str();
        return ss;
    }
};

#pragma endregion TreeDebug

////////////////////////////////////////// Treap starts Here //////////////////////////////////////////////////////

#pragma region ImplicitTreap

constexpr const size_t mod = 10000007;

struct TreapNode
{
    shared_ptr<TreapNode> leftChild, rightChild;

    int key;
    size_t priority, size;

    TreapNode(int key, shared_ptr<TreapNode> left = nullptr, shared_ptr<TreapNode> right = nullptr, size_t priority = rand() % mod)
    {
        this->priority = priority;
        this->key = key;
        leftChild = left;
        rightChild = right;
        size = 1;
    }

    size_t recalculateSize()
    {
        int s = 1;
        if (leftChild)
            s += leftChild->size;
        if (rightChild)
            s += rightChild->size;
        return size = s;
    }

    string toString()
    {
        return "Value : " + to_string(key) + "  priority : " + to_string(priority) + "   size " + to_string(size);
    }
};

class Treap
{
    shared_ptr<TreapNode> root;

    void cleanup(shared_ptr<TreapNode> node)
    {
        if (!node)
            return;
        cleanup(node->leftChild);
        cleanup(node->rightChild);
        node.~shared_ptr();
    }

public:
    Treap() = default;

    size_t getSubTreeSize(shared_ptr<TreapNode> node)
    {
        return node ? node->size : 0;
    }

    void split(int key, shared_ptr<TreapNode> node, shared_ptr<TreapNode> &left, shared_ptr<TreapNode> &right)
    {
        if (!node)
        {
            left = right = nullptr;
            return;
        }

        int currentIndex = getSubTreeSize(node->leftChild) + 1;
        if (key < currentIndex)
        { /// search left subtree according to BST
            right = node;
            split(key, node->leftChild, left, node->leftChild);
        }
        else
        {
            left = node;
            split(key - currentIndex, node->rightChild, node->rightChild, right);
        }
        if (left)
            left->recalculateSize();
        if (right)
            right->recalculateSize();
    }

    shared_ptr<TreapNode> merge(shared_ptr<TreapNode> left, shared_ptr<TreapNode> right)
    {
        if (!left)
            return right;
        if (!right)
            return left;

        if (left->priority > right->priority)
        {                                                      // min priority will be the parent
            left->rightChild = merge(left->rightChild, right); // Right rotation
            left->recalculateSize();
            return left;
        }
        else
        {
            right->leftChild = merge(left, right->leftChild); // Left rotation
            right->recalculateSize();
            return right;
        }
    }

    ////////////////////////////// Core Treap ends here ///////////////////////////////////////////////////////////////////////

    void insert(int pos, int val)
    {
        shared_ptr<TreapNode> newNode = make_shared<TreapNode>(pos, nullptr, nullptr, val); /// 0-based Index
        shared_ptr<TreapNode> left = nullptr, right = nullptr;

        split(pos, root, left, right);
        root = merge(merge(left, newNode), right);
    }

    void build(vector<int> &array)
    {
        for (int i = 0; i < array.size(); i++)
        {
            insert(i, array[i]);
        }
    }

    void remove(int low, int high)
    {

        shared_ptr<TreapNode> left = nullptr, right = nullptr, intervalTree = nullptr;
        split(low, root, left, right);
        int intervalLength = high - low + 1;
        split(intervalLength, right, intervalTree, right);
        root = merge(left, right);

        print(root, "New tree after removal");
    }

    int find_kth_minimum_number_interval(int low, int high, int k)
    {
        shared_ptr<TreapNode> left, right, intervalTree;
        split(low, root, left, right);
        cout << "left tree ================" << endl;
        print(left);
        cout << " left end tree ************" << endl;

        split(high - low + 1, right, intervalTree, right);
        cout << " Interval tree ================" << endl;
        print(intervalTree);
        cout << " Interval tree ************" << endl;
        cout << " right tree ================" << endl;
        print(right);
        cout << " right tree end************" << endl;
        int answer = find_kth_minimum_number(intervalTree, k);
        root = merge(left, merge(intervalTree, right));
        return answer;
    }

    int find_kth_minimum_number(shared_ptr<TreapNode> node, int k)
    {
        if (!node)
            return 0;
        // if (node->size < k)
        //     return 0;
        if (k == 1)
            return node->priority;
        int currentIndex = getSubTreeSize(node->leftChild) + 1;
        if (currentIndex > k)
        {
            return find_kth_minimum_number(node->leftChild, k);
        }
        else
        {
            return find_kth_minimum_number(node->rightChild, k - currentIndex);
        }
    }

    void print(shared_ptr<TreapNode> node, string blockEnding = "This block")
    {
        cout << "----------------  " + blockEnding + "  ---- Starts Here-----------" << endl;
        cout << TreeDebug<TreapNode>::debugTree(node).str() << endl;
        cout << "----------------  " + blockEnding + "  ---- Ends Here-----------" << endl;
    }

    shared_ptr<TreapNode> getRoot()
    {
        return root;
    }

    ~Treap()
    {
        cleanup(root);
    }
};

#pragma endregion ImplicitTreap
/////////////////// Treap ends Here ////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    vector<int> input{10, 20, 5, 7, 11, 3, 1};

    Treap cartesianTree;
    cartesianTree.build(input);
    cout << "########################" << endl;
    cartesianTree.remove(2, 4);

    // int kthMin = cartesianTree.find_kth_minimum_number_interval(2, 5, 2);

    // cout << "answer : " << kthMin << endl;
    // cout << cartesianTree.printTree(cartesianTree.getRoot()).str() << endl;

    return 0;
}

/// ///////////////////////////
///
///     http://e-maxx.ru/algo/treap
///     https://habr.com/en/articles/102364/
///