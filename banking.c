#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accNo;
    char name[50];
    int balance;
};

// Create Account
void createAccount() {
    struct Account a;
    FILE *fp = fopen("bank.txt", "a");

    printf("Enter Acc No: ");
    scanf("%d", &a.accNo);

    printf("Enter Name: ");
    scanf("%s", a.name);

    printf("Enter Balance: ");
    scanf("%d", &a.balance);

    fprintf(fp, "%d %s %d\n", a.accNo, a.name, a.balance);
    fclose(fp);

    printf("Account Created\n");
}

// Display All Accounts
void display() {
    struct Account a;
    FILE *fp = fopen("bank.txt", "r");

    while (fscanf(fp, "%d %s %d", &a.accNo, a.name, &a.balance) != EOF) {
        printf("\nAcc No: %d\nName: %s\nBalance: %d\n",
               a.accNo, a.name, a.balance);
    }

    fclose(fp);
}

// Deposit / Withdraw
void update(int isDeposit) {

    int accNo, amt;
    struct Account a;

    FILE *fp = fopen("bank.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    printf("Enter Acc No: ");
    scanf("%d", &accNo);

    printf("Enter Amount: ");
    scanf("%d", &amt);

    while (fscanf(fp, "%d %s %d", &a.accNo, a.name, &a.balance) != EOF) {

        if (a.accNo == accNo) {

            if (isDeposit)
                a.balance += amt;
            else
                a.balance -= amt;

            printf("Updated Successfully\n");
        }

        fprintf(temp, "%d %s %d\n", a.accNo, a.name, a.balance);
    }

    fclose(fp);
    fclose(temp);

    remove("bank.txt");
    rename("temp.txt", "bank.txt");
}

// Balance Check
void checkBalance() {

    int accNo;
    struct Account a;

    FILE *fp = fopen("bank.txt", "r");

    printf("Enter Acc No: ");
    scanf("%d", &accNo);

    while (fscanf(fp, "%d %s %d", &a.accNo, a.name, &a.balance) != EOF) {

        if (a.accNo == accNo) {
            printf("Name: %s\nBalance: %d\n", a.name, a.balance);
        }
    }

    fclose(fp);
}

// Main Function
int main() {

    int ch;

    do {
        printf("\n1.Create\n2.Deposit\n3.Withdraw\n4.Balance\n5.Display\n6.Exit");
        printf("\nEnter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: createAccount(); break;
            case 2: update(1); break;
            case 3: update(0); break;
            case 4: checkBalance(); break;
            case 5: display(); break;
        }

    } while (ch != 6);

    return 0;
}