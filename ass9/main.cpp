//  The correct code
//  Created by Mega Putra on 3/15/17.
//  Copyright © 2017 Mega Putra. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;

#include "fruit_list.h"

int main(void)
{
    ifstream transactionInputFile;
    Fruit_List Groceries;
    Groceries.openFile(transactionInputFile, "transaction_list2.txt");
    Groceries.getTransactions(transactionInputFile,0);
}

