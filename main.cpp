#include <iostream>
#include <string>

using namespace std;

// Structure to represent a task
struct Task {
    int task_id;
    string description;
    int priority;
    Task* next;  // Pointer to the next task
};

// Function to insert a new task in the task list
void insert_task(Task*& head, int tid, string description, int priority) {
    // Check if the task already exists
    Task* current = head;
    while (current != NULL) {
        if (current->task_id == tid) {
            cout << "Task already exists with ID: " << tid << endl;
            return;
        }
        current = current->next;
    }

    // Create a new task node
    Task* new_task = new Task;
    new_task->task_id = tid;
    new_task->description = description;
    new_task->priority = priority;
    new_task->next = NULL;

    // Insert the task based on priority
    if (head == NULL || head->priority < priority) {
        new_task->next = head;
        head = new_task;
    } else {
        Task* temp = head;
        while (temp->next != NULL && temp->next->priority >= priority) {
            temp = temp->next;
        }
        new_task->next = temp->next;
        temp->next = new_task;
    }
}

// Function to print all tasks
void print_tasks(Task* head) {
    cout << "--------------------------------------" << endl;
    if (head == NULL) {
        cout << "No tasks available." << endl;
    } else {
        Task* current = head;
        while (current != NULL) {
            cout << current->task_id << ": " << current->description << " - Priority: " << current->priority << endl;
            current = current->next;
        }
    }
    cout << "--------------------------------------" << endl;
}

// Function to delete the highest priority task (first task)
void delete_from_start(Task*& head) {
    if (head == NULL) {
        cout << "Task list is empty." << endl;
        return;
    }
    Task* temp = head;
    head = head->next;
    delete temp;
}

// Function to delete a task by its ID
void delete_task_by_id(Task*& head, int tid) {
    if (head == NULL) {
        cout << "Task list is empty. Nothing to delete." << endl;
        return;
    }

    if (head->task_id == tid) {
        Task* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Task* current = head;
    while (current->next != NULL && current->next->task_id != tid) {
        current = current->next;
    }

    if (current->next != NULL) {
        Task* temp = current->next;
        current->next = temp->next;
        delete temp;
    } else {
        cout << "Task with ID " << tid << " not found." << endl;
    }
}

int main() {
    Task* head = NULL;
    int choice, tid, priority;
    string description;

    do {
        cout << "\nTask Management System Menu:\n";
        cout << "1. Add a new task\n";
        cout << "2. View all tasks\n";
        cout << "3. Remove the highest priority task\n";
        cout << "4. Remove a task by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter task ID: ";
                cin >> tid;
                cout << "Enter task description: ";
                cin.ignore();
                getline(cin, description);
                cout << "Enter task priority: ";
                cin >> priority;
                insert_task(head, tid, description, priority);
                break;
            case 2:
                print_tasks(head);
                break;
            case 3:
                delete_from_start(head);
                break;
            case 4:
                cout << "Enter the task ID to delete: ";
                cin >> tid;
                delete_task_by_id(head, tid);
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 5);

    return 0;
}
