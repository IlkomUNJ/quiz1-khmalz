#ifndef BUYER_H
#define BUYER_H

#include <cstddef>
#include <string>
#include "bank_customer.h"

using namespace std;

class Buyer
{
private:
    int id;
    string name;
    string homeAddress;
    string phoneNumber;
    string email;
    BankCustomer *account = nullptr; // Association with BankCustomer

public:
    Buyer(int id,
          const string &name,
          const string &homeAddress,
          const string &phoneNumber,
          const string &email)
        : id(id), name(name), homeAddress(homeAddress),
          phoneNumber(phoneNumber), email(email), account(nullptr) {}

    int getId() const { return id; }
    void setId(int newId) { id = newId; }

    string getName() const { return name; }
    string getAddress() const { return homeAddress; }
    string getPhone() const { return phoneNumber; }
    string getEmail() const { return email; }
    BankCustomer *getAccount() { return account; }
    bool hasAccount() const { return account != nullptr; }

    void printInfo() const
    {
        cout << "\nBuyer ID: " << id << endl;
        cout << "Buyer Name: " << name << endl;
        cout << "Buyer Address: " << homeAddress << endl;
        cout << "Buyer Phone: " << phoneNumber << endl;
        cout << "Buyer Email: " << email << endl;

        if (account)
        {
            account->printInfo();
        }
        else
        {
            cout << "No bank account linked.\n";
        }
    }
};

#endif // BUYER_H