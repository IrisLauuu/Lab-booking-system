#include <fstream>
#include "admin.h"
#include "globalFile.h"


Administrator::Administrator(){
	
}
		
Administrator::Administrator(std::string username, std::string password){	
	this->username = username;
	this->password = password;
	this->initVector();
}

void Administrator::initVector(){
	Administrator::vecStu.clear();
	std::ifstream ifs;
	ifs.open(STUDENT_FILE, std::ios::in);
	if(!ifs.is_open()){
		std::cout << "File Not Found." << std::endl;
		ifs.close();
		return;
	}
	Student s;
	while(ifs >> s.username && ifs>> s.password){
		vecStu.push_back(s);
	}
	ifs.close();
	
	Administrator::vecLab.clear();
	ifs.open(LAB_FILE, std::ios::in);
	if(!ifs.is_open()){
		std::cout << "File Not Found." << std::endl;
		ifs.close();
		return;
	}
	Lab l;
	while(ifs >> l.lab_id && ifs>> l.empty_seat && ifs>> l.max_capacity){
		vecLab.push_back(l);
	}
	ifs.close();
}

bool Administrator::checkRepeat(std::string un){
	for (auto it = vecStu.begin(); it != vecStu.end(); ++it) {
        if(un == it->username)
        	return true;		
    }
    return false;
}	
	
void Administrator::operateMenu(){
	  
    while(true){
    	std::cout << "Welcome Administrator :"<<this->username << std::endl;
    	std::cout << "\t\t ---------------------------------\n";
    	std::cout << "\t\t|                                |\n";
    	std::cout << "\t\t|          1.Create Account      |\n";   	   
		std::cout << "\t\t|                                |\n";
    	std::cout << "\t\t|          2.Account List        |\n";
    	std::cout << "\t\t|                                |\n";
    	std::cout << "\t\t|          3.Lab Info            |\n";
    	std::cout << "\t\t|                                |\n";
    	std::cout << "\t\t|          4.Clear Booking       |\n";
    	std::cout << "\t\t|                                |\n";
    	std::cout << "\t\t|          0.Sign Out            |\n";
    	std::cout << "\t\t|                                |\n";
    	std::cout << "\t\t ---------------------------------\n";
    	std::cout << "Please Select : " << std::endl;
    	
    	int input = 0;
    	std::cin >> input;
    	if(input == 1){
    		addAccount();
		}else if(input == 2){
			showAccount();
		}else if(input == 3){
			showLabInformation();
		}else if(input == 4){
			clearBooking();
		}else{
			return;
		}
	}
}
		
void Administrator::addAccount(){
	std::ofstream ofs;
	ofs.open(STUDENT_FILE, std::ios::out | std::ios::app);
	std::string un;
	std::string pw;
	
	std::cout << "Creating New Student Accounts... " << std::endl;
	while(true){
		std::cout << "New student account username:  " << std::endl;
		std::cin >> un;
		if(checkRepeat(un))
			std::cout << "This account has been registered, use another one. " << std::endl;
		else
			break;
	}
	std::cout << "New student account password:  " << std::endl;
	std::cin >> pw;
	
	ofs << un <<" "<< pw <<" " << std::endl;
	std::cout << "New Account has been created! " << std::endl;
	ofs.close();
	this->initVector();
	system("pause");
    system("cls");
}
		
void Administrator::showAccount(){
	std::cout << "All Student Accounts: " << std::endl;
	
	for (auto it = vecStu.begin(); it != vecStu.end(); ++it) {
        std::cout << "Username: "<<(*it).username<< ", " <<"Password: "<<(*it).password<<std::endl;
    }
    system("pause");
    system("cls");
}
		
void Administrator::showLabInformation(){
	std::cout << "All Lab Information: " << std::endl;
	for (auto it = vecLab.begin(); it != vecLab.end(); ++it) {
        std::cout << "Lab ID: "<<(*it).lab_id<<" Available: "
		<<(*it).empty_seat<<"/"<<(*it).max_capacity << std::endl;
    }
    system("pause");
    system("cls");
}
		
void Administrator::clearBooking(){
	std::ofstream ofs(BOOKING_FILE, std::ios::trunc);
	ofs.close();
	std::cout << "Booking info has been cleaned." << std::endl;
	system("pause");
    system("cls");
}