//VENDING MACHINE SUBMITTED BY ARISHA ATIF 3433-2024 BSCS 1A
//SUBMITTED TO SIR SULAMAN AHMAD NAAZ
//FIRST SEMESTER PROJECT



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITEMS 10
#define MAX_NAME_LENGTH 50
#define MAX_PURCHASES 100

#define DISCOUNT_TYPE1 15       // PKR 15 for purchases above PKR 50
#define DISCOUNT_TYPE2 50      // PKR 150 for purchases above PKR 150
#define DISCOUNT_TYPE3 0.05     // 5% for "Cold Coffee"

// Currency Conversion Rates
float exchangeRates[] = {1.0, 1.0 / 250.0, 1.0 / 290.0}; // PKR, USD, EUR
//
typedef struct {
    char name[MAX_NAME_LENGTH];
    float price;
    int stock;
    int sold;
} Item;

typedef struct {
    float totalAmount;
    int itemsPurchased;
   char items[MAX_PURCHASES][MAX_NAME_LENGTH];  // Names of purchased items
    int quantities[MAX_PURCHASES];  // Quantities of purchased items
    float discountApplied;
    char discountMessage[100];
} UserPurchaseReport;

// Global Variables
Item items[MAX_ITEMS];
int wishlist[MAX_ITEMS] = {0};
float walletBalance = 0.0;
char adminPassword[] = "arisha123";
char selectedCurrency[4] = "PKR";  // Default currency
UserPurchaseReport userPurchaseReport[MAX_PURCHASES];
int purchaseIndex = 0;

// Function Prototypes
void clearScreen();
void printStyledMessage(const char *message);
void printGreeting();
void displayMenu();
void userMenu();
void adminMenu();
void displayItems();
void addToWishlist();
void removeFromWishlist();
void displayWishlist();
void purchaseFromWishlist();
void purchaseDirectly();
void viewBalance();
void rechargeWallet();
void checkWallet();
void applyLoyaltyDiscount(float *totalCost, float *discountApplied, char *discountMessage);
void adminViewStock();
void adminUpdatePrice();
void adminGenerateReport();
float convertCurrency(float price);
void recordUserPurchase(float totalCost);
void generateMonthlyReport();
void generatePurchaseReceipt(float totalCost, const char *items[], int quantities[], int numItems, const char *discountMessage, float discountApplied);
void setCurrency();

int main() {
    int choice;
    
    // Initialize items
    strcpy(items[0].name, "Chips (30g)"); items[0].price = 30.0; items[0].stock = 50;
    strcpy(items[1].name, "Chips (50g)"); items[1].price = 50.0; items[1].stock = 50;
    strcpy(items[2].name, "Chips (100g)"); items[2].price = 100.0; items[2].stock = 50;
    strcpy(items[3].name, "Pepsi"); items[3].price = 120.0; items[3].stock = 50;
    strcpy(items[4].name, "Fanta"); items[4].price = 120.0; items[4].stock = 50;
    strcpy(items[5].name, "Mirinda"); items[5].price = 120.0; items[5].stock = 50;
    strcpy(items[6].name, "Chocolate (10g)"); items[6].price = 10.0; items[6].stock = 50;
    strcpy(items[7].name, "Chocolate (20g)"); items[7].price = 20.0; items[7].stock = 50;
    strcpy(items[8].name, "Chocolate (40g)"); items[8].price = 40.0; items[8].stock = 50;
    strcpy(items[9].name, "Cold Coffee"); items[9].price = 240.0; items[9].stock = 50;

    printGreeting();
    printf("Welcome To Arisha's Vending Machine\n");

    while (1) {
        clearScreen();
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                userMenu();
                break;
            case 2:
                adminMenu();
                break;
            case 0:
                printStyledMessage("Thank you for using Arisha's' Vending Machine! Goodbye!");
                return 0;
            default:
                printStyledMessage("Invalid choice. Please try again.");
        }
    }
    return 0;
}

// Utility Functions
void clearScreen() {
    system("cls");  // Clears the console screen on Windows (Dev C++ environment)
}

void printStyledMessage(const char *message) {
    printf("\n**********************************************\n");
    printf("%s\n", message);
    printf("**********************************************\n");
}

void printGreeting() {
    printf("\n**********************************************\n");
    printf("***** WELCOME TO THE VENDING MACHINE *****\n");
    printf("**********************************************\n");
    printf("We are here to make your snacking experience easy and fun!\n");
    printf("**********************************************\n");
}

void displayMenu() {
    printf("\n=========== MAIN MENU ===========\n");
    printf("1. User Menu\n");
    printf("2. Admin Menu\n");
    printf("0. Exit\n");
    printf("=================================\n");
}

// User Menu Functions
void userMenu() {
    int choice;
    printf("User Menu accessed.\n");
    while (1) {
        clearScreen();
        printf("\n=========== USER MENU ===========\n");
        printf("1. Display Items\n");
        printf("2. Add to Wishlist\n");
        printf("3. Remove from Wishlist\n");
        printf("4. View Wishlist\n");
        printf("5. Purchase from Wishlist\n");
        printf("6. Purchase Item Directly\n");
        printf("7. View Balance\n");
        printf("8. Recharge Wallet\n");
        printf("9. Check Wallet\n");
        printf("10. Set Currency\n");
        printf("11. Generate Monthly Report\n");
        printf("0. Back\n");
        printf("=================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayItems();
                break;
            case 2:
                addToWishlist();
                break;
            case 3:
                removeFromWishlist();
                break;
            case 4:
                displayWishlist();
                break;
            case 5:
                purchaseFromWishlist();
                break;
            case 6:
                purchaseDirectly();
                break;
            case 7:
                viewBalance();
                break;
            case 8:
                rechargeWallet();
                break;
            case 9:
                checkWallet();
                break;
            case 10:
                setCurrency();
                break;
            case 11:
                generateMonthlyReport();
                break;
            case 0:
                return;
            default:
                printStyledMessage("Invalid choice. Please try again.");
        }
    }
}

void displayItems() {
    clearScreen();
    printf("\n=========== AVAILABLE ITEMS ===========\n");
    int i;
    for (i = 0; i < MAX_ITEMS; i++) {
        printf("%d. %s - %.2f %s (Stock: %d)\n", i + 1, items[i].name, convertCurrency(items[i].price), selectedCurrency, items[i].stock);
    }
    printf("========================================\n");
    printf("Press Enter to continue...");
    getchar();
    getchar();
}

void addToWishlist() {
    int itemIndex;
    displayItems();
    printf("Enter the item number to add to wishlist: ");
    scanf("%d", &itemIndex);
    if (itemIndex < 1 || itemIndex > MAX_ITEMS) {
        printStyledMessage("Invalid item number.");
        return;
    }
    if (items[itemIndex - 1].stock <= 0) {
        printStyledMessage("Item out of stock.");
        return;
    }
    wishlist[itemIndex - 1]++;
    printStyledMessage("Item added to wishlist.");
}

void removeFromWishlist() {
    int itemIndex;
    displayWishlist();
    printf("Enter the item number to remove from wishlist: ");
    scanf("%d", &itemIndex);
    if (itemIndex < 1 || itemIndex > MAX_ITEMS || wishlist[itemIndex - 1] == 0) {
        printStyledMessage("Invalid item number.");
        return;
    }
    wishlist[itemIndex - 1]--;
    printStyledMessage("Item removed from wishlist.");
}

void displayWishlist() {
    clearScreen();
    printf("\n=========== YOUR WISHLIST ===========\n");
    float totalCost = 0.0;
    int i;
    for (i = 0; i < MAX_ITEMS; i++) {
        if (wishlist[i] > 0) {
            printf("%d. %s - %.2f %s x %d\n", i + 1, items[i].name, convertCurrency(items[i].price), selectedCurrency, wishlist[i]);
            totalCost += items[i].price * wishlist[i];
        }
    }
    printf("----------------------------------------\n");
    printf("Total Cost: %.2f %s\n", totalCost, selectedCurrency);
    printf("========================================\n");
    printf("Press Enter to continue...");
    getchar();
    getchar();
}

void purchaseFromWishlist() {
    float totalCost = 0.0, discountApplied = 0.0;
    char discountMessage[100] = "No discount applied.";
    
    int i;
    for (i = 0; i < MAX_ITEMS; i++) {
        if (wishlist[i] > 0) {
            if (items[i].stock < wishlist[i]) {
                printf("Not enough stock for %s.\n", items[i].name);
                return;
            }
            totalCost += items[i].price * wishlist[i];
        }
    }

    applyLoyaltyDiscount(&totalCost, &discountApplied, discountMessage);

    if (walletBalance < totalCost) {
        printStyledMessage("Insufficient balance. Please recharge your wallet.");
        return;
    }

    printf("\n=========== PURCHASE RECEIPT ===========\n");
    printf("Items Purchased:\n");
    for (i = 0; i < MAX_ITEMS; i++) {
        if (wishlist[i] > 0) {
            items[i].stock -= wishlist[i];
            items[i].sold += wishlist[i];
            printf("%s - %.2f %s x %d\n", items[i].name, convertCurrency(items[i].price), selectedCurrency, wishlist[i]);
            wishlist[i] = 0;
        }
    }
    printf("----------------------------------------\n");
    printf("Discount Applied: %s\n", discountMessage);
    printf("Total Cost: %.2f %s\n", totalCost, selectedCurrency);
    walletBalance -= totalCost;
    printf("Wallet Balance after purchase: %.2f %s\n", walletBalance, selectedCurrency);
    printf("========================================\n");
    printf("Press Enter to continue...");
    getchar();
    getchar();
}

void purchaseDirectly() {
    int itemIndex, quantity;
    float totalCost = 0.0, discountApplied = 0.0;
    char discountMessage[100] = "No discount applied.";

    displayItems();
    printf("Enter the item number to purchase directly: ");
    scanf("%d", &itemIndex);

    if (itemIndex < 1 || itemIndex > MAX_ITEMS) {
        printStyledMessage("Invalid item number.");
        return;
    }

    printf("Enter the quantity to purchase: ");
    scanf("%d", &quantity);

    if (quantity > items[itemIndex - 1].stock) {
        printStyledMessage("Not enough stock available.");
        return;
    }

    totalCost = items[itemIndex - 1].price * quantity;
    applyLoyaltyDiscount(&totalCost, &discountApplied, discountMessage);

    if (walletBalance < totalCost) {
        printStyledMessage("Insufficient balance. Please recharge your wallet.");
        return;
    }

    items[itemIndex - 1].stock -= quantity;
    items[itemIndex - 1].sold += quantity;

    printf("\n=========== PURCHASE RECEIPT ===========\n");
    printf("Item Purchased: %s - %.2f %s x %d\n", items[itemIndex - 1].name, convertCurrency(items[itemIndex - 1].price), selectedCurrency, quantity);
    printf("Discount Applied: %s\n", discountMessage);
    printf("Total Cost: %.2f %s\n", totalCost, selectedCurrency);
    walletBalance -= totalCost;
    printf("Wallet Balance after purchase: %.2f %s\n", walletBalance, selectedCurrency);
    printf("========================================\n");
    printf("Press Enter to continue...");
    getchar();
    getchar();
}

void applyLoyaltyDiscount(float *totalCost, float *discountApplied, char *discountMessage) {
    if (*totalCost > 150) {
        *discountApplied = DISCOUNT_TYPE2;
        *totalCost -= DISCOUNT_TYPE2;
        strcpy(discountMessage, "Discount of 150 applied.");
    } else if (*totalCost > 50) {
        *discountApplied = DISCOUNT_TYPE1;
        *totalCost -= DISCOUNT_TYPE1;
        strcpy(discountMessage, "Discount of 15 applied.");
    } else if (wishlist[9] > 0) {
        *discountApplied = DISCOUNT_TYPE3;
        *totalCost -= (*totalCost * DISCOUNT_TYPE3);
        strcpy(discountMessage, "5% discount applied for Cold Coffee.");
    }
}

void viewBalance() {
    printf("Current wallet balance: %.2f %s\n", walletBalance, selectedCurrency);
    printf("Press Enter to continue...");
    getchar();
    getchar();
}

void rechargeWallet() {
    float amount;
    printf("Enter amount to recharge: ");
    scanf("%f", &amount);
    if (amount < 0) {
        printStyledMessage("Amount must be positive.");
        return;
    }
    walletBalance += amount;
    printStyledMessage("Wallet recharged successfully.");
}

void checkWallet() {
    printf("Your current wallet balance is: %.2f %s\n", walletBalance, selectedCurrency);
    printf("Press Enter to continue...");
    getchar();
    getchar();
}

// Admin Menu Functions
void adminMenu() {
    int choice;
    char password[20];

    printf("Enter admin password: ");
    scanf("%s", password);

    if (strcmp(password, adminPassword) != 0) {
        printStyledMessage("Incorrect password. Returning to main menu.");
        return;
    }

    while (1) {
        clearScreen();
        printf("\n=========== ADMIN MENU ===========\n");
        printf("1. View Stock\n");
        printf("2. Update Item Price\n");
        printf("3. Generate Monthly Report\n");
        printf("0. Back\n");
        printf("=================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminViewStock();
                break;
            case 2:
                adminUpdatePrice();
                break;
            case 3:
                adminGenerateReport();
                break;
            case 0:
                return;  // Go back to the main menu
            default:
                printStyledMessage("Invalid choice. Please try again.");
        }
    }
}

void adminViewStock() {
    int i;
    printf("\n=========== CURRENT STOCK ===========\n");
    for (i = 0; i < MAX_ITEMS; i++) {
        printf("%s - Stock: %d\n", items[i].name, items[i].stock);
    }
    printf("====================================\n");
    printf("Press Enter to continue...");
    getchar();
    getchar();
}

void adminUpdatePrice() {
    int itemIndex;
    float newPrice;
    displayItems();
    printf("Enter the item number to update the price: ");
    scanf("%d", &itemIndex);

    if (itemIndex < 1 || itemIndex > MAX_ITEMS) {
        printStyledMessage("Invalid item number.");
        return;
    }

    printf("Enter new price for %s: ", items[itemIndex - 1].name);
    scanf("%f", &newPrice);
    items[itemIndex - 1].price = newPrice;
    printStyledMessage("Price updated successfully.");
}

void adminGenerateReport() {
    int i;
    printf("\n=========== SALES REPORT ===========\n");
    for (i = 0; i < MAX_ITEMS; i++) {
        printf("Item: %s - Sold: %d\n", items[i].name, items[i].sold);
    }
    printf("====================================\n");
    printf("Press Enter to continue...");
    getchar();
    getchar();
}

float convertCurrency(float price) {
    if (strcmp(selectedCurrency, "USD") == 0) {
        return price * exchangeRates[1];
    } else if (strcmp(selectedCurrency, "EUR") == 0) {
        return price * exchangeRates[2];
    }
    return price;  // Default is PKR
}

void setCurrency() {
    char currency[4];
    printf("Enter currency (PKR, USD, EUR): ");
    scanf("%s", currency);
    if (strcmp(currency, "PKR") == 0 || strcmp(currency, "USD") == 0 || strcmp(currency, "EUR") == 0) {
        strcpy(selectedCurrency, currency);
        printStyledMessage("Currency set successfully.");
    } else {
        printStyledMessage("Invalid currency. Please enter PKR, USD, or EUR.");
    }
}



void recordUserPurchase(float totalCost) {
    if (purchaseIndex >= MAX_PURCHASES) {
        printStyledMessage("Purchase history limit reached.");
        return;
    }
    UserPurchaseReport report;
    report.totalAmount = totalCost;
    report.itemsPurchased = 0;
    report.discountApplied = 0;
    strcpy(report.discountMessage, "No discount applied.");
    userPurchaseReport[purchaseIndex++] = report;
    printStyledMessage("Purchase recorded.");
} 
void generateMonthlyReport() {
    clearScreen();
    printf("\n=========== MONTHLY PURCHASE REPORT ===========\n");
    

   if (purchaseIndex == 0) {
        printf("No purchases have been made this month.\n");

   } else {
        float totalSpent = 0.0;
       int i;
        for ( i = 0; i < purchaseIndex; i++) {
            printf("\nPurchase #%d:\n", i + 1);
            printf("Total Amount: %.2f %s\n", convertCurrency(userPurchaseReport[i].totalAmount), selectedCurrency);
            printf("Items Purchased:\n");
            int j;
            for (j = 0; j < userPurchaseReport[i].itemsPurchased; j++) {
               printf("- %s x %d\n", userPurchaseReport[i].items[j], userPurchaseReport[i].quantities[j]);
            }
            printf("Discount Applied: %.2f %s\n", convertCurrency(userPurchaseReport[i].discountApplied), selectedCurrency);
            printf("Discount Message: %s\n", userPurchaseReport[i].discountMessage);
           totalSpent += userPurchaseReport[i].totalAmount;
      }
       printf("\n-----------------------------------------------\n");
        printf("Total Spent This Month: %.2f %s\n", convertCurrency(totalSpent), selectedCurrency);
        printf("-----------------------------------------------\n");
  }

   printf("===============================================\n");
    printf("Press Enter to continue...");
    getchar();
    getchar();
};
