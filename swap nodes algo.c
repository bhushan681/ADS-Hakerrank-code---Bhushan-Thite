#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node* create_node(int val) {
    if (val == -1)
        return NULL;
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void inorder(struct node *root) {
    if (!root)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct node *root) {
    if (!root)
        return 0;
    return 1 + max(height(root->left), height(root->right));
}

void swap_nodes_at_level(struct node *root, int inc, int level, int height) {
    if (!root || level > height)
        return;

    if (level % inc == 0) {
        struct node *tmp = root->left;
        root->left = root->right;
        root->right = tmp;
    }

    swap_nodes_at_level(root->left, inc, level + 1, height);
    swap_nodes_at_level(root->right, inc, level + 1, height);
}

int tail = 0, head = 0;

void enqueue(struct node **queue, struct node *root) {
    queue[tail++] = root;
}

struct node* dequeue(struct node **queue) {
    return queue[head++];
}

int main() {
    int nodes_count;
    scanf("%d", &nodes_count);

    struct node *root_perm, *root_temp;
    struct node *q[2 * nodes_count];
    for (int i = 0; i < 2 * nodes_count; i++)
        q[i] = NULL;

    head = tail = 0;
    root_perm = create_node(1);
    enqueue(q, root_perm);

    int index = 1;
    while (index <= 2 * nodes_count && head < tail) {
        root_temp = dequeue(q);
        int temp1, temp2;
        scanf("%d %d", &temp1, &temp2);

        if (temp1 != -1) {
            root_temp->left = create_node(temp1);
            enqueue(q, root_temp->left);
        }
        if (temp2 != -1) {
            root_temp->right = create_node(temp2);
            enqueue(q, root_temp->right);
        }
        index += 2;
    }

    int h = height(root_perm);
    int tc_num;
    scanf("%d", &tc_num);

    while (tc_num--) {
        int inc;
        scanf("%d", &inc);
        swap_nodes_at_level(root_perm, inc, 1, h);
        inorder(root_perm);
        printf("\n");
    }

    return 0;
}
