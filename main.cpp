#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>

#define folderDirectory "C:/KittyCat/"

#define fileUserData "C:/KittyCat/UserData"

#define fileCatID "C:/KittyCat/CatID"
#define fileProductID "C:/KittyCat/ProductID"
#define fileEmployeeID "C:/KittyCat/EmployeeID"

#define fileCatData "C:/KittyCat/CatData"
#define fileProductData "C:/KittyCat/ProductData"
#define fileEmployeeData "C:/KittyCat/EmployeeData"

#define tempCatData "C:/KittyCat/tempCatData"
#define tempProductData "C:/KittyCat/tempProductData"
#define tempEmployeeData "C:/KittyCat/tempEmployeeData"

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

void create_folder()
{
    mkdir(folderDirectory);
}

// struct of cat
struct cat
{
    int id;
    char name[20];
    float weight;
    char type[20];
    int sex;         // 0 - female or 1 - male
    int vaccination; // 0 - not or 1 - yes
};
typedef struct cat CAT;
CAT x; //

struct product
{
    int id;
    char name[20];
    int quantity;
    char expiry[20];
    unsigned int price;
};
typedef struct product PDT;
PDT y;

struct employee
{
    int id;
    char name[20];
    int gender;
    char birthdate[20];
    char Address[100];
};
typedef struct employee EPE;
EPE z;

struct login // before the first use of `l`.
{
    char username[30];
    char password[20];
};

void UI_Menu();
void ManageEmployees();
void ManageCat();
void ManageProduct();
void update(int opt);
void searchFunc();

void ExitToMenu()
{
    char opt;
    printf("\n> Do you want to exit to the main menu ? (Y/N): ");
    fflush(stdin);
    scanf("%c", &opt);
    switch (opt)
    {
    case 'y':
    case 'Y':
        printf("\nExiting to the main menu...");
        delay(3);
        system("cls");
        UI_Menu();
        break;
    case 'n':
    case 'N':
        system("cls");
        break;
    default:
        printf("\nInvalid option!");
        ExitToMenu();
        break;
    }
}

void SubId(int opt)
{
    //! opt 1 - cat, opt 2 - product, 3 - employee
    int fileID;
    FILE *fptr;
    fptr = fopen(opt == 1 ? fileCatID : opt == 2 ? fileProductID
                                                 : fileEmployeeID,
                 "rb");
    fscanf(fptr, "%d", &fileID);
    fileID -= 1;
    fclose(fptr);
    fptr = fopen(opt == 1 ? fileCatID : opt == 2 ? fileProductID
                                                 : fileEmployeeID,
                 "wb");
    fprintf(fptr, "%d", fileID);
    fclose(fptr);
}

int GenerateId(int opt)
{
    //! opt 1 - cat, opt 2 - product, 3 - employee
    int fileID;
    FILE *fptr;
    if ((fptr = fopen(opt == 1 ? fileCatID : opt == 2 ? fileProductID
                                                      : fileEmployeeID,
                      "rb")) == NULL)
    {
        int id = 1;
        fptr = fopen(opt == 1 ? fileCatID : opt == 2 ? fileProductID
                                                     : fileEmployeeID,
                     "wb");
        fprintf(fptr, "%d", id);
        fclose(fptr);
        return 1;
    }
    else
    {
        fscanf(fptr, "%d", &fileID);
        fileID += 1;
        fclose(fptr);
        fptr = fopen(opt == 1 ? fileCatID : opt == 2 ? fileProductID
                                                     : fileEmployeeID,
                     "wb");
        fprintf(fptr, "%d", fileID);
        fclose(fptr);
        return fileID;
    }
}

void login()
{
    char username[30], password[20];
    FILE *log;

    log = fopen(fileUserData, "rb");
    if (log == NULL)
    {
        fputs("Error at opening File!", stderr);
        getch();
        exit(1);
    }
    struct login l;
    puts("------------------------------------------");
    printf("          Login to Shop-meomeo\n");
    puts("------------------------------------------");
    printf("\n> Username: ");
    scanf("%s", username);
    printf("> Password: ");
    scanf("%s", password);
    while (fread(&l, sizeof(l), 1, log))
    {
        if (strcmp(username, l.username) == 0 && strcmp(password, l.password) == 0)

        {
            printf("\nLogin successfully!");
            printf("\nPress any key to continue to the main menu...");
            getch();
            system("cls");
            UI_Menu();
        }
        else
        {
            printf("\nIncorrect login details! Please re-enter the correct credentials!\n");
            getch();
            system("cls");
            login();
        }
    }

    fclose(log);

    return;
}

void registration()
{
    FILE *log;

    log = fopen(fileUserData, "w");
    if (log == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }

    struct login l;
    puts("------------------------------------------");
    printf("      Registration for Shop-meomeo\n");
    puts("------------------------------------------");
    printf("\nFill in these information in order to register new account!");
    printf("\n> Enter your username: ");
    scanf("%s", l.username);
    printf("> Enter your password: ");
    scanf("%s", l.password);

    fwrite(&l, sizeof(l), 1, log);
    fclose(log);

    printf("\nRegisting new account successfully!\n");
    printf("Press any key to continue to the login menu!");
    getch();
    system("CLS");
    login();
}

void userAuthMenu()
{
    int choice;
    puts("------------------------------------------");
    printf("          Welcome to Shop-meomeo\n");
    puts("------------------------------------------");
    printf("\n1. Login");
    printf("\n2. Register");
    printf("\n3. Exit");
    printf("\n\n> Enter your choice: ");
    scanf("%d", &choice);
    while (choice < 1 || choice > 3)
    {
        printf("Invalid choice, please try again:  ");
        scanf("%d", &choice);
    }
    system("cls");
    if (choice == 1)
    {
        login();
    }
    else if (choice == 2)
    {
        registration();
    }
    else if (choice == 3)
    {
        exit(0);
    }
}

void CreateProduct()
{
    system("cls");
    char check;
    int productId = GenerateId(2);
    // char dir[30] = fileProductData;
    FILE *fptr;
    if ((fptr = fopen(fileProductData, "ab")) == NULL)
    {
        printf("Error opening/ creating file!\n");
        exit(0);
    }
    puts("------------------------------------------");
    printf("            Add a new product\n");
    puts("------------------------------------------");
    // input data of cat
    printf("\n> Input product's name: ");
    fflush(stdin);
    gets(y.name);
    printf("> Input the price of your product: ");
    fflush(stdin);
    scanf("%u", &y.price);
    while (y.price <= 0)
    {
        printf("\tInvalid value of price, please re-input it: ");
        scanf("%u", &y.price);
    }
    printf("> Input the quantity of your product: ");
    fflush(stdin);
    scanf("%d", &y.quantity);
    while (y.quantity < 0)
    {
        printf("\tInvalid value of quantity, please re-input it: ");
        scanf("%d", &y.quantity);
    }
    fflush(stdin);
    printf("> Input the expire date of your product: ");
    gets(y.expiry);
    y.id = productId;
    fflush(stdin);
    // output data of product you entered
    system("cls");
    printf("\nYour information of the product that you have entered");
    printf("\n*****************************************************");
    printf("\n- Product's ID: %d", y.id);
    printf("\n- Product's name: %s", y.name);
    printf("\n- Product's price: %d VND", y.price);
    printf("\n- Product's quantity: %d", y.quantity);
    printf("\n- Product's expire date: %s", y.expiry);
    printf("\n*****************************************************");
    printf("\n\n> Do you want to save this product information? (Y/N): ");
SAVE:
    while (1)
    {
        scanf("%c", &check);
        switch (check)
        {
        case 'y':
        case 'Y':
            fwrite(&y, sizeof(y), 1, fptr);
            printf("\n- Product's information is saved!");
            fclose(fptr);
            break;
        case 'n':
        case 'N':
            printf("\n- Product's information isn't being saved!");
            SubId(2);
            break;
        default:
            printf("\nInvalid option, re-input your choice: ");
            scanf("%c", &check);
            goto SAVE;
            break;
        }
        break;
    }
    fflush(stdin);
    printf("\n> Do you want to re-input a new product? (Y/N): ");
    char reInput;
    while (1)
    {
        scanf("%c", &reInput);
        switch (reInput)
        {
        case 'y':
        case 'Y':
            system("cls");
            CreateProduct();
            break;
        case 'n':
        case 'N':
            break;
        default:
            printf("\nInvalid option, re-input your choice: ");
            scanf("%c", &reInput);
            break;
        }
        break;
    }
}

void CreateCat()
{
    system("cls");
    char check;
    int CatId = GenerateId(1);
    // char dir[20] = fileCatData;
    FILE *fptr;
    if ((fptr = fopen(fileCatData, "ab")) == NULL)
    {
        printf("Error opening/ creating file!!\n");
        exit(0);
    }
    puts("------------------------------------------");
    printf("          Add a new cat\n");
    puts("------------------------------------------");
    // input data of cat
    printf("\n> Input cat's name: ");
    fflush(stdin);
    gets(x.name);
    printf("> Input the weight of your cat: ");
    fflush(stdin);
    scanf("%f", &x.weight);
    fflush(stdin);
    printf("> Input the type of your cat: ");
    gets(x.type);
    fflush(stdin);
    printf("> Input the sex of your cat (0 - female/ 1 - male): ");
    scanf("%d", &x.sex);
    while (x.sex != 0 && x.sex != 1)
    {
        printf("\tInvalid option, re-input the sex of your cat: ");
        scanf("%d", &x.sex);
    }
    printf("> Input the vaccination status of your cat (1 - yes/ 0 - no): ");
    scanf("%d", &x.vaccination);
    while (x.vaccination != 0 && x.vaccination != 1)
    {
        printf("\tInvalid option, re-input the vaccination status of your cat: ");
        scanf("%d", &x.vaccination);
    }
    x.id = CatId;
    // output data of cat you entered
    system("cls");
    printf("\nThe information of the cat that you have entered");
    printf("\n************************************************");
    printf("\n- Cat ID %d", x.id);
    printf("\n- Cat's name: %s", x.name);
    printf("\n- Cat's weight: %.1f", x.weight);
    printf("\n- Cat's type: %s", x.type);
    if (x.sex)
    {
        printf("\n- The sex of your cat: Male");
    }
    else
    {
        printf("\n- The sex of your cat: Female");
    }
    if (x.vaccination)
    {
        printf("\n- Your cat is vaccinated");
    }
    else
    {
        printf("\n- Your cat isn't vaccinated");
    }
    fflush(stdin);
    printf("\n************************************************");
    printf("\n\n> Do you want to save this cat information? (Y/N): ");
SAVE:
    while (1)
    {
        scanf("%c", &check);
        switch (check)
        {
        case 'y':
        case 'Y':
            fwrite(&x, sizeof(x), 1, fptr);
            printf("\n- Cat's information is saved!");
            fclose(fptr);
            break;
        case 'n':
        case 'N':
            printf("\n- Cat's information isn't being saved!");
            SubId(1);
            break;
        default:
            printf("\nInvalid option, re-input your option: ");
            scanf("%c", &check);
            goto SAVE;
            break;
        }
        break;
    }
    fflush(stdin);
    printf("\n> Do you want to re-input a new cat? (Y/N): ");
    char reInput;
REINPUT:
    while (1)
    {
        scanf("%c", &reInput);
        switch (reInput)
        {
        case 'y':
        case 'Y':
            system("cls");
            CreateCat();
            break;
        case 'n':
        case 'N':
            break;
        default:
            printf("\nInvalid option, re-input your choice: ");
            scanf("%c", &reInput);
            goto REINPUT;
            break;
        }
        break;
    }
}

void CreateEmployee()
{
    system("cls");
    char check;
    int employeeId = GenerateId(3);
    FILE *fptr;
    if ((fptr = fopen(fileEmployeeData, "ab")) == NULL)
    {
        printf("\nError opening/ creating file!\n");
        exit(0);
    }
    puts("------------------------------------------");
    printf("           Add a new employee\n");
    puts("------------------------------------------");
    // input data of employee
    printf("\n> Input employee's name: ");
    fflush(stdin);
    gets(z.name);
    fflush(stdin);
    printf("> Input the gender of your employee (0 - female/ 1 - male): ");
    scanf("%d", &z.gender);
    while (z.gender != 0 && z.gender != 1)
    {
        printf("\tInvalid option, re-input the gender of your employee: ");
        scanf("%d", &z.gender);
    }
    printf("> Input the birthdate of your employee (dd/mm/yy): ");
    fflush(stdin);
    gets(z.birthdate);
    printf("> Input the address of your employee: ");
    gets(z.Address);
    z.id = employeeId;
    // output data of employee you entered
    system("cls");
    printf("\nYour information of the employee that you have entered");
    printf("\n******************************************************");
    printf("\n- Employee's ID %d", z.id);
    printf("\n- Employee's name: %s", z.name);
    if (z.gender)
    {
        printf("\n- The gender of your employee: Male");
    }
    else
    {
        printf("\n- The gender of your employee: Female");
    }
    printf("\n- Employee's birthdate: %s", z.birthdate);
    printf("\n- Employee's address: %s", z.Address);
    printf("\n******************************************************");
    printf("\n\n> Do you want to save this employee information? (Y/N): ");
SAVE:
    while (1)
    {
        fflush(stdin);
        scanf("%c", &check);
        switch (check)
        {
        case 'y':
        case 'Y':
            fwrite(&z, sizeof(z), 1, fptr);
            printf("\n- Employee's information is saved!");
            fclose(fptr);
            break;
        case 'n':
        case 'N':
            printf("\n- Employee's information isn't being saved!");
            SubId(3);
            break;
        default:
            printf("\nInvalid option, re-input your choice: ");
            scanf("%c", &check);
            goto SAVE;
            break;
        }
        break;
    }
    fflush(stdin);
    printf("\n> Do you want to re-input a new employee? (Y/N): ");
    char reInput;
    while (1)
    {
        scanf("%c", &reInput);
        switch (reInput)
        {
        case 'y':
        case 'Y':
            system("cls");
            CreateEmployee();
            break;
        case 'n':
        case 'N':
            ManageEmployees();
            break;
        default:
            printf("\nInvalid option, re-input your choice: ");
            scanf("%c", &reInput);
            break;
        }
        break;
    }
}

int checkEmployeeAvailable(int employeeId)
{
    // check if the Employee ID is available or not
    FILE *fptr;
    char dir[30] = fileEmployeeData;
    fptr = fopen(dir, "rb");
    while (!feof(fptr))
    {
        fread(&z, sizeof(z), 1, fptr);
        if (employeeId == z.id)
        {
            fclose(fptr);
            return 1;
        }
        else
        {
            fclose(fptr);
            return 0;
        }
    }
}

void searchEmployees()
{
    FILE *fptr;
    char dir[30] = fileEmployeeData;
    int employeeId, searchID;
    if ((fptr = fopen(dir, "rb")) == NULL)
    {
        printf("File not found!");
    }
    fflush(stdin);
    printf("> Enter the Employee ID to search: ");
    scanf("%d", &searchID);
    if (checkEmployeeAvailable(employeeId) == 0)
    {
        printf("\tEmployee ID is invalid! Employee not found!");
    }
    while (fread(&z, sizeof(z), 1, fptr) == 1)
    {
        if (searchID == z.id)
        {
            system("cls");
            printf("\n\t    Information of %s", z.name);
            printf("\n*********************************************");
            printf("\n- Employee's ID: %d", z.id);
            printf("\n- Employee's name: %s", z.name);
            if (z.gender == 1)
                printf("\n- Gender: Male");
            else
                printf("\n- Gender: Female");
            printf("\n- Employee's birthdate: %s", z.birthdate);
            printf("\n- Employee's address: %s", z.Address);
        }
    }
    char reSearch;
    printf("\n\n> Do you want to search for another employee? (Y/N): ");
REINPUTEMPLOYEES:
    scanf("%s", &reSearch);
    switch (reSearch)
    {
    case 'y':
    case 'Y':
        system("cls");
        searchEmployees();
        break;
    case 'n':
    case 'N':
        delay(3);
        system("cls");
        searchFunc();
        break;
    default:
        printf("\tInvalid option, please reinput your choice: ");
        goto REINPUTEMPLOYEES;
        break;
    }
    fclose(fptr);
}

int checkCatAvailable(int catID)
{
    // check if the Kitty ID is available or not
    FILE *fptr;
    char dir[30] = fileCatData;
    fptr = fopen(dir, "rb");
    while (!feof(fptr))
    {
        fread(&x, sizeof(x), 1, fptr);
        if (catID == x.id)
        {
            fclose(fptr);
            return 1;
        }
        else
        {
            fclose(fptr);
            return 0;
        }
    }
}

void searchCats()
{
    FILE *fptr;
    char dir[30] = fileCatData;
    int catID, searchID;
    if ((fptr = fopen(dir, "rb")) == NULL)
    {
        printf("File not found!");
    }
    fflush(stdin);
    printf("> Enter the Cat ID to search: ");
    scanf("%d", &searchID);
    if (checkCatAvailable(catID) == 0)
    {
        printf("\tCat ID is invalid! Cat not found!");
    }
    while (fread(&x, sizeof(x), 1, fptr) == 1)
    {
        if (searchID == x.id)
        {
            system("cls");
            printf("\n\t Kitten %s say hello!", x.name);
            printf("\n*********************************************");
            printf("\n- Cat's ID: %d", x.id);
            printf("\n- Cat's name: %s", x.name);
            printf("\n- Cat's weight: %.1f", x.weight);
            printf("\n- Cat's type: %s", x.type);
            if (x.sex == 1)
                printf("\n- Sex: Male");
            else
                printf("\n- Sex: Female");
            if (x.vaccination == 1)
                printf("\n- Vaccinate status: Vaccinated");
            else
                printf("\n- Vaccinate status: Not vaccinated");
        }
    }
    char reSearch;
    printf("\n\n> Do you want to search for another cat? (Y/N): ");
REINPUTCAT:
    scanf("%s", &reSearch);
    switch (reSearch)
    {
    case 'y':
    case 'Y':
        system("cls");
        searchCats();
        break;
    case 'n':
    case 'N':
        delay(3);
        system("cls");
        searchFunc();
        break;
    default:
        printf("\tInvalid option, please reinput your choice: ");
        goto REINPUTCAT;
        break;
    }
    fclose(fptr);
}

int checkProductAvailable(int productID)
{
    // check if the Product ID is available or not
    FILE *fptr;
    char dir[30] = fileProductData;
    fptr = fopen(dir, "rb");
    while (!feof(fptr))
    {
        fread(&y, sizeof(y), 1, fptr);
        if (productID == y.id)
        {
            fclose(fptr);
            return 1;
        }
        else
        {
            fclose(fptr);
            return 0;
        }
    }
}

void searchProducts()
{
    FILE *fptr;
    char dir[30] = fileProductData;
    int productID, searchID;
    if ((fptr = fopen(dir, "rb")) == NULL)
    {
        printf("File not found!");
    }
    fflush(stdin);
    printf("> Enter the Product ID to search: ");
    scanf("%d", &searchID);
    if (checkProductAvailable(productID) == 0)
    {
        printf("\tProduct ID is invalid! Product not found!");
    }
    while (fread(&y, sizeof(y), 1, fptr) == 1)
    {
        if (searchID == y.id)
        {
            system("cls");
            printf("\n    Information of the product you search");
            printf("\n*********************************************");
            printf("\n- Product's ID: %d", y.id);
            printf("\n- Product's name: %s", y.name);
            printf("\n- Product's price: %dVND", y.price);
            printf("\n- Product's quantity: %d", y.quantity);
            printf("\n- Product's expire date: %s", y.expiry);
        }
    }
    char reSearch;
    printf("\n\n> Do you want to search for another product? (Y/N): ");
REINPUTPRODUCT:
    scanf("%s", &reSearch);
    switch (reSearch)
    {
    case 'y':
    case 'Y':
        system("cls");
        searchProducts();
        break;
    case 'n':
    case 'N':
        delay(3);
        system("cls");
        searchFunc();
        break;
    default:
        printf("\tInvalid option, please reinput your choice: ");
        goto REINPUTPRODUCT;
        break;
    }
    fclose(fptr);
}

void searchFunc()
{
    int searchChoice;
    puts("------------------------------------------");
    printf("       What do you want to search?\n");
    puts("------------------------------------------");
    printf("\n1. Search Employees");
    printf("\n2. Search Cats");
    printf("\n3. Search Products");
    printf("\n4. Exit to the main menu");
    printf("\n\n> Input your choice: ");
    scanf("%d", &searchChoice);
    switch (searchChoice)
    {
    case 1:
        searchEmployees();
        break;
    case 2:
        searchCats();
        break;
    case 3:
        searchProducts();
        break;
    case 4:
        UI_Menu();
        break;
    default:
        printf("\nNo choices were made! Return to the search menu\n");
        searchFunc();
        break;
    }
}

void ShowData(int opt)
{
    // ! 1 - cat, 2 - products, 3 - employees
    FILE *fptr;
    if ((fptr = fopen(opt == 1 ? fileCatData : opt == 2 ? fileProductData
                                                        : fileEmployeeData,
                      "rb")) == NULL)
    {
        printf("File not found!");
    }
    if (opt == 2)
    {
        printf("\n       Information of every products");
        printf("\n*********************************************\n");
        puts("ID \tName\t\t\tPrice\t\tQuantity\tExpire date");
        while (fread(&y, sizeof(y), 1, fptr) == 1)
        {
            printf("%d\t", y.id);
            printf("%s\t\t\t", y.name);
            printf("%dVND\t\t", y.price);
            printf("%d\t\t", y.quantity);
            printf("%s\t", y.expiry);
            printf("\n");
        }
    }
    else if (opt == 1)
    {
        printf("\n         Information of every cats");
        printf("\n*********************************************\n");
        puts("ID \tName\t\t\tWeight\t\tType\t\tSex\t\tVaccination");
        while (fread(&x, sizeof(x), 1, fptr) == 1)
        {
            printf("%d\t", x.id);
            printf("%s\t\t\t", x.name);
            printf("%.1f\t\t", x.weight);
            printf("%s\t\t", x.type);
            x.sex ? printf("Male") : printf("Female");
            printf("\t\t");
            x.vaccination ? printf("Yes") : printf("No");
            printf("\n");
        }
    }
    else if (opt == 3)
    {
        printf("\n       Information of every employees");
        printf("\n*********************************************\n");
        puts("ID \tName\t\t\tGender\t\tBirthdate\t\tAddress\t\t");
        while (fread(&z, sizeof(z), 1, fptr) == 1)
        {
            printf("%d\t", z.id);
            printf("%s\t\t\t", z.name);
            z.gender ? printf("Male\t\t") : printf("Female\t\t");
            printf("%s\t\t", z.birthdate);
            printf("%s\t\t", z.Address);
            printf("\n");
        }
    }
    printf("\n\n\n*********************************************\n");
    printf("\nPress any key to continue: ");
    getch();
    fclose(fptr);
}

void deleteAllEmployee()
{
    system("cls");
    char opt2;
    printf("\n> Are you sure to delete all the employees? (Y/N): ");
    HEHE:
    scanf("%s", &opt2);
    switch (opt2)
    {
    case 'y':
    case 'Y':
        if (remove(fileEmployeeData) == 0)
        {
            printf("\n- The file is deleted successfully.");
        }
        else
        {
            printf("\n- The file isn't deleted.");
        }
        getch();
        system("cls");
        printf("\nReturn to the main menu...");
        printf("\nPress any key to exit");
        getch();
        UI_Menu();
        break;
    case 'n':
    case 'N':
        printf("\nReturn to the main menu...");
        printf("\nPress any key to exit");
        printf("\n");
        getch();
        system("cls");
        UI_Menu();
        break;
    default:
        printf("\nInvalid option, re-input your choice: ");
        goto HEHE;
        break;
    }
}

void deleteAllProducts()
{
    system("cls");
    char opt2;
    printf("\n> Are you sure to delete all the products? (Y/N): ");
    HOHO:
    scanf("%s", &opt2);
    switch (opt2)
    {
    case 'y':
    case 'Y':
        if (remove(fileProductData) == 0)
        {
            printf("\n- The file is deleted successfully.");
        }
        else
        {
            printf("\n- The file isn't deleted");
        }
        getch();
        system("cls");
        printf("\nReturn to the main menu...");
        printf("\nPress any key to exit");
        getch();
        UI_Menu();
        break;
    case 'n':
    case 'N':
        printf("\nReturn to the main menu...");
        printf("\nPress any key to exit");
        printf("\n");
        getch();
        system("cls");
        UI_Menu();
        break;
    default:
        printf("\nInvalid option, re-input your choice: ");
        goto HOHO;
        break;   
    }
}

void deleteAllCats()
{
    system("cls");
    char opt2;
    printf("\n> Are you sure to delete all the cats? (Y/N): ");
    HIHI:
    scanf("%s", &opt2);
    switch (opt2)
    {
    case 'y':
    case 'Y':
        if (remove(fileCatData) == 0)
        {
            printf("\n- The file is deleted successfully.");
        }
        else
        {
            printf("\n- The file isn't deleted.");
        }
        getch();
        system("cls");
        printf("\nReturn to the main menu...");
        printf("\nPress any key to exit");
        getch();
        UI_Menu();
        break;
    case 'n':
    case 'N':
        printf("\nReturn to the main menu...");
        printf("\nPress any key to exit");
        printf("\n");
        getch();
        system("cls");
        UI_Menu();
        break;
    default:
        printf("\nInvalid option, re-input your choice: ");
        goto HIHI;
        break;   
    }
}

void deleteOneEmployee()
{
    int ID;
    printf("\nEnter your id :");
    scanf("%d", &ID);
    FILE *fptr;
    FILE *fptrTemp;
    fptr = fopen(fileEmployeeData, "rb");
    fptrTemp = fopen(tempEmployeeData, "wb");
    if (fptr == NULL)
    {
        printf("\nError opening/creating file!!");
        fclose(fptr);
        exit(0);
    }
    else
        while (fread(&z, sizeof(z), 1, fptr) == 1)
        {
            if (ID != z.id)
            {
                fwrite(&z, sizeof(z), 1, fptrTemp);
            }
        }
    fclose(fptr);
    if (remove(fileEmployeeData) == 0)
    {
        system("cls");
        printf("\nDeleted successfully!");
        getch();
        fflush(stdin);
        fclose(fptrTemp);
        rename(tempEmployeeData, fileEmployeeData);
    }
    else
    {
        printf("\nUnable to delete the file");
    }
}

void deleteOneCat()
{
    int ID;
    printf("\nEnter your id :");
    scanf("%d", &ID);
    FILE *fptr;
    FILE *fptrTemp;
    fptr = fopen(fileCatData, "rb");
    fptrTemp = fopen(tempCatData, "wb");
    if (fptr == NULL)
    {
        printf("\nError opening/creating file!!");
        fclose(fptr);
        exit(0);
    }
    else
        while (fread(&x, sizeof(x), 1, fptr) == 1)
        {
            if (ID != x.id)
            {
                fwrite(&x, sizeof(x), 1, fptrTemp);
            }
        }
    fclose(fptr);
    if (remove(fileCatData) == 0)
    {
        system("cls");
        printf("\nDeleted successfully!");
        getch();
        fflush(stdin);
        fclose(fptrTemp);
        rename(tempCatData, fileCatData);
    }
    else
    {
        printf("\nUnable to delete the file");
    }
}

void deleteOneProduct()
{
    int ID;
    printf("\nEnter your id :");
    scanf("%d", &ID);
    FILE *fptr;
    FILE *fptrTemp;
    fptr = fopen(fileProductData, "rb");
    fptrTemp = fopen(tempProductData, "wb");
    if (fptr == NULL)
    {
        printf("\nError opening/creating file!!");
        fclose(fptr);
        exit(0);
    }
    else
        while (fread(&y, sizeof(y), 1, fptr) == 1)
        {
            if (ID != y.id)
            {
                fwrite(&y, sizeof(y), 1, fptrTemp);
            }
        }
    fclose(fptr);
    if (remove(fileProductData) == 0)
    {
        system("cls");
        printf("\nDeleted successfully!");
        getch();
        fflush(stdin);
        fclose(fptrTemp);
        rename(tempProductData, fileProductData);
    }
    else
    {
        printf("\nUnable to delete the file");
    }
}

void deleteAllMenu()
{
    system("cls");
    int u;
    puts("------------------------------------------");
    printf("           Wiping out all data\n");
    puts("------------------------------------------");
    puts("\n1. Delete all Cats\n2. Delete all Products\n3. Delete all Employee\n4. Return to the main menu");
    printf("\n> Select your choice:");
    scanf("%d", &u);
    while (u < 1 || u > 4)
    {
        printf("\tInvalid choice! Please re-enter a valid choice: ");
        scanf("%d", &u);
    }
    if (u == 1)
    {
        deleteAllCats();
        exit(0);
    }
    else if (u == 2)
    {
        deleteAllProducts();
        exit(0);
    }
    else if (u == 3)
    {
        deleteAllEmployee();
        exit(0);
    }
    else if (u == 4)
    {
        system("cls");
        printf("Return to the main menu...");
        getch();
        UI_Menu;
    }
}

void ManageCat()
{
    puts("------------------------------------------");
    printf("             Cats Managements\n");
    puts("------------------------------------------");
    puts("\n1. Show all existing cats\n2. Add new cat\n3. Update specific cat's information\n4. Delete specific cat\n5. Exit to the main menu\n");
    printf("> Select your choice: ");
    int u;
    scanf("%d", &u);
    while (u < 1 || u > 5)
    {
        printf("\tInvalid choice! Please re-enter another one: ");
        scanf("%d", &u);
    }
    system("cls");
    switch (u)
    {
    case 1:
        ShowData(1);
        break;
    case 2:
        CreateCat();
        break;
    case 3:
        update(1);
        break;
    case 4:
        deleteOneCat();
        break;
    case 5:
        printf("\nExiting to the main menu...");
        delay(3);
        UI_Menu();
        break;
    }
}

void ManageProduct()
{
    puts("------------------------------------------");
    printf("          Products Managements\n");
    puts("------------------------------------------");
    puts("\n1. Show all existing products\n2. Add new product\n3. Update specific product's information\n4. Delete specific product\n5. Exit to Menu\n");
    printf("> Select your choice:  ");
    int u;
    scanf("%d", &u);
    while (u < 1 || u > 5)
    {
        printf("\tInvalid choice! Please re-enter another one: ");
        scanf("%d", &u);
    }
    system("cls");
    switch (u)
    {
    case 1:
        ShowData(2);
        break;
    case 2:
        CreateProduct();
        break;
    case 3:
        update(2);
        break;
    case 4:
        deleteOneProduct();
        break;
    case 5:
        printf("\nExiting to the main menu...");
        delay(3);
        UI_Menu();
        break;
    }
}

void ManageEmployees()
{
    puts("------------------------------------------");
    printf("          Employees Managements\n");
    puts("------------------------------------------");
    puts("\n1. Show all existing employees\n2. Add new employee\n3. Update specific employee's information\n4. Delete specific employee\n5. Exit to Menu\n");
    printf("> Select your choice:  ");
    int u;
    scanf("%d", &u);
    while (u < 1 || u > 5)
    {
        printf("\tInvalid choice, Please enter a valid choice\n");
        scanf("%d", &u);
    }
    system("cls");
    switch (u)
    {
    case 1:
        ShowData(3);
        break;
    case 2:
        CreateEmployee();
        break;
    case 3:
        update(3);
        break;
    case 4:
        deleteOneEmployee();
        break;
    case 5:
        printf("\nExiting to the main menu...");
        delay(3);
        UI_Menu();
        break;
    }
}

void UI_Menu()
{
    // demo UI
    while (1)
    {
        system("cls");
        puts("------------------------------------------");
        printf("          Welcome to Shop-meomeo\n");
        puts("------------------------------------------");
        puts("\n1. Manage Cats\n2. Manage Products\n3. Manage Employees\n4. Search\n5. Wipe out all data\n6. Exit");
        printf("\n> Select your choice: ");
        int u;
        scanf("%d", &u);
        while (u < 1 || u > 6)
        {
            printf("Invalid choice! Please try again: ");
            scanf("%d", &u);
        }
        system("cls");
        if (u == 1)
        {
            ManageCat();
        }
        else if (u == 2)
        {
            ManageProduct();
        }
        else if (u == 3)
        {
            ManageEmployees();
        }
        else if (u == 4)
        {
            searchFunc();
        }
        else if (u == 5)
        {
            deleteAllMenu();
        }
        else if (u == 6)
        {
            exit(0);
        }
    }
}

void CheckShowData(int opt)
{
    //! 1 - cat, 2 - product, 3 - employees
    printf("\n> Do you want to show data?:  ");
    fflush(stdin);
    char check;
    scanf("%c", &check);
    switch (check)
    {
    case 'y':
    case 'Y':
        ShowData(opt);
        break;
    case 'n':
    case 'N':
        break;
    default:
        printf("\tInvalid option!");
        CheckShowData(opt);
        break;
    }
}

void update(int opt)
{
    //! 1 - cat, 2 - product, 3 - employee
    int id;
    int isHave = 0;
    puts("------------------------------------------");
    if (opt == 1)
    {
        puts("    Update cat's information by ID");
    }
    else if (opt == 2)
    {
        puts("  Update product's information by ID");
    }
    else if (opt == 3)
    {
        puts("  Update employee's information by ID");
    }
    puts("------------------------------------------");
    // show cat name here
    CheckShowData(opt);
    FILE *file = fopen(opt == 1 ? fileCatData : opt == 2 ? fileProductData
                                                         : fileEmployeeData,
                       "rb+");
    if (file == NULL)
    {
        printf("\nError opening file!");
        printf("\nExiting to the main menu...");
        delay(3);
        UI_Menu();
    }
    printf("\n> Enter the valid ID: ");
    scanf("%d", &id);
    if (opt == 1)
    {
        while (fread(&x, sizeof(x), 1, file) == 1)
        {
            if (id == x.id)
            {
                printf("\n\t Kitten %s say hello!", x.name);
                printf("\n*********************************************");
                printf("\n- Cat's ID: %d", x.id);
                printf("\n- Cat's name: %s", x.name);
                printf("\n- Cat's weight: %.1f", x.weight);
                printf("\n- Cat's type: %s", x.type);
                if (x.sex == 1)
                    printf("\n- Sex: Male");
                else
                    printf("\n- Sex: Female");
                if (x.vaccination == 1)
                    printf("\n- Vaccinate status: Vaccinated");
                else
                    printf("\n- Vaccinate status: Not vaccinated");
                isHave++;
            }
        }
    }
    else if (opt == 2)
    {
        while (fread(&y, sizeof(y), 1, file) == 1)
        {
            if (id == y.id)
            {
                printf("\n    Information of the product you search");
                printf("\n*********************************************");
                printf("\n- Product's ID: %d", y.id);
                printf("\n- Product's name: %s", y.name);
                printf("\n- Product's price: %dVND", y.price);
                printf("\n- Product's quantity: %d", y.quantity);
                printf("\n- Product's expire date: %s", y.expiry);
                isHave++;
            }
        }
    }
    else if (opt == 3)
    {
        while (fread(&z, sizeof(z), 1, file) == 1)
        {
            if (id == z.id)
            {
                printf("\n\t    Information of %s", z.name);
                printf("\n*********************************************");
                printf("\n- Employee's ID: %d", z.id);
                printf("\n- Employee's name: %s", z.name);
                if (z.gender == 1)
                    printf("\n- Gender: Male");
                else
                    printf("\n- Gender: Female");
                printf("\n- Employee's birthdate: %s", z.birthdate);
                printf("\n- Employee's address: %s", z.Address);
                isHave++;
            }
        }
    }
    fclose(file);
    if (!isHave)
    {
        printf("\n- Information matched with the entered ID not found!");
        ExitToMenu();
        update(opt);
    }
    else
    {
        CAT Data1;
        PDT Data2;
        EPE Data3;
        if (opt == 1)
        {
            printf("\n       Update your cat's information");
            printf("\n********************************************");
            fflush(stdin);
            printf("\n> Input cat's name: ");
            gets(Data1.name);
            printf("> Input the weight of your cat: ");
            fflush(stdin);
            scanf("%f", &Data1.weight);
            fflush(stdin);
            printf("> Input the type of your cat: ");
            gets(Data1.type);
            fflush(stdin);
            printf("> Input the sex of your cat (0 - female/ 1 - male): ");
            scanf("%d", &Data1.sex);
            while (Data1.sex != 0 && Data1.sex != 1)
            {
                printf("\tInvalid option, re-input the sex of your cat: ");
                scanf("%d", &Data1.sex);
            }
            printf("> Input the vaccination of your kitty (1 - yes/ 0 - not): ");
            scanf("%d", &Data1.vaccination);
            while (Data1.vaccination != 0 && Data1.vaccination != 1)
            {
                printf("\tInvalid option, re-input the vaccination of your cat: ");
                scanf("%d", &Data1.vaccination);
            }
            Data1.id = id;
        }
        else if (opt == 2)
        {
            printf("\n     Update your products's information");
            printf("\n********************************************");
            fflush(stdin);
            printf("\n> Input product's name: ");
            gets(Data2.name);
            printf("> Input the price of your product: ");
            fflush(stdin);
            scanf("%u", &Data2.price);
            while (Data2.price <= 0)
            {
                printf("\tInvalid value of price, please re-input it: ");
                scanf("%u", &Data2.price);
            }
            printf("> Input the quantity of your product: ");
            fflush(stdin);
            scanf("%d", &Data2.quantity);
            while (Data2.quantity < 0)
            {
                printf("\tInvalid value of quantity, please re-input it: ");
                scanf("%d", &Data2.quantity);
            }
            fflush(stdin);
            printf("> Input the expire date of your product: ");
            gets(Data2.expiry);
            Data2.id = id;
        }
        else if (opt == 3)
        {
            printf("\n    Update your employee's information");
            printf("\n********************************************");
            printf("\n> Input employee's name: ");
            fflush(stdin);
            gets(Data3.name);
            fflush(stdin);
            printf("> Input the gender of your employee (0 - female/ 1 - male): ");
            scanf("%d", &Data3.gender);
            while (Data3.gender != 0 && Data3.gender != 1)
            {
                printf("\tInvalid option, re-input the gender of your employee: ");
                scanf("%d", &Data3.gender);
            }
            printf("> Input the birthdate of your employee (dd/mm/yy): ");
            fflush(stdin);
            gets(Data3.birthdate);
            printf("> Input the address of your employee: ");
            gets(Data3.Address);
            Data3.id = id;
        }
        FILE *file = fopen(opt == 1 ? fileCatData : opt == 2 ? fileProductData
                                                             : fileEmployeeData,
                           "rb+");
        FILE *fileTemp = fopen(opt == 1 ? tempCatData : opt == 2 ? tempProductData
                                                                 : tempEmployeeData,
                               "wb");
        if (opt == 1)
        {
            while (fread(&x, sizeof(x), 1, file) == 1)
            {
                if (id != x.id)
                {
                    fwrite(&x, sizeof(x), 1, fileTemp);
                }
                else
                {
                    fwrite(&Data1, sizeof(Data1), 1, fileTemp);
                }
            }
        }
        else if (opt == 2)
        {
            while (fread(&y, sizeof(y), 1, file) == 1)
            {
                if (id != y.id)
                {
                    fwrite(&y, sizeof(y), 1, fileTemp);
                }
                else
                {
                    fwrite(&Data2, sizeof(Data2), 1, fileTemp);
                }
            }
        }
        else if (opt == 3)
        {
            while (fread(&z, sizeof(z), 1, file) == 1)
            {
                if (id != z.id)
                {
                    fwrite(&z, sizeof(z), 1, fileTemp);
                }
                else
                {
                    fwrite(&Data3, sizeof(Data3), 1, fileTemp);
                }
            }
        }
        fclose(file);
        fclose(fileTemp);
        if (opt == 1)
        {
            remove(fileCatData);
            rename(tempCatData, fileCatData);
        }
        else if (opt == 2)
        {
            remove(fileProductData);
            rename(tempProductData, fileProductData);
        }
        else if (opt == 3)
        {
            remove(fileEmployeeData);
            rename(tempEmployeeData, fileEmployeeData);
        }
        ShowData(opt);
        if (getch())
        {
            system("cls");
            if (opt == 1)
                ManageCat();
            if (opt == 2)
                ManageProduct();
        }
    }
}

int main()
{
    create_folder();
    userAuthMenu();
    return 0;
}