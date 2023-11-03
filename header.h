#ifndef QUARTENARY_SEARCH_TREE_H
#define QUARTENARY_SEARCH_TREE_H

#include <vector>
#include <iostream>

class InvalidChoiceException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid choice. Please choose a valid option.";
    }
};

class ElementNotFoundException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Element not found.";
    }
};

template <typename Key, typename Value>
class QuartenarySearchTree {
private:
    struct Node {
        Key key;
        Value value;
        Node* children[4];

        Node(const Key& k, const Value& v) : key(k), value(v) {
            for (int i = 0; i < 4; ++i) {
                children[i] = nullptr;
            }
        }
    };

    Node* root;

public:
    QuartenarySearchTree() : root(nullptr) {}

    void insert(const Key& key, const Value& value) {
        root = insertRecursive(root, key, value);
    }

    Value search(const Key& key) const {
        return searchRecursive(root, key);
    }

    void insertAdditional(const Key& key, const Value& value) {
        root = insertRecursive(root, key, value);
    }

    bool deleteKey(const Key& key) {
        return deleteRecursive(root, key);
    }

    void printPreorder() const {
        printPreorder(root);
        std::cout << std::endl;
    }

    void printPostorder() const {
        printPostorder(root);
        std::cout << std::endl;
    }

private:
    Node* insertRecursive(Node* node, const Key& key, const Value& value) {
        if (node == nullptr) {
            return new Node(key, value);
        }

        int index = determineChild(key, node->key);
        node->children[index] = insertRecursive(node->children[index], key, value);
        return node;
    }

    Value searchRecursive(Node* node, const Key& key) const {
        if (node == nullptr) {
            return Value(); // Return a default value if key is not found
        }

        if (node->key == key) {
            return node->value;
        }

        int index = determineChild(key, node->key);
        return searchRecursive(node->children[index], key);
    }

    bool deleteRecursive(Node*& node, const Key& key) {
        if (node == nullptr) {
            return false; // Key not found
        }

        if (node->key == key) {
            deleteNode(node);
            return true;
        }

        int index = determineChild(key, node->key);
        if (deleteRecursive(node->children[index], key)) {
            return true;
        }

        return false; // Key not found in children
    }

    void deleteNode(Node*& node) {
        if (node->children[0] || node->children[1] || node->children[2] || node->children[3]) {
            // Node has children, just mark it as deleted (or set a flag, as per your needs)
        } else {
            // Node is a leaf, safe to delete
            delete node;
            node = nullptr;
        }
    }

    int determineChild(const Key& key, const Key& parentKey) const {
        if (key < parentKey / 2) {
            return 0;
        } else if (key < parentKey) {
            return 1;
        } else if (key < parentKey * 2) {
            return 2;
        } else {
            return 3;
        }
    }

    void printPreorder(Node* node) const {
        if (node) {
            std::cout << node->key << " ";
            for (int i = 0; i < 4; ++i) {
                printPreorder(node->children[i]);
            }
        }
    }

    void printPostorder(Node* node) const {
        if (node) {
            for (int i = 0; i < 4; ++i) {
                printPostorder(node->children[i]);
            }
            std::cout << node->key << " ";
        }
    }
};

#endif // QUARTENARY_SEARCH_TREE_H
