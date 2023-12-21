// assignment.c
#include <stdio.h>
#include <string.h>
#include <strings.h>
#define MAX 5

typedef struct
{
    int roomID;
    int status;
    char customerName[20];
} Room;

int occupancyCheck(Room room[]);
void listOccupiedRooms(Room room[]);
void assignRoom(Room room[]);
void removeRoom(Room room[]);
void findCustomer(Room room[]);

int main(void)
{
    int choice;
    Room room[MAX]; // room[0] has roomID 1; array of 5 elements initialised
    printf("NTU HOTEL ROOM RESERVATION PROGRAM:\n");
    printf("1: listOccupiedRooms()\n");
    printf("2: assignRoom()\n");
    printf("3: removeRoom()\n");
    printf("4: findCustomer()\n");
    printf("5: quit\n");
    do
    {
        printf("Enter your choice:\n");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1: // listOccupiedRooms()
                listOccupiedRooms(room);
                break;
            case 2: // assignRoom()
                assignRoom(room);
                break;
            case 3: // removeRoom()
                removeRoom(room);
                break;
            case 4: // findCustomer()
                findCustomer(room);
                break;
        }
    }
    while (choice != 5);
    return 0;
}

// Returns number of occupied rooms in hotel (out of 5)
int occupancyCheck(Room room[])
{
    int x = 0;
    // Iterates through struct array and checks whether occupied or vacant
    for (int i = 0; i < MAX; i++)
    {
        if (room[i].status == 1)
        {
            x++;
        }
    }
    return x;
}

void listOccupiedRooms(Room room[])
{
    printf("listOccupiedRooms():\n");
    int occupancy = occupancyCheck(room);
    // Return to main() if hotel is empty
    if (occupancy == 0)
    {
        printf("The hotel is empty\n");
        return;
    }
    else
    {
        // Iterates through struct array and prints room info if occupied
        for (int i = 0; i < MAX; i++)
        {
            if (room[i].status == 1)
            {
                printf("roomID: %d\n", room[i].roomID);
                printf("customer name: %s\n", room[i].customerName);
            }
        }
    }
}

void assignRoom(Room room[])
{
    printf("assignRoom():\n");
    int inputRoomID, index;
    char inputName[20], *ptr;
    int occupancy = occupancyCheck(room);
    // Return to main() if hotel is fully occupied
    if (occupancy == MAX)
    {
        printf("The hotel is full\n");
        return;
    }
    // To check user input
    while (1)
    {
        printf("Enter a roomID between 1 and 5:\n");
        scanf("%d", &inputRoomID);
        if (inputRoomID < 1 || inputRoomID > 5)
        {
            continue;
        }
        else
        {
            index = inputRoomID - 1;
            if (room[index].status == 1)
            {
                printf("Occupied! Enter another roomID\n");
                continue;
            }
            else
            {
                room[index].roomID = inputRoomID;
                break;
            }
        }
    }
    // To get customer name & update room status
    printf("Enter customer name:\n");
    scanf("\n");    // To get rid of newline char from previous input (inputRoomID)
    fgets(inputName, 20, stdin);
    if ((ptr = strchr(inputName, '\n')))
    {
        *ptr = '\0';
    }
    strcpy(room[index].customerName, inputName);
    room[index].status = 1;
    printf("The room has been assigned successfully\n");
    return;
}

void removeRoom(Room room[])
{
    printf("removeRoom():\n");
    int inputRoomID, index;
    int occupancy = occupancyCheck(room);
    // Returns to main() if hotel is empty
    if (occupancy == 0)
    {
        printf("All the rooms are empty\n");
        return;
    }
    // To check user input
    while (1)
    {
        printf("Enter a roomID between 1 and 5:\n");
        scanf("%d", &inputRoomID);
        if (inputRoomID < 1 || inputRoomID > 5)
        {
            continue;
        }
        else
        {
            index = inputRoomID - 1;
            if (room[index].status == 0)
            {
                printf("Empty! Enter another roomID for removal\n");
                continue;
            }
            else
            {
                // To remove room
                room[index].roomID = 0;
                room[index].status = 0;
                strcpy(room[index].customerName, "NONE");
                printf("Removal is successful\n");
                return;
            }
        }
    }
}

void findCustomer(Room room[])
{
    printf("findCustomer():\n");
    char inputName[20], *ptr;
    // To get target name
    printf("Enter customer name:\n");
    scanf("\n");    // To get rid of newline char from previous input (choice)
    fgets(inputName, 20, stdin);
    if ((ptr = strchr(inputName, '\n')))
    {
        *ptr = '\0';
    }
    for (int i = 0; i < MAX; i++)
    {
        // Case-insensitive comparison between input and name in database
        if (strcasecmp(room[i].customerName, inputName) == 0)
        {
            printf("The target customer name is found\n");
            printf("roomID: %d\n", room[i].roomID);
            printf("customer name: %s\n", room[i].customerName);
            return;
        }
    }

    /* Own implementation of case-insensitive string comparison
    #include <ctype.h>
    char tmp[20];   // Temporary string
    for (int i = 0; i < MAX; i++)
    {
        // To work with tmp rather than customerName in database
        strcpy(tmp, room[i].customerName);
        // To convert all uppercase letters in tmp and inputName to lowercase for comparison
        for (int j = 0; j < strlen(inputName); j++)
        {
            if (isupper(tmp[j]) == 1 || isupper(inputName[j]) == 1)
            {
                tolower(tmp[j]);
                tolower(isupper(inputName[j]));
            }
        }
        // strcmp() performs case-sensitive comparison
        if (strcmp(tmp, inputName) == 0)
        {
            printf("The target customer name is found\n");
            printf("roomID: %d\n", room[i].roomID);
            printf("customer name: %s", room[i].customerName);
            return;
        }
    }
    */

    // If target name is not found
    printf("The target customer name is not found\n");
}