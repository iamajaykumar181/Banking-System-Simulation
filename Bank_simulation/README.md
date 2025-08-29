# 🏦 Banking System Simulation in C

## 📌 Overview
This project is a **console-based Banking System Simulation** implemented in **C language**.  
It allows users to **create accounts, log in, deposit, withdraw, transfer money, and view transaction history**.  

The system uses **file handling** in C (`users.txt` and per-account transaction files) to persist data even after program termination.  
It is a simplified model of a banking application, designed to demonstrate **C programming concepts** such as:
- Structures
- File I/O
- String handling
- Functions
- Control flow

---

## ⚙️ Features
- **Account Creation**  
  - Users can register with a name, account number, and password.  
  - New accounts start with a default balance of `Rs. 10000`.  
  - Details are stored in `users.txt`.

- **Login System**  
  - Secure login using account number and password.  
  - Each session allows access only to the logged-in user.  

- **Deposit Money**  
  - Add funds to your account after password verification.  
  - Transactions recorded in user-specific files (`Account_<accno>.txt`).  

- **Withdraw Money**  
  - Withdraw funds with password authentication.  
  - Prevents overdrafts (insufficient funds).  

- **Transfer Money**  
  - Transfer balance between accounts.  
  - Updates both sender’s and receiver’s transaction files.  

- **View Account Details**  
  - Displays name, account number, and current balance.  

- **Transaction History**  
  - Each user has a dedicated file (`Account_<accno>.txt`) storing deposits, withdrawals, transfers, along with timestamps.  

- **Data Persistence**  
  - User and transaction details are saved in files → available across program restarts.  

---


---

## 🖥️ How It Works
1. On startup, the program loads existing users from `users.txt`.  
2. Users can either:
   - **Create a new account** → automatically assigned initial balance.  
   - **Login** → access their banking operations.  
3. Once logged in, users can choose from a **menu**:
     
     1.Deposit
     2.Withdraw
     3.Transfer
     4.View Account
     5.Transaction History
     6.Logout  
4. Transactions are logged with **date and time** using `<time.h>` library.  

---

## 🛠️ Technologies Used
- **Language:** C  
- **Concepts:** Structures, Functions, File Handling, Strings, Pointers  
- **Storage:** Flat text files (`users.txt`, `Account_xxx.txt`)  

---


     # Sample Run

WELCOME TO ABC BANK
------------------------------------------------------------
1. Login
2. Create Account
3. Exit
Enter your choice: 2

Creating Account
-----------------------------------
Enter your name: Ajay Kumar
Enter your new account number: 101
Set a password: 1234
Account created successfully! Please log in to continue.

## Login Example

Enter account number: 101
Enter password: 1234
Login successful. Welcome, Ajay Kumar!

## Menu Example

1. Deposit
2. Withdraw
3. Transfer
4. View Account
5. Transaction History
6. Logout

