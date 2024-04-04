#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Function to create a new Membernode
Membernode *createmembernode(Member member){
    Membernode *newnode = (Membernode*)malloc(sizeof(Membernode));
    newnode->data = member;
    newnode->link = NULL;
    return newnode;
}

// Function to add a new member node to the end of the linked list
void add(Membernode **head, Member member){
    Membernode *current, *p;

    current = createmembernode(member);

    p = *head;
    if(*head == NULL){
        *head = current;
    }else{
        while(p->link != NULL){
            p = p->link;
        }
        p->link = current; 
    }
}

// Function to delete a member in the linked list by position
void deleteMember(Membernode **head, char *searchKey) {
    if (*head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    Membernode *current = *head, *prev = NULL;
    int found = 0;

    // Tìm nút cần xóa
    while (current != NULL) {
        if (strcmp(current->data.uid, searchKey) == 0) {
            // Nếu tìm thấy, in thông tin của cư dân và đánh dấu đã tìm thấy
            printf("Resident found:\n");
            printf("UID: %s, Room Number: %s, Name: %s, License Plate: %s\n", current->data.uid, current->data.roomNumber, current->data.name, current->data.licensePlate);
            found = 1;
            break;
        }
        prev = current;
        current = current->link;
    }

    // Nếu không tìm thấy, thông báo và kết thúc hàm
    if (!found) {
        printf("Resident with UID/License Plate %s not found.\n", searchKey);
        return;
    }

    // Xóa nút được tìm thấy
    if (prev != NULL) {
        // Nếu nút không phải là nút đầu tiên
        prev->link = current->link;
    } else {
        // Nếu nút là nút đầu tiên, cập nhật con trỏ head
        *head = current->link;
    }

    // Giải phóng bộ nhớ của nút bị xóa
    free(current);
}

// Function to find a member in the linked list based on UID or License Plate
void findmember(Membernode *head, char *searchKey) {
    Membernode *current = head;
    int found = 0;

    while (current != NULL) {
        // So sánh UID
        if (strcmp(current->data.uid, searchKey) == 0) { //strcmp dùng để so sánh 2 chuỗi với nhau
            printf("Resident found:\n");
            printf("UID: %s, Room Number: %s, Name: %s, License Plate: %s\n", current->data.uid, current->data.roomNumber, current->data.name, current->data.licensePlate);
            found = 1;
            break;
        }
        // So sánh License Plate
        else if (strcmp(current->data.licensePlate, searchKey) == 0) {
            printf("Resident found:\n");
            printf("UID: %s, Room Number: %s, Name: %s, License Plate: %s\n", current->data.uid, current->data.roomNumber, current->data.name, current->data.licensePlate);
            found = 1;
            break;
        }
        current = current->link;
    }

    if (!found) {
        printf("Resident with UID/License Plate %s not found.\n", searchKey);
    }
}

// Function to edit a member based on UID
void editmember(Membernode *head, char *searchKey, Member new_member) {
    Membernode *current = head;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->data.uid, searchKey) == 0 || strcmp(current->data.licensePlate, searchKey) == 0) {
            // Tìm thấy cư dân cần cập nhật
            printf("Resident found:\n");
            printf("UID: %s, Room Number: %s, Name: %s, License Plate: %s\n", current->data.uid, current->data.roomNumber, current->data.name, current->data.licensePlate);
            // Cập nhật thông tin của cư dân
            strcpy(current->data.name, new_member.name);
            strcpy(current->data.roomNumber, new_member.roomNumber);
            strcpy(current->data.licensePlate, new_member.licensePlate);
            printf("Resident information updated successfully.\n");
            found = 1;
            break;
        }
        current = current->link;
    }

    if (!found) {
        printf("Resident with UID/License Plate %s not found.\n", searchKey);
    }
}

// Function to print the main menu
void printMainMenu() {    
                printf("\n\n\t***Apartment Building Residents Information Management System***\n\n");
                printf("\t\t\tMAIN MENU\n");
                printf("\t\t=======================\n");
                printf("\t\t[1] Add A New Resident.\n");
                printf("\t\t[2] Show All Members.\n");
                printf("\t\t[3] Delete A Resident.\n");
                printf("\t\t[4] Update The Information of The Resident.\n");
                printf("\t\t[5] Search for A Resident according to UID/License Plate.\n");
                printf("\t\t[0] Exit the Program.\n");
                printf("\t\t=======================\n");
                printf("\t\tEnter The Choice: ");
}

// Function to print all members in the linked list
void printList(Membernode *head) {
    Membernode *current = head;

    if (current == NULL) {
        printf("The list is empty.\n");
        return;
    }

    printf("List of members:\n");
    while (current != NULL) {
        printf("UID: %s, Room Number: %s, Name: %s, License Plate: %s\n", current->data.uid, current->data.roomNumber, current->data.name, current->data.licensePlate);
        current = current->link;
    }
}

// Function to exit the project
void ExitProject()
{
    system("cls");
    int i;
    char ThankYou[100]     = " ========= Thank You =========\n";
    char SeeYouSoon[100]   = " ========= See You Soon ======\n";
    for(i=0; i<strlen(ThankYou); i++)
    {
        printf("%c",ThankYou[i]);
        Sleep(40);
    }
    for(i=0; i<strlen(SeeYouSoon); i++)
    {
        printf("%c",SeeYouSoon[i]);
        Sleep(40);
    }
    exit(0);
}

//Function to go back the prject or exit
void GoBackOrExit()
{
    getchar();
    char Option;
    printf(" Go back(b)? or Exit(0)?: ");
    scanf("%c",&Option);
    if(Option == '0')
    {
        ExitProject();
    }
    else if (Option != 'b')
    {
        printf("Incorrect, please try again\n");
        GoBackOrExit();
    }
    else
    {
        system("cls");
    }
}

// Function to create the header into CSV file
void writeHeaderToFile() {
    FILE *file = fopen(CSV_FILE, "a"); // Mở file để ghi, append vào cuối file

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Ghi dòng tiêu đề vào file
    fprintf(file, "UID,Room Number,Name,License Plate\n");

    fclose(file); // Đóng file
}

// Function to write the resident's information into CSV file
void writeMemberToFile(Member member) {
    FILE *file = fopen(CSV_FILE, "a"); // Mở file để ghi, append vào cuối file

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Ghi thông tin thành viên vào file theo định dạng CSV
    fprintf(file, "%s,%s,%s,%s\n", member.uid, member.roomNumber, member.name, member.licensePlate);

    fclose(file); // Đóng file
}

// Function to delete the resident's information from CSV file
void deleteMemberFromFile(char *searchKey) {
    FILE *tempFile = fopen("temp.csv", "w"); // Mở một file tạm để ghi

    if (tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE *file = fopen(CSV_FILE, "r"); // Mở file CSV để đọc

    if (file == NULL) {
        printf("Error opening file.\n");
        fclose(tempFile);
        return;
    }

    char line[1024];

    while (fgets(line, sizeof(line), file)) {
        // Tách thông tin của mỗi thành viên từ dòng
        char *uid = strtok(line, ",");
        char *roomNumber = strtok(NULL, ",");
        char *name = strtok(NULL, ",");
        char *licensePlate = strtok(NULL, ",");

        // So sánh UID hoặc License Plate với dòng cần xóa
        if (strcmp(uid, searchKey) != 0) {
            // Ghi lại các dòng khác vào file tạm
            fprintf(tempFile, "%s,%s,%s,%s", uid, roomNumber, name, licensePlate);
        }
    }

    fclose(file); // Đóng file gốc
    fclose(tempFile); // Đóng file tạm

    remove(CSV_FILE); // Xóa file gốc
    rename("temp.csv", CSV_FILE); // Đổi tên file tạm thành tên file gốc
}

// // Function to update the resident's information in CSV file
void updateMemberInFile(char *searchKey, Member new_member) {
    FILE *tempFile = fopen("temp.csv", "w"); // Mở một file tạm để ghi

    if (tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE *file = fopen(CSV_FILE, "r"); // Mở file CSV để đọc

    if (file == NULL) {
        printf("Error opening file.\n");
        fclose(tempFile);
        return;
    }

    char line[1024];

    while (fgets(line, sizeof(line), file)) {
        // Tách thông tin của mỗi thành viên từ dòng
        char *uid = strtok(line, ",");
        char *roomNumber = strtok(NULL, ",");
        char *name = strtok(NULL, ",");
        char *licensePlate = strtok(NULL, ",");

        // So sánh UID hoặc License Plate với dòng cần cập nhật
        if (strcmp(uid, searchKey) == 0) {
            // Ghi thông tin mới vào file tạm
            fprintf(tempFile, "%s,%s,%s,%s", new_member.uid, new_member.roomNumber, new_member.name, new_member.licensePlate);
        } else {
            // Ghi lại các dòng khác vào file tạm
            fprintf(tempFile, "%s,%s,%s,%s", uid, roomNumber, name, licensePlate);
        }
    }

    fclose(file); // Đóng file gốc
    fclose(tempFile); // Đóng file tạm

    remove(CSV_FILE); // Xóa file gốc
    rename("temp.csv", CSV_FILE); // Đổi tên file tạm thành tên file gốc
}

// Function to run the program
void runProgram() {
    Membernode *head = NULL;
    Member member;
    char choice;
    char searchKey[20];
    writeHeaderToFile();
    
    do {
        printMainMenu();
        scanf(" %c", &choice);

        switch(choice) {
            case '1': 
                printf("Enter UID: ");
                scanf("%s", member.uid);
                printf("Enter Room Number: ");
                scanf("%s", member.roomNumber);
                printf("Enter Name: ");
                scanf("%s", member.name);
                printf("Enter License Plate: ");
                scanf("%s", member.licensePlate);
                add(&head, member);
                writeMemberToFile(member);
                GoBackOrExit();
                break;

            case '2':
                printList(head);
                GoBackOrExit();
                break;
          
            case '3':
                printf("Enter the UID of the member to delete: ");
                scanf("%s", searchKey); // Đọc vào UID của thành viên cần xóa từ người dùng

                if (strlen(searchKey) > 0) { // Đảm bảo chuỗi UID không rỗng
                    deleteMember(&head, searchKey); // Gọi hàm deleteMember để xóa thành viên dựa trên UID
                    deleteMemberFromFile(searchKey);
                    
                } else {
                    printf("Invalid UID.\n"); // Thông báo nếu UID rỗng
                }
                
                GoBackOrExit();
                break;

            case '4':
                //char searchKey[20];
                printf("Enter the UID/License Plate of the resident to edit: ");
                scanf("%s", searchKey); // Đọc vào giá trị UID hoặc License Plate từ người dùng

                Member new_member; // Tạo một biến mới để lưu thông tin cập nhật

                printf("Enter the new name: ");
                scanf("%s", new_member.name);
                printf("Enter the new room number: ");
                scanf("%s", new_member.roomNumber);
                printf("Enter the new license plate: ");
                scanf("%s", new_member.licensePlate);

                editmember(head, searchKey, new_member); // Gọi hàm editmember với giá trị UID/License Plate và thông tin cập nhật
                updateMemberInFile(searchKey, new_member);
                GoBackOrExit();
                break;
    
            case '5':
                //char searchKey[20];
                printf("Enter the UID/License Plate to find the resident: ");
                scanf("%s", searchKey); // Đọc vào giá trị UID hoặc License Plate từ người dùng
                findmember(head, searchKey); // Gọi hàm findmember với giá trị UID/License Plate đọc được
                GoBackOrExit();
                break;


            case '0':
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (choice != '0');
}
