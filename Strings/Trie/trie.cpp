#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

string process_word(const string& word) {
    string processed;
    for (char ch : word) {
        if (isalpha(ch)) {
            processed += tolower(ch);
        }
    }
    return processed;
}

struct Node {
    bool end;
    vector<Node*> children;

    Node()
        : end(false), children(26, nullptr) {}

    ~Node() {
        for (Node* child : children) {
            delete child;
        }
    }
};

class Trie {
    Node* root;

    int get_index(char ch) const {
        return ch - 'a';
    }

public:
    Trie() {
        root = new Node();
    }

    ~Trie() {
        delete root;
    }

    void insert(const string& word) {
        string processed_word = process_word(word);
        if (processed_word.empty()) return;

        Node* current = root;

        for (char ch : processed_word) {
            int index = get_index(ch);

            if (current->children[index] == nullptr) {
                current->children[index] = new Node();
            }

            current = current->children[index];
        }

        current->end = true;
    }

    bool search(const string& word) const {
        string processed_word = process_word(word);
        if (processed_word.empty()) return false;

        Node* current = root;

        for (char ch : processed_word) {
            int index = get_index(ch);

            if (current->children[index] == nullptr) {
                return false;
            }

            current = current->children[index];
        }

        return current->end;
    }
};

int main()
{
    Trie trie;
    ifstream file("eng-words.txt");
    int count = 0;

    if (!file.is_open()) {
        cout << "Error." << endl;
        return 1;
    }

    string word;

    while (getline(file, word)) {
        trie.insert(word);
        count++;
    }
    file.close();

    cout << count << endl;
    cout << trie.search("into") << endl;
    cout << trie.search("exit") << endl;
    cout << trie.search("berries") << endl;
    cout << trie.search("a") << endl;
    cout << trie.search("wow") << endl;
    cout << trie.search("mig") << endl;
    cout << trie.search("chauffeur") << endl;


    return 0;
}

