#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::cerr;
using std::string;
using std::ifstream;
using std::ofstream;
using std::setw;
using std::fixed;
using std::setprecision;
using std::left;
using std::right;
using std::ostream;

// github.com/csc2330-master/array-file-class-exercise

void ShowProducts(const string products[], const double prices[], unsigned int size); // Parallel arrays
void OutputInvoice(ostream& output, double total);

int main() {
    const int MAX_PRODUCTS = 100;
    string products[MAX_PRODUCTS];
    double prices[MAX_PRODUCTS] = {0};
    string filename;
    cout << "Dear user, give me the filename: ";
    cin >> filename;
    ifstream productDataFile(filename);
    ofstream invoice;
    if (!productDataFile.is_open()){
        cerr << "Could not open file!" << endl;
        exit(1);
    }
    string product;
    double price;
    int productCount = 0;
    while (productDataFile >> product >> price){
        if (productCount == MAX_PRODUCTS){
            cerr << "Data FULL!!!!" << endl;
            break;
        }
        products[productCount] = product;
        prices[productCount] = price;
        productCount++;
    }
    productDataFile.close();
    char finish, customerFinish;
    int productNumber, productQuantity;
    double customerTotal;
    do{
        customerTotal = 0;
        do {
            ShowProducts(products, prices, productCount);
            cout << "Which product do you want: ";
            cin >> productNumber;
            cout << "How many do you want: ";
            cin >> productQuantity;
            customerTotal += productQuantity * prices[productNumber - 1];
            cout << "Do you want to finish? ";
            cin >> customerFinish;
        }while (customerFinish == 'n');
        // Invoice
        OutputInvoice(cout, customerTotal);
        // File Invoice
        invoice.open("../data/invoice.txt");
        if (!invoice.is_open()){
            cerr << "Could not open invoice file" << endl;
        }else{
            OutputInvoice(invoice, customerTotal);
        }
        invoice.close();
        cout << "Do you want to finish? ";
        cin >> finish;
    }while(finish == 'n');



    // Load the data from file into arrays products and prices
    // Loop for each customer
    // Inside each customer, show the list of products, let the user select the product and quantity, until they tired
    // Show invoice on screen, and save to file
    // go to next customer

    return 0;
}

void ShowProducts(const string products[], const double prices[], unsigned int size){
    for (int i = 0; i < size; ++i) {
        cout << setw(4) << i + 1 << setw(18) << products[i] << setw(8) << fixed << setprecision(2) << prices[i]  << endl;
    }
}

void OutputInvoice(ostream& output, double total){
    output << "Thank you for your patronage!" << endl;
    output << "Your total is: " << fixed << setprecision(2) << total << endl;
    output << "We do not collect tax, because we pay it for you" << endl;

}
