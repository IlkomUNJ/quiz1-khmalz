#include <iostream>
#include "bank_customer.h"
#include "buyer.h"
#include "seller.h"

enum PrimaryPrompt
{
    LOGIN,
    REGISTER,
    EXIT
};

enum LoginPrompt
{
    CHECK_STATUS,
    UPGRADE_TO_SELLER,
    BACK_LOGIN
};

enum RegisterPrompt
{
    CREATE_BUYER,
    CREATE_SELLER,
    BACK_REGISTER
};

using namespace std;

int main()
{
    Buyer *loggedInBuyer = nullptr;
    Seller *loggedInSeller = nullptr;

    // create a loop prompt
    PrimaryPrompt prompt = LOGIN;
    LoginPrompt loginPrompt = CHECK_STATUS;
    RegisterPrompt regPrompt = CREATE_BUYER;

    while (prompt != EXIT)
    {
        cout << "Select an option: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);

        switch (prompt)
        {
        case LOGIN:
        {
            if (!loggedInBuyer)
            {
                cout << "No account registered yet. Please register first.\n";
                break;
            }

            loginPrompt = CHECK_STATUS;

            while (loginPrompt != BACK_LOGIN)
            {
                cout << "\n=== Login Menu ===\n";
                cout << "1. Check Account Status\n";
                cout << "2. Upgrade Account to Seller\n";
                cout << "3. Back\n";

                int loginChoice;
                cin >> loginChoice;
                loginPrompt = static_cast<LoginPrompt>(loginChoice - 1);

                switch (loginPrompt)
                {
                case CHECK_STATUS:
                    cout << "=== Account Status ===\n";
                    loggedInBuyer->printInfo();
                    if (loggedInSeller)
                    {
                        loggedInSeller->printInfo();
                    }
                    break;
                case UPGRADE_TO_SELLER:
                {
                    cout << "=== Upgrade to Seller ===\n";

                    if (loggedInSeller)
                    {
                        cout << "You already have a Seller account.\n";
                        break;
                    }

                    int sellerId = static_cast<int>(rand());
                    string storeName, storeAddress, storePhone, storeEmail;

                    cin.ignore();
                    cout << "Enter Store Name: ";
                    getline(cin, storeName);
                    cout << "Enter Store Address: ";
                    getline(cin, storeAddress);
                    cout << "Enter Store Phone Number: ";
                    getline(cin, storePhone);
                    cout << "Enter Store Email: ";
                    getline(cin, storeEmail);

                    static Seller newSeller(
                        *loggedInBuyer,
                        sellerId,
                        loggedInBuyer->getName(),
                        storeName,
                        storeAddress,
                        storePhone,
                        storeEmail);

                    loggedInSeller = &newSeller;

                    cout << "Upgrade successful! You are now also a Seller.\n";
                    break;
                }
                case BACK_LOGIN:
                    cout << "Back to main menu.\n";
                    loginPrompt = BACK_LOGIN;
                    break;
                default:
                    cout << "Invalid option.\n";
                    break;
                }
            }
            break;
        }
        case REGISTER:
        {
            regPrompt = CREATE_BUYER;

            while (regPrompt != BACK_REGISTER)
            {
                cout << "Register selected.\n";
                cout << "Select an option: " << endl;
                cout << "1. Create Buyer Account" << endl;
                cout << "2. Create Seller Account" << endl;
                cout << "3. Back" << endl;

                int regChoice;
                cin >> regChoice;

                regPrompt = static_cast<RegisterPrompt>(regChoice - 1);

                switch (regPrompt)
                {
                case CREATE_BUYER:
                {
                    if (loggedInBuyer)
                    {
                        cout << "You already have a Buyer account. Please login instead.\n";
                        break;
                    }

                    int id = static_cast<int>(rand());
                    string name, address, phone, email;
                    double balance;

                    cout << "=== Create Buyer Account ===\n";

                    cin.ignore();
                    cout << "Enter Name: ";
                    getline(cin, name);
                    cout << "Enter Home Address: ";
                    getline(cin, address);
                    cout << "Enter Phone Number: ";
                    getline(cin, phone);
                    cout << "Enter Email: ";
                    getline(cin, email);
                    cout << "Enter Balance: ";
                    cin >> balance;

                    static Buyer newBuyer(id, name, address, phone, email);

                    loggedInBuyer = &newBuyer;
                    loggedInSeller = nullptr;
                    cout << "Buyer registration successful! You are now logged in as Buyer.\n";
                    break;
                }
                case CREATE_SELLER:
                {
                    if (loggedInSeller)
                    {
                        cout << "You already have a Seller account. Please login instead.\n";
                        break;
                    }

                    cout << "Create Seller Account selected." << endl;
                    if (!loggedInBuyer)
                    {
                        cout << "Please create a Buyer account first.\n";
                        break;
                    }

                    cout << "=== Create Seller Account ===\n";
                    int sellerId = static_cast<int>(rand());
                    string sellerName, storeName, storeAddress, storePhone, storeEmail;

                    cin.ignore();
                    cout << "Enter Your Name: ";
                    getline(cin, sellerName);
                    cout << "Enter Store Name: ";
                    getline(cin, storeName);
                    cout << "Enter Store Address: ";
                    getline(cin, storeAddress);
                    cout << "Enter Store Phone Number: ";
                    getline(cin, storePhone);
                    cout << "Enter Store Email: ";
                    getline(cin, storeEmail);

                    static Seller newSeller(
                        *loggedInBuyer,
                        sellerId,
                        sellerName,
                        storeName,
                        storeAddress,
                        storePhone,
                        storeEmail);

                    loggedInSeller = &newSeller;
                    cout << "Seller registration successful! You are now logged in as Seller.\n";
                    break;
                }
                case BACK_REGISTER:
                {
                    cout << "Back selected.\n";
                    regPrompt = BACK_REGISTER;
                    break;
                }
                default:
                    cout << "Invalid option.\n";
                    break;
                }
            }
            break;
        }
        case EXIT:
            cout << "Exiting.\n";
            break;
        default:
            cout << "Invalid option.\n";
            break;
        }

        cout << endl;
    }

    return 0;
}
