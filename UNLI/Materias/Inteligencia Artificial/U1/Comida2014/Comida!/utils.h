#pragma once
#include "stdafx.h"
#include <random>

using namespace sf;

class Utils{

public:

	static Vector2f GetRandomVec(float minx, float maxx, float miny, float maxy){

		static std::tr1::mt19937 eng((unsigned int)time(NULL));  // a core engine class 
		//eng.seed((unsigned int)time(NULL));
		std::tr1::uniform_real<float> distX(minx, maxx);
		std::tr1::uniform_real<float> distY(miny, maxy);

		Vector2f ret;
		ret.x = distX(eng);
		ret.y = distY(eng);
		return ret;
	}


	static inline int GetRandomIntValue(int min, int max){
		static std::tr1::mt19937 eng((unsigned int)time(NULL));  // a core engine class 
		//eng.seed((unsigned int)time(NULL));
		std::tr1::uniform_int<int> dist(min, max);
		return dist(eng);
	}

	static  float GetVecDistance(Vector2f a, Vector2f b){

		return sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));

	}

};