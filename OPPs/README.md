# Banking Management System (OOPs Lab)

## 📌 Project Overview
A clean, modular, and beginner-friendly **Banking Management System** developed in **C++** implementing the **4 Core Pillars of Object-Oriented Programming (OOP)**.

---

## 🏛️ OOP Concepts Demonstrated

### 1. Encapsulation
- Bundling data and methods together inside classes.
- Private and protected attributes (`pin`, `balance`, `accountNumber`, `transactionHistory`) to prevent unauthorized external access.
- Controlled access via getters, setters, and authentication methods (`verifyPin`).

### 2. Inheritance
- Base class `BankAccount` containing shared attributes and banking operations.
- Derived classes:
  - `SavingsAccount`: Inherits from `BankAccount` with interest rate calculation and minimum balance validation (Rs. 500).
  - `CurrentAccount`: Inherits from `BankAccount` with business overdraft protection limit (Rs. 5,000).

### 3. Polymorphism (Runtime Polymorphism)
- Virtual functions (`virtual bool withdraw(...)`, `virtual void displayDetails(...)`).
- Dynamic method dispatch allowing accounts to use specific withdrawal rules depending on whether the account is Savings or Current.

### 4. Abstraction
- Exposes high-level banking operations (`deposit()`, `withdraw()`, `checkBalance()`, `viewTransactionHistory()`) while hiding complex internal transaction logging and validation rules.

---

## 📋 Modules Implemented
- **Module 1: Create and Manage Bank Accounts**
  - Create Savings or Current accounts with unique account numbers and 4-digit PINs.
  - View account details.
  - Update account holder name and change PIN.
- **Module 2: Deposit Money**
  - Secure deposit with PIN authentication and automatic transaction logging.
- **Module 3: Withdraw Money**
  - Account-specific withdrawal validation:
    - Minimum balance rule for Savings Account.
    - Overdraft limit for Current Account.
    - Negative balance protection and insufficient funds checks.
- **Module 4: Check Balance & Transaction History**
  - Formatted balance inquiry.
  - Complete transaction log showing Transaction ID, Type, Amount, and Date.

---

## 🚀 How to Compile and Run

Open PowerShell inside the `OPPs` folder:

```powershell
cd OPPs
g++ banking_system.cpp -o banking_system.exe
.\banking_system.exe
```

*(Pre-seeded with demo account `1001` [PIN: `1234`, Savings] and `1002` [PIN: `9999`, Current] for instant testing!)*
