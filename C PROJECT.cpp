#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    typedef struct user
    {
        float balance;
        char pswrd[50];
        char ac[50];
        char ph[50];
    } details;
    details user, usr;
    char userdata[50], phone[50], password[50], phone2[50];
    FILE *fp, *fptr;
    int opt, choice;
    int amount;
    char cont = 'y';
    printf("---  WELCOME TO TELECO BANK  ----\n");
    printf("\nWhat do you want to do ?");
    printf("\n\n1.Register your account");
    printf("\n2.Login to your account");

    printf("\n\nEnter your choice: ");
    scanf("%d", &opt);
    if (opt == 1)
    {
        system("clear");
        printf("\nEnter your account number: ");
        scanf("%s", user.ac);
        printf("Enter your phone number: ");
        scanf("%s", user.ph);
        printf("Enter your new password: ");
        scanf("%s", user.pswrd);
        user.balance = 0;
        strcpy(userdata, user.ph);
        fp = fopen(strcat(userdata, ".dat"), "w");
        fwrite(&user, sizeof(user), 1, fp);
        if (fwrite != 0)
        {
            printf("Succesfully registered");
        }
    }
    else if (opt == 2)
    {
        system("clear");
        printf("\nPhone No.:\t");
        scanf("%s", phone);
        printf("Password:\t");
        scanf("%s", password);
        fp = fopen(strcat(phone, ".dat"), "r");
        if (fp == NULL)
            printf("Account number not registered");
        else
        {
            fread(&user, sizeof(struct user), 1, fp);
            fclose(fp);
            if (!strcmp(password, user.pswrd))
            {
                while (cont == 'y')
                {
                    system("clear");
                    printf("\n\tWelcome %s", user.ph);
                    printf("\n# Press 1 for balance inquiry");
                    printf("\n# Press 2 for adding fund");
                    printf("\n# Press 3 for cash withdraw");
                    printf("\n# Press 4 for online transfer");
                    printf("\n# Press 5 for changing password\n\n");
                    scanf("%d", &choice);
                    switch (choice)
                    {
                    case 1:
                        printf("Your current balance is Rs. %.2f", user.balance);
                        break;

                    case 2:
                        system("clear");
                        printf("Enter amount to be added: ");
                        scanf("%d", &amount);
                        user.balance += amount;
                        fp = fopen(phone, "w");
                        fwrite(&user, sizeof(struct user), 1, fp);
                        if (fwrite != 0)
                            printf("\n\nYou have depostied Rs.%d", amount);
                        fclose(fp);
                        break;

                    case 3:
                        system("clear");
                        printf("Enter withdrawl amount: ");
                        scanf("%d", &amount);
                        if (amount % 500 != 0)
                            printf("\nSorry amount should be multiple of 500");
                        else if (amount > user.balance)
                            printf("\nSorry insufficeint balance");
                        else
                        {
                            user.balance -= amount;
                            fp = fopen(phone, "w");
                            fwrite(&user, sizeof(struct user), 1, fp);
                            if (fwrite != 0)
                                printf("\n\nYou have withdrawn Rs.%d", amount);
                            fclose(fp);
                        }
                        break;

                    case 4:
                        printf("Please enter the phone number to trasnfer balance: ");
                        scanf("%s", phone);
                        printf("Enter the amount to transfer: ");
                        scanf("%d", &amount);
                        if (amount > user.balance)
                            printf("\nSorry insufficent balance");
                        else
                        {
                            fptr = fopen(strcat(phone, ".dat"), "r");
                            if (fptr == NULL)
                                printf("Sorry number is not registered");
                            else
                            {
                                fread(&usr, sizeof(struct user), 1, fptr);
                                fclose(fptr);

                                usr.balance += amount;

                                fptr = fopen(phone, "w");
                                fwrite(&usr, sizeof(struct user), 1, fptr);
                                if (fwrite != 0)
                                {
                                         printf("Your trasfer is completed. You have trasnfered Rs. %d to %s", amount, usr.ph);
                                    fclose(fptr);
                                    user.balance -= amount;
                                    strcpy(userdata, user.ph);
                                    fp = fopen(strcat(userdata, ".dat"), "w");
                                    fwrite(&user, sizeof(struct user), 1, fp);
                                    fclose(fp);
                                }
                            }
                        }
                        break;
                    case 5:
                        printf("\n\nPlease enter your old password: ");
                        scanf("%s", password);
                        if (!strcmp(password, user.pswrd))
                        {
                            printf("\n\nPlease enter your new password: ");
                            scanf("%s", password);
                            strcpy(user.pswrd, password);
                            strcpy(userdata, user.ph);
                            fp = fopen(strcat(userdata, ".dat"), "w");
                            fwrite(&user, sizeof(struct user), 1, fp);
                            fclose(fp);
                            printf("\nPassword succesfullly changed");
                        }
                        else
                            printf("\nSorry your password is wrong");

                    default:
                        break;
                    } 
                    printf("\n\n'y'-> Yes\n");
                    printf("'n'-> No\n");
                    printf("\n\nDo you want to continue?[y/n]: ");

                    scanf("%s", &cont);
                }
            }
            else
            {
                printf("Invalid password");
            }
        }
        printf("\n\n--- Thank you for banking with TELCO BANK ---\n\n");
    }

    return 0;
}