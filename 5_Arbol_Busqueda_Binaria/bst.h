// bst.h
#ifndef BST_H
#define BST_H

#include <queue>
#include <sstream>
#include <string>

template <class T>
class TreeNode {
public:
    T data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(T val) : data(val), left(nullptr), right(nullptr) {}
    
};

template <class T>
class BST {
private:
    TreeNode<T> *root;

    TreeNode<T>* insert(TreeNode<T>* node, T val) {
        if (node == nullptr) {
            return new TreeNode<T>(val);
        }
        if (val < node->data) {
            node->left = insert(node->left, val);
        } else if (val > node->data) {
            node->right = insert(node->right, val);
        }
        return node;
    }

    void preorder(TreeNode<T>* node, std::stringstream& ss) const {
        /*if (node) {

            preorder(node->left, ss);
            preorder(node->right, ss);
            if (ss.tellp() != 1) {
		        ss << " ";
	        }
        }*/

        if (node) {
            if (ss.tellp() != 1) {
                ss << " ";
            }
            ss << node->data;
            preorder(node->left, ss);
            preorder(node->right, ss);
        }
    }


void inorder(TreeNode<T>* node, std::stringstream& ss) const {
    if (node) {
        if (node->left != nullptr) {
            inorder(node->left, ss);
            ss << " ";
        }
        ss << node->data;
        if (node->right != nullptr) {
            ss << " ";
            inorder(node->right, ss);
        }
    }
}

void postorder(TreeNode<T>* node, std::stringstream& ss) const {
    if (node) {
        if (node->left != nullptr) {
            postorder(node->left, ss);
            ss << " ";
        }
        if (node->right != nullptr) {
            postorder(node->right, ss);
            ss << " ";
        }
        ss << node->data;
    }
}

   void levelByLevel(std::stringstream& ss) const {
    if (!root) {
        return;
    }

    std::queue<TreeNode<T>*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; ++i) {
            TreeNode<T>* current = q.front();
            q.pop();
            
            ss << current->data;

            if (i < levelSize - 1) {
                ss << " ";
            }

            if (current->left) {
                q.push(current->left);
            }
            if (current->right) {
                q.push(current->right);
            }
        }

        if (!q.empty()) {
            ss << " ";
        }
    }
}

    int height(TreeNode<T>* node) const {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return std::max(leftHeight, rightHeight) + 1;
    }


    int whatlevelamI(TreeNode<T>* node, T val, int level) const {
        if (node == nullptr) {
            return 0;
        }
        if (node->data == val) {
            return level;
        }
        if (val < node->data) {
            return whatlevelamI(node->left, val, level + 1);
        } else {
            return whatlevelamI(node->right, val, level + 1);
        }
    }

public:
    BST() : root(nullptr) {}

    void add(T val) {
        root = insert(root, val);
    }

    std::string visit() const {
        std::stringstream ss;
        ss << "[";
        preorder(root, ss);
        ss <<"]\n[";
        inorder(root, ss);
        ss <<"]\n[";
        postorder(root, ss);
        ss <<"]\n[";
        levelByLevel(ss);
        ss <<"]";

        return ss.str();
    }

    int height() const {
        return height(root);
    }std::string ancestors(T val) const {
    std::stringstream ss;
    TreeNode<T>* current = root;
    bool found = false;

    while (current != nullptr) {
        if (val == current->data) {
            found = true;
            break;
        }

        if (ss.tellp() != 0) {
            ss << " "; 
        }
        ss << current->data;

        if (val < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (!found) {
        return "[]";
    }

    std::string result = "[" + ss.str() + "]"; 
    return result;
}





    

    int whatlevelamI(T val) const {
        return whatlevelamI(root, val, 1);
    }
};

#endif // BST_H
