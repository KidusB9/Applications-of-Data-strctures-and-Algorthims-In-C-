#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

// Node structure for circular linked list
struct Node
{
    char name[20];
    Node *next;
};

// Function to create a new node
Node* getNewNode(char name[])
{
    Node *newNode = new Node;
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node at the end of the list
void insertEnd(Node **head, char name[])
{
    // If the list is empty, create a new node and make it the head
    if (*head == NULL)
    {
        *head = getNewNode(name);
        (*head)->next = *head;
        return;
    }

    // Find the last node in the list
    Node *curr = *head;
    while (curr->next != *head)
        curr = curr->next;

    // Create a new node and insert it at the end of the list
    Node *newNode = getNewNode(name);
    curr->next = newNode;
    newNode->next = *head;
}

// Function to switch to the next application/program in the list
void switchNext(Node **head)
{
    // If the list is empty, there is nothing to switch to
    if (*head == NULL)
        return;

    // Switch to the next application/program in the list
    *head = (*head)->next;
}

// Function to switch to the previous application/program in the list
void switchPrev(Node **head)
{
    // If the list is empty, there is nothing to switch to
    if (*head == NULL)
        return;

    // Find the last node in the list
    Node *curr = *head;
    while (curr->next != *head)
        curr = curr->next;

    // Switch to the previous application/program in the list
    *head = curr;
}

// Function to display the current application/program
void displayCurrent(Node *head)
{
    // If the list is empty, there is nothing to display
    if (head == NULL)
        return;

    // Display the current application/program
    cout << "Current: " << head->name << endl;
}

// Function to display the list of applications/programs
void displayList(Node *head)
{
    // If the list is empty, there is nothing to display
    if (head == NULL)
        return;

    // Display the list of applications/programs
    cout << "Applications/Programs: ";
    Node *curr = head;
    do
    {
        cout << curr->name << " ";
        curr = curr->next;
    } while (curr != head);
    cout << endl;
}


int main()
{
    Node *head = NULL;

    // Insert some applications/programs into the list
    insertEnd(&head, "App 1");
    insertEnd(&head, "App 2");
    insertEnd(&head, "App 3");
    insertEnd(&head, "App 4");

    // Display the current application/program and the list of applications/programs
    displayCurrent(head);
    displayList(head);

    // Switch to the next application/program
    switchNext(&head);

    // Display the current application/program and the list of applications/programs
    displayCurrent(head);
    displayList(head);

    // Switch to the previous application/program
    switchPrev(&head);

    // Display the current application/program and the list of applications/programs
    displayCurrent(head);
    displayList(head);

    return 0;
}
