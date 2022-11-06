#include <iostream>
#include <fstream>
#include "../code_1/Blockchain.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    Blockchain buffCUoin;

    bool quit = false;
    while (!quit)
    {
        int option, amount;
        string inputLine;
        string source, destination, amount_str;

        cout << "=====Main Menu=====" << endl;
        cout << "1. Add a transaction" << endl;
        cout << "2. Verify Blockchain" << endl;
        cout << "3. Mine Pending Transaction" << endl;

        cout << "4. Quit" << endl;

        getline(cin, inputLine);
        option = stoi(inputLine);
        switch (option)
        {
            case 1: {
                // Add transaction
                cout << "Enter a source address: " << endl;
                getline(cin, source);
                cout << "Enter a destination address: " << endl;
                getline(cin, destination);
                cout << "Enter an amount to send: " << endl;
                getline(cin, amount_str);
                amount = stoi(amount_str);
                buffCUoin.addTransaction(source, destination, amount);
                break;
            }

            case 2: {
                // Verify Blockchain
                if(buffCUoin.isChainValid()){
                    cout << "Blockchain is valid" << endl;
                }
                else{
                    cout << "Blockchain is invalid!" << endl;
                }
                break;
            }

            case 3: {
                // Mine Pending Transaction
                cout << "Enter the address that will mine: " << endl;
                getline(cin, source);
                cout << source << " mining pending block" << endl;
                buffCUoin.minePendingTransactions(source);
                break;
            }

            case 4: {
                // Quit
                quit = true;
                break;
            }
            

        }

    buffCUoin.prettyPrint();

    }








/*
    buffCUoin.prettyPrint(); 

    cout << "ashutosh mining first block ... " << endl;
    buffCUoin.minePendingTransactions("ashutosh");
    buffCUoin.prettyPrint(); 

    cout << "ashutosh paid maciej 1 BFC ... " << endl;
    buffCUoin.addTransaction("ashutosh","maciej", 1);

    cout << "ashutosh paid asa 1 BFC ... " << endl;
    buffCUoin.addTransaction("ashutosh","asa", 1);
    cout << "asa mining second block ... " << endl;
    buffCUoin.minePendingTransactions("asa");
    buffCUoin.prettyPrint(); 
    
    cout << "asa paid ashutosh 1 BFC ... " << endl;
    buffCUoin.addTransaction("asa","ashutosh", 1);    
    cout << "ashutosh paid maciej 2 BFC ... " << endl;
    buffCUoin.addTransaction("ashutosh","maciej", 2);
    
    cout << "maciej mining third block ... " << endl;
    buffCUoin.minePendingTransactions("maciej");
    buffCUoin.prettyPrint(); 
    
    cout << "ashutosh paid asa 6 BFC ... " << endl;
    buffCUoin.addTransaction("ashutosh","asa", 6);
    buffCUoin.addTransaction("ashutosh","asa", 6);
    cout << "asa mining second block ... " << endl;
    buffCUoin.minePendingTransactions("asa");
    buffCUoin.prettyPrint(); 
    */
    return 0;
}