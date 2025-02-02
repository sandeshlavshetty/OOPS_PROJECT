#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <cctype>
#include <locale>
#include <iomanip>
#include <vector>
#include <unordered_map>

using namespace std;

struct StockItem
{
    string itemName;
    int rate;
    int availableQuantity;
};
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
        ofstream stockFile("stock.csv", ios::app);
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

                total_inventory_temp << name << "," << newPrice << "," << newQuantity << "," << newDiscount << endl;
                found = true;
            }
            else
            {

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

                tempFile << name << "," << newPrice << "," << newQuantity << "," << newDiscount << endl;
                found = true;
            }
            else
            {

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

            getline(ss, prodName, ',');

            if (prodName != name)
            {
                total_inventory_temp << line << endl;
            }
            else
            {
                found = true;
            }
        }

        total_inventory.close();
        total_inventory_temp.close();

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

            getline(ss, prodName, ',');

            if (prodName != name)
            {
                tempFile << line << endl;
            }
            else
            {
                found = true;
            }
        }

        stockFile.close();
        tempFile.close();

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

class Invoice
{
private:
    string itemName;
    double rate;
    int quantity;
    double amount;
    double discount;
    double discountedAmount;

public:
    Invoice(const string &itemName, double rate, int quantity, double amount, double discount, double discountedAmount)
        : itemName(itemName), rate(rate), quantity(quantity), amount(amount), discount(discount), discountedAmount(discountedAmount) {}

    string getItemName() const { return itemName; }
    double getRate() const { return rate; }
    int getQuantity() const { return quantity; }
    double getAmount() const { return amount; }
    double getDiscount() const { return discount; }
    double getDiscountedAmount() const { return discountedAmount; }
};

// Stock class definition
class Stockr
{
private:
    string productName;
    double price;
    int quantity;
    double discount;

public:
    Stockr(const string &productName, double price, int quantity, double discount)
        : productName(productName), price(price), quantity(quantity), discount(discount) {}

    Stockr() : productName(""), price(0.0), quantity(0), discount(0.0) {}

    string getProductName() const { return productName; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    double getDiscount() const { return discount; }
};

// SalesReport class definition
class SalesReport
{
private:
    vector<Invoice> invoices;
    vector<Stockr> stocks;
    unordered_map<string, Stockr> stockMap;

    // Helper function to print a horizontal bar chart
    void printBarChart(const string &label, int value, int maxLabelLength, int scaleFactor = 1) const
    {
        cout << left << setw(maxLabelLength) << label << " | ";
        for (int i = 0; i < value / scaleFactor; ++i)
        {
            cout << "*";
        }
        cout << " (" << value << ")\n";
    }

public:
    void readInvoiceData(const string &filename)
    {
        ifstream file(filename);
        string line;
        getline(file, line);

        while (getline(file, line))
        {
            stringstream ss(line);
            string itemName;
            double rate, amount, discount, discountedAmount;
            int quantity;

            getline(ss, itemName, ',');
            ss >> rate;
            ss.ignore();
            ss >> quantity;
            ss.ignore();
            ss >> amount;
            ss.ignore();
            ss >> discount;
            ss.ignore();
            ss >> discountedAmount;

            invoices.emplace_back(itemName, rate, quantity, amount, discount, discountedAmount);
        }
    }

    void readStockData(const string &filename)
    {
        ifstream file(filename);
        string line;
        getline(file, line);

        while (getline(file, line))
        {
            stringstream ss(line);
            string productName;
            double price, discount;
            int quantity;

            getline(ss, productName, ',');
            ss >> price;
            ss.ignore();
            ss >> quantity;
            ss.ignore();
            ss >> discount;

            Stockr stock(productName, price, quantity, discount);
            stocks.push_back(stock);
            stockMap[productName] = stock;
        }
    }

    void generateSalesReport() const
    {
        double totalSales = 0;
        double totalDiscount = 0;
        int totalItemsSold = 0;

        for (const auto &invoice : invoices)
        {
            totalSales += invoice.getDiscountedAmount();
            totalDiscount += invoice.getDiscount();
            totalItemsSold += invoice.getQuantity();
        }

        cout << "Total Sales:      $" << fixed << setprecision(2) << totalSales << endl;
        cout << "Total Discount:   $" << fixed << setprecision(2) << totalDiscount << endl;
        cout << "Total Items Sold: " << totalItemsSold << endl;
    }

    void profitAnalysis() const
    {
        double totalProfit = 0;
        vector<pair<string, double>> profits;

        for (const auto &invoice : invoices)
        {
            auto it = stockMap.find(invoice.getItemName());
            if (it != stockMap.end())
            {
                double costPrice = it->second.getPrice() * invoice.getQuantity();
                double profit = invoice.getDiscountedAmount() - costPrice;
                totalProfit += profit;
                profits.emplace_back(invoice.getItemName(), profit);
            }
        }

        if (totalProfit < 0)
        {
            cout << "Encountered loss:  $" << fixed << setprecision(2) << totalProfit << endl;
            // Line plot for profits with product names
            cout << "\n Loss Per Sale :\n";
            int maxLabelLength = 20;
            for (const auto &entry : profits)
            {
                cout << left << setw(maxLabelLength) << entry.first << " | ";
                int numStars = static_cast<int>(entry.second / 10);
                for (int j = 0; j < numStars; ++j)
                {
                    cout << "*";
                }
                cout << " ($" << fixed << setprecision(2) << entry.second << ")\n";
            }
        }
        else
        {
            cout << "Total Profit:      $" << fixed << setprecision(2) << totalProfit << endl;
            // Line plot for profits with product names
            cout << "\n Profit Per Sale :\n";
            int maxLabelLength = 20;
            for (const auto &entry : profits)
            {
                cout << left << setw(maxLabelLength) << entry.first << " | ";
                int numStars = static_cast<int>(entry.second / 10);
                for (int j = 0; j < numStars; ++j)
                {
                    cout << "*";
                }
                cout << " ($" << fixed << setprecision(2) << entry.second << ")\n";
            }
        }
    }

    void stockLevelAnalysis() const
    {
        cout << "\nStock Level Histogram:\n";
        int maxLabelLength = 20;
        for (const auto &stock : stocks)
        {
            printBarChart(stock.getProductName(), stock.getQuantity(), maxLabelLength, 2);
        }
    }

    void topSellingProducts() const
    {
        unordered_map<string, int> productSales;
        for (const auto &invoice : invoices)
        {
            productSales[invoice.getItemName()] += invoice.getQuantity();
        }

        cout << "\nTop-Selling Products Histogram:\n";
        int maxLabelLength = 20;
        for (const auto &entry : productSales)
        {
            printBarChart(entry.first, entry.second, maxLabelLength, 2);
        }
    }

    void unsoldStockAnalysis() const
    {
        cout << "\nUnsold Stock Items:\n";
        unordered_map<string, bool> soldItems;
        for (const auto &invoice : invoices)
        {
            soldItems[invoice.getItemName()] = true;
        }

        for (const auto &stock : stocks)
        {
            if (soldItems.find(stock.getProductName()) == soldItems.end())
            {
                cout << stock.getProductName() << " - Quantity: " << stock.getQuantity() << endl;
            }
        }
    }

    void printHeader() const
    {
        cout << "****************************************************************************\n";
        cout << "*                                                                          *\n";
        cout << "*                         Sales Report                                     *\n";
        cout << "*                                                                          *\n";
        cout << "****************************************************************************\n\n";
    }

    void printFooter() const
    {
        cout << "\n\n************ End of Report ***********************\n";
    }
};

// hash function
string hashPassword(const string &password)
{
    unsigned long hash = 0;
    for (char c : password)
    {
        hash = (hash * 31) + c;
    }
    stringstream ss;
    ss << hex << hash; // Convert the hash to a hexadecimal string
    return ss.str();
}

// Function to trim
string trim1(const string &str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if (first == string::npos || last == string::npos)
    {
        return "";
    }
    return str.substr(first, (last - first + 1));
}

// Register Admin function
bool registerAdmin()
{
    string username, password;
    cout << "\tRegister Admin" << endl;
    cout << "\tUsername: ";
    cin.ignore(); // To clear any remaining newline characters from previous input
    getline(cin, username);
    username = trim1(username);
    cout << "\tPassword: ";
    getline(cin, password);
    password = trim1(password);

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

//  Login Admin function
bool loginAdmin()
{
    string username, password;
    cout << "\tLogin Admin" << endl;
    cout << "\tUsername: ";
    cin.ignore();
    getline(cin, username);
    username = trim1(username);

    cout << "\tPassword: ";
    getline(cin, password);
    password = trim1(password);

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
    cin.ignore();
    getline(cin, username);
    username = trim1(username);

    cout << "\tPassword: ";
    getline(cin, password);
    password = trim1(password);

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
    cin.ignore();
    getline(cin, username);
    username = trim1(username);

    cout << "\tPassword: ";
    getline(cin, password);
    password = trim1(password);

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

// Function to trim whitespace
string trim(const string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
vector<StockItem> displayStock()
{
    vector<StockItem> stockList;
    ifstream stockFile("stock.csv");
    if (!stockFile.is_open())
    {
        cout << "\tError: Could not open stock.csv!" << endl;
        return stockList;
    }

    string line, itemName, priceStr, quantityStr, discountStr;
    cout << "\n\tAvailable Items in Stock:" << endl;
    cout << "\t-----------------------------------------------------" << endl;
    cout << "\t" << left << setw(5) << "No." << setw(15) << "Item Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
    cout << "\t-----------------------------------------------------" << endl;

    int count = 1;
    getline(stockFile, line);
    while (getline(stockFile, line))
    {
        stringstream ss(line);
        getline(ss, itemName, ',');
        getline(ss, priceStr, ',');
        getline(ss, quantityStr, ',');
        getline(ss, discountStr, ',');

        StockItem item;
        item.itemName = trim(itemName);
        item.rate = stoi(priceStr);
        item.availableQuantity = stoi(quantityStr);

        stockList.push_back(item);
        cout << "\t" << left << setw(5) << count++ << setw(15) << item.itemName << setw(10) << item.rate << setw(10) << item.availableQuantity << endl;
    }

    cout << "\t-----------------------------------------------------" << endl;
    stockFile.close();
    return stockList;
}

void addItem(Cart &b)
{
    bool close = false;
    while (!close)
    {
        int choice;
        cout << "\t1. Add Item to Cart." << endl;
        cout << "\t2. Close." << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            system("cls");

            // Display stock items in a table
            vector<StockItem> stockList = displayStock();
            if (stockList.empty())
            {
                cout << "\tNo items available in stock." << endl;
                return;
            }

            int itemNumber, quant;
            cout << "\n\tEnter the number of the item you want to add: ";
            cin >> itemNumber;

            if (itemNumber < 1 || itemNumber > stockList.size())
            {
                cout << "\tInvalid item number! Please try again." << endl;
                Sleep(2000);
                return;
            }

            StockItem selectedItem = stockList[itemNumber - 1];

            cout << "\tEnter Quantity for " << selectedItem.itemName << ": ";
            cin >> quant;

            if (quant > selectedItem.availableQuantity)
            {
                cout << "\tError: Only " << selectedItem.availableQuantity << " units available!" << endl;
                Sleep(2000);
                return;
            }

            cout << "\n\tYou are adding " << quant << " units of " << selectedItem.itemName << " at a price of " << selectedItem.rate << " per unit." << endl;
            cout << "\tTotal: " << quant * selectedItem.rate << endl;
            cout << "\tConfirm? (y/n): ";
            char confirm;
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y')
            {

                b.setItem(selectedItem.itemName);
                b.setRate(selectedItem.rate);
                b.setQuant(quant);

                ofstream out("cart.csv", ios::app);
                if (!out.is_open())
                {
                    cout << "\tError: Could not open cart.csv!" << endl;
                }
                else
                {

                    out << b.getItem() << "," << b.getRate() << "," << b.getQuant() << endl;
                    cout << "\tItem Added Successfully!" << endl;
                }
                out.close();
            }
            else
            {
                cout << "\tItem addition canceled." << endl;
            }

            Sleep(2000);
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
    int quantityBill = stoi(quantityStr);

    ifstream in("stock.csv");
    ofstream out("stock_temp.csv");

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

        getline(ss, stockItemName, ',');
        getline(ss, stockRateStr, ',');
        getline(ss, stockQuantityStr, ',');
        getline(ss, stockDiscountStr, ',');

        stockItemName = trim1(stockItemName);
        stockRateStr = trim1(stockRateStr);
        stockQuantityStr = trim1(stockQuantityStr);
        stockDiscountStr = trim1(stockDiscountStr);

        if (stockItemName == itemName)
        {
            itemFound = true;

            int stockQuantity = stoi(stockQuantityStr);

            int newQuantity = stockQuantity - quantityBill;

            if (newQuantity >= 0)
            {

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

            out << line << endl;
        }
    }

    if (!itemFound)
    {
        cout << "\tError: Item not found in stock: " << itemName << endl;
    }

    in.close();
    out.close();

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

    invoice << itemName << "," << rateStr << "," << quantityStr << "," << amount << "," << discount << "," << discountedAmount << endl;

    invoice.close();
}
void printBill()
{
    system("cls");
    bool close = false;

    while (!close)
    {

        int choice;
        cout << endl
             << "\t1.Add Bill." << endl;
        cout << "\t2.Close Session." << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            ifstream in("cart.csv");
            ofstream out("cart_temp.csv");

            if (!in.is_open())
            {
                cout << "\tError: Unable to open bill.csv file." << endl;
                return;
            }

            string line;
            int totalPrice = 0;
            int totalDiscountedPrice = 0;

            cout << "\n\tItem | Rate | Quantity | Amount | Discount | Discounted Amount\n";
            cout << "\t---------------------------------------------------------------\n";

            while (getline(in, line))
            {
                stringstream ss(line);
                string itemName, rateStr, quantityStr;
                int rate = 0, quantity = 0;

                getline(ss, itemName, ',');
                getline(ss, rateStr, ',');
                getline(ss, quantityStr, ',');

                itemName = trim1(itemName);
                rateStr = trim1(rateStr);
                quantityStr = trim1(quantityStr);

                if (!rateStr.empty() && !quantityStr.empty() && isNumeric(rateStr) && isNumeric(quantityStr))
                {
                    rate = stoi(rateStr);
                    quantity = stoi(quantityStr);

                    int amount = rate * quantity;
                    totalPrice += amount;

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

                        stockItemName = trim1(stockItemName);
                        stockDiscountStr = trim1(stockDiscountStr);

                        if (stockItemName == itemName)
                        {
                            discount = stoi(stockDiscountStr);
                            break;
                        }
                    }
                    stockFile.close();

                    int discountedAmount = amount - (amount * discount / 100);
                    totalDiscountedPrice += discountedAmount;

                    cout << "\t" << itemName << " | " << rate << " | " << quantity << " | " << amount
                         << " | " << discount << "% | " << discountedAmount << endl;

                    out << itemName << "," << rate << "," << quantity << endl;

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
    cout << endl
         << "\tThanks for shopping!" << endl;
    // Sleep(5000); // Pause for 5 seconds
    order++;
}

void print_stock()
{
    ifstream inFile("stock.csv");

    if (!inFile.is_open())
    {
        cout << "Error: Could not open stock.csv file!" << endl;
        return;
    }

    string line;

    string horizontalLine = "+-----------------+----------+----------+----------+";

    cout << horizontalLine << endl;
    cout << "| " << left << setw(15) << "Product Name"
         << "| " << setw(8) << "Price"
         << "| " << setw(8) << "Quantity"
         << "| " << setw(8) << "Discount" << " |" << endl;
    cout << horizontalLine << endl;

    while (getline(inFile, line))
    {
        stringstream ss(line);
        string productName, priceStr, quantityStr, discountStr;

        getline(ss, productName, ',');
        getline(ss, priceStr, ',');
        getline(ss, quantityStr, ',');
        getline(ss, discountStr, ',');

        productName = trim1(productName);
        priceStr = trim1(priceStr);
        quantityStr = trim1(quantityStr);
        discountStr = trim1(discountStr);

        cout << "| " << left << setw(15) << productName
             << "| " << right << setw(8) << priceStr
             << "| " << right << setw(8) << quantityStr
             << "| " << right << setw(8) << discountStr << " |" << endl;
    }

    cout << horizontalLine << endl;

    inFile.close();
}

void manageStock()
{

    int choice;
    cout << "\tStock Management" << endl;
    cout << "\t****************" << endl;
    cout << "\t1. Add New Item to Stock." << endl;
    cout << "\t2. Update Existing Stock." << endl;
    cout << "\t3. Remove Item from Stock." << endl;
    cout << "\t4. Print Stock." << endl;
    cout << "\t5. Exit." << endl;
    cout << "\tEnter choice: ";
    cin >> choice;

    Stock s;
    string productName;
    double price;
    int quantity;
    double discount;

    if (choice == 1)
    {

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

        s.addToStock();
    }
    else if (choice == 2)
    {

        cout << "\tEnter Product Name to Update: ";
        cin.ignore();
        getline(cin, productName);
        cout << "\tEnter New Price: ";
        cin >> price;
        cout << "\tEnter New Quantity: ";
        cin >> quantity;
        cout << "\tEnter New Discount (%): ";
        cin >> discount;

        Stock::updateStock(productName, quantity, price, discount);
    }
    else if (choice == 3)
    {

        cout << "\tEnter Product Name to Remove: ";
        cin.ignore();
        getline(cin, productName);

        Stock::removeItem(productName);
    }
    else if (choice == 4)
    {
        print_stock();
    }
    else if (choice == 5)
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
    ofstream billFile("cart.csv", ios::trunc);

    if (!billFile.is_open())
    {
        cout << "\tError: Unable to open cart.csv file to clear it." << endl;
        return;
    }

    cout << "Cart has been cleared successfully!" << endl;
    billFile.close();

    ofstream invoice("invoice.csv", ios::app);

    invoice << endl;
}
void removeItemFromBill()
{
    string itemToRemove;
    cout << "\tEnter the name of the item to remove: ";
    cin.ignore(); // to handle any newline characters in the input buffer
    getline(cin, itemToRemove);

    ifstream inFile("cart.csv");
    ofstream outFile("cart_temp.csv");

    if (!inFile.is_open())
    {
        cout << "\tError: Unable to open cart.csv file." << endl;
        return;
    }

    bool itemFound = false;
    string line;

    while (getline(inFile, line))
    {
        stringstream ss(line);
        string itemName, rateStr, quantityStr;

        getline(ss, itemName, ',');
        getline(ss, rateStr, ',');
        getline(ss, quantityStr, ',');

        itemName = trim1(itemName);

        if (itemName == itemToRemove)
        {
            itemFound = true;
            cout << "\tItem '" << itemToRemove << "' has been removed from the cart." << endl;
            continue;
        }

        outFile << itemName << "," << rateStr << "," << quantityStr << endl;
    }

    if (!itemFound)
    {
        cout << "\tItem '" << itemToRemove << "' not found in the cart." << endl;
    }

    inFile.close();
    outFile.close();

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
        Sleep(1000);
        displayHeader("Main Menu");

        int roleChoice;
        mainMenuHeader();
        cout << "\t\t1. Admin (Store Manager)." << endl;
        cout << "\t\t2. Customer." << endl;
        cout << "\t\t3. Exit." << endl;
        printDivider();
        cout << "\t\tEnter Choice: ";
        cin >> roleChoice;

        if (roleChoice == 1)
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
            else if (loginChoice == 2 && loginAdmin())
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
                    cout << "\t2. Print Report." << endl;
                    cout << "\t3. Exit to Main Menu." << endl;
                    printDivider();
                    cout << "\tEnter Choice: ";
                    cin >> adminChoice;

                    if (adminChoice == 1)
                    {
                        displayHeader("Stock Management");
                        manageStock();
                        Sleep(1000);
                    }
                    else if (adminChoice == 2)
                    {
                        SalesReport report;
                        report.readInvoiceData("invoice.csv");
                        report.readStockData("inventory.csv");
                        report.printHeader();
                        report.generateSalesReport();
                        report.profitAnalysis();
                        report.stockLevelAnalysis();
                        report.topSellingProducts();
                        report.unsoldStockAnalysis();
                        cout << endl
                             << "Remaining Stock : " << endl;
                        print_stock();
                        report.printFooter();
                    }
                    else if (adminChoice == 3)
                    {
                        adminExit = true;
                    }
                }
            }
        }
        else if (roleChoice == 2)
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
            else if (loginChoice == 2 && loginCustomer())
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
                        addItem(b);
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
                        printBill();
                        Sleep(1000);
                    }
                    else if (val == 5)
                    {
                        customerExit = true;
                    }
                }
            }
        }
        else if (roleChoice == 3)
        {
            exit = true;
            displayHeader("Exiting...");
            cout << "\tGoodbye! " << endl;
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
