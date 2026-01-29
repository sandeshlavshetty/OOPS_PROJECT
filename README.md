

**Project Title:** Inventory Management System

**Description:**
This C++-based application is designed to manage inventory for a retail store. It provides features for adding, updating, deleting, and viewing stock items. Additionally, it allows customers to create accounts, login, and add items to their carts, with the ability to view and print their bills.

**Key Features:**

* **Stock Management:**
  - Add new items to stock
  - Update item details (price, quantity, discount)
  - Remove items from stock
  - View stock details in a tabular format
* **Customer Accounts:**
  - Customer registration
  - Customer login
* **Cart Functionality:**
  - Add items to the cart
  - View items in the cart
  - Remove items from the cart
  - Proceed to checkout and print the bill
* **Sales Reports:**
  - Generate sales reports based on various criteria
  - Analyze profit/loss, stock levels, top-selling products, and unsold stock

**Prerequisites:**
* C++ compiler (e.g., GCC, Clang)
* Standard C++ libraries

**Preview:**
<img width="1902" height="1024" alt="image" src="https://github.com/user-attachments/assets/7479cd5e-842c-4e57-856a-0864b99ce841" />
<img width="1919" height="1016" alt="image" src="https://github.com/user-attachments/assets/840d417a-6c1c-4abf-9150-b944d08df787" />
<img width="1919" height="1026" alt="image" src="https://github.com/user-attachments/assets/df782bbe-dfdd-44cf-8f5b-aecd44799263" />
<img width="1898" height="991" alt="image" src="https://github.com/user-attachments/assets/1bda2928-c6ef-4718-95fb-6eb225823b64" />
<img width="1917" height="1015" alt="image" src="https://github.com/user-attachments/assets/6bf9d61b-0aa4-4b7e-b903-bab5b3c559b7" />
<img width="1914" height="992" alt="image" src="https://github.com/user-attachments/assets/a162f7eb-6d5f-47f8-89c8-e7e86fb0095e" />


**Usage:**
1. **Compile:**
   - Open a terminal or command prompt.
   - Navigate to the project directory.
   - Compile the code using your C++ compiler:
     ```bash
     g++ inventory_management.cpp -o SuperMarket
     ```
2. **Run:**
   - Execute the compiled executable:
     ```bash
     ./SuperMarket
     ```
3. **Follow Prompts:**
   - The application will guide you through the various features.

**File Structure:**
* `inventory_management.cpp`: Main source code file containing the implementation of all classes and functions.
* `stock.csv`: Stores information about the stock items.
* `cart.csv`: Stores items added to the customer's cart.
* `invoice.csv`: Stores invoice details for each transaction.
* `admin_credentials.csv`: Stores credentials for admin users.
* `customer_credentials.csv`: Stores credentials for customer users.

**Note:**
* Ensure that the necessary CSV files are present in the project directory before running the application.
* The application assumes that the user will enter valid data. Error handling for invalid inputs can be enhanced.

**Future Enhancements:**
* Implement additional reporting features (e.g., sales trends over time).
* Integrate with a database for more efficient data management.
* Add a graphical user interface (GUI) for a more user-friendly experience.


