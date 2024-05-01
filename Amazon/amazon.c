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

int UserId;
bool Exit = false;
bool SignInUserList = true;
int NewId = 100;
int NewItemId = 10005;

Item **Store = NULL;
Customer **UserList = NULL;
Employee **AdminList = NULL;



void UserCookies(int id, const char *name, const char *password);
void initializeEmployeeUserList();
void initializeStore();
bool LogEmployee();
void AdminMenuInterface();
void UserMenuInterface();
void RegisterUser();
bool LogUser();
void Enteruser();
void DisplayStock();
void BuyItems(int id);
void Billing(int id);
void DisplayCart(int id);
void AddItem();
void StockUp();
void UserData();
void LogError(int flag);
void ThankUser();
void Nouser();
void LogOutMsg();
void ThankEmployee();
void window_alert();
void ThrowError();
void LogConfirm();

int main() {
    initializeEmployeeUserList();
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

    free(UserList);
    free(AdminList);
    free(Store);

    return 0;
}

void Removal(int id) {
    char itemname[20];
    int choice;
    DisplayCart();
    printf("1. Remove Item\n");
    printf("2. Modify Item\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);
    if (choice != 1 && choice != 2) {
        ThrowError();
        return;
    }
    printf("\nEnter Item Name: ");
    getchar(); // Consume newline character left in the input buffer
    fgets(itemname, sizeof(itemname), stdin);
    itemname[strcspn(itemname, "\n")] = '\0'; // Remove newline character if present

    Cart* current = UserList[id]->cart;
    Cart* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->itemname, itemname) == 0) {
            if (choice == 1) { // Remove Item
                if (prev == NULL) { // If the item to be removed is the first node
                    UserList[id]->cart = current->next;
                } else {
                    prev->next = current->next;
                }
                free(current); // Free memory of the removed item
                printf("Item removed from the cart.\n");
            } else if (choice == 2) { // Modify Item
                int modifyQuantity;
                printf("\nEnter Quantity to Modify: ");
                scanf("%d", &modifyQuantity);
                if (modifyQuantity < 0) {
                    printf("Quantity cannot be negative.\n");
                    return;
                }
                if (modifyQuantity > Store[id]->quantity) {
                    printf("Insufficient stock.\n");
                    return;
                }
                current->Nitems = modifyQuantity;
                Store[id]->quantity += (current->Nitems - modifyQuantity); // Update stock
                printf("Item quantity modified.\n");
            }
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Item not found in the cart.\n");
}


void initializeEmployeeUserList() {
    AdminList = (Employee **)malloc(3 * sizeof(Employee *));
    for (int i = 0; i < 3; i++) {
        AdminList[i] = (Employee *)malloc(sizeof(Employee));
        AdminList[i]->name = (char *)malloc(12 * sizeof(char));
        AdminList[i]->password = (char *)malloc(12 * sizeof(char));
    }
    strcpy(AdminList[0]->name, "Nikhil");
    strcpy(AdminList[0]->password, "1234");
    strcpy(AdminList[1]->name, "Umar");
    strcpy(AdminList[1]->password, "Umar1234");
    strcpy(AdminList[2]->name, "Nagendra");
    strcpy(AdminList[2]->password, "nrokzzzz");
}

void initializeStore() {
    Store = (Item **)malloc(5 * sizeof(Item *));
    for (int i = 0; i < 5; i++) {
        Store[i] = (Item *)malloc(sizeof(Item));
        Store[i]->itemname = (char *)malloc(20 * sizeof(char));
    }

    strcpy(Store[0]->itemname, "Pencil");
    Store[0]->price = 5;
    Store[0]->quantity = 12;

    strcpy(Store[1]->itemname, "Pen");
    Store[1]->price = 10;
    Store[1]->quantity = 6;

    strcpy(Store[2]->itemname, "MacBook");
    Store[2]->price = 50000;
    Store[2]->quantity = 5;

    strcpy(Store[3]->itemname, "Keyboard");
    Store[3]->price = 500;
    Store[3]->quantity = 25;

    strcpy(Store[4]->itemname, "Mouse");
    Store[4]->price = 250;
    Store[4]->quantity = 35;
}

bool LogEmployee() {
    int id;
    printf("Enter the Employee Id: ");
    scanf("%d", &id);

    if(id == 11) {
        id = 0;
    } else if(id == 22) {
        id = 1;
    } else if(id == 44) {
        id = 2;
    }

    printf(GREEN"Employee Name: %s\n"CLEAR, AdminList[id]->name);

    char enter_password[12];
    printf("Enter the Employee Password: ");
    scanf("%s", enter_password);

    int check = strcmp(AdminList[id]->password, enter_password);

    return !check;
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
            printf("4. Display User Details\n");
            printf("5. Exit\n");
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
                    UserData();
                    break;
                case 5:
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

void RegisterUser() {
    printf("Sign Up Form: \n");
    int index = NewId - 100;

    UserList = (Customer **)realloc(UserList, index * sizeof(Customer *));
    UserList[index] = (Customer *)malloc(sizeof(Customer));
    UserList[index]->name = (char *)malloc(12 * sizeof(char));
    UserList[index]->password = (char *)malloc(12 * sizeof(char));
    UserList[index]->cart = NULL;

    printf("Enter User Name: ");
    scanf(" %[^\n]", UserList[index]->name);

    printf("Enter User Password: ");
    scanf(" %s", UserList[index]->password);

    printf("\n");
    printf(ORANGE"Generating Unique User Id...\n"CLEAR);
    printf(GREEN"Generated Successfull\n");
    printf("Your User Id is: %d\n"CLEAR, NewId);
    printf(GREEN"Cart initialized!\n"CLEAR);

    UserCookies(NewId, UserList[index]->name, UserList[index]->password);
    NewId++;
}

void UserMenuInterface() {
    do {
        int choice;
        printf(GREEN"\t\t\t %s\n"CLEAR, UserList[UserId]->name);
        printf("1. Item Menu\n");
        printf("2. Add Items to Cart\n");
        printf("3. Remove Items in Cart\n");
        printf("4. Display Cart\n");
        printf("5. Buy Items\n");
        printf("6. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                DisplayStock();
                break;
            case 2:
                BuyItems(UserId);
                break;
            case 3:
                Removal(UserId);
                break;
            case 4:
                DisplayCart(UserId);
                break;
            case 5:
                Billing(UserId);
                break;
            case 6:
                printf("\n");
                return;
            default:
                ThrowError();
        }
    } while(true);
}

bool LogUser() {
    if(NewId == 100) {
        return false;
    }
    int id;
    printf("Enter the User Id: ");
    scanf("%d", &id);
    UserId = id - 100;
    if(NewId < id) {
        SignInUserList = false;
        return false;
    }
    char pass[12];
    printf("Enter the User Password: ");
    scanf("%s", pass);

    int check = strcmp(UserList[id - 100]->password, pass);
    return check == 0;
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
                    if(NewId == 100 || SignInUserList == false) {
                        SignInUserList = true;
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

void AddItem() {
    int index = NewItemId - 10000;
    Store = (Item **)realloc(Store, (index + 1) * sizeof(Item *));
    Store[index] = (Item *)malloc(sizeof(Item));
    Store[index]->itemname = (char *)malloc(20 * sizeof(char));

    printf("\nEnter Item Name: ");
    scanf("%s", Store[index]->itemname);

    printf("Enter Item Quantity: ");
    scanf("%d", &Store[index]->quantity);

    printf("Enter Item Price: ");
    scanf("%d", &Store[index]->price);

    printf("Item Id is %d\n", NewItemId);

    printf("\n");
    NewItemId++;
}

void StockUp() {
    int id;
    printf("Enter Item Id: ");
    scanf("%d", &id);

    int add;
    printf("Enter Item Quantity: ");
    scanf("%d", &add);

    printf("\n");
    Store[id - 10000]->quantity += add;
}

void DisplayStock() {
    printf("\n");printf("\n");
    printf("\tItem Id\t\tItem Name\t\tPresent Stock\t\t\t Price\n");
    for (int i = 0; i < NewItemId - 10000; i++) {
        printf("%11d \t\t %11s \t\t %11d\t\t %11d\n", 10000 + i, Store[i]->itemname, Store[i]->quantity, Store[i]->price);
    }
    printf("\n");printf("\n");
}

void DisplayCart(int id) {
    Cart* head = UserList[id]->cart;
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
    Cart *head=UserList[id]->cart;
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
	if(UserList[id]->cart == NULL){
		UserList[id]->cart = newitem;
	} else {
		newitem->next = UserList[id]->cart;
		UserList[id]->cart = newitem;
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
		    printf("choice Your option: ");
		    scanf("%d",&choice);
		    if(choice != 1) {
			    printf(GREEN"\nThank You for Shopping\n"CLEAR);
                return;
	        }
	    }
	    i++;
	
	    int item_id;
	    printf("\nEnter Item Id: ");
	    scanf("%d", &item_id);

        int nitems;
	    printf("\nEnter No.of Item's: ");
	    scanf("%d", &nitems);

        item_id -= 10000;
	    if(item_id < NewItemId - 10000){
		    if(Store[item_id]->quantity > 0){
			    if(nitems <= Store[item_id]->quantity) {		
			        Store[item_id]->quantity -= nitems;
			        Cart* additem = (Cart*)malloc(sizeof(Cart));
			        strcpy(additem->itemname, Store[item_id]->itemname);	
			        additem->price = nitems * Store[item_id]->price;
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

void UserData(){
	if(NewId == 100) {
		printf("No Sign in's Yet!!\n");
		return;
	} else {
		printf("Details About users: \n");
		printf("SI.NO \t\t UserId \t User Name\n");
		for(int i = 0; i < NewId - 100; i++){
			printf("%d \t\t %d \t\t %s \n", i + 1 , 100 + i, UserList[i]->name);
		}
	}
}

void UserCookies(int id, const char *name, const char *password) {
    FILE *fp = fopen("UserCookies.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "ID: %d, Name: %s, Password: %s\n", id, name, password);
        fclose(fp);
    } else {
        printf("Error: Unable to open file for writing.\n");
    }
}