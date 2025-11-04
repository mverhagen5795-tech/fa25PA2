//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};
    //
    // // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");
    //
    // // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);
    //
    // // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);
    //
    // // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);
    //
    // // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);
    //
    return 0;

    // Testing for heap calling pushes to make sure any independent bugs from external testing don't apply

    }



/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
        // The buildEncodingTree is an example of a Huffman tree builder and it works by repeatedly taking the two smallest nodes,
        // merging them into one parent node with a combined weight of their sum, then pushes that parent node into a min heap
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
        MinHeap heap;
    // 2. Push all leaf node indices into the heap.
        for (int i = 0; i < nextFree; i++) {
            heap.push(i, weightArr);
        }
    // 3. While the heap size is greater than 1:
        while (heap.size > 1) {
    //    - Pop two smallest nodes
            int i1 = heap.pop(weightArr);
            int i2 = heap.pop(weightArr);
    //    - Create a new parent node with combined weight
            weightArr[nextFree]= weightArr[i1] + weightArr[i2];
    //    - Set left/right pointers
            leftArr[nextFree] = i1;
            rightArr[nextFree] = i2;
    //    - Push new parent index back into the heap
            heap.push(nextFree, weightArr);
            nextFree++;
    // 4. Return the index of the last remaining node (root)
    }
    return heap.pop(weightArr); // placeholder
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    if (root < 0) {
        return;
    }
    stack<pair<int,string>>stack;
    stack.push({root,""}); // Starts the stack at root with a empty path
    while (!stack.empty()) {
        pair<int,string> p = stack.top();
        stack.pop();
        int node = p.first;
        string code = p.second;

        int left = leftArr[node];
        int right = rightArr[node];

        // Record code when a leaf node is reached.
        if (left == -1 && right == -1) { // means neither has a child node so it must be a leaf node
            if (code.empty()) {
                code = "0";
            }
            char c = charArr[node];
            if (c >= 'a' && c <= 'z' ) { // case to check against uppercase
                codes[ c-'a' ] = code; // assigns the code to the value of ASCII of the letter minus 'a' which is 97

            }
        }
        // Left edge adds '0', right edge adds '1'.
        else {
            if (right != -1){
                stack.push({right, code + "1"});
            }
            if (left != -1){
                stack.push({left, code + "0"});
            }
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}