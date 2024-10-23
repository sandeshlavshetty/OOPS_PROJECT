#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip> // For formatting output

using namespace std;

// Invoice class definition
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

    // Default constructor
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
        getline(file, line); // Skip the header

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
        getline(file, line); // Skip the header

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
        vector<pair<string, double>> profits; // Changed to store product names with profits

        for (const auto &invoice : invoices)
        {
            auto it = stockMap.find(invoice.getItemName());
            if (it != stockMap.end())
            {
                double costPrice = it->second.getPrice() * invoice.getQuantity();
                double profit = invoice.getDiscountedAmount() - costPrice;
                totalProfit += profit;
                profits.emplace_back(invoice.getItemName(), profit); // Store product name and profit
            }
        }

        if (totalProfit < 0)
        {
            cout << "Encountered loss:  $" << fixed << setprecision(2) << totalProfit << endl;
        }
        else
        {
            cout << "Total Profit:      $" << fixed << setprecision(2) << totalProfit << endl;
        }

        // Line plot for profits with product names
        cout << "\nProfit Line Plot (Profit Per Sale):\n";
        int maxLabelLength = 20; // Adjusted for product names
        for (const auto &entry : profits)
        {
            cout << left << setw(maxLabelLength) << entry.first << " | ";
            int numStars = static_cast<int>(entry.second / 10); // Adjusted for better scaling
            for (int j = 0; j < numStars; ++j)
            {
                cout << "*";
            }
            cout << " ($" << fixed << setprecision(2) << entry.second << ")\n";
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

// Main function
int main()
{
    SalesReport report;
    report.readInvoiceData("invoice.csv");
    report.readStockData("inventory.csv");
    report.printHeader(); // Print header before the report
    report.generateSalesReport();
    report.profitAnalysis();
    report.stockLevelAnalysis();
    report.topSellingProducts();
    report.unsoldStockAnalysis();
    report.printFooter(); // Print footer after the report

    return 0;
}
