#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define ORANGE "\x1B[33m"
#define CLEAR "\x1B[0m"

typedef struct {
    char *itemname;
    int quantity;
    int price;
} Item;

typedef struct Cart {
    char itemname[20];
    int Nitems;
    int price;
    struct Cart* next;
} Cart;

typedef struct {
    char *name;
    char *password;
} Employee;

typedef struct {
    int id;
    int cart_size;
    char *name;
    char *password;
    Cart *cart;
} Customer;

int userId;
bool Exit = false;
bool SignInList = true;
int newid = 100;
int newitemid = 10005;

Item **store = NULL;
Customer **list = NULL;
Employee **Mlist = NULL;

void AdminMenuInterface();
void Enteruser();
void LogError();

void ThankUser() {
    printf("\n");
    printf(GREEN"Thank you. Visit again ;) \n" CLEAR);
    printf("\n");
}

void Nouser() {
    printf("\n");
    printf(RED"Please SignUp First\n"CLEAR);
    printf("\n");
}

void LogOutMsg() {
    printf("\n");
    printf(GREEN"Exiting Succesfull\n"CLEAR);
    printf("\n");
}

void ThankEmployee() {
    printf("\n");
    printf(GREEN"Changes Done.\n" CLEAR);
    printf("\n");
}

void window_alert() {
    printf(GREEN"\nRegistered\n"CLEAR);
}

void ThrowError() {
    printf(RED"\nError 402 Command Not Found\n"CLEAR);
    printf("\n");
}

void LogConfirm() {
    printf("\n");
    printf(GREEN"Login Successful!\n"CLEAR);
    printf("\n");
}

void initializeStore() {
    store = (Item **)malloc(5 * sizeof(Item *));
    for (int i = 0; i < 5; i++) {
        store[i] = (Item *)malloc(sizeof(Item));
        store[i]->itemname = (char *)malloc(20 * sizeof(char));
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
        Mlist[i]->name = (char *)malloc(12 * sizeof(char));
        Mlist[i]->password = (char *)malloc(12 * sizeof(char));
    }
    strcpy(Mlist[0]->name, "Nikhil");
    strcpy(Mlist[0]->password, "1234");
    strcpy(Mlist[1]->name, "Umar");
    strcpy(Mlist[1]->password, "Umar1234");
    strcpy(Mlist[2]->name, "Nagendra");
    strcpy(Mlist[2]->password, "nrokzzzz");
}

void AddItem() {
    int index = newitemid - 10000;
    store = (Item **)realloc(store, (index + 1) * sizeof(Item *));
    store[index] = (Item *)malloc(sizeof(Item));
    store[index]->itemname = (char *)malloc(20 * sizeof(char));

    printf("\nEnter Item Name: ");
    scanf("%s", store[index]->itemname);

    printf("Enter Item Quantity: ");
    scanf("%d", &store[index]->quantity);

    printf("Enter Item Price: ");
    scanf("%d", &store[index]->price);

    printf("Item Id is %d\n", newitemid);

    printf("\n");
    newitemid++;
}

void StockUp() {
    int id;
    printf("Enter Item Id: ");
    scanf("%d", &id);

    int add;
    printf("Enter Item Quantity: ");
    scanf("%d", &add);

    printf("\n");
    store[id - 10000]->quantity += add;
}

void DisplayStock() {
    printf("\n");printf("\n");
    printf("\tItem Id\t\tItem Name\t\tPresent Stock\t\t\t Price\n");
    for (int i = 0; i < newitemid - 10000; i++) {
        printf("%11d \t\t %11s \t\t %11d\t\t %11d\n", 10000 + i, store[i]->itemname, store[i]->quantity, store[i]->price);
    }
}

void DisplayCart(int id) {
    Cart* head = list[id]->cart;
    if(head == NULL) {
        printf(RED"Cart is Empty!\n"CLEAR);
        return;
    }
    printf("\n"); printf("\n");
    printf("Item \t No.of Items \t Price \n");
    while(head != NULL){
        printf("%s \t ", head->itemname);
        printf("%d \t\t",head->Nitems);
        printf("%d \n",head->price);
        head = head->next;
    }
}

void Billing(int id){
    printf("\n\n");
    Cart *head=list[id]->cart;
    int total = 0;
    printf("\n");
    printf("\n");
    printf("Item \t No. of Items \t Price \n");
    while(head != NULL){
        total += head->price;
        printf("%s \t ", head->itemname);
        printf("%d \t\t",head->Nitems);
        printf("%d \n",head->price);
        head = head->next;
    } 
    printf("Total Bill:\t\t %11d", total);
    printf("\n\n");
}

void insert(Cart* newitem,int id){
	if(list[id]->cart == NULL){
		list[id]->cart = newitem;
	} else {
		newitem->next = list[id]->cart;
		list[id]->cart = newitem;
	}
}

void BuyItems(int id){
	int i = 0;
    printf("\n");
    DisplayStock();
    printf("\n");
	do{
	    if(i != 0) {
            int choice;
            printf("\n");
		    printf("1. Continue Shopping\n");
		    printf("2. Stop the Shopping\n");
            printf("\n");
		    printf("Choose Your option:");
		    scanf("%d",&choice);
		    if(choice != 1) {
			    printf(GREEN"\nThank You for Shopping\n"CLEAR);
                return;
	        }
	    }
	    i++;
	
	    int item_id;
	    printf("\nEnter item Id: ");
	    scanf("%d", &item_id);

        int nitems;
	    printf("\nEnter No.of items: ");
	    scanf("%d", &nitems);

        item_id -= 10000;
	    if(item_id < newitemid - 10000){
		    if(store[item_id]->quantity > 0){
			    if(nitems <= store[item_id]->quantity) {		
			        store[item_id]->quantity -= nitems;
			        Cart* additem = (Cart*)malloc(sizeof(Cart));
			        strcpy(additem->itemname, store[item_id]->itemname);	
			        additem->price = nitems * store[item_id]->price;
			        additem->Nitems = nitems;
			        additem->next = NULL;
			        insert(additem, id);
		        } else {
                    printf(RED"\nOut of Stock\n"CLEAR);
                }
	        } else {
                printf(RED"\nStock is Not Availabile\n"CLEAR);
            }
	    } else {
            printf(RED"\nItem is Not Availabile\n"CLEAR);
        }
	} while(true);
}

void RegisterUser() {
    printf("Sign Up Form: \n");
    int index = newid - 100;

    list = (Customer **)realloc(list, index * sizeof(Customer *));
    list[index] = (Customer *)malloc(sizeof(Customer));
    list[index]->name = (char *)malloc(12 * sizeof(char));
    list[index]->password = (char *)malloc(12 * sizeof(char));

    printf("Enter User Name: ");
    scanf(" %[^\n]", list[index]->name);

    printf("Enter User Password: ");
    scanf(" %s", list[index]->password);

    printf("\n");
    printf(ORANGE"Generating Unique User Id...\n"CLEAR);
    printf(GREEN"Generated Successfull\n");
    printf("Your User Id is: %d\n"CLEAR, newid);

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
    if(newid == 100) {
        return false;
    }
    int id;
    printf("Enter the User Id: ");
    scanf("%d", &id);
    userId = id - 100;
    if(newid < id) {
        SignInList = false;
        return false;
    }
    char pass[12];
    printf("Enter the User Password: ");
    scanf("%s", pass);

    int check = strcmp(list[id - 100]->password, pass);
    list[userId]->cart = NULL;
    return check == 0;
}


void UserMenuInterface() {
    do {
        int choice;
        printf("1. Item Menu\n");
        printf("2. Add Items to Cart\n");
        printf("3. Display Cart\n");
        printf("4. Buy Items\n");
        printf("5. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                DisplayStock();
                break;
            case 2:
                BuyItems(userId);
                break;
            case 3:
                DisplayCart(userId);
                break;
            case 4:
                Billing(userId);
                break;
            case 5:
                return;
            default:
                ThrowError();
        }
    } while(true);
}

void LogError(int flag) {
    printf(RED"\nWrong Password\n");

    int choice;
    printf("1. Try Again\n"CLEAR);
    printf(GREEN"2. Exit\n"CLEAR);

    printf("\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        if(flag) {
            Enteruser();
        } else {
            AdminMenuInterface();
        }
    } else {
        return;
    }
}

void AdminMenuInterface() {
    if (LogEmployee()) {
        LogConfirm();
        int flag = 0;
        do {
            int choice;
            printf("1. Stock Items\n");
            printf("2. Restock Items\n");
            printf("3. Display Stock\n");
            printf("4. Exit\n");
            printf("Enter Your Choice: ");
            scanf("%d", &choice);

            printf("\n");
            switch (choice) {
                case 1:
                    AddItem();
                    ThankEmployee();
                    break;
                case 2:
                    StockUp();
                    ThankEmployee();
                    break;
                case 3:
                    DisplayStock();
                    break;
                case 4:
                    flag = 1;
                    break;
                default:
                    ThrowError();
            }
        } while (!flag);
    } else {
        LogError(0);
    }
}

void Enteruser() {
    do {
        int choice;
        printf("1. Sign Up.\n");
        printf("2. Log In\n");
        printf("3. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        printf("\n");
        switch(choice) {
            case 1:
                RegisterUser();
                window_alert();
                break;
            case 2:
                if (LogUser()) {
                    LogConfirm();
                    UserMenuInterface();
                } else {
                    if(newid == 100 || SignInList == false) {
                        SignInList = true;
                        Nouser();
                    } else {
                        LogError(1);
                    }
                }
                break;
            case 3:
                return;
            default:
                ThrowError();
        }
    } while(true);
}

int main() {
    initializeEmployeeList();
    initializeStore();
    printf(GREEN"\n\n\n\t\t\t\tTecH Store\n\n"CLEAR);
    do {
        int Query;
        printf("\n");
        printf("1. User Interface\n");
        printf("2. Admin Interface\n");
        printf("3. Exit\n");
        printf("Choose Event: ");
        scanf("%d", &Query);

        printf("\n");
        switch (Query) {
            case 1:
                Enteruser();
                LogOutMsg();
                break;
            case 2:
                AdminMenuInterface();
                LogOutMsg();
                break;
            case 3:
                ThankUser();
                exit(0);
            default:
                ThrowError();
        }

    } while (true);

    free(list);
    free(Mlist);
    free(store);

    return 0;
}