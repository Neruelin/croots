
struct Node;

typedef struct Node {
    int value;
    struct Node* next;
} Node;

int concat(Node* root, Node* other);
int appendValue(Node* root, int v);
int removeLast(Node* root);