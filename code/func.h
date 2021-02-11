#ifndef FUNC_04062019
#define FUNC_04062019

#include "Display.h"
#include "Point.h"
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>

void drawRectangle(SDL_Renderer * renderer, double x1, double y1, double x2, double y2);
void drawCircle(SDL_Renderer * renderer, double centreX, double centreY, double radius);
void rotatePoint(double angle, Point * origin, Point center); // rotate a point (origin) around a (center) point
double pi();
bool closeEnough(double a, double b); // are two double close enough to be considered equal
void splitString(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> splitString(const std::string &s, char delim); //split a string into words that are stored in a vector
double pythagoras(double a, double b); // pythagoras triangle between a and b
std::vector<std::string> menuOptions(std::string type); // returns menuoptions for a specified type
void fillCircle(SDL_Renderer * renderer, double centreX, double centreY, double radius);
double randomDouble(double min, double max);
std::vector<std::string> getLevelArray();

#endif
