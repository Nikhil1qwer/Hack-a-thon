#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define CLEAR "\x1B[0m"

typedef struct vehicle {
    char* Id;
    char Route;
    int Speed;
} Vehicle;

Vehicle** list = NULL;

int VehicleCount;
int RutF[26], RutA[26];


void PromptQuery() {
    list[VehicleCount] = (Vehicle *)malloc(sizeof(Vehicle));
    list[VehicleCount]->Id = (char *) malloc(sizeof(char) * 7);

    printf("\nEnter Vehicle ID: ");
    char *id = (char *)malloc(sizeof(char) * 3);
    scanf(" %s", id);
    strcpy(list[VehicleCount]->Id, "AP ");
    strcat(list[VehicleCount]->Id, id);

    printf("Enter Vehicle Route: ");
    scanf(" %c", &list[VehicleCount]->Route);
    RutF[list[VehicleCount]->Route - 'A']++;

    printf("Enter Vehicle Speed: ");
    scanf("%d", &list[VehicleCount]->Speed);

    RutA[list[VehicleCount]->Route - 'A'] +=  list[VehicleCount]->Speed;
    
    VehicleCount++;
}

void RegisterVehicle() {
    list = (Vehicle **)realloc(list, (VehicleCount + 1) * sizeof(Vehicle *));
    PromptQuery();
}

int cmp(const void* a, const void* b) {
    if(RutF[list[*(int*)a]->Route - 'A'] == RutF[list[*(int*)b]->Route - 'A']) {
        if(list[*(int*)a]->Route != list[*(int*)b]->Route) {
            return list[*(int*)a]->Route - list[*(int*)b]->Route;
        }
        return list[*(int*)b]->Speed - list[*(int*)a]->Speed;
    }
    return RutF[list[*(int*)b]->Route - 'A'] - RutF[list[*(int*)a]->Route - 'A'];
}

void OptimizeTrafficFlow(bool a) {
    int FlowControl[VehicleCount];
    for(int i = 0; i < VehicleCount; i++) {
        FlowControl[i] = i;
    }
    qsort(FlowControl, VehicleCount, sizeof(int), cmp);
    if(a) {
        for(int i = 0; i < VehicleCount; i++) {
            int I = FlowControl[i];
            printf("Vehicle Id: %s\t", list[I]->Id);
            printf("Route: %c\t", list[I]->Route);
            printf("Speed: %d\n", list[I]->Speed);
        }
    }
    if(!a) {
        char c;
        printf("Enter Intersection to Optimize: ");
        scanf(" %c", &c);
        if(RutF[c - 'A']) {
            printf(GREEN"Optimized at Intersection %c\n" CLEAR, c);
        } else {
            printf(RED"Intersection doesn't Exist\n"CLEAR);
        }
    }
}

void RealTimeTraffic() {
    for(int i = 0; i < 26; i++) {
        if(RutF[i]) {
            printf("Route %c: ", i + 'A');
            if(RutF[i] <= 3) {
                printf("Light ");
            } else if(RutF[i] <= 5) {
                printf("Moderate ");
            } else {
                printf("Heavy ");
            }
            printf(", Average Speed: %d\n", RutA[i] / RutF[i]);
        }
    }
}

void DisplayTraffic() {
    for(int i = 0; i < VehicleCount; i++) {
        printf("\nId: %s\t", list[i]->Id);
        printf("Route: %c\t", list[i]->Route);
        printf("Speed: %d\n", list[i]->Speed);
    }
}

void ThrowError() {
    printf(RED"\nError 402 Command Not Found\n"CLEAR);
}


void Display() {
    int choice;
    printf("1. Display Data\n");
    printf("2. Optimized Data\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    if(choice == 1) {
        DisplayTraffic();
    } else if(choice == 2) {
        OptimizeTrafficFlow(true);
    } else {
        ThrowError();
    }
}

void ThankUser() {
    printf(GREEN"Thank you. visit again ;) \n" CLEAR);
}

void window_alert() {
    printf(GREEN"\nRegistered\n"CLEAR);
}

int main() {
    do {
        int Query;
        printf("\n");
        printf("1. Add Vehicle\n");
        printf("2. Optimize Traffic Signals\n");
        printf("3. RealTime Traffic Conditions\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Choose Event: ");
        scanf("%d", &Query);

        switch(Query) {
            case 1:
                    RegisterVehicle();
                    window_alert();
                    break;
            case 2:
                    OptimizeTrafficFlow(false);
                    break;
            case 3:
                    RealTimeTraffic();
                    break;
            case 4:
                    Display();
                    break;
            case 5:
                    ThankUser();
                    exit(0);
            default:
                    ThrowError();
        }

    } while(true);

    return 0;
}

