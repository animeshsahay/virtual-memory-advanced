#include <iostream>
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
#include <bits/stdc++.h>

//macros 
#define address_byte 8
#define PAGE_SIZE 128
#define FRAME_NUMBER 8
#define PAGE_NUMBER 32

using namespace std;

void getLogicalAddress(vector<int>);
void getPageFaults(vector<int>);
void convertToBinandWrite(vector<int>);

int main(int argc, char ** argv){
	
	FILE* file_; 
    char buffer[8] = {0}; 
    file_ = fopen(argv[1], "rb");
	vector<int> physical_address;		
   
    int long_value = 0;
    while (!feof(file_)) 
    {  
        fread(buffer, sizeof(buffer), 1, file_);
        memcpy(&long_value, buffer, sizeof long_value);
		physical_address.push_back(long_value);
    } 
	getLogicalAddress(physical_address);
    fclose(file_);	
    return 0; 
}

//Function calculating the respective page_number with the given page to frame transformation
void getLogicalAddress(vector<int> virtual_address){
	vector<int> arr;	
	for(vector<int>::size_type i = 0; i != virtual_address.size(); i++) {
		int page_table[PAGE_NUMBER] = {2,4,1,7,3,5,6};
		int offset = virtual_address[i] % PAGE_SIZE;
		int page_table_entry = virtual_address[i] / PAGE_SIZE; 
		int frame_entry = page_table[page_table_entry];
		int frame_address = (PAGE_SIZE * frame_entry) + offset;
		arr.push_back(frame_address);	
	}
	convertToBinandWrite(arr);
}	

void convertToBinandWrite(vector<int> final_address){
	std::string buffer;
	std::stringstream str;
	std::ofstream outfile("output-part1", std::ios::out | std::ios::binary);
	//Converting the vector values to hex and then to string
	for(vector<int>::size_type i = 0; i != final_address.size(); i++) {
		str<<hex<<std::setfill('0')<<std::setw(address_byte * 2)<<final_address[i];
		buffer = str.str();
		//bringing the string to desired format to maintain endianess
		for(int i=0;i<buffer.size()/2;i++){
		   char temp = buffer[i];
		   buffer[i] = buffer[buffer.size()-1-i];
		   buffer[buffer.length()-1-i] = temp;		
		}	
		char temp1 = buffer[0];
		buffer[0] = buffer[1];
		buffer[1] = temp1;
	
		char temp2 = buffer[2];
		buffer[2] = buffer[3];
		buffer[3] = temp2;
		
		//Writing to the file byte by byte
		for (int i = 0; i < buffer.size(); i+=2){
			string temp;
			temp.push_back(buffer[i]);
			temp.push_back(buffer[i + 1]);
			int num = stoi(temp, 0 ,16);
			outfile.write((char*)(&num), 1);
		}
		//clearing states
		str.str(std::string());
		buffer.clear();	
	}	
}
