#pragma once
#include "buyer.h"
#include "item.h"
#include <string>
#include <vector>

using namespace std;

class Seller : public Buyer
{

private:
    // Add seller-specific private members here
    int sellerId;
    string sellerName, storeName, storeAddress, storePhone, storeEmail;
    bool idDisplayed(int itemId) const
    {
        // Example implementation, can be customized
        return itemId > 0; // Assuming valid IDs are positive integers
    }

    vector<Item> items; // Assuming seller has a collection of items

public:
    Seller() = default;

    Seller(Buyer buyer, int sellerId,
           const string &sellerName,
           const string &storeName,
           const string &storeAddress,
           const string &storePhone,
           const string &storeEmail)
        : Buyer(buyer.getId(),
                buyer.getName(),
                buyer.getAddress(),
                buyer.getPhone(),
                buyer.getEmail()),
          sellerId(sellerId), sellerName(sellerName), storeName(storeName), storeAddress(storeAddress),
          storePhone(storePhone), storeEmail(storeEmail)
    {
        Buyer::setId(buyer.getId());
    }

    virtual ~Seller() = default;

    void addNewItem(int newId, const std::string &newName, int newQuantity, double newPrice)
    {
        Item newItem(newId, newName, newQuantity, newPrice);
        items.push_back(newItem);
    }

    void updateItem(int itemId, const std::string &newName, int newQuantity, double newPrice)
    {
        for (auto &item : items)
        {
            if (item.getId() == itemId)
            {
                item.alterItemById(itemId, newName, newQuantity, newPrice); // Assuming alterItemById is a method
            }
        }
    }

    void makeItemVisibleToCustomer(int itemId)
    {
        for (auto &item : items)
        {
            if (item.getId() == itemId)
            {
                item.setDisplay(true); // Assuming setDisplay is a method in Item class
                break;
            }
        }
    }

    void printInfo() const
    {
        cout << "Seller ID: " << sellerId << endl;
        cout << "Store Name: " << storeName << endl;
        cout << "Store Address: " << storeAddress << endl;
        cout << "Store Phone: " << storePhone << endl;
        cout << "Store Email: " << storeEmail << endl;
    }

    // Add seller-specific members here
};