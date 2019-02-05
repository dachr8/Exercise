//3. Record maintenance
#include <stdio.h>

typedef struct commodity {
    int id, quantity;
    char name[35];
    float price;
} COMMODITY;

int getChoices() {
    printf("\nPlease enter your choice:\n");
    printf("1--Create a 100 empty record file\n");
    printf("2--Input product record\n");
    printf("3--Update product record\n");
    printf("4--Delete product record\n");
    printf("5--Output all product records\n");
    printf("6--Exit the program\n");
    int choice;
    scanf("%d", &choice);
    return choice;
}

void createFile(char *fileName) {
    COMMODITY blank = {0, 0, "", 0.0};
    FILE *fp = fopen(fileName,
                     "wb");//Open or create a binary file in read/write mode that allows reading and writing.

    for (int i = 0; i < 100; ++i)
        fwrite(&blank, sizeof(COMMODITY), 1, fp);
    printf("100 empty records created\n");

    fclose(fp);
}

void outputRecords(char *fileName) {
    COMMODITY output = {0, 0, "", 0.0};
    FILE *fp = fopen(fileName, "rb");//Open a binary file in read mode, allowing only read/write data.

    printf("Product information is as follows:\n");
    printf("%-16s%-16s%-11s%11s\n", "Record Number", "Product Name", "Quantity", "Price");
    fread(&output, sizeof(COMMODITY), 1, fp);
    while (!feof(fp)) {
        if (output.id)
            printf("%-16d%-16s%-11d%10.2f\n", output.id, output.name, output.quantity, output.price);
        fread(&output, sizeof(COMMODITY), 1, fp);
    }

    fclose(fp);
}

void inputRecord(char *fileName) {
    COMMODITY input = {0, 0, "", 0.0};
    FILE *fp = fopen(fileName, "rb+");//Open a binary file in read/write mode, allowing only read/write data.

    printf("Please enter product information [ID is -1 for end of input]:");
    printf("\nProduct ID:");
    scanf("%d", &input.id);
    while (input.id != -1) {
        printf("Product name:");
        getchar();
        scanf("%[^\n]", input.name);
        printf("Quantity:");
        scanf("%d", &input.quantity);
        printf("Price:");
        scanf("%f", &input.price);
        fseek(fp, (input.id - 1) * sizeof(COMMODITY), SEEK_SET);
        fwrite(&input, sizeof(COMMODITY), 1, fp);

        printf("Please enter product information [ID is -1 for end of input]:");
        printf("\nProduct ID:");
        scanf("%d", &input.id);

    }
    printf("\nEnd of product information input\n");

    fclose(fp);
    outputRecords(fileName);
}

void updateRecord(char *fileName) {
    COMMODITY update = {0, 0, "", 0.0};
    FILE *fp = fopen(fileName, "rb+");//Open a binary file in read/write mode, allowing only read/write data.

    printf("Please enter the product ID to be updated [ID is -1 for end of update]:\n");
    int id, tmp;
    scanf("%d", &id);
    while (id != -1) {
        fseek(fp, (id - 1) * sizeof(COMMODITY), SEEK_SET);
        fread(&update, sizeof(COMMODITY), 1, fp);
        if (update.id != id)
            printf("Sorry, the product with record number %d does not exist and cannot be updated\n", id);
        else {
            printf("The original product information is as follows:\n");
            printf("%-16s%-16s%-11s%10s\n", "Record Number", "Product Name", "Quantity", "Price");
            printf("%-16d%-16s%-11d%10.2f\n", update.id, update.name, update.quantity, update.price);

            printf("Please enter the updated information [If an item is not updated, press the Enter key]:\n");
            printf("Product name:");
            getchar();
            if ((tmp = getchar()) != '\n') {
                ungetc(tmp, stdin);
                scanf("%[^\n]", update.name);
                getchar();
            }
            printf("Quantity:");
            if ((tmp = getchar()) != '\n') {
                ungetc(tmp, stdin);
                scanf("%d", &update.quantity);
                getchar();
            }
            printf("Price:");
            if ((tmp = getchar()) != '\n') {
                ungetc(tmp, stdin);
                scanf("%f", &update.price);
            }

            fseek(fp, (id - 1) * sizeof(COMMODITY), SEEK_SET);
            fwrite(&update, sizeof(COMMODITY), 1, fp);
            printf("The updated product information is as follows:\n");
            printf("%-16s%-16s%-11s%10s\n", "Record Number", "Product Name", "Quantity", "Price");
            printf("%-16d%-16s%-11d%10.2f\n", update.id, update.name, update.quantity, update.price);
        }
        printf("Please enter the product ID to be updated [ID is -1 for end of update]:\n");
        scanf("%d", &id);
    }
    printf("End of update\n");

    fclose(fp);
}

void deleteRecord(char *fileName) {
    COMMODITY blank = {0, 0, "", 0.0};
    COMMODITY delete = {0, 0, "", 0.0};
    char choice;

    printf("Please enter the product ID to be deleted [ID is -1 for end of delete]:\n");
    int id;
    scanf("%d", &id);
    while (id != -1) {
        FILE *fp = fopen(fileName, "rb+");//Open a binary file in read/write mode, allowing only read/write data.
        fseek(fp, (id - 1) * sizeof(COMMODITY), SEEK_SET);
        fread(&delete, sizeof(COMMODITY), 1, fp);
        if (delete.id != id)
            printf("Sorry, the product with record number %d does not exist and cannot be deleted\n", id);
        else {
            printf("The product information is as follows:\n");
            printf("%-16s%-16s%-11s%10s\n", "Record Number", "Product Name", "Quantity", "Price");
            printf("%-16d%-16s%-11d%10.2f\n", delete.id, delete.name, delete.quantity, delete.price);

            printf("Is it really deleted (confirmed by Y, canceled by N)?\n");
            getchar();
            scanf("%c", &choice);
            if (choice == 'Y') {
                fseek(fp, (id - 1) * sizeof(COMMODITY), SEEK_SET);
                fwrite(&blank, sizeof(COMMODITY), 1, fp);
                printf("Record number %d product successfully deleted\n", delete.id);
                fclose(fp);
            } else
                printf("You choose not to delete product with record number %d\n", delete.id);

            fclose(fp);
            outputRecords(fileName);
        }
        printf("Please enter the product ID to be deleted [ID is -1 for end of delete]:\n");
        scanf("%d", &id);
    }
    printf("End of delete\n");
}

int main(void) {
    int choice;
    char *fileName = "commodity.dat";

    while ((choice = getChoices()) != 6)
        switch (choice) {
            case 1:
                createFile(fileName);
                break;
            case 2:
                inputRecord(fileName);
                break;
            case 3:
                updateRecord(fileName);
                break;
            case 4:
                deleteRecord(fileName);
                break;
            case 5:
                outputRecords(fileName);
                break;
            default:
                break;
        }
    printf("The end of the program, bye!");

    return 0;
}
