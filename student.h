#pragma once
#include <iostream>
#include <string>
#include "identity.h"
#include "lab.h"
#include <vector>

class Student : public Identity{
	
	public:
		
		std::vector<Lab> vecLab;
		
		Student();
		
		Student(std::string name, std::string password);
							
		void operateMenu();
		
		void applyBooking();
		
		void showMyBooking();		
		
		void cancelBooking();
		
};