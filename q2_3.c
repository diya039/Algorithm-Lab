#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* buildHuffmanTree(char data[], char* encoding[], int size) {
    Node* root = createNode('\0');
    for (int i = 0; i < size; ++i) {
        Node* current = root;
        for (int j = 0; encoding[i][j] != '\0'; ++j) {
            if (encoding[i][j] == '0') {
                if (current->left == NULL)
                    current->left = createNode('\0');
                current = current->left;
            } else {
                if (current->right == NULL)
                    current->right = createNode('\0');
                current = current->right;
            }
        }
        current->data = data[i];
    }
    return root;
}

void decodeHuffman(Node* root, char* encodedText) {
    Node* current = root;
    for (char* c = encodedText; *c != '\0'; ++c) {
        if (*c == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        if (current->left == NULL && current->right == NULL) {
            printf("%c", current->data);
            current = root;
        }
    }
}

int main() {
    char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    char* encoding[] = {"1010", "10", "1100", "1101", "0", "111"};
    int size = sizeof(data) / sizeof(data[0]);

    Node* root = buildHuffmanTree(data, encoding, size);

    char* encodedText = "1010110011010111"; // Example encoded text

    printf("Decoded text: ");
    decodeHuffman(root, encodedText);
    printf("\n");

    return 0;
}
