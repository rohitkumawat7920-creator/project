/*
 * Project: Banking Management System (OOPs Lab)
 * Language: C++
 * 
 * Demonstrates the 4 Core Pillars of Object-Oriented Programming (OOP):
 * 1. Encapsulation: Data hiding with private/protected attributes and public methods.
 * 2. Inheritance: SavingsAccount and CurrentAccount inherit from BankAccount.
 * 3. Polymorphism: Virtual functions for account-specific withdrawal and display logic.
 * 4. Abstraction: Clean interface exposing banking operations while hiding internal logic.
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// ============================================================================
// CLASS 1: Transaction (Encapsulation)
// ============================================================================
class Transaction {
private:
    int txnId;
    string type;      // "Deposit" or "Withdrawal"
    double amount;
    string date;

public:
    // Constructor
    Transaction(int id, string t, double amt, string d) {
        txnId = id;
        type = t;
        amount = amt;
        date = d;
    }

    // Display transaction details
    void display() const {
        cout << left << setw(10) << txnId 
             << setw(18) << type 
             << "Rs. " << setw(12) << fixed << setprecision(2) << amount 
             << setw(15) << date << endl;
    }
};

// ============================================================================
// CLASS 2: BankAccount (Base Class - Demonstrates Abstraction & Encapsulation)
// ============================================================================
class BankAccount {
protected:
    // Protected attributes: accessible by derived classes, hidden from outside
    int accountNumber;
    string accountHolderName;
    int pin;
    double balance;
    vector<Transaction> transactionHistory;
    int nextTxnId;

public:
    // Parameterized Constructor
    BankAccount(int accNum, string name, int p, double initialBal) {
        accountNumber = accNum;
        accountHolderName = name;
        pin = p;
        balance = initialBal;
        nextTxnId = 101;
        // Record opening balance as first transaction
        recordTransaction("Initial Deposit", initialBal, "Opening");
    }

    // Virtual Destructor
    virtual ~BankAccount() {}

    // Getters
    int getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    double getBalance() const { return balance; }

    // PIN Authentication
    bool verifyPin(int inputPin) const {
        return (pin == inputPin);
    }

    // Update account details (Module 1)
    void updateName(const string& newName) {
        accountHolderName = newName;
        cout << "[SUCCESS] Account holder name updated to: " << accountHolderName << endl;
    }

    void updatePin(int newPin) {
        pin = newPin;
        cout << "[SUCCESS] PIN updated successfully!" << endl;
    }

    // Record a transaction
    void recordTransaction(const string& type, double amount, const string& date) {
        Transaction txn(nextTxnId++, type, amount, date);
        transactionHistory.push_back(txn);
    }

    // Module 2: Deposit Money
    void deposit(double amount, const string& date) {
        if (amount <= 0) {
            cout << "[ERROR] Deposit amount must be positive!" << endl;
            return;
        }
        balance += amount;
        recordTransaction("Deposit", amount, date);
        cout << "\n[SUCCESS] Successfully deposited Rs. " << fixed << setprecision(2) << amount << endl;
        cout << "Updated Balance: Rs. " << balance << endl;
    }

    // Module 3: Withdraw Money (Virtual function - Overridden by derived classes for Polymorphism)
    virtual bool withdraw(double amount, const string& date) {
        if (amount <= 0) {
            cout << "[ERROR] Withdrawal amount must be greater than zero!" << endl;
            return false;
        }
        if (amount > balance) {
            cout << "[ERROR] Insufficient funds! Current balance: Rs. " << balance << endl;
            return false;
        }

        balance -= amount;
        recordTransaction("Withdrawal", amount, date);
        cout << "\n[SUCCESS] Successfully withdrew Rs. " << fixed << setprecision(2) << amount << endl;
        cout << "Remaining Balance: Rs. " << balance << endl;
        return true;
    }

    // Module 4: Check Balance & Transaction History
    void checkBalance() const {
        cout << "\n----------------------------------------" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Current Balance: Rs. " << fixed << setprecision(2) << balance << endl;
        cout << "----------------------------------------" << endl;
    }

    void viewTransactionHistory() const {
        cout << "\n=== TRANSACTION HISTORY FOR ACCOUNT #" << accountNumber << " ===" << endl;
        if (transactionHistory.empty()) {
            cout << "No transactions recorded yet." << endl;
            return;
        }

        cout << left << setw(10) << "Txn ID" 
             << setw(18) << "Type" 
             << setw(16) << "Amount" 
             << setw(15) << "Date" << endl;
        cout << "--------------------------------------------------------" << endl;

        for (const auto& txn : transactionHistory) {
            txn.display();
        }
    }

    // Pure virtual or virtual display to demonstrate Polymorphism
    virtual void displayDetails() const {
        cout << "\n--- Account Details ---" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Holder Name   : " << accountHolderName << endl;
        cout << "Balance       : Rs. " << fixed << setprecision(2) << balance << endl;
    }
};

// ============================================================================
// CLASS 3: SavingsAccount (Inherits from BankAccount - Polymorphism & Inheritance)
// ============================================================================
class SavingsAccount : public BankAccount {
private:
    double minBalance;
    double interestRate; // e.g. 4.0%

public:
    SavingsAccount(int accNum, string name, int p, double initialBal, double minBal = 500.0, double rate = 4.0)
        : BankAccount(accNum, name, p, initialBal), minBalance(minBal), interestRate(rate) {}

    // Overriding withdraw to enforce minimum balance rule (Polymorphism)
    bool withdraw(double amount, const string& date) override {
        if (amount <= 0) {
            cout << "[ERROR] Withdrawal amount must be greater than zero!" << endl;
            return false;
        }
        if (balance - amount < minBalance) {
            cout << "[ERROR] Withdrawal failed! Minimum balance of Rs. " << minBalance 
                 << " must be maintained." << endl;
            cout << "Max you can withdraw right now: Rs. " 
                 << ((balance > minBalance) ? (balance - minBalance) : 0.0) << endl;
            return false;
        }

        balance -= amount;
        recordTransaction("Withdrawal", amount, date);
        cout << "\n[SUCCESS] Withdrew Rs. " << fixed << setprecision(2) << amount 
             << " from Savings Account." << endl;
        cout << "Remaining Balance: Rs. " << balance << endl;
        return true;
    }

    // Overriding displayDetails (Polymorphism)
    void displayDetails() const override {
        BankAccount::displayDetails();
        cout << "Account Type  : Savings Account" << endl;
        cout << "Min Balance   : Rs. " << fixed << setprecision(2) << minBalance << endl;
        cout << "Interest Rate : " << interestRate << "% per annum" << endl;
    }
};

// ============================================================================
// CLASS 4: CurrentAccount (Inherits from BankAccount - Overdraft facility)
// ============================================================================
class CurrentAccount : public BankAccount {
private:
    double overdraftLimit; // Allows withdrawing beyond 0 up to overdraftLimit

public:
    CurrentAccount(int accNum, string name, int p, double initialBal, double odLimit = 5000.0)
        : BankAccount(accNum, name, p, initialBal), overdraftLimit(odLimit) {}

    // Overriding withdraw to allow overdraft (Polymorphism)
    bool withdraw(double amount, const string& date) override {
        if (amount <= 0) {
            cout << "[ERROR] Withdrawal amount must be greater than zero!" << endl;
            return false;
        }
        if (balance - amount < -overdraftLimit) {
            cout << "[ERROR] Withdrawal exceeds overdraft limit of Rs. " << overdraftLimit << "!" << endl;
            cout << "Max you can withdraw: Rs. " << (balance + overdraftLimit) << endl;
            return false;
        }

        balance -= amount;
        recordTransaction("Withdrawal", amount, date);
        cout << "\n[SUCCESS] Withdrew Rs. " << fixed << setprecision(2) << amount 
             << " from Current Account." << endl;
        cout << "Remaining Balance: Rs. " << balance << endl;
        return true;
    }

    void displayDetails() const override {
        BankAccount::displayDetails();
        cout << "Account Type    : Current Account (Business)" << endl;
        cout << "Overdraft Limit : Rs. " << fixed << setprecision(2) << overdraftLimit << endl;
    }
};

// ============================================================================
// CLASS 5: Bank (Manages Collection of BankAccount pointers)
// ============================================================================
class Bank {
private:
    vector<BankAccount*> accounts; // Polymorphic collection

    // Helper: Find account pointer by account number
    BankAccount* findAccount(int accNum) {
        for (auto acc : accounts) {
            if (acc->getAccountNumber() == accNum) {
                return acc;
            }
        }
        return nullptr;
    }

public:
    // Destructor to clean up dynamically allocated accounts
    ~Bank() {
        for (auto acc : accounts) {
            delete acc;
        }
        accounts.clear();
    }

    // Seed sample accounts for easy testing
    void seedData() {
        // Sample Savings Account
        accounts.push_back(new SavingsAccount(1001, "Rohit Kumawat", 1234, 15000.0, 500.0, 4.0));
        // Sample Current Account
        accounts.push_back(new CurrentAccount(1002, "Tech Solutions Corp", 9999, 25000.0, 10000.0));
    }

    // Module 1: Create Account
    void createAccount() {
        int accNum, pin, accType;
        string name;
        double initialBal;

        cout << "\n=== CREATE BANK ACCOUNT ===" << endl;
        cout << "Enter unique Account Number: ";
        cin >> accNum;

        if (findAccount(accNum) != nullptr) {
            cout << "[ERROR] An account with number " << accNum << " already exists!" << endl;
            return;
        }

        cin.ignore(); // Flush newline
        cout << "Enter Account Holder Name: ";
        getline(cin, name);

        cout << "Set a 4-digit PIN: ";
        cin >> pin;

        cout << "Select Account Type:\n1. Savings Account\n2. Current Account\nChoice (1-2): ";
        cin >> accType;

        cout << "Enter Initial Deposit (Minimum Rs. 500): Rs. ";
        cin >> initialBal;

        if (initialBal < 500.0) {
            cout << "[ERROR] Minimum initial deposit is Rs. 500.00." << endl;
            return;
        }

        if (accType == 1) {
            accounts.push_back(new SavingsAccount(accNum, name, pin, initialBal));
            cout << "\n[SUCCESS] Savings Account created successfully for " << name << "!" << endl;
        } else if (accType == 2) {
            accounts.push_back(new CurrentAccount(accNum, name, pin, initialBal));
            cout << "\n[SUCCESS] Current Account created successfully for " << name << "!" << endl;
        } else {
            cout << "[ERROR] Invalid account type selected!" << endl;
        }
    }

    // Module 1: Manage / View Account
    void manageAccount() {
        int accNum, pin;
        cout << "\n=== MANAGE ACCOUNT ===" << endl;
        cout << "Enter Account Number: ";
        cin >> accNum;

        BankAccount* acc = findAccount(accNum);
        if (!acc) {
            cout << "[ERROR] Account not found!" << endl;
            return;
        }

        cout << "Enter PIN: ";
        cin >> pin;

        if (!acc->verifyPin(pin)) {
            cout << "[ERROR] Invalid PIN!" << endl;
            return;
        }

        acc->displayDetails();

        cout << "\nActions:" << endl;
        cout << "1. Update Holder Name" << endl;
        cout << "2. Change PIN" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << "Enter choice: ";
        int ch;
        cin >> ch;

        if (ch == 1) {
            cin.ignore();
            string newName;
            cout << "Enter new name: ";
            getline(cin, newName);
            acc->updateName(newName);
        } else if (ch == 2) {
            int newPin;
            cout << "Enter new 4-digit PIN: ";
            cin >> newPin;
            acc->updatePin(newPin);
        }
    }

    // Module 2: Deposit Money
    void depositMoney() {
        int accNum, pin;
        double amount;
        string date;

        cout << "\n=== DEPOSIT MONEY ===" << endl;
        cout << "Enter Account Number: ";
        cin >> accNum;

        BankAccount* acc = findAccount(accNum);
        if (!acc) {
            cout << "[ERROR] Account not found!" << endl;
            return;
        }

        cout << "Enter PIN: ";
        cin >> pin;
        if (!acc->verifyPin(pin)) {
            cout << "[ERROR] Invalid PIN!" << endl;
            return;
        }

        cout << "Enter amount to deposit: Rs. ";
        cin >> amount;
        cout << "Enter Date (e.g. 2026-11-02): ";
        cin >> date;

        acc->deposit(amount, date);
    }

    // Module 3: Withdraw Money
    void withdrawMoney() {
        int accNum, pin;
        double amount;
        string date;

        cout << "\n=== WITHDRAW MONEY ===" << endl;
        cout << "Enter Account Number: ";
        cin >> accNum;

        BankAccount* acc = findAccount(accNum);
        if (!acc) {
            cout << "[ERROR] Account not found!" << endl;
            return;
        }

        cout << "Enter PIN: ";
        cin >> pin;
        if (!acc->verifyPin(pin)) {
            cout << "[ERROR] Invalid PIN!" << endl;
            return;
        }

        cout << "Enter amount to withdraw: Rs. ";
        cin >> amount;
        cout << "Enter Date (e.g. 2026-11-02): ";
        cin >> date;

        // Dynamic dispatch: calls SavingsAccount::withdraw or CurrentAccount::withdraw
        acc->withdraw(amount, date);
    }

    // Module 4: Check Balance & Transaction History
    void checkBalance() {
        int accNum, pin;
        cout << "\n=== CHECK BALANCE ===" << endl;
        cout << "Enter Account Number: ";
        cin >> accNum;

        BankAccount* acc = findAccount(accNum);
        if (!acc) {
            cout << "[ERROR] Account not found!" << endl;
            return;
        }

        cout << "Enter PIN: ";
        cin >> pin;
        if (!acc->verifyPin(pin)) {
            cout << "[ERROR] Invalid PIN!" << endl;
            return;
        }

        acc->checkBalance();
    }

    void viewTransactionHistory() {
        int accNum, pin;
        cout << "\n=== VIEW TRANSACTION HISTORY ===" << endl;
        cout << "Enter Account Number: ";
        cin >> accNum;

        BankAccount* acc = findAccount(accNum);
        if (!acc) {
            cout << "[ERROR] Account not found!" << endl;
            return;
        }

        cout << "Enter PIN: ";
        cin >> pin;
        if (!acc->verifyPin(pin)) {
            cout << "[ERROR] Invalid PIN!" << endl;
            return;
        }

        acc->viewTransactionHistory();
    }
};

// ============================================================================
// MAIN FUNCTION & MENU
// ============================================================================
int main() {
    Bank bank;
    bank.seedData(); // Loads 2 sample accounts (1001: Savings, 1002: Current)

    int choice;
    while (true) {
        cout << "\n============================================\n";
        cout << "        BANKING MANAGEMENT SYSTEM (OOPs)    \n";
        cout << "============================================\n";
        cout << "1. Create New Bank Account (Savings/Current)\n";
        cout << "2. View & Manage Account Details (Name / PIN)\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Check Balance\n";
        cout << "6. View Transaction History\n";
        cout << "7. Exit\n";
        cout << "--------------------------------------------\n";
        cout << "Enter choice (1-7): ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[ERROR] Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.manageAccount(); break;
            case 3: bank.depositMoney(); break;
            case 4: bank.withdrawMoney(); break;
            case 5: bank.checkBalance(); break;
            case 6: bank.viewTransactionHistory(); break;
            case 7:
                cout << "\nThank you for banking with us. Have a great day!\n";
                return 0;
            default:
                cout << "\n[ERROR] Invalid choice! Please select 1-7.\n";
        }
    }

    return 0;
}
