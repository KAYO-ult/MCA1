#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node* createNode(int val) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}

struct Node* insertAtBeginning(struct Node *head, int val) {
    struct Node *newNode = createNode(val);
    newNode->next = head;
    return newNode;
}

struct Node* insertEnd(struct Node *head, int val) {
    if (head == NULL) return createNode(val);
    head->next = insertEnd(head->next, val);
    return head;
}

struct Node* insertPos(struct Node *head, int val, int pos) {
    if (pos < 1) {
        printf("Position out of bounds\n");
        return head;
    }
    if (pos == 1) {
        struct Node *newNode = createNode(val);
        newNode->next = head;
        return newNode;
    }
    if (head == NULL) {
        printf("Position out of bounds\n");
        return NULL;
    }
    head->next = insertPos(head->next, val, pos - 1);
    return head;
}

struct Node* deleteBeg(struct Node *head) {
    if (head == NULL) return NULL;
    struct Node *temp = head;
    head = head->next;
    free(temp);
    return head;
}

struct Node* deleteEnd(struct Node *head) {
    if (head == NULL) return NULL;
    if (head->next == NULL) {
        free(head);
        return NULL;
    }
    head->next = deleteEnd(head->next);
    return head;
}

struct Node* deletePos(struct Node *head, int pos) {
    if (head == NULL || pos < 1) {
        printf("Position out of bounds\n");
        return head;
    }
    if (pos == 1) {
        struct Node *temp = head->next;
        free(head);
        return temp;
    }
    head->next = deletePos(head->next, pos - 1);
    return head;
}

int countNodes(struct Node *head) {
    if (head == NULL) return 0;
    return 1 + countNodes(head->next);
}

int searchNodePos(struct Node *head, int key) {
    if (head == NULL) return -1;
    if (head->data == key) return 1;
    int res = searchNodePos(head->next, key);
    return (res == -1) ? -1 : 1 + res;
}

int searchIndex(struct Node *head, int key) {
    if (head == NULL) return -1;
    if (head->data == key) return 0;
    int res = searchIndex(head->next, key);
    return (res == -1) ? -1 : 1 + res;
}

void display(struct Node *head) {
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    printf("%d -> ", head->data);
    display(head->next);
}

// 11. REVERSE (Recursive)
struct Node* reverseList(struct Node *head) {
    if (head == NULL || head->next == NULL)
        return head;

    struct Node *newHead = reverseList(head->next);
    head->next->next = head;
    head->next = NULL;

    return newHead;
}

// 12. BUBBLE SORT (Recursive)
void bubbleSort(struct Node *head) {
    if (head == NULL || head->next == NULL)
        return;

    int swapped = 0;

    for (struct Node *temp = head; temp->next != NULL; temp = temp->next) {
        if (temp->data > temp->next->data) {
            int x = temp->data;
            temp->data = temp->next->data;
            temp->next->data = x;
            swapped = 1;
        }
    }

    if (swapped)
        bubbleSort(head);
}

// 13. SELECTION SORT (Recursive)
void selectionSort(struct Node *head) {
    if (head == NULL || head->next == NULL)
        return;

    struct Node *min = head;

    for (struct Node *ptr = head->next; ptr != NULL; ptr = ptr->next) {
        if (ptr->data < min->data)
            min = ptr;
    }

    int x = head->data;
    head->data = min->data;
    min->data = x;

    selectionSort(head->next);
}

// 14. INSERTION SORT (Recursive with for loop)
void insertionSort(struct Node *head, struct Node *curr) {
    if (curr == NULL)
        return;

    for (struct Node *ptr = head; ptr != curr; ptr = ptr->next) {
        if (ptr->data > curr->data) {
            int x = ptr->data;
            ptr->data = curr->data;
            curr->data = x;
        }
    }

    insertionSort(head, curr->next);
}

// 15. QUICK SORT (Recursive)
void quickSort(struct Node *low, struct Node *high) {
    if (low == NULL || high == NULL || low == high || low == high->next)
        return;

    int pivot = high->data;
    struct Node *i = NULL;

    // PARTITION
    for (struct Node *j = low; j != high; j = j->next) {
        if (j->data <= pivot) {
            if (i == NULL)
                i = low;
            else
                i = i->next;

            int x = i->data;
            i->data = j->data;
            j->data = x;
        }
    }

    struct Node *p;
    if (i == NULL)
        p = low;
    else
        p = i->next;

    int x = p->data;
    p->data = high->data;
    high->data = x;

    // FIND PREVIOUS NODE (LEFT PARTITION)
    if (p != low) {
        struct Node *prev = low;
        for (; prev->next != p; prev = prev->next);
        quickSort(low, prev);
    }

    // RIGHT PARTITION
    quickSort(p->next, high);
}

// 16. MERGE SORT (Recursive with for loop to find middle)
struct Node* merge(struct Node *a, struct Node *b) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    if (a->data <= b->data) {
        a->next = merge(a->next, b);
        return a;
    } else {
        b->next = merge(a, b->next);
        return b;
    }
}

struct Node* mergeSort(struct Node *head) {
    if (head == NULL || head->next == NULL)
        return head;

    struct Node *slow = head;
    struct Node *fast = head->next;

    for (; fast != NULL && fast->next != NULL; slow = slow->next, fast = fast->next->next);

    struct Node *mid = slow->next;
    slow->next = NULL;

    struct Node *left = mergeSort(head);
    struct Node *right = mergeSort(mid);

    return merge(left, right);
}


int main() {
    struct Node *head = NULL;
    struct Node *last = NULL;
    int choice, val, pos, res;

    while (1) {
        printf("\n--- RECURSIVE LINKED LIST ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert Anywhere (Position)\n");
        printf("4. Delete at Beginning\n");
        printf("5. Delete at End\n");
        printf("6. Delete Anywhere (Position)\n");
        printf("7. Count Number of Nodes\n");
        printf("8. Search Element (1-based Node Number)\n");
        printf("9. Search Element (0-based Index)\n");
        printf("10. Display\n");
        printf("11. Reverse Linked List\n");
        printf("12. Bubble Sort\n");
        printf("13. Selection Sort\n");
        printf("14. Insertion Sort\n");
        printf("15. Quick Sort\n");
        printf("16. Merge Sort\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 0) break;

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                head = insertAtBeginning(head, val);
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &val);
                head = insertEnd(head, val);
                break;
            case 3:
                printf("Enter value and 1-based position: ");
                scanf("%d %d", &val, &pos);
                head = insertPos(head, val, pos);
                break;
            case 4:
                head = deleteBeg(head);
                break;
            case 5:
                head = deleteEnd(head);
                break;
            case 6:
                printf("Enter 1-based position to delete: ");
                scanf("%d", &pos);
                head = deletePos(head, pos);
                break;
            case 7:
                printf("Total Nodes: %d\n", countNodes(head));
                break;
            case 8:
                printf("Enter element to search: ");
                scanf("%d", &val);
                res = searchNodePos(head, val);
                if (res == -1) printf("Element not found\n");
                else printf("Element %d is at Node #%d\n", val, res);
                break;
            case 9:
                printf("Enter element to search: ");
                scanf("%d", &val);
                res = searchIndex(head, val);
                if (res == -1) printf("Element not found\n");
                else printf("Element %d is at Index %d\n", val, res);
                break;
            case 10:
                display(head);
                break;
            case 11:
                head = reverseList(head);
                printf("Reversed Linked List:\n");
                display(head);
                break;
            case 12:
                bubbleSort(head);
                printf("Sorted Linked List (Bubble Sort):\n");
                display(head);
                break;
            case 13:
                selectionSort(head);
                printf("Sorted Linked List (Selection Sort):\n");
                display(head);
                break;
            case 14:
                insertionSort(head, head);
                printf("Sorted Linked List (Insertion Sort):\n");
                display(head);
                break;
            case 15:
                for (last = head; last != NULL && last->next != NULL; last = last->next);
                quickSort(head, last);
                printf("Sorted Linked List (Quick Sort):\n");
                display(head);
                break;
            case 16:
                head = mergeSort(head);
                printf("Sorted Linked List (Merge Sort):\n");
                display(head);
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}