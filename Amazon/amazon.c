#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define CLEAR "\x1B[0m"

typedef struct {
    char *itemname;
    int quantity;
    int price;
} Item;

typedef struct {
    char *name;
    char *password;
} Employee;

typedef struct {
    char *name;
    int id;
    char *password;
    int cart_size;
    Item *cart;
} Customer;

bool Exit = false;
int newid = 100;
int newitemid = 10005;

Item **store = NULL;
Customer **list = NULL;
Employee **Mlist = NULL;

void initializeStore() {
    store = (Item **)malloc(5 * sizeof(Item *));
    for (int i = 0; i < 5; i++) {
        store[i] = (Item *)malloc(sizeof(Item));
        store[i]->itemname = (char *)malloc(20 * sizeof(char)); // Allocate memory for itemname
    }

    strcpy(store[0]->itemname, "Pencil");
    store[0]->price = 5;
    store[0]->quantity = 12;

    strcpy(store[1]->itemname, "Pen");
    store[1]->price = 10;
    store[1]->quantity = 6;

    strcpy(store[2]->itemname, "MacBook");
    store[2]->price = 50000;
    store[2]->quantity = 5;

    strcpy(store[3]->itemname, "Keyboard");
    store[3]->price = 500;
    store[3]->quantity = 25;

    strcpy(store[4]->itemname, "Mouse");
    store[4]->price = 250;
    store[4]->quantity = 35;
}

void initializeEmployeeList() {
    Mlist = (Employee **)malloc(3 * sizeof(Employee *));
    for (int i = 0; i < 3; i++) {
        Mlist[i] = (Employee *)malloc(sizeof(Employee));
        Mlist[i]->name = (char *)malloc(12 * sizeof(char)); // Allocate memory for name
        Mlist[i]->password = (char *)malloc(12 * sizeof(char)); // Allocate memory for password
    }
    strcpy(Mlist[0]->name, "Nikhil");
    strcpy(Mlist[0]->password, "1234");
    strcpy(Mlist[1]->name, "Umar");
    strcpy(Mlist[1]->password, "Umar1234");
    strcpy(Mlist[2]->name, "Nagendra");
    strcpy(Mlist[2]->password, "nrokzzzz");
}

void ThankUser() {
    printf(GREEN"Thank you. Visit again ;) \n" CLEAR);
}

void ThankEmployee() {
    printf(GREEN"Changes Done.\n" CLEAR);
}

void window_alert() {
    printf(GREEN"\nRegistered\n"CLEAR);
}

void ThrowError() {
    printf(RED"\nError 402 Command Not Found\n"CLEAR);
}

void LogConfirm() {
    printf(GREEN"Login Successful!\n"CLEAR);
}

void AddItem() {
    int index = newitemid - 10005;
    store = (Item **)realloc(store, (index + 1) * sizeof(Item *));
    store[index] = (Item *)malloc(sizeof(Item));
    store[index]->itemname = (char *)malloc(20 * sizeof(char)); // Allocate memory for itemname

    printf("Enter Item Name: ");
    scanf("%s", store[index]->itemname);

    printf("Enter Item Quantity: ");
    scanf("%d", &store[index]->quantity);

    printf("Enter Item Price: ");
    scanf("%d", &store[index]->price);

    printf("Item Id is %d\n", newitemid);
    newitemid++;
}

void StockUp() {
    int id;
    printf("Enter Item Id: ");
    scanf("%d", &id);

    int add;
    printf("Enter Item Quantity: ");
    scanf("%d", &add);

    store[id - 10005]->quantity += add;
}

void DisplayStock() {
    printf("\tItem Id\t\tItem Name\t\tPresent Stock\n");
    for (int i = 0; i < newitemid - 10000; i++) {
        printf("%11d \t\t %11s \t\t %11d\n", 10000 + i, store[i]->itemname, store[i]->quantity);
    }
}

void RegisterUser() {
    int index = newid - 100;
    list = (Customer **)realloc(list, index * sizeof(Customer *));
    list[index] = (Customer *)malloc(sizeof(Customer));
    list[index]->name = (char *)malloc(12 * sizeof(char)); // Allocate memory for name
    list[index]->password = (char *)malloc(12 * sizeof(char)); // Allocate memory for password
    printf("Enter your Name: ");
    scanf("%s", list[index]->name);

    printf("Enter your Password: ");
    scanf("%s", list[index]->password);

    printf(GREEN"\nYour Registration Id is: %d\n"CLEAR, newid);
    newid++;
}

bool LogEmployee() {
    int id;
    printf("Enter the Employee Id: ");
    scanf("%d", &id);

    printf(GREEN"Employee Name: %s\n"CLEAR, Mlist[id]->name);

    char enter_password[12];
    printf("Enter the Employee Password: ");
    scanf("%s", enter_password);

    int check = strcmp(Mlist[id]->password, enter_password);

    return !check;
}

bool LogUser() {
    int id;
    printf("Enter the User Id: ");
    scanf("%d", &id);

    char pass[12];
    printf("Enter the User Password: ");
    scanf("%s", pass);

    int check = strcmp(list[id - 100]->password, pass);

    return check == 0;
}

void LogInterface();
void LogError();

void LogInterface() {
    int choice;
    printf("1. User Login\n");
    printf("2. Employee Login\n");
    printf("3. Exit\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        if (LogUser()) {
            LogConfirm();
            // BuyInStore();
        } else {
            LogError();
        }
    } else if (choice == 2) {
        if (LogEmployee()) {
            LogConfirm();
            int flag = 0;
            do {
                printf("1. Stock Items\n");
                printf("2. Restock Items\n");
                printf("3. Display Stock\n");
                printf("4. Exit\n");
                printf("Enter Your Choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        AddItem();
                        break;
                    case 2:
                        StockUp();
                        break;
                    case 3:
                        DisplayStock();
                        break;
                    case 4:
                        flag = 1;
                        ThankEmployee();
                        break;
                    default:
                        ThrowError();
                }
            } while (!flag);
        } else {
            LogError();
        }
    } else if (choice == 3) {
        Exit = true;
    } else {
        ThrowError();
    }
}

void LogError() {
    printf(RED"\nWrong Password\n"CLEAR);

    int choice;
    printf(RED"1. Try Again\n"CLEAR);
    printf("2. Exit\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        LogInterface();
    } else {
        Exit = true;
    }
}

int main() {
    initializeEmployeeList();
    initializeStore();
    do {
        int Query;
        printf("\n");
        printf("1. Sign up\n");
        printf("2. Log in\n");
        printf("3. Exit\n");
        printf("Choose Event: ");
        scanf("%d", &Query);

        switch (Query) {
            case 1:
                RegisterUser();
                window_alert();
                break;
            case 2:
                Exit = false;
                do {
                    LogInterface();
                } while (!Exit);
                break;
            case 3:
                ThankUser();
                exit(0);
            default:
                ThrowError();
        }

    } while (true);

    return 0;
}
