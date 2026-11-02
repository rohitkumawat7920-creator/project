# ATM Management System (DSA Lab)

## 📌 Project Overview
A beginner-friendly, menu-driven **ATM Management System** built in **C** using core Data Structures and Algorithms (DSA) concepts: **Arrays**, **Linear Search**, and **Bubble Sort**.

---

## 🛠️ Main DSA Concepts Used
1. **Arrays of Structures (`struct`)**:
   - `Account accounts[MAX_ACCOUNTS]`: Stores user accounts (Account number, name, PIN, balance, daily withdrawal tracker).
   - `Transaction transactions[MAX_TRANSACTIONS]`: Stores transaction history (Txn ID, Account number, type, amount, date).
2. **Searching**:
   - **Linear Search** to find an account by Account Number (`findAccountIndex`).
   - **Linear Search** to look up a transaction by Transaction ID (`searchTransactionById`).
   - **Filtering/Searching** transactions by Type (`Deposit` or `Withdrawal`).
3. **Sorting**:
   - **Bubble Sort** algorithm to sort transactions chronologically or by transaction amount (low to high).

---

## 📋 Features & Modules
- **Module 1: Account Creation & Update**
  - Create a new account with a unique account number, name, 4-digit PIN, and initial deposit ($\ge$ Rs. 500 minimum balance).
  - View account details after PIN authentication.
  - Update account details (change name or change PIN).
- **Module 2: Balance Inquiry & Deposit**
  - Check account balance securely with PIN verification.
  - Deposit cash and immediately log the transaction into history.
- **Module 3: Cash Withdrawal & Validation**
  - Withdraw cash with strict validations:
    - Minimum balance maintenance (Rs. 500).
    - Daily withdrawal limit enforcement (Rs. 20,000 / day).
    - Sufficient balance validation.
- **Module 4: Transaction History, Sorting & Searching**
  - View full transaction history log.
  - Sort transactions by amount using Bubble Sort.
  - Sort transactions by date using Bubble Sort.
  - Search any transaction by its unique Transaction ID.
  - Filter transactions by type (`Deposit` / `Withdrawal`).

---

## 🚀 How to Compile and Run
Open your terminal inside the `DSA` directory and run:

```bash
gcc atm_system.c -o atm_system.exe
./atm_system.exe
```

*(Pre-loaded with sample demo data for quick testing!)*
