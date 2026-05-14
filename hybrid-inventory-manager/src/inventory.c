#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

#define FILENAME "inventory.dat"

static int find_item_position(FILE *file, int id, long *position, Item *item, int active_only) {
    rewind(file);

    while (1) {
        long current_position = ftell(file);
        if (fread(item, sizeof(Item), 1, file) != 1) {
            return 0;
        }

        if (item->id == id && (!active_only || item->is_deleted == 0)) {
            if (position != NULL) {
                *position = current_position;
            }
            return 1;
        }
    }
}

static int item_exists(int id) {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        return 0;
    }

    Item item;
    int found = find_item_position(file, id, NULL, &item, 0);
    fclose(file);
    return found;
}

int add_item(const Item item) {
    if (item.id <= 0 || item.quantity < 0 || item.price < 0.0f) {
        return 0;
    }

    if (item_exists(item.id)) {
        return 0;
    }

    FILE *file = fopen(FILENAME, "ab");
    if (!file) return 0;

    if (fwrite(&item, sizeof(Item), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}

int get_item(int id, Item *out) {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) return 0;

    Item item;
    while (fread(&item, sizeof(Item), 1, file) == 1) {
        if (item.id == id && item.is_deleted == 0) {
            *out = item;
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int update_item(int id, const Item updated) {
    FILE *file = fopen(FILENAME, "r+b");
    if (!file) return 0;

    long pos;
    Item item;
    while ((pos = ftell(file)), fread(&item, sizeof(Item), 1, file) == 1) {
        if (item.id == id && item.is_deleted == 0) {
            fseek(file, pos, SEEK_SET);
            if (fwrite(&updated, sizeof(Item), 1, file) != 1) {
                fclose(file);
                return 0;
            }
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int delete_item(int id) {
    FILE *file = fopen(FILENAME, "r+b");
    if (!file) return 0;

    long pos;
    Item item;
    while ((pos = ftell(file)), fread(&item, sizeof(Item), 1, file) == 1) {
        if (item.id == id && item.is_deleted == 0) {
            item.is_deleted = 1;
            fseek(file, pos, SEEK_SET);
            if (fwrite(&item, sizeof(Item), 1, file) != 1) {
                fclose(file);
                return 0;
            }
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int list_items(Item *buffer, int max_items) {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) return 0;

    int count = 0;
    Item item;
    while (count < max_items && fread(&item, sizeof(Item), 1, file) == 1) {
        if (item.is_deleted == 0) {
            buffer[count++] = item;
        }
    }
    fclose(file);
    return count;
}