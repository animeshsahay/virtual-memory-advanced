#ifndef HEADERPART3_H
#define HEADERPART3_H

#include <iostream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <stdlib.h> 
#include <sstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <math.h>
#include <bits/stdc++.h>

//macros
#define address_byte 8

using namespace std;

class Arguments
{
private:
    int mSizeOfPage;
    int mSizeOfVirtualMemory;
    int mSizeOfPhysicalMemory;
 
public:
	Arguments(int sizeOfPage, int sizeOfVirtualMemory, int sizeOfPhysicalMemory)
    {
        setArguments(sizeOfPage, sizeOfVirtualMemory, sizeOfPhysicalMemory);
    }
 
    void setArguments(int sizeOfPage, int sizeOfVirtualMemory, int sizeOfPhysicalMemory)
    {
        mSizeOfPage = sizeOfPage;
        mSizeOfVirtualMemory = sizeOfVirtualMemory;
        mSizeOfPhysicalMemory = sizeOfPhysicalMemory;
    }
 
    int getSizeOfPage() { return mSizeOfPage; }
    int getSizeOfVirtualMemory() { return mSizeOfVirtualMemory; }
    int getSizeOfPhysicalMemory()  { return mSizeOfPhysicalMemory; }
};


void getLogicalAddress(vector<int>, Arguments *ar);
void getPageFaults(vector<int>, int);
void convertToBinandWrite(vector<int>);

#endif
