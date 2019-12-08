#pragma once
#include "../../Graphics/Texture/Texture.h"
#include <iostream>
using std::string;

class FirstBusiness : public Texture
{
public:
	FirstBusiness(string fileNamee, int x, int y, int w, int h) : Texture(fileNamee, x, y, w, h){};
	~FirstBusiness() {};
};


