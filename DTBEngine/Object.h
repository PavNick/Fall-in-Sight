#pragma once

#include <string>

class Object
{
	std::string propertyString;
	int propertyInt;
	float propertyFloat;
	bool propertyBool;
public:
	// set
	void setProp(std::string prop) { this->propertyString = prop; }
	void setProp(int prop) { this->propertyInt = prop; }
	void setProp(float prop) { this->propertyFloat = prop; }
	void setProp(bool prop) { this->propertyBool = prop; }
	// get
	std::string getString() { return this->propertyString; }
	int getInt() { return this->propertyInt; }
	float getFloat() { return this->propertyFloat; }
	bool getBool() { return this->propertyBool; }
};