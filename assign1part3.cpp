#include <iostream>
#include "headerpart3.h"

using namespace std;

int main(int argc, char ** argv){
	
	int first = atoi(argv[1]);
	int second = atoi(argv[2]);
	int third = atoi(argv[3]);
    Arguments *ar = new Arguments(first, second, third);
    FILE* file_; 
    char buffer[8] = {0}; 
    file_ = fopen(argv[4], "rb");
	vector<int> physical_address;		
    int long_value = 0;
    while (!feof(file_)) 
    {  
        fread(buffer, sizeof(buffer), 1, file_);
        memcpy(&long_value, buffer, sizeof long_value);
		physical_address.push_back(long_value);
    } 
	getLogicalAddress(physical_address, ar);
    fclose(file_);	
    return 0; 
}
