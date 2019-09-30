//This function file calculates the actual physical frames that are being allocated.
#include "headerpart3.h"
#include <iostream>

using namespace std;

void getPageFaults(vector<int> frame_address, int frame_size){

	int set_size = frame_size;		//getting value of number of frames from command lines
	int size = frame_address.size();
	vector<int> final_address;	
	unordered_set<int> s_page; //current pages are represented by this
	
	unordered_map<int, int> maps; //to store index of least recently used page
	int fault = 0;

	//starting from index 1 because 0 frame is reserved for the OS
	for(int i=1;i<=size;i++){
		if(s_page.size() < set_size){
			if(s_page.find(frame_address[i])==s_page.end()){ //if page not present insert it and increase the page fault
				s_page.insert(frame_address[i]);
				fault++;
			}
			maps[frame_address[i]] = i;		
		}
		else{
			if(s_page.find(frame_address[i])==s_page.end()){
				int leastRecentlyUsed = INT_MAX;
				int val;
				for(auto it=s_page.begin();it!=s_page.end();it++){ //find the least recently used page 
					if(maps[*it]<leastRecentlyUsed){
						leastRecentlyUsed = maps[*it];
						val = *it;
					}
				}
				s_page.erase(val); //remove the page and increase the page fault
				s_page.insert(frame_address[i]);
				
				fault++;
			}
			maps[frame_address[i]] = i;
		}	
	}
	
	//printing the physical_addresses in the required format
  	for ( auto it = maps.begin(); it != maps.end(); ++it ){
    	final_address.push_back(it->first);
    }
  	
  	cout<<"Page fault is:"<<fault<<endl;
  	
	convertToBinandWrite(final_address);
}

void convertToBinandWrite(vector<int> final_address){
	std::string buffer;
	std::stringstream str;
	std::ofstream outfile("output-part2", std::ios::out | std::ios::binary);
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
