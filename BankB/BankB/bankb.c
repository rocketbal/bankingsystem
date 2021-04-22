#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct Acctinfo {
    char name[100];
    char cznum[100];
    char address[100];
    char phonenum[100];
    char money[50];
};

//struct acctinfo acctinfo1[10];

// Operation menu
int menu() {
    int choice;
    printf("Customer Account Banking Management System\n\n");
    printf("1. Create an account\n");
    printf("2. Update information of an existing account\n");
    printf("3. For transactions\n");
    printf("4. Check details of an existing account\n");
    printf("5. Remove existing account\n");
    printf("6. Exit Program\n\n\n");
    printf("Enter your choices:\n");
    scanf_s("%d", &choice);
    getchar();

    printf("User picked: %d\n", choice);
    return choice;
};

// Creating a new account
void new_acct() {
   
    struct Acctinfo* acct1;
    acct1 = (struct Acctinfo*)malloc(sizeof(struct Acctinfo));

    FILE* view, *count;
    errno_t err, err1;
    err = fopen_s(&view, "Bankinfo.txt", "a");
    //err1 = fopen_s(&count, "count.txt", "w+");

    if (view == 0)
    {
        printf("The file 'Bankinfo.txt' was not opened\n");
    }
    else
    {
        printf("The file 'Bankinfo.text' was opened\n");
    }

    printf("Create a new account\n");
    printf("Please enter your name: \n");
   
    gets_s(acct1->name,80);
    printf("You have entered: %s\n", acct1->name);

    printf("Enter your address:\n");
    gets_s(acct1->address, 80);
    printf("Address entered: %s\n", acct1->address);
 
    printf("Enter your phone number:\n");
    gets_s(acct1->phonenum, 80);
    printf("Phone number entered: %s\n", acct1->phonenum);

    printf("How much much would you like to deposit? :\n");
    gets_s(acct1->money, 40);
    printf("Phone number entered: $%s\n", acct1->money);
   
    // Send new user information into the file
    fprintf(view, "%d|%s|%s|%s|%s\n", 1, acct1->name, acct1->address, acct1->phonenum,acct1->money);
 
    fclose(view);

};

// To update information in a new account
void view_list(struct Acctinfo *acct) {
    // grab information from the file and print

    FILE* view, *tempfile;
    errno_t err, err1;
    char temp[512];
    int line_num = 0;
    int choice;

    err = fopen_s(&view, "Bankinfo.txt", "r");
    err1 = fopen_s(&tempfile, "temp.txt", "w");

    if (view == NULL)
    {
        printf("The file 'Textline.txt' was not opened\n");
    }
    else
    {
        printf("The file 'textline.txt' was opened\n");
    }


    // Asking user's name to find their information
    int i = 0;
    char name[100];
    printf("Enter your name:\n");
    gets_s(name, 80);

    //Search for Customer's name in a File
    while (fgets(temp, 512, view) != NULL) {
        if ((strstr(temp, name)) != NULL) {
            printf("A match found on line: %d\n", line_num);
            //printf("\n%s\n", temp);
        }
        line_num++;
    }

    rewind(view);

    // Print user information using the line found in previous step
    char str[100];
    char str2[100];
    int ctr = 0;
    while (!feof(view))
    {
        //strcpy(str, "\0");
        fgets(str, 256, view);
        if (!feof(view))
        {
            ctr++;
            /* print line which contains information */
            if (ctr == line_num)
            {
                strcpy(str2,str);
                printf("%s", str2);
            }
        }
    }

    char name2[100], address[100], phonenumber[100], acct1[10],amount[50];
    char* token = strtok(str2, "|");
    i = 0;
    // loop through the string to extract all other tokens
    while (token != NULL) {
        if (i == 0)
            strcpy(acct1, token);
        else if (i == 1)
            strcpy(name2, token);
        else if (i == 2)
            strcpy(address, token);
        else if (i == 3)
            strcpy(phonenumber, token);
        else if (i == 4)
            strcpy(amount, token);
        printf(" %s\n", token); //printing each token
        token = strtok(NULL, "|");
        i++;
    }

    // Ask the user what they would like to modify
    printf("Please select a field you'd like to update: \n");
    printf("1. Name\n");
    printf("2. Address\n");
    printf("3. Phone Number\n");
    scanf_s("%d", &choice);
    getchar();

    if (choice == 1)
    {
        printf("Pleaes enter new name: \n");
        gets_s(name2, 80);
    }
    else if (choice == 2)
    {
        printf("Please enter new address for this account: \n");
        gets_s(address, 80);
    }
    else if (choice == 3)
    {
        printf("Please enter the new phone number for this account: \n");
        gets_s(phonenumber, 80);
    }


    rewind(view);
    // Print user information using the line found in previous step
    ctr = 0;
    while (!feof(view))
    {
        strcpy(str, "\0");
        fgets(str, 256, view);
        if (!feof(view))
        {
            ctr++;
            /* print line which contains information */
            if (ctr == line_num)
            {
                fprintf(tempfile, "%d|%s|%s|%s|%s\n", 1, name2, address, phonenumber,amount);
            }
            else
            {
                fprintf(tempfile, "%s", str);
            }
        }
    }

    fclose(view);
    remove("Bankinfo.txt");
    fclose(tempfile);
    rename("temp.txt", "Bankinfo.txt");



    fclose(view);
};

// For the regular transcation in an account
void transcat() {
    // grab information from the file and print

    FILE* view, * tempfile;
    errno_t err, err1;
    char temp[512];
    int line_num = 0;
    int choice;

    err = fopen_s(&view, "Bankinfo.txt", "r");
    err1 = fopen_s(&tempfile, "temp.txt", "w");

    if (view == NULL)
    {
        printf("The file 'Textline.txt' was not opened\n");
    }
    else
    {
        printf("The file 'textline.txt' was opened\n");
    }


    // Asking user's name to find their information
    int i = 0;
    char name[100];
    printf("Enter your name:\n");
    gets_s(name, 80);

    //Search for Customer's name in a File
    while (fgets(temp, 512, view) != NULL) {
        if ((strstr(temp, name)) != NULL) {
            printf("A match found on line: %d\n", line_num);
            //printf("\n%s\n", temp);
            line_num++;
        }
    }

    rewind(view);

    // Print user information using the line found in previous step
    char str[100];
    char str2[100];
    int ctr = 0;
    while (!feof(view))
    {
        //strcpy(str, "\0");
        fgets(str, 256, view);
        if (!feof(view))
        {
            ctr++;
            /* print line which contains information */
            if (ctr == line_num)
            {
                strcpy(str2, str);
                printf("%s", str2);
            }
        }
    }

    char name2[100], address[100], phonenumber[100], acct1[10], amount[50];
    char* token = strtok(str2, "|");
    i = 0;
    // loop through the string to extract all other tokens
    while (token != NULL) {
        if (i == 0)
            strcpy(acct1, token);
        else if (i == 1)
            strcpy(name2, token);
        else if (i == 2)
            strcpy(address, token);
        else if (i == 3)
            strcpy(phonenumber, token);
        else if (i == 4)
            strcpy(amount, token);
        printf(" %s\n", token); //printing each token
        token = strtok(NULL, "|");
        i++;
    }

    char* ptr;
    double ret;

    ret = strtod(amount, &ptr);
    printf("The number(double) is %.2f\n", ret);



    double withdraw = 0.0, deposit = 0.0, x = 0.0;
    // Ask the user what they would like to modify
    printf("Please select withdraw or deposit: \n");
    printf("1. Withdraw\n");
    printf("2. Deposit\n");
    scanf_s("%d", &choice);
    getchar();

    if (choice == 1)
    {
        printf("Pleaes enter the amount you would like to wihdraw: \n");
        scanf_s("%lf", &withdraw);
        ret = ret - withdraw;
    }
    else if (choice == 2)
    {
        printf("Please enter the amount you would like to deposit: \n");
        scanf_s("%lf", &deposit);
        ret = ret + deposit;
    }

    getchar();

    snprintf(amount, 7, "%f", ret);

    rewind(view);
    // Print user information using the line found in previous step
    ctr = 0;
    while (!feof(view))
    {
        strcpy(str, "\0");
        fgets(str, 256, view);
        if (!feof(view))
        {
            ctr++;
            /* print line which contains information */
            if (ctr == line_num)
            {
                fprintf(tempfile, "%d|%s|%s|%s|%s\n", 1, name2, address, phonenumber, amount);
            }
            else
            {
                fprintf(tempfile, "%s", str);
            }
        }
    }

    fclose(view);
    remove("Bankinfo.txt");
    fclose(tempfile);
    rename("temp.txt", "Bankinfo.txt");



    fclose(view);
}

// To check information about a user
void checkinfo()
{
    FILE* view;
    errno_t err;
    char temp[512];
    int line_num = 0;

    err = fopen_s(&view, "Bankinfo.txt", "r");
    if (view == NULL)
    {
        printf("The file 'Textline.txt' was not opened\n");
    }
    else
    {
        printf("The file 'textline.txt' was opened\n");
    }

    int i = 0;
    char name[100];
    printf("Enter your name:\n");
    gets_s(name, 80);

    //Search for Customer's name in a File
    while (fgets(temp, 512, view) != NULL) {
        if ((strstr(temp, name)) != NULL) {
            printf("A match found on line: %d\n", line_num);
            //printf("\n%s\n", temp);
            line_num++;
        }
    }

    rewind(view);

    if (line_num == 0)
    {
        printf("User does not exist in the system\n");
        return;
    }
    // Print user information using the line found in previous step
    char str[100];
    int ctr = 0;
    while (!feof(view))
    {
        strcpy(str, "\0");
        fgets(str, 256, view);
        if (!feof(view))
        {
            ctr++;
            /* print line which contains information */
            if (ctr == line_num)
            {
                printf("%s", str);
            }
        }
    }

    fclose(view);
}

// To remove a user from an account
void removeacct() {

    FILE* view, * tempfile;
    errno_t err,err1;
    char temp[512];
    int line_num = 0;

    err = fopen_s(&view, "Bankinfo.txt", "r");
    err1 = fopen_s(&tempfile, "temp.txt", "w");
    if (view == NULL)
    {
        printf("The file 'Textline.txt' was not opened\n");
    }
    else
    {
        printf("The file 'textline.txt' was opened\n");
    }

    int i = 0;
    char name[100];
    printf("Enter your name:\n");
    gets_s(name, 80);

    //Search for Customer's name in a File
    while (fgets(temp, 512, view) != NULL) {
        if ((strstr(temp, name)) != NULL) {
            printf("A match found on line: %d\n", line_num);
            //printf("\n%s\n", temp);
        }
        line_num++;
    }

    rewind(view);

    // Print user information using the line found in previous step
    char str[100];
    int ctr = 0;
    while (!feof(view))
    {
        strcpy(str, "\0");
        fgets(str, 256, view);
        if (!feof(view))
        {
            ctr++;
            /* print line which contains information */
            if (ctr != line_num)
            {
                fprintf(tempfile,"%s", str);
            }
        }
    }

    fclose(view);
    remove("Bankinfo.txt");
    fclose(tempfile);
    rename("temp.txt", "Bankinfo.txt");
}

int main()
{
    struct Acctinfo acctinfo1;
    int choice = menu();
 
    switch (choice) {
    case 1:
        new_acct(); // create a new user acoount
        break;
    case 2:
        view_list(&acctinfo1);
        break;
    case 3:
        transcat();
        break;
    case 4:
        checkinfo(); // lookup user info
        break;
    case 5:
        removeacct(); // remove user account
        break;
    case 6:
        printf("Thank you for choosing our Banking System\n");
        break;
    }
    printf("Program Exited\n");

    return 0;
}

