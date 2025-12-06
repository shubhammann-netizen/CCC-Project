#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY 20
#define MAX_STACK 20
#define MAX_QUEUE 20

/* ---------------- ARRAY SIMULATION ---------------- */

int arr[MAX_ARRAY];
int arrSize = 0;

void displayArray() {
    int i;
    if (arrSize == 0) {
        printf("Array is empty.\n");
        return;
    }
    printf("Current Array (size = %d): ", arrSize);
    for (i = 0; i < arrSize; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void insertArray(int pos, int value) {
    int i;
    if (arrSize == MAX_ARRAY) {
        printf("Array is full. Cannot insert.\n");
        return;
    }
    if (pos < 0 || pos > arrSize) {
        printf("Invalid position.\n");
        return;
    }

    printf("Inserting %d at position %d (0-based index).\n", value, pos);
    for (i = arrSize - 1; i >= pos; i--) {
        printf("Shifting arr[%d] = %d to arr[%d].\n", i, arr[i], i + 1);
        arr[i + 1] = arr[i];
    }
    arr[pos] = value;
    arrSize++;
    displayArray();
}

void deleteArray(int pos) {
    int i;
    if (arrSize == 0) {
        printf("Array is empty. Cannot delete.\n");
        return;
    }
    if (pos < 0 || pos >= arrSize) {
        printf("Invalid position.\n");
        return;
    }

    printf("Deleting element at position %d (value = %d).\n", pos, arr[pos]);
    for (i = pos; i < arrSize - 1; i++) {
        printf("Shifting arr[%d] = %d to arr[%d].\n", i + 1, arr[i + 1], i);
        arr[i] = arr[i + 1];
    }
    arrSize--;
    displayArray();
}

/* ---------------- LINKED LIST SIMULATION ---------------- */

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *head = NULL;

void displayList() {
    Node *temp = head;
    if (!temp) {
        printf("Linked list is empty.\n");
        return;
    }
    printf("Linked List: head -> ");
    while (temp) {
        printf("[%d|next] -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void insertAtEnd(int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    Node *temp;
    newNode->data = value;
    newNode->next = NULL;

    if (!head) {
        printf("List is empty, inserting first node. head points to new node.\n");
        head = newNode;
        return;
    }

    temp = head;
    while (temp->next) {
        printf("Moving from node with data %d to next node.\n", temp->data);
        temp = temp->next;
    }
    printf("Reached last node with data %d. Linking its next to new node %d.\n",
           temp->data, value);
    temp->next = newNode;
}

void deleteFromBeginning() {
    Node *temp;
    if (!head) {
        printf("List is empty. Cannot delete.\n");
        return;
    }
    temp = head;
    printf("Deleting node with data %d. head will move to next node.\n", temp->data);
    head = head->next;
    free(temp);
}

void freeList() {
    Node *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/* ---------------- STACK SIMULATION (ARRAY) ---------------- */

int stack[MAX_STACK];
int top = -1;

void displayStack() {
    int i;
    if (top == -1) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack (top at right): ");
    for (i = 0; i <= top; i++)
        printf("%d ", stack[i]);
    printf("<- top\n");
}

void push(int value) {
    if (top == MAX_STACK - 1) {
        printf("Stack overflow. Cannot push.\n");
        return;
    }
    top++;
    printf("Incrementing top to %d and inserting %d at stack[%d].\n",
           top, value, top);
    stack[top] = value;
    displayStack();
}

void pop() {
    if (top == -1) {
        printf("Stack underflow. Cannot pop.\n");
        return;
    }
    printf("Popping element %d from stack[%d] then decrementing top.\n",
           stack[top], top);
    top--;
    displayStack();
}

/* ---------------- QUEUE SIMULATION (CIRCULAR ARRAY) ---------------- */

int queue[MAX_QUEUE];
int front = 0, rear = -1, count = 0;

void displayQueue() {
    int i, idx;
    if (count == 0) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue (front to rear): ");
    idx = front;
    for (i = 0; i < count; i++) {
        printf("%d ", queue[idx]);
        idx = (idx + 1) % MAX_QUEUE;
    }
    printf("\nfront index = %d, rear index = %d, count = %d\n",
           front, rear, count);
}

void enqueue(int value) {
    if (count == MAX_QUEUE) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    rear = (rear + 1) % MAX_QUEUE;
    printf("Moving rear to index %d and inserting %d.\n", rear, value);
    queue[rear] = value;
    count++;
    displayQueue();
}

void dequeue() {
    if (count == 0) {
        printf("Queue is empty. Cannot dequeue.\n");
        return;
    }
    printf("Removing element %d from front index %d and moving front forward.\n",
           queue[front], front);
    front = (front + 1) % MAX_QUEUE;
    count--;
    displayQueue();
}

/* ---------------- RECURSION SIMULATION (FACTORIAL) ---------------- */

int factorialTrace(int n, int depth) {
    int i;
    for (i = 0; i < depth; i++) printf("  ");
    printf("factorial(%d) called.\n", n);

    if (n == 0 || n == 1) {
        for (i = 0; i < depth; i++) printf("  ");
        printf("Base case reached, returning 1.\n");
        return 1;
    }

    int result = n * factorialTrace(n - 1, depth + 1);

    for (i = 0; i < depth; i++) printf("  ");
    printf("Returning %d * factorial(%d) = %d.\n", n, n - 1, result);
    return result;
}

/* ---------------- MENUS ---------------- */

void arrayMenu() {
    int choice, pos, value;
    do {
        printf("\n--- ARRAY SIMULATION ---\n");
        printf("1. Insert\n2. Delete\n3. Display\n0. Back to main menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter position (0 to %d) and value: ", arrSize);
            scanf("%d%d", &pos, &value);
            insertArray(pos, value);
            break;
        case 2:
            printf("Enter position (0 to %d): ", arrSize - 1);
            scanf("%d", &pos);
            deleteArray(pos);
            break;
        case 3:
            displayArray();
            break;
        case 0:
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

void listMenu() {
    int choice, value;
    do {
        printf("\n--- LINKED LIST SIMULATION ---\n");
        printf("1. Insert at end\n2. Delete from beginning\n3. Display list\n0. Back to main menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            insertAtEnd(value);
            break;
        case 2:
            deleteFromBeginning();
            break;
        case 3:
            displayList();
            break;
        case 0:
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

void stackMenu() {
    int choice, value;
    do {
        printf("\n--- STACK SIMULATION ---\n");
        printf("1. Push\n2. Pop\n3. Display stack\n0. Back to main menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter value to push: ");
            scanf("%d", &value);
            push(value);
            break;
        case 2:
            pop();
            break;
        case 3:
            displayStack();
            break;
        case 0:
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

void queueMenu() {
    int choice, value;
    do {
        printf("\n--- QUEUE SIMULATION ---\n");
        printf("1. Enqueue\n2. Dequeue\n3. Display queue\n0. Back to main menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter value to enqueue: ");
            scanf("%d", &value);
            enqueue(value);
            break;
        case 2:
            dequeue();
            break;
        case 3:
            displayQueue();
            break;
        case 0:
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

void recursionMenu() {
    int n, result;
    printf("\n--- RECURSION SIMULATION (FACTORIAL) ---\n");
    printf("Enter n (0-10): ");
    scanf("%d", &n);
    if (n < 0 || n > 10) {
        printf("n out of range.\n");
        return;
    }
    result = factorialTrace(n, 0);
    printf("\nFactorial of %d = %d\n", n, result);
}

int main() {
    int choice;
    do {
        printf("\n============================\n");
        printf(" DATA STRUCTURE SIMULATION\n");
        printf("============================\n");
        printf("1. Array simulation\n");
        printf("2. Linked list simulation\n");
        printf("3. Stack simulation\n");
        printf("4. Queue simulation\n");
        printf("5. Recursion simulation\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
        case 1: arrayMenu();   break;
        case 2: listMenu();    break;
        case 3: stackMenu();   break;
        case 4: queueMenu();   break;
        case 5: recursionMenu(); break;
        case 0:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    freeList();   // clean linked list memory
    return 0;
}
