#pragma once
#include <iostream>
#include <string>

class Identity{
	
public:
	
	virtual void operateMenu() = 0;
	
	std::string username;
	std::string password;
		
};