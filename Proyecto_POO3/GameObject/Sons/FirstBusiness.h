#pragma once
#include "../../Graphics/Texture/Texture.h"
#include <iostream>
using std::string;

class FirstBusiness : public Texture
{

	static const int ID = 100;
public:
	FirstBusiness() {};
	FirstBusiness(string fileNamee, int x, int y, int w, int h, int id = ID) :  Texture(fileNamee, x, y, w, h, ID){};
	~FirstBusiness() {};
};


