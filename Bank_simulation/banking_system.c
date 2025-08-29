#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 100

struct User {
    char name[50];
    int acc_no;
    char password[20];
    int balance;
};

struct User users[MAX_USERS];
int user_count = 0;
int current_user = -1;

// Save all users to users.txt
void save_users_to_file() {
    FILE *file = fopen("users.txt", "w");
    if (!file) return;
    for (int i = 0; i < user_count; i++) {
        fprintf(file, "%s\n%d\n%s\n%d\n", 
                users[i].name, 
                users[i].acc_no, 
                users[i].password, 
                users[i].balance);
    }
    fclose(file);
}

// Load users from users.txt
void load_users_from_file() {
    FILE *file = fopen("users.txt", "r");
    if (!file) return;
    while (fgets(users[user_count].name, sizeof(users[user_count].name), file)) {
        users[user_count].name[strcspn(users[user_count].name, "\n")] = '\0'; 
        fscanf(file, "%d\n", &users[user_count].acc_no);
        fgets(users[user_count].password, sizeof(users[user_count].password), file);
        users[user_count].password[strcspn(users[user_count].password, "\n")] = '\0';
        fscanf(file, "%d\n", &users[user_count].balance);
        user_count++;
    }
    fclose(file);
}

void divider() {
    for (int i = 0; i < 60; i++) {
        if(i<10) printf(" ");
        else printf("-");
    }
    printf("\n");
}

void small_divider(){
    for (int i = 0; i < 43; i++) {
        if(i<5) printf(" ");
        else printf("-");
    }
    printf("\n");
}

void save_transaction(int acc_no, const char* message) {
    char filename[60];
    snprintf(filename, sizeof(filename), "Account_%d.txt", acc_no);
    FILE* file = fopen(filename, "a");
    if (file) {
        time_t now;
        time(&now);
        fprintf(file, "%s\nDate/Time: %s\n\n", message, ctime(&now));
        fclose(file);
    }
}

void create_account() {
    printf("\n\t\tCreating Account\n");
    small_divider();
    struct User new_user;
    getchar();
    printf("Enter your name: ");
    fgets(new_user.name, sizeof(new_user.name), stdin);
    new_user.name[strcspn(new_user.name, "\n")] = '\0';

    printf("Enter your new account number: ");
    scanf("%d", &new_user.acc_no);

    getchar();
    printf("Set a password: ");
    scanf("%s", new_user.password);

    new_user.balance = 10000;
    users[user_count++] = new_user;

    save_users_to_file(); // save data to file

    system("cls"); 
    printf("\t\t\tWELCOME TO ABC BANK\n");
    divider();
    printf("Account created successfully! Please log in to continue.\n\n");
}

int login() {
    printf("\n\t\tLogging in\n");
    small_divider();
    int acc;
    char pass[20];
    printf("Enter account number: ");
    scanf("%d", &acc);
    printf("Enter password: ");
    scanf("%s", pass);
    for (int i = 0; i < user_count; i++) {
        if (users[i].acc_no == acc && strcmp(users[i].password, pass) == 0) {
            current_user = i;
            system("cls");
            return 1;
        }
    }
    return 0;
}

void deposit_money() {
    char pass[20];
    printf("\n\t\tDepositing Money\n");
    small_divider();
    printf("Enter your password to continue: ");
    scanf("%s", pass);
    if (strcmp(pass, users[current_user].password) != 0) {
        printf("Incorrect password!\n");
        return;
    }

    int amt;
    printf("Enter amount to deposit: ");
    scanf("%d", &amt);
    users[current_user].balance += amt;
    printf("Deposited successfully. New balance: Rs%d\n", users[current_user].balance);

    save_users_to_file(); // update saved data

    char msg[100];
    sprintf(msg, "Deposited Rs%d", amt);
    save_transaction(users[current_user].acc_no, msg);
}

void withdraw_money() {
    char pass[20];
    printf("\n\t\tWithdraw Money\n");
    small_divider();
    printf("Enter your password to continue: ");
    scanf("%s", pass);
    if (strcmp(pass, users[current_user].password) != 0) {
        printf("Incorrect password!\n");
        return;
    }

    int amt;
    printf("Enter amount to withdraw: ");
    scanf("%d", &amt);
    if (amt > users[current_user].balance) {
        printf("Insufficient funds!\n");
        return;
    }
    users[current_user].balance -= amt;
    printf("Withdrawn successfully. New balance: Rs%d\n", users[current_user].balance);

    save_users_to_file(); // update saved data

    char msg[100];
    sprintf(msg, "Withdrawn Rs%d", amt);
    save_transaction(users[current_user].acc_no, msg);
}

void transfer_money() {
    char pass[20];
    printf("\n\t\tTransferring Money\n");
    small_divider();
    printf("Enter your password to continue: ");
    scanf("%s", pass);
    if (strcmp(pass, users[current_user].password) != 0) {
        printf("Incorrect password!\n");
        return;
    }

    int acc, amt;
    printf("Enter recipient account number: ");
    scanf("%d", &acc);
    printf("Enter amount to transfer: ");
    scanf("%d", &amt);

    if (amt > users[current_user].balance) {
        printf("Insufficient funds!\n");
        return;
    }

    for (int i = 0; i < user_count; i++) {
        if (users[i].acc_no == acc) {
            users[current_user].balance -= amt;
            users[i].balance += amt;

            save_users_to_file(); // update data

            printf("Transferred successfully. New balance: Rs%d\n", users[current_user].balance);
            char msg[100];
            sprintf(msg, "Transferred Rs%d to account %d", amt, acc);
            save_transaction(users[current_user].acc_no, msg);

            char msg2[100];
            sprintf(msg2, "Received Rs%d from account %d", amt, users[current_user].acc_no);
            save_transaction(acc, msg2);
            return;
        }
    }
    printf("Recipient account not found!\n");
}

void view_account() {
    printf("\n\t\tAccount Details\n");
    small_divider();
    printf("Name: %s\n", users[current_user].name);
    printf("Account No: %d\n", users[current_user].acc_no);
    printf("Balance: Rs%d\n", users[current_user].balance);
}

void transaction_details() {
    printf("\n\t\tTransaction Details\n");
    small_divider();
    char filename[60];
    snprintf(filename, sizeof(filename), "Account_%d.txt", users[current_user].acc_no);
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("No transactions yet.\n");
        return;
    }
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        printf("%c", ch);
    }
    fclose(file);
}

void menu() {
    int choice;
    do {
        printf("\n\t\tMAIN MENU\n");
        small_divider();
        printf("1. Deposit\n2. Withdraw\n3. Transfer\n4. View Account\n5. Transaction History\n6. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: deposit_money(); break;
            case 2: withdraw_money(); break;
            case 3: transfer_money(); break;
            case 4: view_account(); break;
            case 5: transaction_details(); break;
            case 6: printf("\n\t\tLogging out...\n"); break;
            default: printf("Invalid choice\n"); break;
        }
    } while (choice != 6);
}

int main() {
    load_users_from_file(); // load existing user data
    printf("\t\t\tWELCOME TO ABC BANK\n");
    divider();
    int choice;
    while (1) {
        printf("1. Login\n2. Create Account\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                if (login()) {
                    printf("\t\t\tWELCOME TO ABC BANK\n");
                    divider();
                    printf("\nLogin successful. Welcome, %s!\n", users[current_user].name);
                    menu();
                } else {
                    printf("Login failed. Try again.\n");
                }
                break;
            case 2:
                create_account();
                break;
            case 3:
                printf("Thank you for using ABC Bank.\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;

}
