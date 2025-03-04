//Mark Goulet
//CIS-17B
//3-3-2025

#include <iostream>
#include <string>

using namespace std;

//class declaration
class BankAccount {
  private:
       string accountHolderName;
       int accountNumber;
       double balance;

  public:
    //constructor
    BankAccount(const string &name, int accNum, double initialBalance) {
      this->accountHolderName = name; //ran into an issue where I needed to use pointers to reference class information
      this->accountNumber = accNum;   //this was probably a more difficult way to do this
      this->balance = initialBalance;
    }

  //class functions
  void deposit(double amount) {
        balance += amount;
     }

  void withdraw(double amount) {
        balance -= amount;
     }

  double getBalance() {
        return balance;
     }
};

//function definitions to deposit, withdraw, and retrieve balance
void deposit (BankAccount* account) {
      double d_amount = 0;
      do {
          cout << "Enter the amount to deposit: ";
          cin >> d_amount;
          try {
              if (d_amount < 0) {
                throw invalid_argument("Deposit failed. Please enter a valid amount.");
                }
                account->deposit(d_amount);
                cout << "Deposit successful. New balance: $" << account->getBalance() << endl;
             } catch (const invalid_argument& e) {
               cout << "Error: " << e.what() << endl;
             }
          } while (d_amount < 0);
  }

void withdraw (BankAccount* account) {
     double w_amount = 0;
     do {
        cout << "Enter amount to withdraw: ";
        cin >> w_amount;
        try {
            if (w_amount < 0) {
                throw invalid_argument("Withdraw failed. Please enter a valid amount.");
                }
            if (w_amount > account->getBalance()) {
                throw invalid_argument("Withdraw failed. Insufficient Funds.");
                }
            account->withdraw(w_amount);
            cout << "Withdraw successful. New balance: $" << account->getBalance() << endl;
        } catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
        }
     } while (w_amount < 0 || w_amount > account->getBalance());
}

void accBalance (BankAccount* account) {
    cout << "Account Balance: $" << account->getBalance() << endl;
}

//function for initial startup - create account or exit
BankAccount* welcomeMenu () {
    int choice = 0;
    string name;
    double amount;
    BankAccount* account = nullptr;

    cout << "Welcome to Simple Bank System" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Exit" << endl;
      /*I made the welcome menu only have 2 options because it
         doesn't make sense to do account functions without an account*/
    do {
      cout << "Please enter menu option: ";
      cin >> choice;
      try {
           if (choice == 1) {
             cout << "Enter account name: ";
             cin.ignore();
             getline(cin, name);
             cout << "Enter amount to deposit: ";
             cin >> amount;
             account = new BankAccount(name, 1234, amount);
             cout << "\nAccount created successfully!" << endl;
           }
           if (choice == 2) {
             exit(0);
           }
           if (choice < 0 || choice > 1) {
             cout << "Invalid choice. Please enter valid menu option." << endl;
           }
      } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
      }
     } while (choice < 0 || choice > 1);
    return account;
}

//menu function to loop through account actions until exit
void accountMenu(BankAccount* account) {
    int choice = 0;

    do {
        cout << "\nAccount menu" << endl;
        cout << "1. Deposit Money" << endl;
        cout << "2. Withdraw Money" << endl;
        cout << "3. View Balance" << endl;
        cout << "4. Exit" << endl;
        cout << "Please enter menu option: ";
        cin >> choice;
        try {
             if (choice == 1) {
               deposit(account);
             }
             if (choice == 2) {
               withdraw(account);
             }
             if (choice == 3) {
               accBalance(account);
             }
             if (choice == 4) {
               exit(0);
             }
             if (choice < 0 || choice > 4) {
               cout << "Invalid choice. Please enter valid menu option." << endl;
             }
             } catch (const invalid_argument& e) {
               cout << "Error: " << e.what() << endl;
             }
    } while (choice != 4);
}

int main() {

  BankAccount* account = welcomeMenu(); //define pointer to reference through functions and define
                                        //new instance of BankAccount class

  if (account) {
    accountMenu(account); //call account menu function
    delete account;       //delete memory after exiting
  }

  return 0;
}