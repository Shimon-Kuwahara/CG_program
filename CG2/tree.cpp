#include <stdio.h>
#include <stdlib.h>

// 木構造のノードを表す構造体
typedef struct Node {
    int data;
    struct Node* firstChild;  // 最初の子ノード
    struct Node* nextSibling; // 次の兄弟ノード
} Node;

// 新しいノードを作成する関数
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "メモリの割り当てエラー\n");
        exit(1);
    }
    newNode->data = data;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

// 木構造を先行順走査する再帰関数
void preorderTraversal(Node* node) {
    if (node == NULL) {
        return;
    }
    // ノードのデータを処理
    printf("%d ", node->data);
    // 最初の子ノードを走査
    preorderTraversal(node->firstChild);
    // 次の兄弟ノードを走査
    preorderTraversal(node->nextSibling);
}

int main() {
    // 例: 木構造を作成
    Node* root = createNode(1);
    root->firstChild = createNode(2);
    root->firstChild->nextSibling = createNode(3);
    root->firstChild->nextSibling->firstChild = createNode(4);
    root->firstChild->nextSibling->nextSibling = createNode(5);

    // 先行順走査を実行
    printf("木構造の先行順走査結果: ");
    preorderTraversal(root);
    printf("\n");

    // メモリの解放
    // 通常、実際のアプリケーションではメモリの解放が必要ですが、ここでは省略しています

    return 0;
}
