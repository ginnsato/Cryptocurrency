#include<iostream>
#include <sstream>

#include "Transaction.hpp"
#include "Block.hpp"
#include "Blockchain.hpp"
#include<vector>

using namespace std;

Blockchain::Blockchain() {
    Transaction genesis("BFC","BFC",0);
    pending.push_back(genesis);

    Block gBlock(pending, time(nullptr), "In the beginning..");
    chain.push_back(gBlock);

    Transaction freeMoney("BFC","make money by mining",0);      
    pending.push_back(freeMoney);

    difficulty = 4;
    miningReward = 10;
}

Block Blockchain::getLatestBlock() { 
    return chain.back();
}

void Blockchain::addTransaction(string src, string dst, int coins) {
    
    int balanceSrc = getBalanceOfAddress(src);                      // retrieve balance of address

    if(balanceSrc >= coins){        
                                                                     // see if address has enough coins to make successful transaction
        pending.push_back(Transaction(src, dst, coins));            // push transaction into pending transactions
    }
    else if(balanceSrc == -1 || balanceSrc < coins){                // otherwise balance is negative or less than amount required to make transaction

        cout << "Balance of sender is insufficient, mine blocks to get money" << endl;
    }
}

bool Blockchain::isChainValid() { 

    string hash;

    for(int i = 1; i < chain.size(); i++){                          // iterate through block chain
        if(chain[i-1].getHash() == chain[i].getPreviousHash()){     // make sure prevBlock hash equals the current blocks prev hash
            hash = chain[i].getHash();      
            for(int j = 0; j < difficulty; j++){                    // ensure that blocks hash passes dificulty level
                if(hash[j] != '0'){
                    return false;                                   // otherwise return false
                }
            }   
        }
        else{
            return false;                                   
        }
    }

    return true;
}

bool Blockchain::minePendingTransactions(string minerAddress) {
    
    // 1. create new block with pending transactions
    Block NewBlock(pending, time(nullptr), getLatestBlock().getHash());

    // 2. Invoke mineBlock with specified level of difficulty
    NewBlock.mineBlock(difficulty);

    // 3. Clear list of pending transactions 
    pending.clear();

    // 4. Push new block to chain
    chain.push_back(NewBlock);

    // 5. Reward miner by creating pending transaction with specified reward  
    pending.push_back(Transaction("BFC", minerAddress, miningReward));

    return true;
}

int Blockchain::getBalanceOfAddress(string address) {

    int total = 0;
    vector<Transaction> trans;                      // create vector of transactions to iterate through

    for(int i = 0; i < chain.size(); i++){          // iterate through the Block Chain
        trans = chain[i].returnTransactions();      // set one blocks transactions to trans           
        for(int j = 0; j < trans.size(); j++){      // iterate through transactions
            Transaction t = trans[j];               
            if(t.getReceiver() == address){         // if the specified address is recieving money,
                total += t.getAmount();             // increase their total
            }
            if(t.getSender() == address){           // if the specified address is sending money, 
                total -= t.getAmount();             // decrease their total
            }
            if(total < 0){                          // check if balance ever goes negative, if it does (which it shouldn't), return -1
                cout << "error, balance is negative" << endl;           
                return -1;                                              
            }
        }
    }
    
    for(int k = 0; k < pending.size(); k++){        // now we check the list of pending transactions
        Transaction t = pending[k];
        if(t.getReceiver() == address){             // if the specified address has pending incoming money,
                total += t.getAmount();             // increase their total
            }
        if(t.getSender() == address){               // if the specified address has pending outgoing money, 
            total -= t.getAmount();                 // decrease their total
        }
        if(total < 0){                              // check if balance ever goes negative, if it does (which it shouldn't), return -1
            cout << "error, balance is negative" << endl;           
            return -1;                                              
        }
    }

    return total;
}

void Blockchain::prettyPrint() {

    for(int i = 0; i < chain.size(); i++){
        chain[i].printBlock();
        cout << "-------------------------------------------------------------------------------" << endl;
        if(i!=chain.size()-1){
        cout << "                                       |                                       " << endl;
        cout << "                                       |                                       " << endl;
        cout << "                                       |                                       " << endl;
        cout << "                                       v                                       " << endl;
        }
    }

}