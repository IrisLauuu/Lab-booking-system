#include <iostream>
#include <string>
#include <fstream>
#include "identity.h"
#include "globalFile.h"
#include "identity.h"
#include "student.h"
#include "admin.h"

void showMainPage(){
	std::cout << "====================== Welcome To Lab Booking System =====================" 
         << std::endl;
    std::cout << "\t\t          Login Page            \n "<< std::endl;
    std::cout << "\t\t -------------------------------\n";
    std::cout << "\t\t|                               |\n";
    std::cout << "\t\t|          1. Student           |\n";
    std::cout << "\t\t|                               |\n";
    std::cout << "\t\t|          2. Administrator     |\n";
    std::cout << "\t\t|                               |\n";
    std::cout << "\t\t|          0. Quit              |\n";
    std::cout << "\t\t|                               |\n";
    std::cout << "\t\t -------------------------------\n";
    std::cout << "Please Enter Your Number: "<< std::endl;
}

void login(std::string fileName, int type){
	
	Identity *person = NULL;
	
	std::ifstream ifs;
	ifs.open(fileName, std::ios::in);
	if(!ifs.is_open()){
		std::cout << "File Not Found." << std::endl;
		ifs.close();
		return;
	}
	
	std::string inputUsername;
	std::string inputPassword;
	std::string fileUsername;
	std::string filePassword;
	std::cout << "Please Enter Your Username: " << std::endl;
	std::cin >> inputUsername;
	std::cout << "Please Enter Your Password: " << std::endl;
	std::cin >> inputPassword;
	
	if(type == 1){
			
		while(ifs >> fileUsername && ifs >> filePassword){
			if(fileUsername == inputUsername && filePassword == inputPassword){
				std::cout << "Login Successfully!" << std::endl;
				system("pause");
                system("cls");
                person = new Student(fileUsername, filePassword);
                person->operateMenu();
                delete person;
                std::cout << "Student Signout Successfully!" << std::endl;
                system("pause");
    			system("cls");
                return;
			}
		}
		
	}else if(type == 2){
		while(ifs >> fileUsername && ifs >> filePassword){
			if(fileUsername == inputUsername && filePassword == inputPassword){
				std::cout << "Login Successfully!" << std::endl;
				system("pause");
                system("cls");
                person = new Administrator(fileUsername, filePassword);
                person->operateMenu();
                delete person;
                std::cout << "Admin Signout Successfully!" << std::endl;
                system("pause");
    			system("cls");
                return;
			}
		}
	}
	
	std::cout << "Login Failed!" << std::endl;
	system("pause");
    system("cls");
	return;
}

void checkInput(std::string input){
	
	int i = std::stoi(input);
	
	switch(i){
		case 1:
			login(STUDENT_FILE, 1);
			break;
		case 2:
			login(ADMIN_FILE, 2);
			break;
		case 0:
			std::cout << "Thanks for using, see you next time." << std::endl;
			system("pause");
			exit(0);
    		break;
		default:
			std::cout << "Error! Please Enter a Valid Number Again." << std::endl;
			system("pause");
            system("cls");
            break;
	}
}

int main() 
{
	std::string input;
    while(true){
    	
    	showMainPage();
    	std::cin >> input;
    	checkInput(input);
	}
       
		
    system("pause");

    return 0;
}