#include "student.h"
#include <fstream>
#include <tuple>
#include "globalFile.h"

Student::Student(){
	
}
		
Student::Student(std::string name, std::string password){
	this->username = name;
	this->password = password;
	std::ifstream ifs;
	ifs.open(LAB_FILE, std::ios::in);
	if(!ifs.is_open()){
		std::cout << "File Not Found." << std::endl;
		ifs.close();
		return;
	}
	Lab l;
	while(ifs >> l.lab_id && ifs>>l.empty_seat  && ifs>> l.max_capacity){
		vecLab.push_back(l);
	}
	ifs.close();
}
							
void Student::operateMenu(){
	while(true){
    	std::cout << "Welcome Student :"<<this->username << std::endl;
    	std::cout << "\t\t ---------------------------------\n";
    	std::cout << "\t\t|                                |\n";
    	std::cout << "\t\t|          1.Book a Lab          |\n";   		
	    std::cout << "\t\t|                                |\n";
    	std::cout << "\t\t|          2.My Booking          |\n";
    	std::cout << "\t\t|                                |\n";
    	std::cout << "\t\t|          3.Cancel Booking      |\n";
    	std::cout << "\t\t|                                |\n";
    	std::cout << "\t\t|          0.Sign Out            |\n";
    	std::cout << "\t\t|                                |\n";
    	std::cout << "\t\t ---------------------------------\n";
    	std::cout << "Please Select : " << std::endl;
    	
    	int input = 0;
    	std::cin >> input;
    	if(input == 1){
    		applyBooking();
		}else if(input == 2){
			showMyBooking();
		}else if(input == 3){
			cancelBooking();
		}else{
			return;
		}
	}
}
		
void Student::applyBooking(){
	std::cout << "Lab Open Hours: 8AM-12AM, 1PM-5PM " << std::endl<<std::endl;
	std::cout << "Choose booking time " << std::endl;
	std::cout << "1. AM  " << std::endl;
	std::cout << "2. PM  " << std::endl;
	int date = 0;
	while(true){
		std::cin >> date;
		if(date == 1 || date == 2 )
			break;
		std::cout << "Invalid input.Try again." << std::endl;
	}
	std::cout << "Select lab room: " << std::endl;
	std::cout << "LAB 1: " << vecLab[0].empty_seat <<"/"<<vecLab[0].max_capacity << std::endl;
	std::cout << "LAB 2: " << vecLab[1].empty_seat <<"/"<<vecLab[1].max_capacity << std::endl;
	std::cout << "LAB 3: " << vecLab[2].empty_seat <<"/"<<vecLab[2].max_capacity << std::endl;
	int room = 0;
	while(true){
		std::cin >> room;
		if(room >= 1 && room <= 3 && vecLab[(room-1)].empty_seat > 0){
			vecLab[(room-1)].empty_seat --;
			std::cout << "Booking Confirmed! " << std::endl;
			break;
		}
		std::cout << "Invalid input.Try again." << std::endl;
	}
	std::ofstream ofs;
	ofs.open(BOOKING_FILE, std::ios::app);
	ofs << this->username <<" " << date << " "<< room << std::endl;
	ofs.close();
	
	ofs.open(LAB_FILE, std::ios::trunc);
	for(int i = 0; i < 3; i++){
		ofs << (i+1) <<" "<< vecLab[i].empty_seat <<" "<< vecLab[i].max_capacity << std::endl;
	}
	ofs.close();
	system("pause");
    system("cls");
}
		
void Student::showMyBooking(){
	std::ifstream ifs;
	ifs.open(BOOKING_FILE, std::ios::in);
	if(!ifs.is_open()){
		std::cout << "File Not Found." << std::endl;
		ifs.close();
		return;
	}
	std::string un;
	int date;
	int room;
	std::cout << "Booking History for " << this->username << ": "<< std::endl << std::endl;
	while(ifs >> un && ifs>> date && ifs>> room){
		if(un == this->username){			
			std::cout << "Tomorrow "<< (date == 1 ? "8AM-12AM" : "1PM-5PM" ) << " LAB " << room << std::endl<< std::endl;				
		}			
	}
	ifs.close();
	system("pause");
    system("cls");
}
	
		
void Student::cancelBooking(){
	std::ifstream ifs;
	ifs.open(BOOKING_FILE, std::ios::in);
	std::string un;
	int date;
	int room;
	int i = 0;
	int index = 1;
	std::vector<int> vecIndex;
	std::vector<std::tuple<std::string, int ,int>> vecBooking;
	std::cout << "Booking History for " << this->username << ": "<< std::endl << std::endl;
	while(ifs >> un && ifs>> date && ifs>> room){		
		auto booking = std::make_tuple(un, date, room);
		vecBooking.push_back(booking);		
		if(un == this->username){	
			vecIndex.push_back(i);			
			std::cout << index++ <<". Tomorrow "<< (date == 1 ? "8AM-12AM" : "1PM-5PM" ) << " LAB " << room << std::endl<< std::endl;				
		}
		i++;			
	}
	ifs.close();
	
	std::cout << "Please enter the one you want to cancel:" << std::endl;
	int select = 0;
	while(true){
		std::cin >> select;
		if(select >= 0 && select <= vecIndex.size() ){
			vecBooking.erase(vecBooking.begin()+vecIndex[select-1]);
			std::cout << "This booking has been cancelled." << std::endl;
			break;
		}
			
		std::cout << "Invalid input.Try again." << std::endl;
	}
	std::ofstream ofs;
	ofs.open(BOOKING_FILE, std::ios::trunc);
	for (auto it = vecBooking.begin(); it != vecBooking.end(); ++it) {
        ofs << std::get<0>((*it)) <<" " << std::get<1>((*it)) << " "<< std::get<2>((*it)) << std::endl;
    }
	ofs.close();
	system("pause");
    system("cls");
}