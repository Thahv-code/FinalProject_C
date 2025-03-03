#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// loại bọ phần trống
#include <ctype.h>

#define MAX_BOOKS 50
#define ADMIN 50
#define CUSTOMER 50
typedef struct Book
{
    int id;
    char bookName[100];
    char author[50];
    char category[50];
    long price;
    int n;
} Book;

typedef struct Customer
{
    int id;
    char customerName[50];
    char userName[50];
    char password[50];
} Customer;

typedef struct Admin
{
    int id;
    char adminName[50];
    char userName[50];
    char password[50];
} Admin;

Admin admin[ADMIN];
Customer customer[CUSTOMER];
Book book[MAX_BOOKS];

int n = 0;
int l = 0;
int t = 0;
char FileNameBook[50] = "book.txt";
char FileNameAdmin[50] = "admin.txt";

void inputCustomer(Customer *customer, int *t);
void inputBooks(Book *book, int *n);
void displayBook(Book *book, int n);
void addBook(Book *book, int *n);
void deleteBook(Book *book, int *n);
void changebookInformation(Book *book, int n);
void searchBookByName(Book *book, int n);
void sortbookByPrice(Book *book, int n);
void saveToFile(Book *book, int n);
void readFileBook(Book *book, int *n);
void readFileAdmin(Admin *admin, int *l);
void trimNewline(char *str);
void validadmin(char *Username, char *Password, Admin *admin, int adminCount);
void mainDisplay();
void loginadmin();
void adminMenu();
void i(Book *book, int *n);
void customerMenu();

void readFileAdmin(Admin *admin, int *l)
{
    FILE *file = fopen(FileNameAdmin, "r");

    char line[256];
    int index = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (index >= ADMIN)
        {
            printf("Maximum admin.\n");
            break;
        }
        Admin temp;
        sscanf(line, "%d,%99[^,],%49[^,],%49[^,]",
               temp.id, temp.adminName, temp.userName, temp.password);
        admin[index++] = temp;
    }

    *l = index;

    fclose(file);
}
void readFileBook(Book *book, int *n)
{
    FILE *file = fopen(FileNameBook, "r");

    char line[256];
    int index = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (index >= MAX_BOOKS)
        {
            printf("Maximum book storage reached.\n");
            break;
        }

        Book temp;
        sscanf(line, "%d,%99[^,],%49[^,],%49[^,],%ld,%d",
               &temp.id, temp.bookName, temp.author, temp.category, &temp.price, &temp.n);

        book[index++] = temp;
    }

    *n = index;

    fclose(file);
}

void inputBooks(Book *book, int *n)
{
    printf("Enter number of books: ");
    scanf("%d", n);
    getchar();
    for (int i = 0; i < *n; i++)
    {
        book[i].id = i + 1;
        printf("Please insert book name: ");
        fgets(book[i].bookName, 100, stdin);
        book[i].bookName[strcspn(book[i].bookName, "\n")] = '\0';
        printf("Please insert author name: ");
        fgets(book[i].author, 50, stdin);
        book[i].author[strcspn(book[i].author, "\n")] = '\0';
        printf("Please insert category: ");
        fgets(book[i].category, 50, stdin);
        book[i].category[strcspn(book[i].category, "\n")] = '\0';
        printf("Please insert price: ");
        scanf("%ld", &book[i].price);
        getchar();
    }
}

void displayBook(Book *book, int n)
{
    printf("|=======|====================|====================|===============|===============|\n");
    printf("|   ID  |         Bookname   |        Author      |     Category  |      Price    |\n");
    printf("|=======|====================|====================|===============|===============|\n");
    for (int i = 0; i < n; i++)
    {
        printf("|   %d   |   %-16s |   %-16s |   %-11s |   %11.2f |\n", book[i].id, book[i].bookName, book[i].author, book[i].category, (double)book[i].price);
    }
    printf("|=======|====================|====================|===============|===============|\n");
    printf("\n");
}

void addBook(Book *book, int *n)
{
    book[*n].id = *n + 1;
    printf("\n=============== ADD BOOK ===============\n");
    printf("Enter book name: ");
    getchar();
    fgets(book[*n].bookName, 100, stdin);
    book[*n].bookName[strcspn(book[*n].bookName, "\n")] = '\0';
    printf("Enter author name: ");
    fgets(book[*n].author, 50, stdin);
    book[*n].author[strcspn(book[*n].author, "\n")] = '\0';
    printf("Enter category: ");
    fgets(book[*n].category, 50, stdin);
    book[*n].category[strcspn(book[*n].category, "\n")] = '\0';
    printf("Enter price: ");
    while (scanf("%ld", &book[*n].price) != 1 || book[*n].price <= 0)
    {
        printf("Invalid input. Please enter a positive number: ");
        while (getchar() != '\n')
            ;
    }
    (*n)++;

    printf("\nBook added successfully!\n");
    printf("=========================================\n");
}

void deleteBook(Book *book, int *n)
{
    int id;
    printf("Please insert book ID you want to delete: ");
    scanf("%d", &id);
    getchar();
    int found = 0;
    for (int i = 0; i < *n; i++)
    {
        if (book[i].id == id)
        {
            printf("Are you sure you want to delete this book? (Y/N): ");
            char confirmation;
            scanf("%c", &confirmation);
            getchar();
            if (confirmation == 'Y' || confirmation == 'y')
            {
                for (int j = i; j < *n - 1; j++)
                {
                    book[j] = book[j + 1];
                }
                (*n)--;
                printf("Book has been deleted.\n");
            }
            else
            {
                printf("Book has not been deleted.\n");
            }
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Book not found.\n");
    }

    printf("Press Enter to return to the main menu...\n");
    getchar();
}

void changebookInformation(Book *book, int n)
{
    int id;
    int found = 0;
    printf("Please insert book ID you want to change: ");
    scanf("%d", &id);
    getchar();
    for (int i = 0; i < n; i++)
    {
        if (book[i].id == id)
        {
            printf("Please insert book name: ");
            fgets(book[i].bookName, 100, stdin);
            book[i].bookName[strcspn(book[i].bookName, "\n")] = '\0';
            printf("Please insert author name: ");
            fgets(book[i].author, 50, stdin);
            book[i].author[strcspn(book[i].author, "\n")] = '\0';
            printf("Please insert category: ");
            fgets(book[i].category, 50, stdin);
            book[i].category[strcspn(book[i].category, "\n")] = '\0';
            printf("Please insert price: ");
            scanf("%ld", &book[i].price);
            found = 1;
            getchar();
            break;
        }
    }
    if (!found)
    {
        printf("Book not found.\n");
    }
}

void searchBookByName(Book *book, int n)
{
    char name[100];
    int found = 0;
    printf("Please insert part of the book name you want to search: ");
    getchar();
    fgets(name, 100, stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("\n        *** Search Book By Name ***   \n");
    printf("|=======|====================|====================|===============|===============|\n");
    printf("|   ID  |         Bookname   |        Author      |     Category  |      Price    |\n");
    printf("|=======|====================|====================|===============|===============|\n");
    for (int i = 0; i < n; i++)
    {
        if (strstr(book[i].bookName, name) != NULL)
        {
            printf("|   %d   |   %-16s |   %-16s |   %-11s |   %11.2f |\n", book[i].id, book[i].bookName, book[i].author, book[i].category, (double)book[i].price);
            found = 1;
        }
    }
    printf("|=======|====================|====================|===============|===============|\n");
    if (!found)
    {
        printf("\nNo books found containing \"%s\" in the name.\n", name);
    }
    printf("Press Enter to return to the main menu...");
    getchar();
}

void sortbookByPrice(Book *book, int n)
{
    Book temp;
    int choice;
    printf("Sort in ascending(1) or descending(2): ");
    scanf("%d", &choice);
    getchar();
    switch (choice)
    {
    case 1:
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (book[i].price > book[j].price)
                {
                    temp = book[i];
                    book[i] = book[j];
                    book[j] = temp;
                }
            }
        }
        printf("Books have been sorted in ascending order by price.\n");
        break;
    case 2:
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (book[i].price < book[j].price)
                {
                    temp = book[i];
                    book[i] = book[j];
                    book[j] = temp;
                }
            }
        }
        printf("Books have been sorted in descending order by price.\n");
        break;
    default:
        printf("Invalid choice. Please try again.\n");
        return;
    }

    printf("Press Enter to return to the main menu...");
    getchar();
}

void saveToFile(Book *book, int n)
{
    FILE *file = fopen(FileNameBook, "w");

    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%d,%s,%s,%s,%ld\n",
                book[i].id, book[i].bookName, book[i].author, book[i].category, book[i].price);
    }

    fclose(file);
    printf("\nBooks saved to '%s' successfully!\n", FileNameBook);
}

void inputCustomer(Customer *customer, int *t)
{
    for (int i = 0; i < *t; i++)
    {
        customer[i].id = i + 1;
        printf("Please insert your name: ");
        //quick fix :)))
        fgets(customer[i].customerName, 50, stdin);
        customer[i].customerName[strcspn(customer[i].customerName, "\n")] = '\0';
        fgets(customer[i].customerName, 50, stdin);
        customer[i].customerName[strcspn(customer[i].customerName, "\n")] = '\0';
        printf("Please enter your user name: ");
        fgets(customer[i].userName, 50, stdin);
        customer[i].userName[strcspn(customer[i].userName, "\n")] = '\0';
        printf("Please enter your password: ");
        fgets(customer[i].password, 50, stdin);
        customer[i].password[strcspn(customer[i].password, "\n")] = '\0';
        printf("\n");
    }
}

void displayUser(Customer *customer, int *n)
{
    printf("|=======|====================|====================|===============|\n");
    printf("|   ID  |         Name       |        User        |     Password  |\n");
    printf("|=======|====================|====================|===============|\n");
    for (int i = 0; i < n; i++)
    {
        printf("|   %d   |   %-16s |   %-16s |   %-11s |\n", book[i].id, customer[i].customerName, customer[i].userName, customer[i].password);
    }
    printf("|=======|====================|====================|===============|\n");
    printf("\n");
}

void adminMenu()
{
    int choice;
    while (1)
    {
        printf("\n        *** Login Admin ***   \n");
        printf("1. Login \n");
        printf("2. Return \n");
        printf("Choice your option: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            loginadmin();

        case 2:
            mainDisplay();
        default:
            printf("Invalid choice, please try again");
            break;
        }
    }
}
void loginadmin()
{
    char adminUsername[50];
    char adminPassword[50];
    printf("\n        *** Login ***   \n");
    printf("1. Please insert your username: ");
    scanf("%49s", adminUsername);
    printf("2. Please insert your password: ");
    scanf("%49s", adminPassword);
    validadmin(adminUsername, adminPassword, admin, l);
}

void trimNewline(char *str)
{
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        // loại bổ rồng thừa
        str[len - 1] = '\0';
    }
}

void validadmin(char *Username, char *Password, Admin *admin, int adminCount)
{
    for (int i = 0; i < adminCount; i++)
    {
        trimNewline(admin[i].password);
        if (strcmp(admin[i].userName, Username) == 0 && strcmp(admin[i].password, Password) == 0)
        {
            printf("Welcome, %s!\n", admin[i].adminName);
            bookMenu();
        }
    }
    printf("Invalid username or password. Please try again.\n");
    adminMenu();
}
void customerMenu()
{
    int choice;
    while (1)
    {
        printf("\n        ***Customer Menu ***   \n");
        printf("[1]. Insert customer infomation \n");
        printf("[2]. Display all customer infomation \n");
        printf("[3]. Return to main menu \n");
        printf("=================================================\n");
        printf("Choice your option: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            inputCustomer(customer, &t);
            break;
        case 2:
            displayUser(customer, t);
            break;
        case 3:
            mainDisplay();
        default:
            printf("Invalid choice, please try again");
            break;
        }
    }
}
void bookMenu()
{
    int choice;
    while (1)
    {
        printf("======================MENU=======================\n");
        printf("[1]. Insert amount of book and information \n");
        printf("[2]. Display all book infomation \n");
        printf("[3]. Add a book \n");
        printf("[4]. Delete a book \n");
        printf("[5]. Change book infomation \n");
        printf("[6]. Search book by name \n");
        printf("[7]. Sort books by price \n");
        printf("[8]. Save file and exit \n");
        printf("[9]. Return to main menu \n");
        printf("=================================================\n");
        printf("Choice your option: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            inputBooks(book, &n);
            break;
        case 2:
            displayBook(book, n);
            break;
        case 3:
            addBook(book, &n);
            break;
        case 4:
            deleteBook(book, &n);
            break;
        case 5:
            changebookInformation(book, n);
            break;
        case 6:
            searchBookByName(book, n);
            break;
        case 7:
            sortbookByPrice(book, n);
            break;
        case 8:
            saveToFile(book, n);
            return;
        case 9:
            mainDisplay();
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}
void mainDisplay()
{
    int choice;
    while (1)
    {
        printf("======================MENU=======================\n");
        printf("[1]. Admin Management \n");
        printf("[2]. Customer Management \n");
        printf("[3]. Exit \n");
        printf("=================================================\n");
        printf("Choice your option: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            adminMenu();
            break;
        case 2:
            customerMenu();
            break;
        case 3:
            return 0;
        default:
            printf("Invalid choice. Please try again. \n");
            break;
        }
    }
}

int main()
{
    readFileAdmin(admin, &l);
    readFileBook(book, &n);
    mainDisplay();
    return 0;
}
