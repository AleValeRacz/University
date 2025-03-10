#include "Ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

Ui* createUi(Service* s)
{
	Ui* ui = (Ui*)malloc(sizeof(Ui));
	if (ui == NULL)
		return NULL;
	ui->serv = s;

	return ui;
}

void destroyUi(Ui* ui)
{
	destroy_service(ui->serv);
	free(ui);
}
void printMenu()
{
	printf("Menu\n");
	printf("1.Add medicine\n");
	printf("2.List medicines \n");
	printf("3.Delete medicine\n");
	printf("4.Update medicine\n");
	printf("5.Search for medicine by name\n");
    printf("6.Print medicines in short suply\n");
    printf("7.Undo\n");
    printf("8.Redo\n");
	printf("0.Exit\n");
} 
int readIntegerNumber(const char* message)
{
    char s[16];
    int res = 0;
    int flag = 0;
    int r = 0;

    while (flag == 0)
    {
        printf(message);
        scanf("%s", s);

        r = sscanf(s, "%d", &res);	// reads data from s and stores them as integer, if possible; returns 1 if successful
        flag = (r == 1);
        if (flag == 0)
            printf("Error reading number!\n");
    }
    return res;
}
void readStringWithSpaces(const char* message, int maxStrSize, char str[])
{
    printf(message);
    fgets(str, maxStrSize, stdin);
    // the newline is also read so we must eliminate it from the string
    size_t size = strlen(str) - 1;
    if (str[size] == '\n')
        str[size] = '\0';
}
void list_all_medicines(Ui* ui)
{
    if (ui == NULL)
        return;
    Repository* r = get_repo(ui->serv);
    int len = get_repo_length(r);
    printf("%d", len);
    for (int i = 0; i < len; i++)
    {
        Medicine* m = get_medicine_on_pos(r, i);
        char medicine_string[200];
        to_string(m, medicine_string);
        printf("%s\n", medicine_string);
    }
}
void print_medicines_in_array(DynamicArray* arr)
{
    if (arr == NULL)
    {
        printf("Invalid dynamic array.\n");
        return;
    }

    for (int i = 0; i < getSize(arr); i++)
    {
        Medicine* m = (Medicine*)get(arr, i);
        char medicine_string[200];
        to_string(m, medicine_string);
        printf("%s\n", medicine_string);
    }
}

void start(Ui* ui)
{
    int choice;
    do {
        printMenu();
         choice = readIntegerNumber("Enter choice:");
        
        if (choice == 1)
        {
            char name[40];
            int quantity;
            double price, concentration;
            fgetc(stdin);
            readStringWithSpaces("Enter name: ", 50, name);
            printf("Enter concentration: ");
            scanf("%lf", &concentration);
            printf("Enter quantity: ");
            scanf("%d", &quantity);
            printf("Enter price: ");
            scanf("%lf", &price);
            int res = add_medicine_serv(ui->serv, name, concentration, quantity, price);
            if (res == 0)
                printf("Invalid input\n");
            else
                if (res == 1)
                    printf("Succesfully added\n");
                else
                    printf("Updated the quantity\n");

                
        }
        else if (choice == 2)
        {
            list_all_medicines(ui);
        }
        
        else if (choice == 3)
        {
            char name[40];
            double concentration;
            printf("Enter name to delete: ");
            scanf("%s", name);
            printf("Enter concentration to delete: ");
            scanf("%lf", &concentration);
            remove_medicine_serv(ui->serv, name, concentration);
        }
        
        else if (choice == 4)
        {
            char name[50];
            int updated_quantity;
            double  updated_price, concentration;
            printf("Enter name to update: ");
            scanf("%s", name);
            printf("Enter concentration to update: ");
            scanf("%lf", &concentration);
            printf("Enter new quantity: ");
            scanf("%d", &updated_quantity);
            printf("Enter new price: ");
            scanf("%lf", &updated_price);
            update_medicine_serv(ui->serv, name, concentration, updated_quantity, updated_price);

        }
        
        else if (choice == 5)
        {
            char string[20];
            printf("enter string to search by: ");
            scanf("%s", string);
            DynamicArray* res = search_medicines_by_name(ui->serv, string);
            print_medicines_in_array(res);
            free(res->elems);
            free(res);

        }
        else if (choice == 6)
        {
            int treshold;
            printf("Enter treshold: ");
            scanf("%d", &treshold);
            DynamicArray* res = find_medicines_in_short_supply(ui->serv, treshold);
            print_medicines_in_array(res);
            free(res->elems);
            free(res);
        }
        else if (choice == 7) 
        {

           int res= undo(ui->serv);
           if (res == 0)
               printf("No more undos!\n");
           else
               printf("Undo succesfully\n");
        }
        else if (choice == 8)
        {
            int res = redo(ui->serv);
            if (res == 0)
                printf("No more redos!\n");
            else
                printf("Redo succesfully\n");

        }
        else if (choice == 0)
        {
            printf("Goodbye!\n");
            break;
        }
        else
        {
            printf("Invalid choice!\n");
        }

    } while (choice != 0);
}