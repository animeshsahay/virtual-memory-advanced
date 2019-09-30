#include <iostream>
#include "headerpart3.h"

using namespace std;

void getLogicalAddress(vector<int> virtual_address, Arguments *argument){
	vector<int> arr;
	int page_bits = log2(argument->getSizeOfPage());
	int vm_size = log2(argument->getSizeOfVirtualMemory());
	int num_pages = vm_size - page_bits;
	int actual_page_size = pow(2,num_pages);
	int fram_size = log2(argument->getSizeOfPhysicalMemory());
	int num_frame = fram_size - page_bits;
	int actual_frame_size = pow(2,num_frame);
	for(vector<int>::size_type i = 0; i != virtual_address.size(); i++) {
		int page_table[actual_page_size] = {2,4,1,7,3,5,6};
		int offset = virtual_address[i] % argument->getSizeOfPage();
		int page_table_entry = virtual_address[i] / argument->getSizeOfPage(); 
		int frame_entry = page_table[page_table_entry];
		int frame_address = (argument->getSizeOfPage() * frame_entry) + offset;
		arr.push_back(frame_address);	
	}		
	getPageFaults(arr, actual_frame_size);		
}
