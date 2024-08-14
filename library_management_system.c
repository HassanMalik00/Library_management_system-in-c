#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BOOKS 100
#define MAX_USERS 100

typedef struct {
    char title[100];
    char author[100];
    int isAvailable;
    char borrowedBy[100]; 
} Book;

typedef struct {
    char name[100];
    char address[200];
    char contact[12]; 
} User;

Book books[MAX_BOOKS];
int bookCount = 0;

User users[MAX_USERS];
int userCount = 0;

void displayMenu() {
    printf("\nLibrary Management System\n");
    printf("1. Add Book\n");
    printf("2. View Books\n");
    printf("3. Search Book\n");
    printf("4. Borrow Book\n");
    printf("5. Return Book\n");
    printf("6. Add User\n");
    printf("7. View Users\n");
    printf("8. Search User\n");
    printf("9. Remove User\n");
    printf("10. Exit\n");
    printf("Choose an option: ");
}

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    Book newBook;
    printf("Enter book title: ");
    scanf(" %[^\n]", newBook.title);
    printf("Enter book author: ");
    scanf(" %[^\n]", newBook.author);
    newBook.isAvailable = 1;
    strcpy(newBook.borrowedBy, "");

    books[bookCount++] = newBook;
    printf("Book added successfully.\n");
}

void viewBooks() {
	int i;
    printf("List of Books:\n");
    for ( i = 0; i < bookCount; i++) {
        printf("%d. Title: %s, Author: %s, Available: %s, Borrowed By: %s\n",
               i + 1,
               books[i].title,
               books[i].author,
               books[i].isAvailable ? "Yes" : "No",
               books[i].isAvailable ? "N/A" : books[i].borrowedBy);
    }
}

void searchBook() {
	int i;
    char searchTitle[100];
    printf("Enter book title to search: ");
    scanf(" %[^\n]", searchTitle);

    int found = 0;

    for ( i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, searchTitle)) {
            printf("Found: Title: %s, Author: %s, Available: %s, Borrowed By: %s\n",
                   books[i].title,
                   books[i].author,
                   books[i].isAvailable ? "Yes" : "No",
                   books[i].isAvailable ? "N/A" : books[i].borrowedBy);
            found = 1;
        }
    }

    if (!found) {
        printf("No book found with the given title.\n");
    }
}

void borrowBook() {
	int i;
    char borrowTitle[100];
    char userName[100];
    printf("Enter user name: ");
    scanf(" %[^\n]", userName);
    printf("Enter book title to borrow: ");
    scanf(" %[^\n]", borrowTitle);

    int found = 0;

    for ( i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, borrowTitle) && books[i].isAvailable) {
            printf("%d. %s by %s\n", i + 1, books[i].title, books[i].author);
            found++;
        }
    }

    if (found == 0) {
        printf("No available book found matching the title.\n");
        return;
    } else if (found == 1) {
        
        for ( i = 0; i < bookCount; i++) {
            if (strstr(books[i].title, borrowTitle) && books[i].isAvailable) {
                books[i].isAvailable = 0;
                strcpy(books[i].borrowedBy, userName);
                printf("%s has borrowed: %s\n", userName, books[i].title);
                return;
            }
        }
    } else {
        
        int choice;
        printf("Multiple books found. Enter the number of the book to borrow: ");
        scanf("%d", &choice);

        if (choice > 0 && choice <= bookCount && books[choice - 1].isAvailable) {
            books[choice - 1].isAvailable = 0;
            strcpy(books[choice - 1].borrowedBy, userName);
            printf("%s has borrowed: %s\n", userName, books[choice - 1].title);
        } else {
            printf("Invalid selection or book is not available.\n");
        }
    }
}


void returnBook() {
	int i;
    char returnTitle[100];
    printf("Enter book title to return: ");
    scanf(" %[^\n]", returnTitle);

    int found = 0;

    for ( i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, returnTitle) && !books[i].isAvailable) {
            printf("%d. %s by %s\n", i + 1, books[i].title, books[i].author);
            found++;
        }
    }

    if (found == 0) {
        printf("No borrowed book found matching the title.\n");
        return;
    } else if (found == 1) {
        
        for ( i = 0; i < bookCount; i++) {
            if (strstr(books[i].title, returnTitle) && !books[i].isAvailable) {
                books[i].isAvailable = 1;
                strcpy(books[i].borrowedBy, "");
                printf("You have returned: %s\n", books[i].title);
                return;
            }
        }
    } else {
    
        int choice;
        printf("Multiple books found. Enter the number of the book to return: ");
        scanf("%d", &choice);

        if (choice > 0 && choice <= bookCount && !books[choice - 1].isAvailable) {
            books[choice - 1].isAvailable = 1;
            strcpy(books[choice - 1].borrowedBy, "");
            printf("You have returned: %s\n", books[choice - 1].title);
        } else {
            printf("Invalid selection or book is not borrowed.\n");
        }
    }
}


void addUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached. Cannot add more users.\n");
        return;
    }

    User newUser;
    printf("Enter user name: ");
    scanf(" %[^\n]", newUser.name);
    printf("Enter user address: ");
    scanf(" %[^\n]", newUser.address);
    printf("Enter user contact number (up to 11 digits): ");
    scanf(" %11s", newUser.contact);

    users[userCount++] = newUser;
    printf("User added successfully.\n");
}

void viewUsers() {
	int i;
    printf("List of Users:\n");
    for ( i = 0; i < userCount; i++) {
        printf("%d. Name: %s, Address: %s, Contact: %s\n",
               i + 1,
               users[i].name,
               users[i].address,
               users[i].contact);
    }
}

void searchUser() {
	int i;
    char searchName[100];
    printf("Enter user name or contact number to search: ");
    scanf(" %[^\n]", searchName);

    int found = 0;

    for ( i = 0; i < userCount; i++) {
        if (strstr(users[i].name, searchName) || strstr(users[i].contact, searchName)) {
            printf("Found: Name: %s, Address: %s, Contact: %s\n",
                   users[i].name,
                   users[i].address,
                   users[i].contact);
            found = 1;
        }
    }

    if (!found) {
        printf("No user found with the given name or contact number.\n");
    }
}

void removeUser() {
	int i;
	int j;
    char removeName[100];
    printf("Enter user name to remove: ");
    scanf(" %[^\n]", removeName);

    int found = 0;

    for ( i = 0; i < userCount; i++) {
        if (strcmp(users[i].name, removeName) == 0) {
            for ( j = i; j < userCount - 1; j++) {
                users[j] = users[j + 1];
            }
            userCount--;
            printf("User %s removed successfully.\n", removeName);
            found = 1;
            break; 
        }
    }

    if (!found) {
        printf("No user found with the given name.\n");
    }
}

void saveLibraryData() {
    FILE *file = fopen("library_data.dat", "wb");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    
    fwrite(&bookCount, sizeof(int), 1, file);
    fwrite(books, sizeof(Book), bookCount, file);

    
    fwrite(&userCount, sizeof(int), 1, file);
    fwrite(users, sizeof(User), userCount, file);

    fclose(file);
    printf("Data saved successfully.\n");
}

void loadLibraryData() {
    FILE *file = fopen("library_data.dat", "rb");
    if (!file) {
        printf("No data file found. Starting with an empty library.\n");
        return;
    }

    
    fread(&bookCount, sizeof(int), 1, file);
    fread(books, sizeof(Book), bookCount, file);

    
    fread(&userCount, sizeof(int), 1, file);
    fread(users, sizeof(User), userCount, file);

    fclose(file);
    printf("Data loaded successfully.\n");
}

void initLibrary() {
    bookCount = 0;
    userCount = 0;
}

int main() {
    int choice;
    initLibrary();
    loadLibraryData();

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                viewBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                borrowBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
                addUser();
                break;
            case 7:
                viewUsers();
                break;
            case 8:
                searchUser();
                break;
            case 9:
                removeUser();
                break;
            case 10:
                saveLibraryData();
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

