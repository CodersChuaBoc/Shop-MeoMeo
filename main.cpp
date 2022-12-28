#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>

#define folderDirectory "C:/KittyCat/"

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
    int age;
    char birthdate[20];
    char homeTown[20];
};
typedef struct employee EPE;
EPE z;

void UI_Menu();
void update(int opt);
void ExitToMenu()
{
    char opt;
    printf("\nDo you want to exit to menu ?(Y/N): ");
    fflush(stdin);
    scanf("%c", &opt);
    switch (opt)
    {
    case 'y':
    case 'Y':
        printf("\nExing to menu.............");
        delay(3);
        system("cls");
        UI_Menu();
        break;
    case 'n':
    case 'N':
        system("cls");
        break;
    default:
        printf("\nInvalid option.");
        ExitToMenu();
        break;
    }
}

void SubId(int opt)
{
    //! opt 1 - cat, opt 2 - product, 3- employee
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

void CreateProduct()
{
    char check;
    int productId = GenerateId(2);
    // char dir[30] = fileProductData;
    FILE *fptr;
    if ((fptr = fopen(fileProductData, "ab")) == NULL)
    {
        printf("Error opening/creating file!!\n");
        exit(0);
    }
    puts("\t\t\t==============================");
    puts("\t\t\t     Create a new Product  ");
    puts("\t\t\t==============================");
    puts("\t\t\t* * * * * * * * * * * * * * * *");
    // input data of cat
    printf("\nInput your product: ");
    fflush(stdin);
    gets(y.name);
    printf("\nInput the price of your product: ");
    fflush(stdin);
    scanf("%u", &y.price);
    while (y.price <= 0)
    {
        printf("\nInvalid value of price, please re-input it");
        scanf("%u", &y.price);
    }
    printf("\nInput the quantity of your product: ");
    fflush(stdin);
    scanf("%d", &y.quantity);
    while (y.quantity < 0)
    {
        printf("\nInvalid value of quantity, please re-input it");
        scanf("%d", &y.quantity);
    }
    fflush(stdin);
    printf("\nInput the expiry of your product: ");
    gets(y.expiry);
    y.id = productId;
    fflush(stdin);
    // output data of product you entered
    system("cls");
    printf("\nYour information of product that you have entered:");
    printf("\n*********************************************");
    printf("\nProduct ID %d", y.id);
    printf("\nProduct name: %s", y.name);
    printf("\nProduct price: %d VND", y.price);
    printf("\nProduct quantity: %d", y.quantity);
    printf("\nProduct expiry: %s", y.expiry);
    printf("\n*********************************************");
    printf("\nDo you want to save this product(Y/N): ");
SAVE:
    while (1)
    {
        scanf("%c", &check);
        switch (check)
        {
        case 'y':
        case 'Y':
            fwrite(&y, sizeof(y), 1, fptr);
            printf("\nProduct is saved");
            fclose(fptr);
            break;
        case 'n':
        case 'N':
            printf("\nProduct is not saved");
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
    printf("\nDo you want to re-input a new product(Y/N): ");
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
    char check;
    int CatId = GenerateId(1);
    // char dir[20] = fileCatData;
    FILE *fptr;
    if ((fptr = fopen(fileCatData, "ab")) == NULL)
    {
        printf("Error opening/creating file!!\n");
        exit(0);
    }
    puts("\t\t\t==============================");
    puts("\t\t\t     Create a new Kitty  ");
    puts("\t\t\t==============================");
    puts("\t\t\t* * * * * * * * * * * * * * * *");
    // input data of cat
    printf("\nInput your kitty: ");
    fflush(stdin);
    gets(x.name);
    printf("\nInput the weight of your kitty: ");
    fflush(stdin);
    scanf("%f", &x.weight);
    fflush(stdin);
    printf("\nInput the type of your kitty: ");
    gets(x.type);
    fflush(stdin);
    printf("\nInput the sex of your kitty (0-female or 1-male): ");
    scanf("%d", &x.sex);
    while (x.sex != 0 && x.sex != 1)
    {
        printf("\nInvalid option, re-input the sex of your kitty");
        scanf("%d", &x.sex);
    }
    printf("\nInput the vaccination of your kitty (1-yes or 0-not): ");
    scanf("%d", &x.vaccination);
    while (x.vaccination != 0 && x.vaccination != 1)
    {
        printf("\nInvalid option, re-input the vaccination of your kitty");
        scanf("%d", &x.vaccination);
    }
    x.id = CatId;
    // output data of cat you entered
    system("cls");
    printf("\nYour information of kitty that you have entered:");
    printf("\n*********************************************");
    printf("\nKitty ID %d", x.id);
    printf("\nKitty name: %s", x.name);
    printf("\nKitty weight: %.1f", x.weight);
    printf("\nKitty type: %s", x.type);
    if (x.sex)
    {
        printf("\nThe sex of your kitty: male");
    }
    else
    {
        printf("\nThe sex of your kitty: female");
    }
    if (x.vaccination)
    {
        printf("\nYour kitty is vaccinated");
    }
    else
    {
        printf("\nYour kitty is not vaccinated");
    }
    fflush(stdin);
    printf("\n*********************************************");
    printf("\nDo you want to save this kitty(Y/N): ");
SAVE:
    while (1)
    {
        scanf("%c", &check);
        switch (check)
        {
        case 'y':
        case 'Y':
            fwrite(&x, sizeof(x), 1, fptr);
            printf("\nKitty is saved");
            fclose(fptr);
            break;
        case 'n':
        case 'N':
            printf("\nKitty is not saved");
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
    printf("\nDo you want to re-input a new cat(Y/N): ");
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
    char check;
    int employeeId = GenerateId(3);
    FILE *fptr;
    if ((fptr = fopen(fileEmployeeData, "ab")) == NULL)
    {
        printf("Error opening/creating file!!\n");
        exit(0);
    }
    puts("\t\t\t==============================");
    puts("\t\t\t     Create a new Employee  ");
    puts("\t\t\t==============================");
    puts("\t\t\t* * * * * * * * * * * * * * * *");
    // input data of cat
    printf("\nInput your Employee: ");
    fflush(stdin);
    gets(z.name);
    printf("\nInput the age of your employee: ");
    fflush(stdin);
    scanf("%d", &z.age);
    while (z.age <= 0)
    {
        printf("\nInvalid value of age, please re-input it");
        scanf("%d", &z.age);
    }
    printf("\nInput the birthday of your employee(dd/mm/yy): ");
    fflush(stdin);
    gets(z.birthday);
    printf("\nInput the home town of your product: ");
    gets(z.homeTown);
    z.id = employeeId;
    // output data of product you entered
    system("cls");
    printf("\nYour information of employee that you have entered:");
    printf("\n*********************************************");
    printf("\nEmployee ID %d", z.id);
    printf("\nEmployee name: %s", z.name);
    printf("\nEmployee age: %d VND", z.age);
    printf("\nEmployee birthday: %s", z.birthdate);
    printf("\nEmployee home town: %s", z.homeTown);
    printf("\n*********************************************");
    printf("\nDo you want to save this product(Y/N): ");
    fflush(stdin);
SAVE:
    while (1)
    {
        scanf("%c", &check);
        switch (check)
        {
        case 'y':
        case 'Y':
            fwrite(&y, sizeof(y), 1, fptr);
            printf("\nEmployee is saved");
            fclose(fptr);
            break;
        case 'n':
        case 'N':
            printf("\nEmployee is not saved");
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
    printf("\nDo you want to re-input a new Employee(Y/N): ");
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
            break;
        default:
            printf("\nInvalid option, re-input your choice: ");
            scanf("%c", &reInput);
            break;
        }
        break;
    }
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
    printf("> Enter the Kitty ID to search: ");
    scanf("%d", &searchID);
    if (checkCatAvailable(catID) == 0)
    {
        printf("\nKitty ID is invalid! Kitty not found!");
    }
    while (fread(&x, sizeof(x), 1, fptr) == 1)
    {
        if (searchID == x.id)
        {
            system("cls");
            printf("\n\tKitty %s say hello!", x.name);
            printf("\n*********************************************");
            printf("\n- Kitty ID: %d", x.id);
            printf("\n- Kitty name: %s", x.name);
            printf("\n- Kitty weight: %.1f", x.weight);
            printf("\n- Kitty type: %s", x.type);
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
    char reSearch1;
    printf("\n> Do you want to search for another kitty? (Y/N): ");
REINPUT1:
    scanf("%s", &reSearch1);
    switch (reSearch1)
    {
    case 'y':
    case 'Y':
        system("cls");
        searchCats();
        break;
    case 'n':
    case 'N':
        break;
    default:
        printf("Invalid option, please reinput your choice: ");
        goto REINPUT1;
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
        printf("\nProduct ID is invalid! Product not found!");
    }
    while (fread(&y, sizeof(y), 1, fptr) == 1)
    {
        if (searchID == y.id)
        {
            system("cls");
            printf("\nInformation of the product you search");
            printf("\n*********************************************");
            printf("\n- Product ID: %d", y.id);
            printf("\n- Product name: %s", y.name);
            printf("\n- Product price: %dVND", y.price);
            printf("\n- Product quantity: %d", y.quantity);
            printf("\n- Product expiry: %s", y.expiry);
        }
    }
    char reSearch2;
    printf("\n> Do you want to search for another product? (Y/N): ");
REINPUT2:
    scanf("%s", &reSearch2);
    switch (reSearch2)
    {
    case 'y':
    case 'Y':
        system("cls");
        searchProducts();
        break;
    case 'n':
    case 'N':
        break;
    default:
        printf("Invalid option, please reinput your choice: ");
        goto REINPUT2;
        break;
    }
    fclose(fptr);
}

void searchFunc()
{
    int searchChoice;
    printf("=========== SEARCH ============");
    printf("\n1. Search Cats");
    printf("\n2. Search Products");
    printf("\n\n> What do you want to search: ");
    scanf("%d", &searchChoice);
    switch (searchChoice)
    {
    case 1:
        searchCats();
        break;
    case 2:
        searchProducts();
        break;
    default:
        printf("\nNo choices were made! Return to the search menu\n");
        searchFunc();
        break;
    }
}

void ShowData(int opt)
{
    // ! 1- cat, 2 - products, 3 - employees
    FILE *fptr;
    if ((fptr = fopen(opt == 1 ? fileCatData : opt == 2 ? fileProductData
                                                        : fileEmployeeData,
                      "rb")) == NULL)
    {
        printf("File not found!");
    }
    if (opt == 2)
    {
        printf("\nInformation of the products");
        printf("\n*********************************************\n");
        puts("ID \tName\t\t\tPrice\t\tQuantity\tExpiration");
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
        printf("\nInformation of the cats");
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
        printf("\nInformation of the Employees");
        printf("\n*********************************************\n");
        puts("ID \tName\t\t\tAge\t\tBirthday\t\tHome Town\t\t");
        while (fread(&z, sizeof(z), 1, fptr) == 1)
        {
            printf("%d\t", z.id);
            printf("%s\t\t\t", z.name);
            printf("%d\t\t", z.age);
            printf("%s\t\t", z.birthdate);
            printf("%s\t\t", z.homeTown);
            printf("\n");
        }
    }
    fclose(fptr);
}

void ManageCat()
{
    puts("\t\t\t==============================");
    puts("\t\t\t     Manage cat  ");
    puts("\t\t\t==============================");
    puts("\t\t\t* * * * * * * * * * * * * * * *");
    puts("\t\t\t1. Show all Cats\n\n\t\t\t2. Add cat\n\n\t\t\t3. Search Cat\n\n\t\t\t4. Update cat by ID\n\n\t\t\t5. Delete cat by ID\n\n\t\t\t6. Exit to Menu\n");
    printf("\t\t\tSelect your choice:  ");
    int u;
    scanf("%d", &u);
    while (u < 1 || u > 5)
    {
        printf("Invalid choice, Please enter a valid choice\n");
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
        searchCats();
        break;
    case 4:
        update(1);
        break;
    case 5:
        printf("Delete cat");
        break;
    case 6:
        printf("\nExting to menu ..........");
        delay(3);
        UI_Menu();
        break;
    }
}
void ManageProduct()
{
    puts("\t\t\t==============================");
    puts("\t\t\t     Manage Product  ");
    puts("\t\t\t==============================");
    puts("\t\t\t* * * * * * * * * * * * * * * *");
    puts("\t\t\t1. Show all products\n\n\t\t\t2. Add product\n\n\t\t\t3. Search Product\n\n\t\t\t4. Update product by ID\n\n\t\t\t5. Delete product by ID\n\n\t\t\t5. Exit to Menu\n");
    printf("\t\t\tSelect your choice:  ");
    int u;
    scanf("%d", &u);
    while (u < 1 || u > 5)
    {
        printf("Invalid choice, Please enter a valid choice\n");
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
        searchProducts();
        break;
    case 4:
        update(2);
        break;
    case 5:
        printf("\nDelete product\n");
        break;
    case 6:
        printf("\nExting to menu ..........");
        delay(3);
        UI_Menu();
        break;
    }
}

void ManageEmployees()
{
    puts("\t\t\t==============================");
    puts("\t\t\t     Manage Employees  ");
    puts("\t\t\t==============================");
    puts("\t\t\t* * * * * * * * * * * * * * * *");
    puts("\t\t\t1. Show all Employees\n\n\t\t\t2. Add Employee\n\n\t\t\t3. Search Employee\n\n\t\t\t4. Update Employee by ID\n\n\t\t\t5. Delete Employee by ID\n\n\t\t\t5. Exit to Menu\n");
    printf("\t\t\tSelect your choice:  ");
    int u;
    scanf("%d", &u);
    while (u < 1 || u > 5)
    {
        printf("Invalid choice, Please enter a valid choice\n");
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
        searchProducts();
        break;
    case 4:
        update(3);
        break;
    case 5:
        printf("\nDelete product\n");
        break;
    case 6:
        printf("\nExting to menu ..........");
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
        puts("\t\t\t==============================");
        puts("\t\t\t     WELCOME TO THE SHOP  ");
        puts("\t\t\t==============================");
        puts("\t\t\t* * * * * * * * * * * * * * * *");
        puts("\t\t\t1. Manage Cat\n\n\t\t\t2. Manage Products\n\n\t\t\t3. Your Cart\n\n\t\t\t4. Manage Finance\n\n\t\t\t5. Manage Client\n\n\t\t\t6. Exit");
        printf("\t\t\tSelect your choice:  ");
        int u;
        scanf("%d", &u);
        while (u < 1 || u > 6)
        {
            printf("Invalid choice, Please try again:  ");
            scanf("%d", &u);
        }
        system("cls");
        if (u == 1)
        {
            ManageCat();
            exit(0);
        }
        else if (u == 2)
        {
            ManageProduct();
            exit(0);
        }
        else if (u == 3)
        {
            printf("Your choice is 3");
            exit(0);
        }
        else if (u == 4)

        {
            printf("Your choice is 4");
            exit(0);
        }
        else if (u == 5)
        {
            printf("Your choice is 5");
            exit(0);
        }
        else if (u == 6)
        {
            printf("exit");
            exit(0);
        }
    }
}

void CheckShowData(int opt)
{
    //! 1-cat, 2- product, 3 - employees
    printf("\nDo you want to show data:  ");
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
        printf("\nInvalid option.");
        CheckShowData(opt);
        break;
    }
}

void update(int opt)
{
    //! 1- cat, 2 - product, 3- employee
    int id;
    int isHave = 0;
    puts("\t\t\t==============================");
    if (opt == 1)
    {
        puts("\t\t\tUpdate cat by id");
    }
    else if (opt == 2)
    {
        puts("\t\t\tUpdate Product by id");
    }
    else if (opt == 3)
    {
        puts("\t\t\tUpdate Employee by id");
    }
    puts("\t\t\t==============================");
    puts("\t\t\t* * * * * * * * * * * * * * * *");
    // show cat name here
    CheckShowData(opt);
    FILE *file = fopen(opt == 1 ? fileCatData : opt == 2 ? fileProductData
                                                         : fileEmployeeData,
                       "rb+");
    if (file == NULL)
    {
        printf("\nError opening file");
        printf("\nExiting to menu........");
        delay(3);
        UI_Menu();
    }
    printf("Please, Enter your id: ");
    scanf("%d", &id);
    if (opt == 1)
    {
        while (fread(&x, sizeof(x), 1, file) == 1)
        {
            if (id == x.id)
            {
                printf("\n\tKitty %s say hello!", x.name);
                printf("\n*********************************************");
                printf("\n- Kitty ID: %d", x.id);
                printf("\n- Kitty name: %s", x.name);
                printf("\n- Kitty weight: %.1f", x.weight);
                printf("\n- Kitty type: %s", x.type);
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
                printf("\nInformation of the product:");
                printf("\n*********************************************");
                printf("\n- Product ID: %d", y.id);
                printf("\n- Product name: %s", y.name);
                printf("\n- Product price: %dVND", y.price);
                printf("\n- Product quantity: %d", y.quantity);
                printf("\n- Product expiry: %s", y.expiry);
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
                printf("\nYour information of employee:");
                printf("\n*********************************************");
                printf("\nEmployee ID %d", z.id);
                printf("\nEmployee name: %s", z.name);
                printf("\nEmployee age: %d VND", z.age);
                printf("\nEmployee birthday: %s", z.birthdate);
                printf("\nEmployee home town: %s", z.homeTown);
                isHave++;
            }
        }
    }

    fclose(file);

    if (!isHave)
    {
        printf("\nNot found");
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
            printf("\n********************************************");
            printf("\nUpdate your kitty: ");
            fflush(stdin);
            printf("\nInput your name kitty: ");
            gets(Data1.name);
            printf("\nInput the weight of your kitty: ");
            fflush(stdin);
            scanf("%f", &Data1.weight);
            fflush(stdin);
            printf("\nInput the type of your kitty: ");
            gets(Data1.type);
            fflush(stdin);
            printf("\nInput the sex of your kitty (0-female or 1-male): ");
            scanf("%d", &Data1.sex);
            while (Data1.sex != 0 && Data1.sex != 1)
            {
                printf("\nInvalid option, re-input the sex of your kitty");
                scanf("%d", &Data1.sex);
            }
            printf("\nInput the vaccination of your kitty (1-yes or 0-not): ");
            scanf("%d", &Data1.vaccination);
            while (Data1.vaccination != 0 && Data1.vaccination != 1)
            {
                printf("\nInvalid option, re-input the vaccination of your kitty");
                scanf("%d", &Data1.vaccination);
            }
            Data1.id = id;
        }
        else if (opt == 2)
        {
            printf("\nUpdate your product: ");
            fflush(stdin);
            printf("\nInput your name product: ");
            gets(Data2.name);
            printf("\nInput the price of your product: ");
            fflush(stdin);
            scanf("%u", &Data2.price);
            while (Data2.price <= 0)
            {
                printf("\nInvalid value of price, please re-input it");
                scanf("%u", &Data2.price);
            }
            printf("\nInput the quantity of your product: ");
            fflush(stdin);
            scanf("%d", &Data2.quantity);
            while (Data2.quantity < 0)
            {
                printf("\nInvalid value of quantity, please re-input it");
                scanf("%d", &Data2.quantity);
            }
            fflush(stdin);
            printf("\nInput the expiry of your product: ");
            gets(Data2.expiry);
            Data2.id = id;
        }
        else if (opt == 3)
        {
            printf("\nUpdate your Employee: ");
            printf("Input your name employee: ");
            fflush(stdin);
            gets(Data3.name);
            printf("\nInput the age of your employee: ");
            fflush(stdin);
            scanf("%d", &Data3.age);
            while (Data3.age <= 0)
            {
                printf("\nInvalid value of age, please re-input it");
                scanf("%d", &Data3.age);
            }
            printf("\nInput the birthday of your employee(dd/mm/yy): ");
            fflush(stdin);
            gets(Data3.birthday);
            printf("\nInput the home town of your product: ");
            gets(Data3.homeTown);
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
        printf("\nPress any key to Continue to Menu\n");
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
    UI_Menu();
    return 0;
}