#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

class Customer
{
private:
    string name;

public:
    void setName(const string &userName)
    {
        name = userName;
    }

    string getName() const
    {
        return name;
    }
};

class Product
{
private:
    string productID;
    string name;
    double price;
    int quantity;

public:
    void listProduct()
    {
        cout << "Product ID" << setw(40) << "Name" << setw(40) << "Price" << endl;
        cout << "ABC" << setw(40) << "Goat Cheese" << setw(40) << "400 PHP" << endl;
        cout << "DEF" << setw(40) << "Cheddar " << setw(40) << "700 PHP" << endl;
        cout << "GHI" << setw(40) << "Blue Cheese" << setw(40) << "120 PHP" << endl;
        cout << "JKL" << setw(40) << "Mozzarella" << setw(40) << "120 PHP" << endl;
    }

    void setProductID(const string &ID)
    {
        productID = ID;

        if (ID == "ABC")
        {
            name = "Goat Cheese";
            price = 400;
        }
        if (ID == "DEF")
        {
            name = "Cheddar";
            price = 700;
        }
        if (ID == "GHI")
        {
            name = "Blue Cheese";
            price = 120;
        }
        if (ID == "JKL")
        {
            name = "Mozzarella";
            price = 120;
        }
        quantity = 1;
    }

    string getProductID() const
    {
        return productID;
    }

    string getName() const
    {
        return name;
    }

    double getPrice() const
    {
        return price;
    }

    int getQuantity() const
    {
        return quantity;
    }

    void setQuantity(int qty)
    {
        quantity = qty;
    }
};

class ShoppingCart
{
private:
    Product cart[20];
    int productCount;

public:
    ShoppingCart() : productCount(0) {}

    void addItem(const Product &p)
    {
        if (productCount < 20)
        {
            cart[productCount] = p;
            productCount++;
        }
    }

    void displayCart() const
    {
        if (productCount == 0)
        {
            cout << "Your shopping cart is empty! Try adding some in the Menu." << endl;
            return;
        }

        cout << "These are your ordered products:" << endl;
        cout << "Product ID" << setw(35) << "Name" << setw(35) << "Price" << setw(35) << "Quantity" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;

        for (int i = 0; i < productCount; i++)
        {
            cout << cart[i].getProductID() << setw(40) << cart[i].getName() << setw(40)
                 << cart[i].getPrice() << setw(40) << cart[i].getQuantity() << endl;
        }
    }
    double getTotalAmount() const
    {
        double total = 0.0;
        for (int i = 0; i < productCount; i++)
        {
            total += cart[i].getPrice() * cart[i].getQuantity();
        }
        return total;
    }
};

class Order
{
private:
    string customerName;
    Product item;
    int itemQuantity;

public:
    Order(const string &name = "", const Product &prod = Product(), int qty = 0) : customerName(name), item(prod), itemQuantity(qty) {}

    void displayOrder() const
    {

        cout << item.getProductID() << setw(40) << item.getName() << setw(40) << item.getPrice() << setw(40) << item.getQuantity() << endl;
    }

    void setCustomerUserName(const string &name)
    {
        customerName = name;
    }

    string getCustomerName() const
    {
        return customerName;
    }
};

string getUpperCase(const string &x)
{
    string result = x;
    for (char &c : result)
    {
        c = toupper(c);
    }

    return result;
}
int main()
{
    Customer a;
    string userName;

    cout << "WElCOME TO AMAZON ONLINE!" << endl;
    cout << "Please Enter Customer's Name to Continue: ";
    getline(cin, userName);

    string uppercaseName = getUpperCase(userName); // MAKES USER NAME INPUT INTO UPPER CASE

    a.setName(uppercaseName);
    std::cout << "Hello " << a.getName() << "!" << endl
              << endl;

    Product customerA[20];
    string IDproduct;
    char addProduct, checkout;
    int menu = 0, quantity = 0, productCounter = 0;
    bool exit = true;

    ShoppingCart cartA;
    Order orderA(a.getName(), customerA[0], quantity);

    do
    {
        cout << setw(20) << "Menu" << endl;
        cout << "1. View Products" << endl;
        cout << "2. View Shopping Cart" << endl;
        cout << "3. View Orders" << endl;
        cout << "4. Exit " << endl;
        cout << "Enter the number of your choice: ";
        cin >> menu;

     
        switch (menu)
        {
        case 1: //"1. View Products"            //product ID is string
            do
            {
                customerA[productCounter].listProduct();
                string upperCaseProductID1;
                do
                {
                    cout << endl
                         << "Enter the ID of the product you want to add in the shopping cart: ";
                    cin >> IDproduct;

                   upperCaseProductID1 = getUpperCase(IDproduct);
                    if (upperCaseProductID1 != "ABC" && upperCaseProductID1 != "DEF" && upperCaseProductID1 != "GHi" && upperCaseProductID1 != "JKL")
                    {
                        cout << "Invalid Input. Please enter the correct product ID." << endl;
                    }
                } while (upperCaseProductID1 != "ABC" && upperCaseProductID1 != "DEF" && upperCaseProductID1 != "GHi" && upperCaseProductID1 != "JKL");

                string upperCaseProductID2 = getUpperCase(IDproduct);

                customerA[productCounter].setProductID(upperCaseProductID2);
                do{
                cout << "Enter the quantity of this product: ";
                cin >> quantity;
                if (quantity <=0){
                    cout << "ERROR! The quantity of the product must not be equal or lower than 0. That's absurd" << endl;
                }
                }while(quantity <=0);
                customerA[productCounter].setQuantity(quantity);

                cartA.addItem(customerA[productCounter]);

                cout << "Product Added Successfully!" << endl;
                productCounter++;

                cout << "Would you like to add another product? (Y/N): ";
                cin >> addProduct;

            } while (addProduct == 'y' || addProduct == 'Y');
            break;

        case 2: //"2. View Shopping Cart"
            cartA.displayCart();
            if (productCounter > 0)
            {   
                bool redo = false;
                do{
                cout << "Do you want to check out all the products? Y/N: ";
                cin >> checkout;

                if (checkout == 'Y' || checkout == 'y')
                {
                    cout << "Checking out the product....." << endl;
                    cartA.displayCart();
                    cout << "Total Amount: " << cartA.getTotalAmount() << "PHP" << endl;
                    cout << "You have successfully checked out the products!" << endl;
                    break;
                   
                }
                else if (checkout == 'n' || checkout == 'N')
                {
                    cout << "Returning to Menu..." << endl
                         << endl;
                         break;
                         
                }
                else
                {   
                    cout << "Invalid Input. Try again." << endl;
                    redo = true;

                }
                }while(redo);
            }

            break;
        case 3: //"3. View Orders"
            if (productCounter == 0)
            {
                cout << "No products to display! Try adding some in the Menu." << endl;
                break;
            }
            else
            {
                cout << "Displaying the details of all the orders:" << endl;
                cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                for (int i = 0; i < productCounter; i++)
                {
                    cout << "Customer's Name: " << a.getName() << endl;
                    cout << "Total Amount: " << cartA.getTotalAmount() << "PHP " << endl;
                    cout << "Product ID" << setw(35) << "Name" << setw(35) << "Price" << setw(35) << "Quantity" << endl;
                    cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;

                    for (int i = 0; i < productCounter; i++)
                    {
                        Order currentOrder(a.getName(), customerA[i], customerA[i].getQuantity());
                        currentOrder.displayOrder();
                    }
                    cout << endl
                         << endl;
                }
            }
            break;
        case 4:
            exit = false;
            break;
        default:
            cout << "Invalid Input. Please Enter the correct number." << endl;
            break;
        }
    } while (exit == true);

    return 0;
}
