#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}

struct Node* insertAtBeginning(struct Node* head, int val) {
    struct Node* newNode = createNode(val);
    newNode->next = head;
    return newNode;
}

struct Node* insertEnd(struct Node* head, int val) {
    struct Node* newNode = createNode(val);
    if (head == NULL) return newNode;

    struct Node* temp;
    for (temp = head; temp->next != NULL; temp = temp->next);
    temp->next = newNode;
    return head;
}

struct Node* insertPos(struct Node* head, int val, int pos) {
    if (pos < 1) return head;
    if (pos == 1) return insertAtBeginning(head, val);

    struct Node* temp = head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position out of bounds\n");
        return head;
    }
    struct Node* newNode = createNode(val);
    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

struct Node* deleteBeg(struct Node* head) {
    if (head == NULL) return NULL;
    struct Node* temp = head;
    head = head->next;
    free(temp);
    return head;
}

struct Node* deleteEnd(struct Node* head) {
    if (head == NULL) return NULL;
    if (head->next == NULL) {
        free(head);
        return NULL;
    }
    struct Node* temp;
    for (temp = head; temp->next->next != NULL; temp = temp->next);
    free(temp->next);
    temp->next = NULL;
    return head;
}

struct Node* deletePos(struct Node* head, int pos) {
    if (head == NULL || pos < 1) return head;
    if (pos == 1) return deleteBeg(head);

    struct Node* temp = head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Position out of bounds\n");
        return head;
    }
    struct Node* toDelete = temp->next;
    temp->next = toDelete->next;
    free(toDelete);
    return head;
}

int countNodes(struct Node* head) {
    int count = 0;
    for (struct Node* temp = head; temp != NULL; temp = temp->next) {
        count++;
    }
    return count;
}

int searchNodePos(struct Node* head, int key) {
    int pos = 1;
    for (struct Node* temp = head; temp != NULL; temp = temp->next, pos++) {
        if (temp->data == key) return pos;
    }
    return -1;
}

int searchIndex(struct Node* head, int key) {
    int idx = 0;
    for (struct Node* temp = head; temp != NULL; temp = temp->next, idx++) {
        if (temp->data == key) return idx;
    }
    return -1;
}

void display(struct Node* head) {
    for (struct Node* temp = head; temp != NULL; temp = temp->next) {
        printf("%d -> ", temp->data);
    }
    printf("NULL\n");
}

// 11. REVERSE 
struct Node* reverseList(struct Node* head) {
    struct Node *prev = NULL, *curr = head, *next = NULL;

    for (; curr != NULL; curr = next) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
    }

    return prev;
}

// 12. BUBBLE SORT (Using nested for loops)
void bubbleSort(struct Node* head) {
    if (head == NULL || head->next == NULL)
        return;

    for (struct Node* i = head; i != NULL; i = i->next) {
        int swapped = 0;

        for (struct Node* temp = head; temp->next != NULL; temp = temp->next) {
            if (temp->data > temp->next->data) {
                int x = temp->data;
                temp->data = temp->next->data;
                temp->next->data = x;
                swapped = 1;
            }
        }

        if (!swapped)
            break;
    }
}

// 13. SELECTION SORT 
void selectionSort(struct Node* head) {
    for (struct Node* i = head; i != NULL && i->next != NULL; i = i->next) {
        struct Node* min = i;

        for (struct Node* ptr = i->next; ptr != NULL; ptr = ptr->next) {
            if (ptr->data < min->data)
                min = ptr;
        }

        int x = i->data;
        i->data = min->data;
        min->data = x;
    }
}

// 14. INSERTION SORT 
void insertionSort(struct Node* head) {
    if (head == NULL || head->next == NULL)
        return;

    for (struct Node* curr = head->next; curr != NULL; curr = curr->next) {
        for (struct Node* ptr = head; ptr != curr; ptr = ptr->next) {
            if (ptr->data > curr->data) {
                int x = ptr->data;
                ptr->data = curr->data;
                curr->data = x;
            }
        }
    }
}

// 15. QUICK SORT (Divide & Conquer with for-loop Partition)
void quickSort(struct Node* low, struct Node* high) {
    if (low == NULL || high == NULL || low == high || low == high->next)
        return;

    int pivot = high->data;
    struct Node* i = NULL;

    // PARTITION
    for (struct Node* j = low; j != high; j = j->next) {
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

    struct Node* p;
    if (i == NULL)
        p = low;
    else
        p = i->next;

    int x = p->data;
    p->data = high->data;
    high->data = x;

    // FIND PREVIOUS NODE (LEFT PARTITION)
    if (p != low) {
        struct Node* prev = low;
        for (; prev->next != p; prev = prev->next);
        quickSort(low, prev);
    }

    // RIGHT PARTITION
    quickSort(p->next, high);
}

// 16. MERGE SORT (Divide & Conquer with iterative for-loop Merge)
struct Node* merge(struct Node* a, struct Node* b) {
    struct Node dummy;
    struct Node* tail = &dummy;
    dummy.next = NULL;

    for (; a != NULL && b != NULL; tail = tail->next) {
        if (a->data <= b->data) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
    }

    tail->next = (a != NULL) ? a : b;
    return dummy.next;
}

struct Node* mergeSort(struct Node* head) {
    if (head == NULL || head->next == NULL)
        return head;

    struct Node* slow = head;
    struct Node* fast = head->next;

    for (; fast != NULL && fast->next != NULL; slow = slow->next, fast = fast->next->next);

    struct Node* mid = slow->next;
    slow->next = NULL;

    struct Node* left = mergeSort(head);
    struct Node* right = mergeSort(mid);

    return merge(left, right);
}

int main() {
    struct Node* head = NULL;
    struct Node* last = NULL;
    int choice, val, pos, res;

    for (;;) {
        printf("\n--- LINKED LIST (FOR LOOP) ---\n");
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
                insertionSort(head);
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