#ifndef MENU_H
#define MENU_H

// Định nghĩa tên file CSV
#define CSV_FILE "Residents_Information.csv"

// Struct Contains Member Data 
typedef struct Member {
    char uid[20];
    char roomNumber[10];
    char name[50];
    char licensePlate[20];
} Member;

// Struct of Node Contains Member Data
typedef struct Membernode {
    Member data;
    struct Membernode *link;
} Membernode;

// Function prototypes
Membernode *createmembernode(Member member);
void add(Membernode **head, Member member);
void deleteMember(Membernode **head, char *searchKey);
void findmember(Membernode *head, char *searchKey);
void editmember(Membernode *head, char *searchKey, Member new_member);
void printMainMenu();
void printList(Membernode *head);
void ExitProject();
void GoBackOrExit();
void writeHeaderToFile();
void writeMemberToFile(Member member);
void deleteMemberFromFile(char *searchKey);
void updateMemberInFile(char *searchKey, Member new_member);
void runProgram();

#endif
