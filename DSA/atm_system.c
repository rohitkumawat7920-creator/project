/*
 * Project: ATM Management System (DSA Lab)
 * Concepts Used: 
 *   1. Arrays (Storing accounts and transaction records)
 *   2. Searching (Linear Search for Account & Transaction lookup)
 *   3. Sorting (Bubble Sort by Transaction Amount and ID)
 * Language: C (Simple and beginner-friendly)
 */

#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 50
#define MAX_TRANSACTIONS 200
#define MIN_BALANCE 500.0      // Minimum required balance
#define DAILY_LIMIT 20000.0    // Daily withdrawal limit

// Structure to store a single transaction
typedef struct {
    int txnId;
    int accNumber;
    char type[15];     // "Deposit" or "Withdrawal"
    float amount;
    char date[15];     // e.g. "2026-11-02"
} Transaction;

// Structure to store account details
typedef struct {
    int accNumber;
    char name[50];
    int pin;
    float balance;
    float dailyWithdrawn; // Tracks amount withdrawn today
} Account;

// Global arrays and counts
Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

Transaction transactions[MAX_TRANSACTIONS];
int transactionCount = 0;
int nextTxnId = 1001; // Auto-incrementing transaction ID

// -------------------------------------------------------------
// HELPER FUNCTION: Find account index by account number (Linear Search)
// Returns index if found, -1 if not found
// -------------------------------------------------------------
int findAccountIndex(int accNum) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accNumber == accNum) {
            return i; // Found
        }
    }
    return -1; // Not found
}

// -------------------------------------------------------------
// HELPER FUNCTION: Record a new transaction into transactions array
// -------------------------------------------------------------
void recordTransaction(int accNum, const char* type, float amount, const char* date) {
    if (transactionCount >= MAX_TRANSACTIONS) {
        printf("Transaction log is full!\n");
        return;
    }
    transactions[transactionCount].txnId = nextTxnId++;
    transactions[transactionCount].accNumber = accNum;
    strcpy(transactions[transactionCount].type, type);
    transactions[transactionCount].amount = amount;
    strcpy(transactions[transactionCount].date, date);
    transactionCount++;
}

// -------------------------------------------------------------
// MODULE 1: Account Creation & Update
// -------------------------------------------------------------
void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("\n[ERROR] Account limit reached! Cannot add more accounts.\n");
        return;
    }

    Account newAcc;
    printf("\n=== CREATE NEW ACCOUNT ===\n");
    printf("Enter Account Number (unique integer): ");
    scanf("%d", &newAcc.accNumber);

    // Check if account number already exists (Linear Search)
    if (findAccountIndex(newAcc.accNumber) != -1) {
        printf("[ERROR] An account with this number already exists!\n");
        return;
    }

    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]s", newAcc.name); // reads full name with spaces

    printf("Set a 4-digit PIN: ");
    scanf("%d", &newAcc.pin);

    printf("Enter Initial Deposit (Minimum balance is Rs. %.2f): ", MIN_BALANCE);
    scanf("%f", &newAcc.balance);

    if (newAcc.balance < MIN_BALANCE) {
        printf("[ERROR] Initial deposit must be at least Rs. %.2f.\n", MIN_BALANCE);
        return;
    }

    newAcc.dailyWithdrawn = 0.0;
    accounts[accountCount] = newAcc;
    accountCount++;

    // Record initial deposit as first transaction
    recordTransaction(newAcc.accNumber, "Deposit", newAcc.balance, "Initial");

    printf("\n[SUCCESS] Account created successfully for %s! Account Number: %d\n", newAcc.name, newAcc.accNumber);
}

void viewAccountDetails() {
    int accNum, pin;
    printf("\n=== VIEW ACCOUNT DETAILS ===\n");
    printf("Enter Account Number: ");
    scanf("%d", &accNum);

    int idx = findAccountIndex(accNum);
    if (idx == -1) {
        printf("[ERROR] Account not found!\n");
        return;
    }

    printf("Enter 4-digit PIN: ");
    scanf("%d", &pin);

    if (accounts[idx].pin != pin) {
        printf("[ERROR] Incorrect PIN!\n");
        return;
    }

    printf("\n--- Account Details ---\n");
    printf("Account Number : %d\n", accounts[idx].accNumber);
    printf("Holder Name    : %s\n", accounts[idx].name);
    printf("Current Balance: Rs. %.2f\n", accounts[idx].balance);
    printf("Withdrawn Today: Rs. %.2f / Rs. %.2f\n", accounts[idx].dailyWithdrawn, DAILY_LIMIT);
}

void updateAccountDetails() {
    int accNum, pin;
    printf("\n=== UPDATE ACCOUNT DETAILS ===\n");
    printf("Enter Account Number: ");
    scanf("%d", &accNum);

    int idx = findAccountIndex(accNum);
    if (idx == -1) {
        printf("[ERROR] Account not found!\n");
        return;
    }

    printf("Enter current PIN: ");
    scanf("%d", &pin);

    if (accounts[idx].pin != pin) {
        printf("[ERROR] Incorrect PIN!\n");
        return;
    }

    int choice;
    printf("\nWhat would you like to update?\n");
    printf("1. Update Holder Name\n");
    printf("2. Change PIN\n");
    printf("Enter choice (1-2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter new Name: ");
        scanf(" %[^\n]s", accounts[idx].name);
        printf("[SUCCESS] Name updated successfully!\n");
    } else if (choice == 2) {
        int newPin, confirmPin;
        printf("Enter new 4-digit PIN: ");
        scanf("%d", &newPin);
        printf("Confirm new PIN: ");
        scanf("%d", &confirmPin);

        if (newPin == confirmPin) {
            accounts[idx].pin = newPin;
            printf("[SUCCESS] PIN changed successfully!\n");
        } else {
            printf("[ERROR] PINs do not match!\n");
        }
    } else {
        printf("[ERROR] Invalid choice!\n");
    }
}

// -------------------------------------------------------------
// MODULE 2: Balance Inquiry & Deposit
// -------------------------------------------------------------
void checkBalance() {
    int accNum, pin;
    printf("\n=== BALANCE INQUIRY ===\n");
    printf("Enter Account Number: ");
    scanf("%d", &accNum);

    int idx = findAccountIndex(accNum);
    if (idx == -1) {
        printf("[ERROR] Account not found!\n");
        return;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);

    if (accounts[idx].pin != pin) {
        printf("[ERROR] Incorrect PIN!\n");
        return;
    }

    printf("\n[INFO] Account Holder: %s\n", accounts[idx].name);
    printf("[INFO] Current Balance: Rs. %.2f\n", accounts[idx].balance);
}

void depositCash() {
    int accNum, pin;
    float amount;
    char date[15];

    printf("\n=== DEPOSIT CASH ===\n");
    printf("Enter Account Number: ");
    scanf("%d", &accNum);

    int idx = findAccountIndex(accNum);
    if (idx == -1) {
        printf("[ERROR] Account not found!\n");
        return;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);

    if (accounts[idx].pin != pin) {
        printf("[ERROR] Incorrect PIN!\n");
        return;
    }

    printf("Enter amount to deposit: Rs. ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("[ERROR] Deposit amount must be positive!\n");
        return;
    }

    printf("Enter Date (e.g. 2026-11-02): ");
    scanf("%s", date);

    accounts[idx].balance += amount;
    recordTransaction(accounts[idx].accNumber, "Deposit", amount, date);

    printf("\n[SUCCESS] Rs. %.2f deposited successfully!\n", amount);
    printf("Updated Balance: Rs. %.2f\n", accounts[idx].balance);
}

// -------------------------------------------------------------
// MODULE 3: Cash Withdrawal & Balance Validation
// -------------------------------------------------------------
void withdrawCash() {
    int accNum, pin;
    float amount;
    char date[15];

    printf("\n=== WITHDRAW CASH ===\n");
    printf("Enter Account Number: ");
    scanf("%d", &accNum);

    int idx = findAccountIndex(accNum);
    if (idx == -1) {
        printf("[ERROR] Account not found!\n");
        return;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);

    if (accounts[idx].pin != pin) {
        printf("[ERROR] Incorrect PIN!\n");
        return;
    }

    printf("Enter amount to withdraw: Rs. ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("[ERROR] Withdrawal amount must be greater than zero!\n");
        return;
    }

    // Validation 1: Daily withdrawal limit
    if (accounts[idx].dailyWithdrawn + amount > DAILY_LIMIT) {
        printf("[ERROR] Exceeds daily withdrawal limit! Remaining allowed today: Rs. %.2f\n",
               DAILY_LIMIT - accounts[idx].dailyWithdrawn);
        return;
    }

    // Validation 2: Sufficient funds & Minimum balance check
    if (accounts[idx].balance - amount < MIN_BALANCE) {
        printf("[ERROR] Insufficient balance! A minimum balance of Rs. %.2f must be maintained.\n", MIN_BALANCE);
        printf("Maximum you can withdraw right now: Rs. %.2f\n", 
               (accounts[idx].balance > MIN_BALANCE) ? (accounts[idx].balance - MIN_BALANCE) : 0.0);
        return;
    }

    printf("Enter Date (e.g. 2026-11-02): ");
    scanf("%s", date);

    // Deduct amount
    accounts[idx].balance -= amount;
    accounts[idx].dailyWithdrawn += amount;
    recordTransaction(accounts[idx].accNumber, "Withdrawal", amount, date);

    printf("\n[SUCCESS] Please collect your cash: Rs. %.2f\n", amount);
    printf("Remaining Balance: Rs. %.2f\n", accounts[idx].balance);
}

// -------------------------------------------------------------
// MODULE 4: Transaction History, Sorting & Searching
// -------------------------------------------------------------
void displayTransactionList(Transaction list[], int count) {
    if (count == 0) {
        printf("No transactions found.\n");
        return;
    }

    printf("\n%-10s %-12s %-12s %-10s %-12s\n", "Txn ID", "Acc Number", "Type", "Amount", "Date");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-10d %-12d %-12s Rs.%-8.2f %-12s\n",
               list[i].txnId, list[i].accNumber, list[i].type, list[i].amount, list[i].date);
    }
}

// View all transactions
void viewAllTransactions() {
    printf("\n=== ALL TRANSACTIONS LOG ===\n");
    displayTransactionList(transactions, transactionCount);
}

// Sorting transactions by Amount using Bubble Sort (DSA Concept)
void sortTransactionsByAmount() {
    if (transactionCount <= 1) {
        printf("\nNot enough transactions to sort.\n");
        return;
    }

    // Create a copy of array so we don't mess up original log order if user wants
    Transaction sortedList[MAX_TRANSACTIONS];
    for (int i = 0; i < transactionCount; i++) {
        sortedList[i] = transactions[i];
    }

    // Bubble Sort: compare adjacent elements and swap if out of order
    for (int i = 0; i < transactionCount - 1; i++) {
        for (int j = 0; j < transactionCount - i - 1; j++) {
            if (sortedList[j].amount > sortedList[j + 1].amount) {
                // Swap
                Transaction temp = sortedList[j];
                sortedList[j] = sortedList[j + 1];
                sortedList[j + 1] = temp;
            }
        }
    }

    printf("\n=== TRANSACTIONS SORTED BY AMOUNT (Low to High - Bubble Sort) ===\n");
    displayTransactionList(sortedList, transactionCount);
}

// Sorting transactions by Date using Bubble Sort
void sortTransactionsByDate() {
    if (transactionCount <= 1) {
        printf("\nNot enough transactions to sort.\n");
        return;
    }

    Transaction sortedList[MAX_TRANSACTIONS];
    for (int i = 0; i < transactionCount; i++) {
        sortedList[i] = transactions[i];
    }

    for (int i = 0; i < transactionCount - 1; i++) {
        for (int j = 0; j < transactionCount - i - 1; j++) {
            if (strcmp(sortedList[j].date, sortedList[j + 1].date) > 0) {
                // Swap
                Transaction temp = sortedList[j];
                sortedList[j] = sortedList[j + 1];
                sortedList[j + 1] = temp;
            }
        }
    }

    printf("\n=== TRANSACTIONS SORTED BY DATE (Chronological - Bubble Sort) ===\n");
    displayTransactionList(sortedList, transactionCount);
}

// Search transaction by Transaction ID (Linear Search)
void searchTransactionById() {
    int targetId;
    printf("\n=== SEARCH TRANSACTION BY ID ===\n");
    printf("Enter Transaction ID to search: ");
    scanf("%d", &targetId);

    int found = 0;
    // Linear Search through transactions array
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i].txnId == targetId) {
            printf("\n[FOUND] Transaction Details:\n");
            printf("Txn ID        : %d\n", transactions[i].txnId);
            printf("Account Number: %d\n", transactions[i].accNumber);
            printf("Type          : %s\n", transactions[i].type);
            printf("Amount        : Rs. %.2f\n", transactions[i].amount);
            printf("Date          : %s\n", transactions[i].date);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("[NOT FOUND] No transaction exists with ID %d.\n", targetId);
    }
}

// Search transactions by Type ("Deposit" or "Withdrawal")
void searchTransactionsByType() {
    char searchType[15];
    printf("\n=== SEARCH TRANSACTIONS BY TYPE ===\n");
    printf("Enter Transaction Type ('Deposit' or 'Withdrawal'): ");
    scanf("%s", searchType);

    Transaction matched[MAX_TRANSACTIONS];
    int matchCount = 0;

    for (int i = 0; i < transactionCount; i++) {
        // Case-insensitive check can also be done, standard comparison here:
        if (stricmp(transactions[i].type, searchType) == 0) {
            matched[matchCount++] = transactions[i];
        }
    }

    printf("\n--- Results for type: %s ---\n", searchType);
    displayTransactionList(matched, matchCount);
}

// Seed initial demo data so the user can test searching/sorting right away
void seedSampleData() {
    // Demo Account 1
    accounts[0].accNumber = 101;
    strcpy(accounts[0].name, "Rohit Kumawat");
    accounts[0].pin = 1234;
    accounts[0].balance = 15000.0;
    accounts[0].dailyWithdrawn = 0.0;

    // Demo Account 2
    accounts[1].accNumber = 102;
    strcpy(accounts[1].name, "Aman Sharma");
    accounts[1].pin = 4321;
    accounts[1].balance = 8000.0;
    accounts[1].dailyWithdrawn = 0.0;

    accountCount = 2;

    // Demo Transactions
    recordTransaction(101, "Deposit", 15000.0, "2026-11-01");
    recordTransaction(102, "Deposit", 8000.0, "2026-11-01");
    recordTransaction(101, "Withdrawal", 2000.0, "2026-11-02");
    recordTransaction(102, "Withdrawal", 500.0, "2026-11-02");
    recordTransaction(101, "Deposit", 3500.0, "2026-11-02");
}

// -------------------------------------------------------------
// MAIN FUNCTION & MENU
// -------------------------------------------------------------
int main() {
    // Load some sample accounts & transactions so you don't have to start from scratch!
    seedSampleData();

    int choice;
    while (1) {
        printf("\n============================================\n");
        printf("           ATM MANAGEMENT SYSTEM (DSA)       \n");
        printf("============================================\n");
        printf("1. Create New Account\n");
        printf("2. View Account Details\n");
        printf("3. Update Account Details (Name / PIN)\n");
        printf("4. Check Balance\n");
        printf("5. Deposit Cash\n");
        printf("6. Withdraw Cash\n");
        printf("7. View All Transactions\n");
        printf("8. Sort Transactions by Amount (Bubble Sort)\n");
        printf("9. Sort Transactions by Date (Bubble Sort)\n");
        printf("10. Search Transaction by ID (Linear Search)\n");
        printf("11. Search Transactions by Type (Deposit/Withdrawal)\n");
        printf("12. Exit\n");
        printf("--------------------------------------------\n");
        printf("Enter your choice (1-12): ");

        if (scanf("%d", &choice) != 1) {
            // Clear invalid input buffer
            while (getchar() != '\n');
            printf("[ERROR] Please enter a valid number.\n");
            continue;
        }

        switch (choice) {
            case 1:  createAccount(); break;
            case 2:  viewAccountDetails(); break;
            case 3:  updateAccountDetails(); break;
            case 4:  checkBalance(); break;
            case 5:  depositCash(); break;
            case 6:  withdrawCash(); break;
            case 7:  viewAllTransactions(); break;
            case 8:  sortTransactionsByAmount(); break;
            case 9:  sortTransactionsByDate(); break;
            case 10: searchTransactionById(); break;
            case 11: searchTransactionsByType(); break;
            case 12:
                printf("\nThank you for using the ATM Management System. Goodbye!\n");
                return 0;
            default:
                printf("\n[ERROR] Invalid choice! Please select between 1 and 12.\n");
        }
    }

    return 0;
}
