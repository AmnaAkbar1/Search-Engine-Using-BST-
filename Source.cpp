#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Node 
{
    string keyword;
    vector<string> urls;
    Node* left;
    Node* right;
    Node(const string& key, const string& url) : keyword(key), left(nullptr), right(nullptr) 
    {
        urls.push_back(url);
    }
};


class BST {
private:
    Node* root;

    
    Node* insert(Node* root, const string& key, const string& url) {
        
        if (root == nullptr) {
            return new Node(key, url);
        }

        if (key < root->keyword) {
            root->left = insert(root->left, key, url);
        }
        else if (key > root->keyword) {
            root->right = insert(root->right, key, url);
        }
        else {
            root->urls.push_back(url); // Keyword already exists, add URL to existing node
        }
        return root;
    }

    
    vector<string> search(Node* root, const string& key) {
        
        vector<string> result;
        if (root == nullptr) {
            return result;
        }

        if (key < root->keyword) {
            return search(root->left, key);
        }
        else if (key > root->keyword) {
            return search(root->right, key);
        }
        else {
            
            result = root->urls;

            // Search in both left and right subtrees for the same keyword
            vector<string> leftResult = search(root->left, key);
            vector<string> rightResult = search(root->right, key);

            // Merge results from left and right subtrees with the current node's URLs
            result.insert(result.end(), leftResult.begin(), leftResult.end());
            result.insert(result.end(), rightResult.begin(), rightResult.end());
        }
        return result;
    }

 

public:
    BST() : root(nullptr) {}

    
    void insert(const string& key, const string& url) {
        root = insert(root, key, url);
    }

    vector<string> search(const string& key) {
        return search(root, key);
    }

    
};

// Function to read data from file and build BST
BST readDataFromFile(const string& filename) {
    ifstream file(filename);
    BST bst;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            string id, url, keywords;
            if (!line.empty()) {
                istringstream iss(line);
                iss >> id >> url;
                getline(file, keywords);

                istringstream kss(keywords);
                string keyword;
                while (kss >> keyword) {
                    bst.insert(keyword, url);
                }
            }
        }
        file.close();
    }
    return bst;
}

// Function to interact with the user
void searchInterface(BST& bst) {
    string keyword;
    cout << "Please enter a word to search: ";
    cin >> keyword;

    vector<string> results = bst.search(keyword);
    cout << results.size() << " result(s) found\n";
    for (const string& result : results) {
        cout << result << endl;
    }
}

int main() {
    string filename;
    cout << "Please enter a filename: ";
    cin >> filename; //Assignment_data.txt

    BST bst = readDataFromFile(filename);
    cout << "File loaded successfully.\n";

    searchInterface(bst);

    return 0;
}
