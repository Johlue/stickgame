#ifndef EDITOROBJECT_30082019
#define EDITOROBJECT_30082019

#include "GameObject.h"

class EditorObject
{
public:
  EditorObject();
protected:
  int x; int y; int width; int height;
  int stringLength; // how many separated letters in a string
  int type; //as in object type
};

#endif
