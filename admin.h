#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "identity.h"
#include "student.h"
#include "lab.h"

class Administrator : public Identity{
	
	public:
		std::vector<Student> vecStu;
		
		std::vector<Lab> vecLab;
		
		Administrator();
		
		Administrator(std::string username, std::string password);
		
		void operateMenu();
		
		void addAccount();
		
		void showAccount();
		
		void showLabInformation();
		
		void clearBooking();
		
		void initVector();
		
		bool checkRepeat(std::string un);
};