# Hybrid Inventory Manager

Hybrid Inventory Manager is a console app with a split architecture: the data layer is written in C and stores inventory records in a binary file, while the menu and presentation layer is written in C++ with classes and STL.

## What It Does

- Add items with unique IDs
- View a single item by ID
- Update an item in place using `fseek`
- Soft delete items so they disappear from views and lists
- List all active items in sorted order

## Project Layout

```
hybrid-inventory-manager
├── include
│   └── inventory.h
├── src
│   ├── inventory.c
│   ├── InventoryManager.h
│   ├── InventoryManager.cpp
│   └── main.cpp
├── Makefile
└── README.md
```

## Build And Run

Build with Make:

```bash
make
```

Run the program:

```bash
./inventory_manager
```

If you want a clean rebuild:

```bash
make clean
make
```

## Sample Test Cases

- Add 3 items, exit, relaunch, and list all items to confirm they persist.
- Update one item, restart the app, and verify the updated values remain.
- Delete one item, then confirm it no longer appears in view or list output.
- Try adding a second item with the same ID and confirm it is rejected.
- Enter invalid IDs, negative quantities, and negative prices to confirm the app re-prompts safely.

## Notes

- Data persists in `inventory.dat` in the project folder.
- Deleted records remain in the file with `is_deleted = 1` so the record can be skipped in future views.