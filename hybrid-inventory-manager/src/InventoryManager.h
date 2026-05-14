#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

class InventoryManager {
public:
    void run();

private:
    void addItem();
    void viewItem();
    void updateItem();
    void deleteItem();
    void listItems();

    void showTitle() const;
    int promptInt(const char *label, int minimumValue);
    float promptFloat(const char *label, float minimumValue);
    void promptName(char *buffer, int size);
};

#endif // INVENTORY_MANAGER_H