#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <fstream>

using namespace std;

class Account {
private:
    int accountNumber;
    string accountHolderName;
    double balance;
    string accountType;

public:
    // Constructor
    Account(int accNo, string name, double initialBalance, string type) {
        accountNumber = accNo;
        accountHolderName = name;
        balance = initialBalance;
        accountType = type;
    }

    // Getters
    int getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    double getBalance() const { return balance; }
    string getAccountType() const { return accountType; }

    // Deposit money
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "\n✅ Amount deposited successfully!" << endl;
            cout << "New balance: $" << fixed << setprecision(2) << balance << endl;
        } else {
            cout << "\n❌ Invalid deposit amount!" << endl;
        }
    }

    // Withdraw money
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "\n✅ Amount withdrawn successfully!" << endl;
            cout << "New balance: $" << fixed << setprecision(2) << balance << endl;
            return true;
        } else if (amount > balance) {
            cout << "\n❌ Insufficient balance!" << endl;
            return false;
        } else {
            cout << "\n❌ Invalid withdrawal amount!" << endl;
            return false;
        }
    }

    // Display account details
    void displayAccount() const {
        cout << "\n═══════════════════════════════════════" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "═══════════════════════════════════════" << endl;
    }
};

class BankingSystem {
private:
    vector<Account> accounts;
    int nextAccountNumber;
    const string DATA_FILE = "accounts_data.txt";

public:
    BankingSystem() {
        nextAccountNumber = 1001; // Starting account number
        loadAccountsFromFile();
    }

    // Create a new account
    void createAccount() {
        system("cls"); // Use "clear" for Linux/Mac
        cout << "\n═══════════════════════════════════════" << endl;
        cout << "         CREATE NEW ACCOUNT" << endl;
        cout << "═══════════════════════════════════════" << endl;

        string name, type;
        double initialDeposit;

        cout << "Enter Account Holder Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Account Type (Savings/Current): ";
        getline(cin, type);

        cout << "Enter Initial Deposit: $";
        cin >> initialDeposit;

        if (initialDeposit < 0) {
            cout << "\n❌ Initial deposit cannot be negative!" << endl;
            return;
        }

        Account newAccount(nextAccountNumber, name, initialDeposit, type);
        accounts.push_back(newAccount);

        cout << "\n✅ Account created successfully!" << endl;
        cout << "Your Account Number is: " << nextAccountNumber << endl;
        
        nextAccountNumber++;
        saveAccountsToFile();
        
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    // Find account by account number
    int findAccountIndex(int accNo) {
        for (size_t i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccountNumber() == accNo) {
                return i;
            }
        }
        return -1;
    }

    // Deposit money
    void depositMoney() {
        system("cls");
        cout << "\n═══════════════════════════════════════" << endl;
        cout << "            DEPOSIT MONEY" << endl;
        cout << "═══════════════════════════════════════" << endl;

        int accNo;
        double amount;

        cout << "Enter Account Number: ";
        cin >> accNo;

        int index = findAccountIndex(accNo);
        
        if (index != -1) {
            cout << "Enter amount to deposit: $";
            cin >> amount;
            accounts[index].deposit(amount);
            saveAccountsToFile();
        } else {
            cout << "\n❌ Account not found!" << endl;
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    // Withdraw money
    void withdrawMoney() {
        system("cls");
        cout << "\n═══════════════════════════════════════" << endl;
        cout << "           WITHDRAW MONEY" << endl;
        cout << "═══════════════════════════════════════" << endl;

        int accNo;
        double amount;

        cout << "Enter Account Number: ";
        cin >> accNo;

        int index = findAccountIndex(accNo);
        
        if (index != -1) {
            cout << "Enter amount to withdraw: $";
            cin >> amount;
            accounts[index].withdraw(amount);
            saveAccountsToFile();
        } else {
            cout << "\n❌ Account not found!" << endl;
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    // Check balance
    void checkBalance() {
        system("cls");
        cout << "\n═══════════════════════════════════════" << endl;
        cout << "            CHECK BALANCE" << endl;
        cout << "═══════════════════════════════════════" << endl;

        int accNo;
        cout << "Enter Account Number: ";
        cin >> accNo;

        int index = findAccountIndex(accNo);
        
        if (index != -1) {
            cout << "\nAccount Holder: " << accounts[index].getAccountHolderName() << endl;
            cout << "Current Balance: $" << fixed << setprecision(2) 
                 << accounts[index].getBalance() << endl;
        } else {
            cout << "\n❌ Account not found!" << endl;
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    // Display all accounts
    void displayAllAccounts() {
        system("cls");
        cout << "\n═══════════════════════════════════════" << endl;
        cout << "         ALL ACCOUNT DETAILS" << endl;
        cout << "═══════════════════════════════════════" << endl;

        if (accounts.empty()) {
            cout << "\nNo accounts found in the system!" << endl;
        } else {
            for (const auto& acc : accounts) {
                acc.displayAccount();
            }
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    // Delete account
    void deleteAccount() {
        system("cls");
        cout << "\n═══════════════════════════════════════" << endl;
        cout << "            DELETE ACCOUNT" << endl;
        cout << "═══════════════════════════════════════" << endl;

        int accNo;
        cout << "Enter Account Number to delete: ";
        cin >> accNo;

        int index = findAccountIndex(accNo);
        
        if (index != -1) {
            cout << "\nAccount Details:" << endl;
            accounts[index].displayAccount();
            
            char confirm;
            cout << "\nAre you sure you want to delete this account? (Y/N): ";
            cin >> confirm;
            
            if (confirm == 'Y' || confirm == 'y') {
                accounts.erase(accounts.begin() + index);
                cout << "\n✅ Account deleted successfully!" << endl;
                saveAccountsToFile();
            } else {
                cout << "\n❌ Account deletion cancelled!" << endl;
            }
        } else {
            cout << "\n❌ Account not found!" << endl;
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    // Save accounts to file
    void saveAccountsToFile() {
        ofstream file(DATA_FILE);
        if (file.is_open()) {
            for (const auto& acc : accounts) {
                file << acc.getAccountNumber() << ","
                     << acc.getAccountHolderName() << ","
                     << acc.getBalance() << ","
                     << acc.getAccountType() << "\n";
            }
            file.close();
        }
    }

    // Load accounts from file
    void loadAccountsFromFile() {
        ifstream file(DATA_FILE);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                size_t pos = 0;
                vector<string> tokens;
                
                while ((pos = line.find(',')) != string::npos) {
                    tokens.push_back(line.substr(0, pos));
                    line.erase(0, pos + 1);
                }
                tokens.push_back(line);
                
                if (tokens.size() == 4) {
                    int accNo = stoi(tokens[0]);
                    string name = tokens[1];
                    double balance = stod(tokens[2]);
                    string type = tokens[3];
                    
                    Account acc(accNo, name, balance, type);
                    accounts.push_back(acc);
                    
                    if (accNo >= nextAccountNumber) {
                        nextAccountNumber = accNo + 1;
                    }
                }
            }
            file.close();
        }
    }

    // Main menu
    void mainMenu() {
        int choice;
        
        do {
            system("cls");
            cout << "\n═══════════════════════════════════════" << endl;
            cout << "     SIMPLE BANKING MANAGEMENT SYSTEM" << endl;
            cout << "═══════════════════════════════════════" << endl;
            cout << "1. Create New Account" << endl;
            cout << "2. Deposit Money" << endl;
            cout << "3. Withdraw Money" << endl;
            cout << "4. Check Balance" << endl;
            cout << "5. Display All Accounts" << endl;
            cout << "6. Delete Account" << endl;
            cout << "7. Exit" << endl;
            cout << "═══════════════════════════════════════" << endl;
            cout << "Enter your choice (1-7): ";
            cin >> choice;

            switch (choice) {
                case 1:
                    createAccount();
                    break;
                case 2:
                    depositMoney();
                    break;
                case 3:
                    withdrawMoney();
                    break;
                case 4:
                    checkBalance();
                    break;
                case 5:
                    displayAllAccounts();
                    break;
                case 6:
                    deleteAccount();
                    break;
                case 7:
                    cout << "\nThank you for using the Banking System!" << endl;
                    cout << "Goodbye!" << endl;
                    break;
                default:
                    cout << "\n❌ Invalid choice! Please try again." << endl;
                    cout << "\nPress Enter to continue...";
                    cin.ignore();
                    cin.get();
            }
        } while (choice != 7);
    }
};

int main() {
    BankingSystem bank;
    bank.mainMenu();
    return 0;
}