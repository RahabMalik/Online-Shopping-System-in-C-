#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;
void login();
void registration();
void forget();
void print_time(void);
void search();
void main_menu();
int main();
void admin_login_menu();
class Customer
{
private:
    char home_address[200];
    char phone_number[12];
    string email_address;

public:
    char full_name[30];
    void enter_details();
    void display_details();
};
class Silver_Customer : public Customer
{
public:
    double applyDiscount_S(double totalAmount)
    {
        if (totalAmount >= 1500 && totalAmount < 2500)
            return 0.1 * totalAmount;
        else
            return 0.0;
    }
};

class Golden_Customer : public Customer
{
public:
    double applyDiscount_G(double totalAmount)
    {
        if (totalAmount >= 2500 && totalAmount < 3000)
            return 0.25 * totalAmount;
        else
            return 0.0;
    }
};

class Diamond_Customer : public Customer
{
public:
    double applyDiscount_D(double totalAmount)
    {
        if (totalAmount >= 3000)
            return 0.3 * totalAmount;
        else
            return 0.0;
    }
};

void Customer::enter_details()
{
    int i = 0, temp = 0, check = 0;
    cout << "\nPlease enter your details below: \n";

    while (1)
    {
        cout << "\nFull name: ";
        cin >> full_name;

        for (i = 0; i < strlen(full_name); i++)
        {
            if (toupper(full_name[i]) >= 65 && toupper(full_name[i]) <= 90 || full_name[i] == 32)
            {
                check = 1;
                continue;
            }
            else
            {
                check = 0;
                break;
            }
        }

        if (check == 1 && (i == strlen(full_name)))
            break;
        if (check == 0)
            cout << "\nInvalid name. Please enter again.";
    }

    while (1)
    {
        cout << "\nPhone number: ";
        cin >> phone_number;
        for (i = 0; i < strlen(phone_number); i++)
        {
            if ((phone_number[i] - 48 >= 0 && phone_number[i] - 48 <= 9) && strlen(phone_number) <= 11)
            {
                temp = 1;
                continue;
            }
            else
            {
                temp = 0;
                break;
            }
        }
        if (temp == 1 && (i == strlen(phone_number)) && strlen(phone_number) >= 8)
        {
            break;
        }
        else
            cout << "\nInvalid phone number. Please enter again.";
    }
    cout << "\nHome address: ";
    cin >> home_address;
    cout << "\nEmail: ";
    cin >> email_address;
}

void Customer::display_details()
{
    cout << "\n\t\tName:              " << full_name;
    cout << "\n\t\tContact Number:    " << phone_number;
    cout << "\n\t\tEmail address:     " << email_address;
}

class transaction : public Customer
{
private:
    double total_amount = 0;
    int quantity = 0;
    double price = 0;

public:
    void set_amount(int qty, double p);
    transaction operator*(const transaction &temp);
    void generate_bill();
};

void transaction::set_amount(int qty, double p)
{
    quantity = qty;
    price = p;
    total_amount += qty * p;
}

transaction transaction::operator*(const transaction &temp)
{
    transaction result;
    result.total_amount = this->quantity * this->price;
    return result;
}

void transaction::generate_bill()
{
    char item_code[6];
    string item_name;
    double item_price;
    int item_qty;
    transaction Customer_transaction;
    Customer_transaction.enter_details();
    cout << "\n\t\t---------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\tINVOICE";
    cout << "\n\t\t---------------------------------------------------------------------------------------\n";
    Customer_transaction.display_details();
    cout << "\n\t\t---------------------------------------------------------------------------------------\n";

    cout << "\t\tItem name\tPrice\t\tQuantity" << endl;

    ifstream cart;
    cart.open("ShoppingCart.txt");

    double total_amount = 0;

    while (cart >> item_code >> item_name >> item_price >> item_qty)
    {
        cout << "\t\t" << item_name << "\t\t" << item_price << "\t\t" << item_qty << endl;
        set_amount(item_qty, item_price);
        total_amount += item_qty * item_price;
    }

    Silver_Customer silverCustomer;
    Golden_Customer goldenCustomer;
    Diamond_Customer diamondCustomer;

    double discount = 0.0;

    if (total_amount >= 3000)
    {
        discount = diamondCustomer.applyDiscount_D(total_amount);
    }
    else if (total_amount >= 2500)
    {
        discount = goldenCustomer.applyDiscount_G(total_amount);
    }
    else if (total_amount >= 1500)
    {
        discount = silverCustomer.applyDiscount_S(total_amount);
    }

    double result = total_amount - discount;
    cout << "\n\t\tTotal balance due (before discount): " << total_amount;
    cout << "\n\t\tDiscount applied: " << discount;
    cout << "\n\t\tTotal balance due (after discount): " << result;
    cout << "\n\t\t---------------------------------------------------------------------------------------\n";
    print_time();
    cart.close();
    ofstream transactionRecord("TransactionRecord.txt", ios::out | ios::app);
    cart.open("ShoppingCart.txt");

    while (cart >> item_code >> item_name >> item_price >> item_qty)
    {
        transactionRecord << item_code << "   " << item_name << "   " << item_price << "   " << item_qty << endl;
    }

    cart.close();
    transactionRecord.close();
    remove("ShoppingCart.txt");
}

void print_time()
{
    time_t t;
    time(&t);
    printf("\t\t%s", ctime(&t));
}

class store_item
{
protected:
    char product_code[6];
    string product_name;
    int small_size;
    int medium_size;
    int large_size;
    double item_price;

public:
    char show_more();
    void order_item();
};

class men_category : public virtual store_item
{
public:
    char show_more();
    void show_eastern();
    void show_western();
};

class women_category : public virtual store_item
{
public:
    char show_more();
    void show_eastern();
    void show_western();
};
class kids_category : public virtual store_item
{
public:
    char show_more();
    void show_girl();
    void show_boy();
};

class shopping_cart : public men_category, public women_category, public kids_category
{
public:
    void show_cart();
    void select_item(const char filename[]);
};
char kids_category::show_more()
{
    char type;
    cout << "\nG>>>> Girl\n";
    cout << " B>>>> boy\n";
    cout << "\n\nEnter type: ";
    cin >> type;
    return type;
}
void kids_category::show_girl()
{
    ifstream infile("KidsGirlItems.txt");
    cout << "\n---------------------------------------------------------------------------------------\n";
    cout << "\n                                  Quantity (Sizes)";
    cout << "\nCode   Names\t\tSmall   Medium   Large\n";
    cout << "\n---------------------------------------------------------------------------------------\n";
    while (infile >> product_code >> product_name >> small_size >> medium_size >> large_size >> item_price)
    {
        cout << product_code << "   " << product_name << "\t\t" << small_size << "    " << medium_size << "    " << large_size << "   " << item_price << endl;
    }
    cout << "\n---------------------------------------------------------------------------------------\n";
    infile.close();
}
void kids_category::show_boy()
{
    ifstream infile("KidsBoyItems.txt");
    cout << "\n---------------------------------------------------------------------------------------\n";
    cout << "\n                                  Quantity (Sizes)";
    cout << "\nCode   Names\t\tSmall   Medium   Large\n";
    cout << "\n---------------------------------------------------------------------------------------\n";
    while (infile >> product_code >> product_name >> small_size >> medium_size >> large_size >> item_price)
    {
        cout << product_code << "   " << product_name << "\t\t" << small_size << "    " << medium_size << "    " << large_size << "   " << item_price << endl;
    }
    cout << "\n---------------------------------------------------------------------------------------\n";
    infile.close();
}
char women_category::show_more()
{
    char type;
    cout << "\n E >>>> Eastern\n";
    cout << " W >>>> Western\n";
    cout << "\n\nEnter type: ";
    cin >> type;
    return type;
}

void women_category::show_eastern()
{
    ifstream infile("WomenEasternItems.txt");
    cout << "\n---------------------------------------------------------------------------------------\n";
    cout << "\n                                  Quantity (Sizes)";
    cout << "\nCode   Names\t\tSmall   Medium   Large\n";
    cout << "\n---------------------------------------------------------------------------------------\n";
    while (infile >> product_code >> product_name >> small_size >> medium_size >> large_size >> item_price)
    {
        cout << product_code << "   " << product_name << "\t\t" << small_size << "    " << medium_size << "    " << large_size << "   " << item_price << endl;
    }
    cout << "\n---------------------------------------------------------------------------------------\n";
    infile.close();
}

void women_category::show_western()
{
    ifstream infile("WomenWesternItems.txt");
    cout << "\n---------------------------------------------------------------------------------------\n";
    cout << "\n                                  Quantity (Sizes)";
    cout << "\nCode   Names\t\tSmall   Medium   Large\n";
    cout << "\n---------------------------------------------------------------------------------------\n";
    while (infile >> product_code >> product_name >> small_size >> medium_size >> large_size >> item_price)
    {
        cout << product_code << "   " << product_name << "\t\t" << small_size << "   " << medium_size << "   " << large_size << "   " << item_price << endl;
    }
    cout << "\n---------------------------------------------------------------------------------------\n";
    infile.close();
}

char men_category::show_more()
{
    char type;
    cout << "\n E >>>> Eastern\n";
    cout << " W >>>> Western\n";
    cout << "\n\nEnter type: ";
    cin >> type;
    return type;
}

void men_category::show_eastern()
{
    ifstream infile("MenEasternItems.txt");
    cout << "\n---------------------------------------------------------------------------------------\n";
    cout << "\n                                  Quantity (Sizes)";
    cout << "\nCode   Names\t\tSmall   Medium   Large\n";
    cout << "\n---------------------------------------------------------------------------------------\n";
    while (infile >> product_code >> product_name >> small_size >> medium_size >> large_size >> item_price)
    {
        cout << product_code << "   " << product_name << "\t\t" << small_size << "   " << medium_size << "   " << large_size << "   " << item_price << endl;
    }
    cout << "\n---------------------------------------------------------------------------------------\n";
    infile.close();
}

void men_category::show_western()
{
    ifstream infile("MenWesternItems.txt");
    cout << "\n---------------------------------------------------------------------------------------\n";
    cout << "\n                                  Quantity (Sizes)";
    cout << "\nCode   Names\t\tSmall   Medium   Large\n";
    cout << "\n---------------------------------------------------------------------------------------\n";
    while (infile >> product_code >> product_name >> small_size >> medium_size >> large_size >> item_price)
    {
        cout << product_code << "   " << product_name << "\t\t" << small_size << "   " << medium_size << "   " << large_size << "   " << item_price << endl;
    }
    cout << "\n---------------------------------------------------------------------------------------\n";
    infile.close();
}

char store_item::show_more()
{
    char type;
    cout << "\n\tW >>> Women";
    cout << "\n\tM >>> Men";
    cout << "\n\tK >>> Kids";
    cout << "\n\n\tEnter type: ";
    cin >> type;
    return type;
}

void shopping_cart::select_item(const char filename[])
{
    char option[6], sizes, answer;
    int temp = 0, quantity = 0;
    ifstream infile;
    ofstream updated_file, cart_file;
    updated_file.open("temp.txt");
    cart_file.open("ShoppingCart.txt", ios::out | ios::app);

    do
    {
        cout << "\nEnter code to select: ";
        cin >> option;
        infile.open(filename);

        while (infile >> product_code >> product_name >> small_size >> medium_size >> large_size >> item_price)
        {
            if (strcmp(option, product_code) == 0)
            {
                temp = 0;
                break;
            }
            else
                temp = 1;
        }

        if (temp == 1)
        {
            cout << "\nInvalid code entered! Please enter correct code";
            infile.close();
        }

        infile.close();
    } while (temp == 1);

    infile.open(filename);

    cout << "\nS >>> Small\n";
    cout << "\nM >>> Medium\n";
    cout << "\nL >>> Large\n";

    cout << "\nEnter Size: ";
    cin >> sizes;
    while (!(sizes == 'S' || sizes == 's' || sizes == 'M' || sizes == 'm' || sizes == 'L' || sizes == 'l'))
    {
        cout << "Invalid choice .... Please enter again: ";
        cin >> sizes;
    }

    cout << "\n\nEnter Quantity: ";
    cin >> quantity;

    while (infile >> product_code >> product_name >> small_size >> medium_size >> large_size >> item_price)
    {
        if (strcmp(option, product_code) == 0)
        {
            if (((sizes == 'S' || sizes == 's') && small_size < quantity) ||
                ((sizes == 'M' || sizes == 'm') && medium_size < quantity) ||
                ((sizes == 'L' || sizes == 'l') && large_size < quantity))
            {
                cout << "\n\nSorry for inconvenience. This item is out of stock for your required size and quantity.";
                updated_file.close();
                remove("temp.txt");
                cart_file.close();
                infile.close();
                continue;
            }
            else
            {
                if (sizes == 'S' || sizes == 's')
                {
                    small_size = small_size - quantity;
                }
                else if (sizes == 'M' || sizes == 'm')
                {
                    medium_size = medium_size - quantity;
                }
                else if (sizes == 'L' || sizes == 'l')
                {
                    large_size = large_size - quantity;
                }
            }
            cart_file << product_code << "   " << product_name << "   " << item_price << "   " << quantity << endl;
            cout << endl
                 << product_code << "\t\t" << product_name << "\t\t" << item_price << "\t\t" << quantity << endl;
        }
        updated_file << product_code << "   " << product_name << "   " << small_size << "   " << medium_size << "   " << large_size << "   " << item_price << endl;
    }
    infile.close();
    cart_file.close();
    updated_file.close();
    remove(filename);
    rename("temp.txt", filename);

    cout << "\nDo you want to buy anything else?(y/n)";
    cin >> answer;
    if (answer == 'y')
    {
        order_item();
    }
    else
    {
        show_cart();
    }
}
void store_item::order_item()
{
    shopping_cart cart;
    char type;
    do
    {
        type = show_more();
        if (type == 'M' || type == 'm')
        {
            men_category men;
            do
            {
                type = men.show_more();
                if (type == 'E' || type == 'e')
                {
                    men.show_eastern();
                    cart.select_item("MenEasternItems.txt");
                }
                else if (type == 'W' || type == 'w')
                {
                    men.show_western();
                    cart.select_item("MenWesternItems.txt");
                }
                else
                {
                    cout << "\nInvalid Choice! Please enter correct choice";
                }

            } while (!(type == 'E' || type == 'e' || type == 'W' || type == 'w'));
        }
        else if (type == 'W' || type == 'w')
        {
            women_category women;
            do
            {
                type = women.show_more();
                if (type == 'E' || type == 'e')
                {
                    women.show_eastern();
                    cart.select_item("WomenEasternItems.txt");
                }
                else if (type == 'W' || type == 'w')
                {
                    women.show_western();
                    cart.select_item("WomenWesternItems.txt");
                }
                else
                {
                    cout << "\nInvalid Choice! Please enter correct choice";
                }

            } while (!(type == 'E' || type == 'e' || type == 'W' || type == 'w'));
        }
        else if (type == 'K' || type == 'k')
        {
            kids_category k;
            do
            {
                type = k.show_more();
                if (type == 'G' || type == 'g')
                {
                    k.show_girl();
                    cart.select_item("KidsGirlItems.txt");
                }
                else if (type == 'B' || type == 'b')
                {
                    k.show_boy();
                    cart.select_item("KidsBoyItems.txt");
                }
                else
                {
                    cout << "\nInvalid Choice! Please enter correct choice";
                }

            } while (!(type == 'G' || type == 'B' || type == 'b' || type == 'g'));
        }
        else
        {
            cout << "\nInvalid Choice! Please enter correct choice";
        }

    } while (!(type == 'M' || type == 'm' || type == 'W' || type == 'w'));
}

void shopping_cart::show_cart()
{
    int quantity = 0;
    ifstream cart_file("ShoppingCart.txt");
    cout << "\n\t\t\t\t\t\tYour Cart";
    cout << "\n\t\t---------------------------------------------------------------------------------------\n";
    cout << "\n\t\t\tCode   Names\t\t\tPrice\t\tQuantity\n";
    cout << "\n\t\t---------------------------------------------------------------------------------------\n";
    while (cart_file >> product_code >> product_name >> item_price >> quantity)
    {
        cout << "\t\t\t" << product_code << "   " << product_name << "\t\t\t" << item_price << "\t\t" << quantity << endl;
    }
    cout << "\n\t\t---------------------------------------------------------------------------------------\n";
    cart_file.close();
    // Display the bill
    transaction transaction_obj;
    transaction_obj.generate_bill();
    char q;
    cout << "Press 1 to go to main menu: " << endl;
    cout << "Press 2 to exit :" << endl;
    cin >> q;
    switch (q)
    {
    case '1':
    {
        main();
        break;
    }
    case '2':
    {
        exit(0);
    }
    default:
        cout << "Enter right option " << endl;
    }
}
bool admin_login()
{
    string admin_email = "rehabmalik@gmail.com";
    string admin_password = "rehab123";

    string entered_email, entered_password;

    cout << "Enter Admin Email: ";
    cin >> entered_email;

    cout << "Enter Admin Password: ";
    cin >> entered_password;

    return (entered_email == admin_email && entered_password == admin_password);
}

void show_transaction_records()
{
    ifstream transactionRecord("TransactionRecord.txt");
    char c, q;
    cout << "Press 1 to see all transactions: " << endl;
    cout << "Press 2 to see transaction of specific Id :" << endl;
    cin >> c;
    if (c == '1')
    {
        cout << "\n\t\t\t\t\tTransaction Records";
        cout << "\n\t\t---------------------------------------------------------------------------------------\n";
        cout << "\n\t\t\tCode   Names\tPrice\tQuantity\n";
        cout << "\n\t\t---------------------------------------------------------------------------------------\n";
        string line;
        while (getline(transactionRecord, line)) // puri line ko read kre ga specific .txt file se aur line string mn save
        {                                        // krwa dega
            cout << "\t\t\t" << line << endl;
        }

        cout << "\n\t\t---------------------------------------------------------------------------------------\n";
        transactionRecord.close();
        cout << "Press 1 to go to main menu: " << endl;
        cout << "Press 2 to exit :" << endl;
        cin >> q;
        switch (q)
        {
        case '1':
        {
            main();
            break;
        }
        case '2':
        {
            exit(0);
        }
        default:
            cout << "Enter right option " << endl;
        }
    }
    else if (c == '2')
    {
        char c;
        string productCode;
        cout << "Enter product code to display details: ";
        cin >> productCode;
        bool found = false;
        string product_code, product_name;
        double item_price;
        int quantity;

        ifstream cart_file("TransactionRecord.txt");
        while (cart_file >> product_code >> product_name >> item_price >> quantity)
        {
            if (product_code == productCode)
            {
                found = true;
                cout << "\n\t\t\t" << product_code << "   " << product_name << "\t" << item_price << "\t" << quantity << endl;
            }
        }

        cart_file.close();

        if (!found)
        {
            cout << "\nProduct with code " << productCode << " not found in the transaction records.\n";
            show_transaction_records();
        }
    }
    else
    {
        cout << "Enter right choice: " << endl;
    }
    cout << "Press 1 to go to main menu: " << endl;
    cout << "Press 2 to exit :" << endl;
    cin >> q;
    switch (q)
    {
    case '1':
    {
        main();
        break;
    }
    case '2':
    {
        exit(0);
    }
    default:
        cout << "Enter right option " << endl;
    }
}

void admin_login_menu()
{
    char admin_choice;
    if (admin_login())
    {

        cout << "\n\t\t _________________________________________________________________\n";
        cout << "\t\t|                         ADMIN MENU                                |\n";
        cout << "\t\t|___________________________________________________________________|\n\n";
        cout << "\t\t| Press 1 to view transaction records                              |\n";
        cout << "\t\t| Press 2 to go back to the main menu                              |\n";
        cout << "\n\t\tPlease enter your choice:";
        cin >> admin_choice;

        switch (admin_choice)
        {
        case '1':
            show_transaction_records();
            break;

        case '2':
            main();
            break;

        default:
            cout << "Please select from the options given above.\n";
        }
    }
    else
    {
        cout << "Enter right username or password" << endl;
    }
}

void main_menu()
{
    char choice;

    cout << "\t\t\t _________________________________________________________________\n";
    cout << "\t\t\t|                    WELCOME TO LOGIN PAGE                        |\n";
    cout << "\t\t\t|                                                                 |\n";
    cout << "\t\t\t|______________________      MENU        _________________________|\n\n\n";
    cout << "\t| Press 1 to login                  |" << endl;
    cout << "\t| Press 2 to registration           |" << endl;
    cout << "\t| Press 3 if you forget password    |" << endl;
    cout << "\t| Press 4 to exit                   |" << endl;
    cout << "\n\t\tPlease enter your choice:";
    cin >> choice;
    switch (choice)
    {
    case '1':
        login();
        break;
    case '2':
        registration();
        break;
    case '3':
        forget();
        break;
    case '4':
        cout << "\t\t\t Thank you!\n\n";
        exit(0);
    default:
        system("cls");
        cout << "Please select from the options given above\n";
        main_menu();
    }
}

void registration()
{
    string username, password;
    system("cls");
    cout << "\t\t\tEnter username:" << endl;
    cin >> username;
    cout << "\t\t\tEnter password:" << endl;
    cin >> password;

    ofstream out("data.txt", ios::app);
    out << username << " " << password << endl;
    system("cls");
    cout << "Registration is successful" << endl;
    main_menu();
}

void login()
{
    int count = 0;
    string username, password, stored_username, stored_password;
    system("cls");
    cout << "\t\tPlease enter username and password:" << endl;
    cout << "\t\t  USERNAME:  " << endl;
    cin >> username;
    cout << "\t\t   PASSWORD:  " << endl;
    cin >> password;

    ifstream in("data.txt");

    while (in >> stored_username >> stored_password)
    {
        if (stored_username == username && stored_password == password)
        {
            count = 1;
            system("cls");
            break;
        }
    }
    in.close();
    system("cls");
    if (count == 1)
    {
        cout << username << "\n Your login is successful \n Thanks for logging in! \n"
             << endl;

        cout << "\t\t\t _________________________________________________________________\n";
        cout << "\t\t\t|                WELCOME TO ONLINE SHOPPING                       |\n";
        cout << "\t\t\t|                                                                 |\n";
        cout << "\t\t\t|______________________      MENU        _________________________|\n\n\n";

        store_item store;
        store.order_item();
    }
    else
    {
        cout << "Login error! \n Please check your username and password\n";
        main_menu();
    }
}

void forget()
{
    char option;
    cout << "\t\t Forgot your password? No worries" << endl;
    cout << " Press 1 to search your Id by name" << endl;
    cout << " Press 2 to go to the main menu" << endl;
    cout << "\t\t Enter your choice " << endl;
    cin >> option;

    switch (option)
    {
    case '1':
        search();
        break;
    case '2':
        main_menu();
        break;
    default:
        cout << "Invalid option. Please enter 1 or 2." << endl;
        forget();
    }
}

void search()
{
    int option;
    string search_name, stored_username, stored_password, name;

    cout << "Enter your name: ";
    cin >> search_name;

    ifstream in("data.txt");

    while (in >> stored_username >> stored_password)
    {
        if (stored_username == search_name)
        {
            name = stored_username;
            break;
        }
    }
    in.close();
    if (name == search_name)
    {
        cout << "Your Id is: " << name << "\n Enter 3 to go to main menu: ";
        cin >> option;
        if (option == 3)
        {
            main_menu();
        }
        else
        {
            cout << "Invalid option. Please enter 3." << endl;
            search();
        }
    }
    else
    {
        cout << "Name not found. Please try again." << endl;
        search();
    }
}
int main()
{
    char c;
    system("cls");
    cout << "\t\t\t _________________________________________________________________\n";
    cout << "\t\t\t|                    WELCOME TO LOGIN PAGE                        |\n";
    cout << "\t\t\t|                                                                 |\n";
    cout << "\t\t\t|______________________      MENU        _________________________|\n\n\n";
    cout << "\t| Enter 1 for user:       |" << endl;
    cout << "\t| Enter 2 for admin       |" << endl;
    cin >> c;
    if (c == '1')
    {
        main_menu();
    }
    else if (c == '2')
    {
        admin_login_menu();
    }
    else
    {
        cout << "Invalid input. Please enter 1 or 2.\n";
        main();
    }
    return 0;
}
