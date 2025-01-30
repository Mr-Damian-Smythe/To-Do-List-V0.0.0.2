#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 100
#define MAX_DESCRIPTION 100
#define FILENAME "todo_list.txt"

typedef struct {
    char description[MAX_DESCRIPTION];
    char due_date[11]; // YYYY-MM-DD
    char due_time[6];  // HH:MM
} TodoEntry;

TodoEntry todo_list[MAX_ENTRIES];
int entry_count = 0;

void load_entries() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) return;

    while (fscanf(file, "%[^|]|%[^|]|%[^\n]\n", todo_list[entry_count].description, 
                  todo_list[entry_count].due_date, todo_list[entry_count].due_time) != EOF) {
        entry_count++;
    }

    fclose(file);
}

void save_entries() {
    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < entry_count; i++) {
        fprintf(file, "%s|%s|%s\n", todo_list[i].description, todo_list[i].due_date, todo_list[i].due_time);
    }

    fclose(file);
}

void add_entry() {
    if (entry_count >= MAX_ENTRIES) {
        printf("To-do list is full.\n");
        return;
    }

    printf("Enter description: ");
    scanf(" %[^\n]", todo_list[entry_count].description);
    printf("Enter due date (YYYY-MM-DD): ");
    scanf("%s", todo_list[entry_count].due_date);
    printf("Enter due time (HH:MM): ");
    scanf("%s", todo_list[entry_count].due_time);

    entry_count++;
    save_entries();
    printf("Entry added successfully.\n");
}

void list_entries() {
    if (entry_count == 0) {
        printf("No entries found.\n");
        return;
    }

    for (int i = 0; i < entry_count; i++) {
        printf("%d. Description: %s | Due: %s %s\n", i + 1, todo_list[i].description, 
               todo_list[i].due_date, todo_list[i].due_time);
    }
}

void modify_entry() {
    int index;
    list_entries();
    printf("Enter the entry number to modify: ");
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= entry_count) {
        printf("Invalid entry number.\n");
        return;
    }

    printf("Enter new description: ");
    scanf(" %[^\n]", todo_list[index].description);
    printf("Enter new due date (YYYY-MM-DD): ");
    scanf("%s", todo_list[index].due_date);
    printf("Enter new due time (HH:MM): ");
    scanf("%s", todo_list[index].due_time);

    save_entries();
    printf("Entry modified successfully.\n");
}

void remove_entry() {
    int index;
    list_entries();
    printf("Enter the entry number to remove: ");
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= entry_count) {
        printf("Invalid entry number.\n");
        return;
    }

    for (int i = index; i < entry_count - 1; i++) {
        todo_list[i] = todo_list[i + 1];
    }

    entry_count--;
    save_entries();
    printf("Entry removed successfully.\n");
}

int main() {
    int choice;
    load_entries();

    while (1) {
        printf("\nTo-Do List Manager\n");
        printf("1. Add Entry\n");
        printf("2. List Entries\n");
        printf("3. Modify Entry\n");
        printf("4. Remove Entry\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_entry();
                break;
            case 2:
                list_entries();
                break;
            case 3:
                modify_entry();
                break;
            case 4:
                remove_entry();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
