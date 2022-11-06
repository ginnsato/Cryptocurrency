#include<iostream>
#include <sstream>
#include <string.h>

#include "Transaction.hpp"
#include "Block.hpp"
#include "sha256.hpp"

using namespace std;

Block::Block(vector<Transaction> _transactions, time_t _timestamp, string _previousHash) {
    nonce = -1;
    transactions = _transactions;
    previousHash = _previousHash;
    timestamp = _timestamp;
    hash = calculateHash();
}

void Block::setPreviousHash(string _previousHash) {
    previousHash = _previousHash;
}

string Block::calculateHash() {
    return sha256(toString());
}

void Block::mineBlock(unsigned int difficulty) {
    int count;
    while(1){
        count = 0;                                  // reset count
        for(int i = 0; i < difficulty; i++){        // iterate through first #difficulty letters of hash
            if(hash[i] == '0'){                     // check if they are '0'
                count ++;                           // iterate count
            }
        }
        if(count == difficulty){                    // if true we have have successfully mined block
            break;
        }
        nonce ++;                                   // otherwise iterate nonce
        hash = calculateHash();                     // recalculate hash
    }
}

string Block::toString() {

    stringstream ss;                                // create string stream object
    string s = "";       

    vector<Transaction> trans;
               
    for(int j = 0; j < trans.size(); j++){
        Transaction t = trans[j];
        s += t.toString();                          // concatenate string of transactions
    }

    ss << nonce << timestamp << previousHash << s;  // put them into string stream object
    return ss.str();                                // return string version of ss 
}

vector<Transaction> Block::returnTransactions() {   
    return transactions;
}

string Block::getHash(){                            
    return hash;
}

string Block::getPreviousHash(){
    return previousHash;
}

void Block::printBlock(){
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "     Nonce:    " << nonce << endl;
    cout << " Transactions: ";
    for(int i = 0; i < transactions.size(); i++){
        if(i == 0){
            cout << transactions[i].toString() << endl;
        }
        else{
            cout << "               " << transactions[i].toString() << endl;
        }
    }
    cout << "  Time Stamp:  " << timestamp << endl;
    cout << "Previous Hash: " << previousHash << endl;
    cout << "     Hash:     " << hash << endl;

}