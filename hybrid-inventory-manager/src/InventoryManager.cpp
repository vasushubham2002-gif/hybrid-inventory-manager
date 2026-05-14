#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cstring>
#include "inventory.h"
#include "InventoryManager.h"

namespace {
    void printItemRow(const Item &item) {
        std::cout << std::left << std::setw(8) << item.id
                  << std::setw(28) << item.name
                  << std::right << std::setw(12) << item.quantity
                  << std::setw(14) << std::fixed << std::setprecision(2) << item.price
                  << std::endl;
    }
}

void InventoryManager::showTitle() const {
    std::cout << "==============================================\n";
    std::cout << "           Hybrid Inventory Manager           \n";
    std::cout << "==============================================\n";
}

int InventoryManager::promptInt(const char *label, int minimumValue) {
    int value = 0;
    while (true) {
        std::cout << label;
        if (std::cin >> value && value >= minimumValue) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cout << "Invalid input. Please try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

float InventoryManager::promptFloat(const char *label, float minimumValue) {
    float value = 0.0f;
    while (true) {
        std::cout << label;
        if (std::cin >> value && value >= minimumValue) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cout << "Invalid input. Please try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void InventoryManager::promptName(char *buffer, int size) {
    while (true) {
        std::cout << "Enter item name: ";
        std::cin.getline(buffer, size);
        if (std::strlen(buffer) > 0) {
            return;
        }

        std::cout << "Name cannot be empty. Please try again.\n";
    }
}

void InventoryManager::addItem() {
    Item item{};
    item.id = promptInt("Enter item ID: ", 1);
    promptName(item.name, static_cast<int>(sizeof(item.name)));
    item.quantity = promptInt("Enter item quantity: ", 0);
    item.price = promptFloat("Enter item price: ", 0.0f);
    item.is_deleted = 0;

    if (add_item(item) == 0) {
        std::cout << "Item could not be added. Duplicate IDs are not allowed.\n";
        return;
    }

    std::cout << "Item added successfully.\n";
}

void InventoryManager::viewItem() {
    int id = promptInt("Enter item ID to view: ", 1);
    Item item{};
    if (get_item(id, &item) == 1) {
        std::cout << "\nID: " << item.id << "\n";
        std::cout << "Name: " << item.name << "\n";
        std::cout << "Quantity: " << item.quantity << "\n";
        std::cout << "Price: " << std::fixed << std::setprecision(2) << item.price << "\n";
        return;
    }

    std::cout << "Item not found.\n";
}

void InventoryManager::updateItem() {
    int id = promptInt("Enter item ID to update: ", 1);
    Item current{};
    if (get_item(id, &current) == 0) {
        std::cout << "Item not found.\n";
        return;
    }

    Item updated = current;
    std::cout << "Current name: " << current.name << "\n";
    std::cout << "Enter new name: ";
    std::cin.getline(updated.name, static_cast<std::streamsize>(sizeof(updated.name)));
    while (std::strlen(updated.name) == 0) {
        std::cout << "Name cannot be empty. Enter new name: ";
        std::cin.getline(updated.name, static_cast<std::streamsize>(sizeof(updated.name)));
    }

    updated.quantity = promptInt("Enter new quantity: ", 0);
    updated.price = promptFloat("Enter new price: ", 0.0f);
    updated.is_deleted = 0;

    if (update_item(id, updated) == 1) {
        std::cout << "Item updated successfully.\n";
        return;
    }

    std::cout << "Failed to update item.\n";
}

void InventoryManager::deleteItem() {
    int id = promptInt("Enter item ID to delete: ", 1);
    if (delete_item(id) == 1) {
        std::cout << "Item deleted successfully.\n";
        return;
    }

    std::cout << "Item not found.\n";
}

void InventoryManager::listItems() {
    std::vector<Item> items;
    Item buffer[100];
    int count = list_items(buffer, 100);
    for (int i = 0; i < count; ++i) {
        items.push_back(buffer[i]);
    }

    std::sort(items.begin(), items.end(), [](const Item &left, const Item &right) {
        return left.id < right.id;
    });

    std::cout << "\n================ Current Inventory ================\n";
    if (items.empty()) {
        std::cout << "No active items found.\n";
        return;
    }

    std::cout << std::left << std::setw(8) << "ID"
              << std::setw(28) << "Name"
              << std::right << std::setw(12) << "Quantity"
              << std::setw(14) << "Price" << "\n";
    std::cout << "----------------------------------------------------\n";
    for (const auto &item : items) {
        printItemRow(item);
    }
}

void InventoryManager::run() {
    while (true) {
        showTitle();
        std::cout << "1. Add item\n";
        std::cout << "2. View item\n";
        std::cout << "3. Update item\n";
        std::cout << "4. Delete item\n";
        std::cout << "5. List all\n";
        std::cout << "6. Exit\n";

        int choice = promptInt("Choose an option: ", 1);
        if (choice == 6) {
            std::cout << "Goodbye.\n";
            break;
        }

        switch (choice) {
            case 1: addItem(); break;
            case 2: viewItem(); break;
            case 3: updateItem(); break;
            case 4: deleteItem(); break;
            case 5: listItems(); break;
            default:
                std::cout << "Invalid choice. Please select 1-6.\n";
        }

        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
}