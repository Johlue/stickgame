#ifndef EO_STRING_20092019
#define EO_STRING_20092019

#include <iostream>
#include <string>

enum menuTypes
{NUMBER, DROPDOWN};

class EO_String // info for EditorObjects
{
public:
  EO_String();
  EO_String(std::string v, std::string t);
  std::string value; // what is the value of the variable in question
  std::string type; // what is the type of the variable
protected:

};

#endif
