#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <cctype>
#include <locale>
#include <iomanip> // For text formatting like setw
using namespace std;

int order = 1;
class Cart
{
private:
    string Item;
    int Rate, Quantity;

public:
    Cart() : Item(""), Rate(0), Quantity(0) {}

    void setItem(string item)
    {
        Item = item;
    }

    void setRate(int rate)
    {
        Rate = rate;
    }

    void setQuant(int quant)
    {
        Quantity = quant;
    }

    string getItem()
    {
        return Item;
    }

    int getRate()
    {
        return Rate;
    }

    int getQuant()
    {
        return Quantity;
    }
};

class Stock
{
private:
    string productName;
    double price;
    int quantity;
    double discount;

public:
    Stock() : productName(""), price(0.0), quantity(0), discount(0.0) {}

    // Setters
    void setProductName(string name)
    {
        productName = name;
    }

    void setPrice(double p)
    {
        price = p;
    }

    void setQuantity(int q)
    {
        quantity = q;
    }

    void setDiscount(double d)
    {
        discount = d;
    }

    // Getters
    string getProductName() const
    {
        return productName;
    }

    double getPrice() const
    {
        return price;
    }

    int getQuantity() const
    {
        return quantity;
    }

    double getDiscount() const
    {
        return discount;
    }

    // Function to add stock to CSV
    void addToStock()
    {
        ofstream stockFile("stock.csv", ios::app); // Appends to file
        ofstream total_inventory("inventory.csv", ios::app);
        if (!total_inventory.is_open())
        {
            cout << "Error: Could not open inventory file!" << endl;
            return;
        }
        if (!stockFile.is_open())
        {
            cout << "Error: Could not open stock file!" << endl;
            return;
        }
        // Write the stock item in CSV format
        stockFile << productName << "," << price << "," << quantity << "," << discount << endl;
        total_inventory << productName << "," << price << "," << quantity << "," << discount << endl;
        stockFile.close();
        total_inventory.close();
        cout << "Item added to stock successfully!" << endl;
    }

    static void updateInventory(string name, int newQuantity, double newPrice, double newDiscount)
    {
        ifstream total_inventory("stock.csv");
        ofstream total_inventory_temp("temp.csv");

        if (!total_inventory.is_open() || !total_inventory_temp.is_open())
        {
            cout << "Error: Could not open file!" << endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(total_inventory, line))
        {
            stringstream ss(line);
            string prodName, priceStr, quantityStr, discountStr;

            getline(ss, prodName, ',');
            getline(ss, priceStr, ',');
            getline(ss, quantityStr, ',');
            getline(ss, discountStr, ',');

            if (prodName == name)
            {
                // Update the stock data for the matched product
                total_inventory_temp << name << "," << newPrice << "," << newQuantity << "," << newDiscount << endl;
                found = true;
            }
            else
            {
                // Write the existing data to the temp file
                total_inventory_temp << line << endl;
            }
        }

        if (!found)
        {
            cout << "Item not found in stock!" << endl;
        }
        else
        {
            cout << "Stock updated successfully!" << endl;
        }

        total_inventory.close();
        total_inventory_temp.close();

        // Replace the old stock file with the updated one
        remove("stock.csv");
        rename("temp.csv", "stock.csv");
    }
    // Function to update stock
    static void updateStock(string name, int newQuantity, double newPrice, double newDiscount)
    {
        updateInventory(name, newQuantity, newPrice, newDiscount);
        ifstream stockFile("stock.csv");
        ofstream tempFile("temp.csv");

        if (!stockFile.is_open() || !tempFile.is_open())
        {
            cout << "Error: Could not open file!" << endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(stockFile, line))
        {
            stringstream ss(line);
            string prodName, priceStr, quantityStr, discountStr;

            getline(ss, prodName, ',');
            getline(ss, priceStr, ',');
            getline(ss, quantityStr, ',');
            getline(ss, discountStr, ',');

            if (prodName == name)
            {
                // Update the stock data for the matched product
                tempFile << name << "," << newPrice << "," << newQuantity << "," << newDiscount << endl;
                found = true;
            }
            else
            {
                // Write the existing data to the temp file
                tempFile << line << endl;
            }
        }

        if (!found)
        {
            cout << "Item not found in stock!" << endl;
        }
        else
        {
            cout << "Stock updated successfully!" << endl;
        }

        stockFile.close();
        tempFile.close();

        // Replace the old stock file with the updated one
        remove("stock.csv");
        rename("temp.csv", "stock.csv");
    }

    static void remove_from_inventory(string name)
    {
        ifstream total_inventory("stock.csv");
        ofstream total_inventory_temp("temp.csv");

        if (!total_inventory.is_open() || !total_inventory_temp.is_open())
        {
            cout << "Error: Could not open file!" << endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(total_inventory, line))
        {
            stringstream ss(line);
            string prodName;

            // Read product name from line
            getline(ss, prodName, ',');

            // If the product name doesn't match the one to remove, write it to the temp file
            if (prodName != name)
            {
                total_inventory_temp << line << endl;
            }
            else
            {
                found = true; // Mark as found for feedback to the user
            }
        }

        total_inventory.close();
        total_inventory_temp.close();

        // Replace old stock file with updated file
        remove("stock.csv");
        rename("temp.csv", "stock.csv");

        if (found)
        {
            cout << "Item '" << name << "' removed successfully!" << endl;
        }
        else
        {
            cout << "Item '" << name << "' not found in stock!" << endl;
        }
    }

    // Function to remove an item from stock
    static void removeItem(string name)
    {
        remove_from_inventory(name);
        ifstream stockFile("stock.csv");
        ofstream tempFile("temp.csv");

        if (!stockFile.is_open() || !tempFile.is_open())
        {
            cout << "Error: Could not open file!" << endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(stockFile, line))
        {
            stringstream ss(line);
            string prodName;

            // Read product name from line
            getline(ss, prodName, ',');

            // If the product name doesn't match the one to remove, write it to the temp file
            if (prodName != name)
            {
                tempFile << line << endl;
            }
            else
            {
                found = true; // Mark as found for feedback to the user
            }
        }

        stockFile.close();
        tempFile.close();

        // Replace old stock file with updated file
        remove("stock.csv");
        rename("temp.csv", "stock.csv");

        if (found)
        {
            cout << "Item '" << name << "' removed successfully!" << endl;
        }
        else
        {
            cout << "Item '" << name << "' not found in stock!" << endl;
        }
    }
};

// string trim(const string &str)
// {
//     size_t first = str.find_first_not_of(' '); // Find the first non-space character
//     size_t last = str.find_last_not_of(' ');   // Find the last non-space character

//     if (first == string::npos || last == string::npos)
//     {
//         return ""; // If all characters are spaces or empty string, return empty string
//     }

//     return str.substr(first, (last - first + 1)); // Return the substring with no spaces at the start or end
// }

// A simple hash function (for demonstration purposes)
string hashPassword(const string &password)
{
    unsigned long hash = 0;
    for (char c : password)
    {
        hash = (hash * 31) + c; // Using a basic hashing method
    }
    stringstream ss;
    ss << hex << hash; // Convert the hash to a hexadecimal string
    return ss.str();
}

// Function to trim leading and trailing whitespace from a string
string trim(const string &str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if (first == string::npos || last == string::npos)
    {
        return ""; // Empty or all spaces
    }
    return str.substr(first, (last - first + 1));
}

// Register Admin function
bool registerAdmin()
{
    string username, password;
    cout << "\tRegister Admin" << endl;
    cout << "\tUsername: ";
    cin.ignore();              // To clear any remaining newline characters from previous input
    getline(cin, username);    // Using getline to handle spaces
    username = trim(username); // Trim leading/trailing spaces

    cout << "\tPassword: ";
    getline(cin, password); // Using getline for password as well
    password = trim(password);

    // Hash the password
    string hashedPassword = hashPassword(password);

    ofstream outFile("admin_credentials.csv", ios::app);
    if (!outFile.is_open())
    {
        cout << "\tError: Unable to open admin credentials file." << endl;
        return false;
    }

    outFile << username << "," << hashedPassword << endl;
    outFile.close();

    cout << "\tAdmin registered successfully!" << endl;
    return true;
}

// changes done
//  Login Admin function
bool loginAdmin()
{
    string username, password;
    cout << "\tLogin Admin" << endl;
    cout << "\tUsername: ";
    cin.ignore();           // To clear any remaining newline characters from previous input
    getline(cin, username); // Using getline to handle spaces
    username = trim(username);

    cout << "\tPassword: ";
    getline(cin, password); // Using getline for password as well
    password = trim(password);

    // Hash the input password
    string hashedPassword = hashPassword(password);

    ifstream inFile("admin_credentials.csv");
    if (!inFile.is_open())
    {
        cout << "\tError: Unable to open admin credentials file." << endl;
        return false;
    }

    string line, storedUsername, storedPassword;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        getline(ss, storedUsername, ',');
        getline(ss, storedPassword, ',');

        if (storedUsername == username && storedPassword == hashedPassword)
        {
            cout << "\tAdmin logged in successfully!" << endl;
            inFile.close();
            return true;
        }
    }
    inFile.close();
    cout << "\tInvalid username or password." << endl;
    return false;
}

// Register Customer function
bool registerCustomer()
{
    string username, password;
    cout << "\tRegister Customer" << endl;
    cout << "\tUsername: ";
    cin.ignore();           // To clear any remaining newline characters from previous input
    getline(cin, username); // Using getline to handle spaces
    username = trim(username);

    cout << "\tPassword: ";
    getline(cin, password); // Using getline for password as well
    password = trim(password);

    // Hash the password
    string hashedPassword = hashPassword(password);

    ofstream outFile("customer_credentials.csv", ios::app);
    if (!outFile.is_open())
    {
        cout << "\tError: Unable to open customer credentials file." << endl;
        return false;
    }

    outFile << username << "," << hashedPassword << endl;
    outFile.close();

    cout << "\tCustomer registered successfully!" << endl;
    return true;
}

// Login Customer function
bool loginCustomer()
{
    string username, password;
    cout << "\tLogin Customer" << endl;
    cout << "\tUsername: ";
    cin.ignore();           // To clear any remaining newline characters from previous input
    getline(cin, username); // Using getline to handle spaces
    username = trim(username);

    cout << "\tPassword: ";
    getline(cin, password); // Using getline for password as well
    password = trim(password);

    // Hash the input password
    string hashedPassword = hashPassword(password);

    ifstream inFile("customer_credentials.csv");
    if (!inFile.is_open())
    {
        cout << "\tError: Unable to open customer credentials file." << endl;
        return false;
    }

    string line, storedUsername, storedPassword;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        getline(ss, storedUsername, ',');
        getline(ss, storedPassword, ',');

        if (storedUsername == username && storedPassword == hashedPassword)
        {
            cout << "\tCustomer logged in successfully!" << endl;
            inFile.close();
            return true;
        }
    }
    inFile.close();
    cout << "\tInvalid username or password." << endl;
    return false;
}

// Helper function to check if a string is numeric
bool isNumeric(const string &str)
{
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

void addItem(Cart b)
{
    bool close = false;
    while (!close)
    {
        int choice;
        cout << "\t1. Add." << endl;
        cout << "\t2. Close." << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            system("cls");
            string item;
            int rate, quant;

            cout << "\tEnter Item Name: ";
            cin >> item;
            b.setItem(item);

            cout << "\tEnter Rate Of Item: ";
            cin >> rate;
            b.setRate(rate);

            cout << "\tEnter Quantity Of Item: ";
            cin >> quant;
            b.setQuant(quant);

            // Open CSV file to append data
            ofstream out("cart.csv", ios::app);
            if (!out.is_open())
            {
                cout << "\tError: Could not open cart.csv!" << endl;
            }
            else
            {
                // Write the item, rate, and quantity in CSV format
                out << b.getItem() << "," << b.getRate() << "," << b.getQuant() << endl;
                cout << "\tItem Added Successfully!" << endl;
            }
            out.close();
            Sleep(2000); // 2 seconds pause for user confirmation
        }
        else if (choice == 2)
        {
            system("cls");
            close = true;
            cout << "\tReturning to Main Menu..." << endl;
            Sleep(2000);
        }
    }
}

bool stock_store(string itemName, string rateStr, string quantityStr)
{
    bool flag = true;
    int quantityBill = stoi(quantityStr); // Quantity billed

    ifstream in("stock.csv");       // Reading from stock CSV file
    ofstream out("stock_temp.csv"); // Temporary file to write updated stock

    if (!in.is_open() || !out.is_open())
    {
        cout << "\tError: Unable to open stock file." << endl;
        return false;
    }

    string line;
    bool itemFound = false;

    while (getline(in, line))
    {
        stringstream ss(line);
        string stockItemName, stockRateStr, stockQuantityStr, stockDiscountStr;

        // Splitting the line based on ',' delimiter
        getline(ss, stockItemName, ',');
        getline(ss, stockRateStr, ',');
        getline(ss, stockQuantityStr, ',');
        getline(ss, stockDiscountStr, ',');

        // Trim spaces from the strings
        stockItemName = trim(stockItemName);
        stockRateStr = trim(stockRateStr);
        stockQuantityStr = trim(stockQuantityStr);
        stockDiscountStr = trim(stockDiscountStr);

        if (stockItemName == itemName)
        {
            itemFound = true;

            // Convert stock quantity to integer
            int stockQuantity = stoi(stockQuantityStr);

            // Update the stock by reducing the quantity billed
            int newQuantity = stockQuantity - quantityBill;

            if (newQuantity >= 0)
            {
                // Write updated data to temporary file
                out << stockItemName << "," << stockRateStr << "," << newQuantity << "," << stockDiscountStr << endl;
                cout << "\tUpdated stock for " << itemName << ": " << newQuantity << " remaining." << endl;
            }
            else
            {
                flag = false;
                cout << "\tError: Insufficient stock for item: " << itemName << endl;
                out << stockItemName << "," << stockRateStr << "," << stockQuantity << "," << stockDiscountStr << endl;
            }
        }
        else
        {
            // flag = false;
            // Write the unmodified line for other items
            out << line << endl;
            // cout << stockItemName << " is not available currently" << endl;
        }
    }

    if (!itemFound)
    {
        cout << "\tError: Item not found in stock: " << itemName << endl;
    }

    in.close();
    out.close();

    // Replace the original stock file with the updated file
    remove("stock.csv");
    rename("stock_temp.csv", "stock.csv");
    return flag;
}

void add_to_invoice(string itemName, string rateStr, string quantityStr, int amount, int discount, int discountedAmount)
{
    ofstream invoice("invoice.csv", ios::app);

    if (!invoice.is_open())
    {
        cout << "\tError: Unable to open invoice.csv. " << endl;
        return;
    }

    // invoice << endl
    //         << order << ",";
    invoice << itemName << "," << rateStr << "," << quantityStr << "," << amount << "," << discount << "," << discountedAmount << endl;

    invoice.close();
}
void printBill()
{
    system("cls");
    bool close = false;

    while (!close)
    {
        // system("cls");
        int choice;
        cout << endl
             << "\t1.Add Bill." << endl;
        cout << "\t2.Close Session." << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            ifstream in("cart.csv");       // Reading the bill from CSV
            ofstream out("cart_temp.csv"); // Writing to a temporary file

            if (!in.is_open())
            {
                cout << "\tError: Unable to open bill.csv file." << endl;
                return;
            }

            string line;
            int totalPrice = 0;
            int totalDiscountedPrice = 0; // Total price after applying discounts

            cout << "\n\tItem | Rate | Quantity | Amount | Discount | Discounted Amount\n";
            cout << "\t---------------------------------------------------------------\n";

            while (getline(in, line))
            {
                stringstream ss(line);
                string itemName, rateStr, quantityStr;
                int rate = 0, quantity = 0;

                // Splitting the line based on ',' delimiter
                getline(ss, itemName, ',');
                getline(ss, rateStr, ',');
                getline(ss, quantityStr, ',');

                // Trim spaces
                itemName = trim(itemName);
                rateStr = trim(rateStr);
                quantityStr = trim(quantityStr);

                // Convert rate and quantity to integers
                if (!rateStr.empty() && !quantityStr.empty() && isNumeric(rateStr) && isNumeric(quantityStr))
                {
                    rate = stoi(rateStr);
                    quantity = stoi(quantityStr);

                    // Calculate the total amount for this item
                    int amount = rate * quantity;
                    totalPrice += amount;

                    // Retrieve the discount from stock.csv
                    ifstream stockFile("stock.csv");
                    string stockLine;
                    string discountStr;
                    int discount = 0;

                    while (getline(stockFile, stockLine))
                    {
                        stringstream stockSS(stockLine);
                        string stockItemName, stockRateStr, stockQuantityStr, stockDiscountStr;

                        getline(stockSS, stockItemName, ',');
                        getline(stockSS, stockRateStr, ',');
                        getline(stockSS, stockQuantityStr, ',');
                        getline(stockSS, stockDiscountStr, ',');

                        stockItemName = trim(stockItemName);
                        stockDiscountStr = trim(stockDiscountStr);

                        if (stockItemName == itemName)
                        {
                            discount = stoi(stockDiscountStr); // Apply the discount
                            break;
                        }
                    }
                    stockFile.close();

                    // Apply discount to calculate the discounted amount
                    int discountedAmount = amount - (amount * discount / 100);
                    totalDiscountedPrice += discountedAmount;

                    // Display the details on the terminal
                    cout << "\t" << itemName << " | " << rate << " | " << quantity << " | " << amount
                         << " | " << discount << "% | " << discountedAmount << endl;

                    // Write the data to the temporary bill CSV
                    out << itemName << "," << rate << "," << quantity << endl;

                    // Call stock_manage() to update stock
                    bool flag = stock_store(itemName, rateStr, quantityStr);
                    if (flag)
                    {
                        add_to_invoice(itemName, rateStr, quantityStr, amount, discount, discountedAmount);
                    }
                }
                else
                {
                    cout << "\tError: Invalid data format in bill.csv." << endl;
                }
            }

            cout << "\n\tTotal Price: " << totalPrice << endl;
            cout << "\tTotal Discounted Price: " << totalDiscountedPrice << endl;

            out.close();
            in.close();

            // Replace the original bill file with the updated file
            remove("cart.csv");
            rename("cart_temp.csv", "cart.csv");
        }
        else if (choice == 2)
        {
            close = true;
            cout << "\tClosing session..." << endl;
        }

        // Sleep(10000); // Pause for 3 seconds
    }

    // system("cls");
    cout << "\tThanks for shopping!" << endl;
    // Sleep(5000); // Pause for 5 seconds
    order++;
}

void manageStock()
{

    int choice;
    cout << "\tStock Management" << endl;
    cout << "\t****************" << endl;
    cout << "\t1. Add New Item to Stock." << endl;
    cout << "\t2. Update Existing Stock." << endl;
    cout << "\t3. Remove Item from Stock." << endl; // New option for removing an item
    cout << "\t4. Exit." << endl;
    cout << "\tEnter choice: ";
    cin >> choice;

    Stock s;
    string productName;
    double price;
    int quantity;
    double discount;

    if (choice == 1)
    {
        // Add new item to stock
        cout << "\tEnter Product Name: ";
        cin.ignore();
        getline(cin, productName);
        cout << "\tEnter Price: ";
        cin >> price;
        cout << "\tEnter Quantity: ";
        cin >> quantity;
        cout << "\tEnter Discount (%): ";
        cin >> discount;

        s.setProductName(productName);
        s.setPrice(price);
        s.setQuantity(quantity);
        s.setDiscount(discount);

        s.addToStock(); // Call to add the item to stock
    }
    else if (choice == 2)
    {
        // Update existing item in stock
        cout << "\tEnter Product Name to Update: ";
        cin.ignore();
        getline(cin, productName);
        cout << "\tEnter New Price: ";
        cin >> price;
        cout << "\tEnter New Quantity: ";
        cin >> quantity;
        cout << "\tEnter New Discount (%): ";
        cin >> discount;

        Stock::updateStock(productName, quantity, price, discount); // Static method to update stock
    }
    else if (choice == 3)
    {
        // Remove item from stock
        cout << "\tEnter Product Name to Remove: ";
        cin.ignore();
        getline(cin, productName);

        Stock::removeItem(productName); // Call the static removeItem method
    }
    else if (choice == 4)
    {
        cout << "\tExiting stock management..." << endl;
    }
    else
    {
        cout << "\tInvalid choice!" << endl;
    }
}
void clearBill()
{
    ofstream billFile("cart.csv", ios::trunc); // Open the bill file in trunc mode to clear its contents

    if (!billFile.is_open())
    {
        cout << "\tError: Unable to open bill.csv file to clear it." << endl;
        return;
    }

    cout << "\tBill has been cleared successfully!" << endl;
    billFile.close(); // Close the file after clearing

    // ofstream invoice("invoice.csv", ios::app);

    // invoice << endl;
}
void removeItemFromBill()
{
    string itemToRemove;
    cout << "\tEnter the name of the item to remove: ";
    cin.ignore(); // to handle any newline characters in the input buffer
    getline(cin, itemToRemove);

    ifstream inFile("cart.csv");       // Open the bill.csv file for reading
    ofstream outFile("cart_temp.csv"); // Temporary file for updated bill

    if (!inFile.is_open())
    {
        cout << "\tError: Unable to open bill.csv file." << endl;
        return;
    }

    bool itemFound = false;
    string line;

    // Process each line in the bill.csv file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string itemName, rateStr, quantityStr;

        // Extract the item name, rate, and quantity from the line
        getline(ss, itemName, ',');
        getline(ss, rateStr, ',');
        getline(ss, quantityStr, ',');

        // Trim any spaces
        itemName = trim(itemName);

        // Check if the current item matches the one to remove
        if (itemName == itemToRemove)
        {
            itemFound = true;
            cout << "\tItem '" << itemToRemove << "' has been removed from the bill." << endl;
            continue; // Skip adding this item to the temp file (i.e., remove it)
        }

        // Write the remaining items to the temp file
        outFile << itemName << "," << rateStr << "," << quantityStr << endl;
    }

    if (!itemFound)
    {
        cout << "\tItem '" << itemToRemove << "' not found in the bill." << endl;
    }

    inFile.close();
    outFile.close();

    // Replace the original bill.csv with the updated temp file
    remove("cart.csv");
    rename("cart_temp.csv", "cart.csv");
}

void displayHeader(const string &title)
{
    system("cls");
    cout << "\n\t************************************************************\n";
    cout << "\t*                                                          *\n";
    cout << "\t*              " << setw(50) << left << title << " *\n";
    cout << "\t*                                                          *\n";
    cout << "\t************************************************************\n\n";
}

void printDivider()
{
    cout << "\n\t============================================================\n";
}

void printFancyDivider()
{
    cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void mainMenuHeader()
{
    cout << "\n\t==================== WELCOME ====================\n";
    cout << "\t||                                                  ||\n";
    cout << "\t||        Super Market Billing & Management System   ||\n";
    cout << "\t||                                                  ||\n";
    cout << "\t======================================================\n\n";
}

void adminSectionHeader()
{
    cout << "\n\t\t[ Admin Section - Manage Everything! ]" << endl;
    printFancyDivider();
}

void customerSectionHeader()
{
    cout << "\n\t\t[ Customer Section - Shopping Made Easy! ]" << endl;
    printFancyDivider();
}

void addArt()
{
    cout << "\t______________________[ Add to Cart ]______________________\n";
    cout << "\t|                                                      |\n";
    cout << "\t|   Add Items to your Cart and Enjoy Shopping!          |\n";
    cout << "\t|______________________________________________________|\n";
}

void removeArt()
{
    cout << "\t______________________[ Remove from Cart ]______________________\n";
    cout << "\t|                                                      |\n";
    cout << "\t|   Remove Items if you changed your mind!              |\n";
    cout << "\t|______________________________________________________|\n";
}

void printBillArt()
{
    cout << "\t______________________[ Bill ]______________________\n";
    cout << "\t|                                                      |\n";
    cout << "\t|   Check your Bill and Get Ready to Pay!               |\n";
    cout << "\t|______________________________________________________|\n";
}
int main()
{
    Cart b;
    bool exit = false;

    while (!exit)
    {
        Sleep(1000); // Less wait time for smoother experience
        displayHeader("Main Menu");

        int roleChoice;
        mainMenuHeader();
        cout << "\t\t1. Admin (Store Manager)." << endl;
        cout << "\t\t2. Customer." << endl;
        cout << "\t\t3. Exit." << endl;
        printDivider();
        cout << "\t\tEnter Choice: ";
        cin >> roleChoice;

        if (roleChoice == 1) // Admin Section
        {
            int loginChoice;
            displayHeader("Admin Login/Registration");
            cout << "\t1. Register as Admin." << endl;
            cout << "\t2. Login as Admin." << endl;
            printDivider();
            cout << "\tEnter choice: ";
            cin >> loginChoice;

            if (loginChoice == 1)
            {
                registerAdmin();
                Sleep(1000);
            }
            else if (loginChoice == 2 && loginAdmin()) // If login is successful
            {
                bool adminExit = false;
                while (!adminExit)
                {
                    Sleep(1000);
                    adminSectionHeader();

                    int adminChoice;
                    cout << "\tAdmin Section Menu" << endl;
                    cout << "\t===================" << endl;
                    cout << "\t1. Manage Stock." << endl;
                    cout << "\t2. Exit to Main Menu." << endl;
                    printDivider();
                    cout << "\tEnter Choice: ";
                    cin >> adminChoice;

                    if (adminChoice == 1)
                    {
                        displayHeader("Stock Management");
                        manageStock(); // Admin manages the stock
                        Sleep(1000);
                    }
                    else if (adminChoice == 2)
                    {
                        adminExit = true;
                    }
                }
            }
        }
        else if (roleChoice == 2) // Customer Section
        {
            int loginChoice;
            displayHeader("Customer Login/Registration");
            cout << "\t1. Register as Customer." << endl;
            cout << "\t2. Login as Customer." << endl;
            printDivider();
            cout << "\tEnter choice: ";
            cin >> loginChoice;

            if (loginChoice == 1)
            {
                registerCustomer();
                Sleep(1000);
            }
            else if (loginChoice == 2 && loginCustomer()) // If login is successful
            {
                bool customerExit = false;
                while (!customerExit)
                {
                    Sleep(1000);
                    customerSectionHeader();

                    int val;
                    cout << "\tCustomer Section Menu" << endl;
                    cout << "\t=======================" << endl;
                    cout << "\t1. Add Item to Cart." << endl;
                    cout << "\t2. Remove Item from Cart." << endl;
                    cout << "\t3. Empty the Cart." << endl;
                    cout << "\t4. Print Bill." << endl;
                    cout << "\t5. Exit to Main Menu." << endl;
                    printDivider();
                    cout << "\tEnter Choice: ";
                    cin >> val;

                    if (val == 1)
                    {
                        displayHeader("Add Item to Cart");
                        addArt();
                        addItem(b); // Add item for the customer bill
                        Sleep(1000);
                    }
                    else if (val == 2)
                    {
                        displayHeader("Remove Item from Cart");
                        removeArt();
                        removeItemFromBill();
                        Sleep(1000);
                    }
                    else if (val == 3)
                    {
                        displayHeader("Empty Cart");
                        clearBill();
                        Sleep(1000);
                    }
                    else if (val == 4)
                    {
                        displayHeader("Bill");
                        printBillArt();
                        printBill(); // Print the customer's bill
                        Sleep(1000);
                    }
                    else if (val == 5)
                    {
                        customerExit = true; // Go back to main menu
                    }
                }
            }
        }
        else if (roleChoice == 3) // Exit the system
        {
            exit = true;
            displayHeader("Exiting...");
            cout << "\tGoodbye!" << endl;
            cout << "\tThank you for using the Super Market Billing System!" << endl;
            Sleep(2000);
        }
        else
        {
            cout << "\n\tInvalid Choice. Please Try Again." << endl;
            Sleep(1000);
        }
    }
}
