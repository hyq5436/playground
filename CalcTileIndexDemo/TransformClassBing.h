#pragma once
/*
 * Created by CntChen 2017.03.09
 * 参考资料： https://msdn.microsoft.com/en-us/library/bb259689.aspx
 * 适用地图： bing 地图 
*/
#include "TransformClassSlippy.h"

#include<sstream>
#include<string>
#include<tuple>

class TransformClassBing: public TransformClassNormal {
public:
  TransformClassBing(int levelRange_max, int levelRange_min)
      : TransformClassNormal(levelRange_max, levelRange_min) {}
  std::string lnglatToQuadkey(int tileX, int tileY, int level) {
	std::stringstream quadKey;  
	for (int i = level; i > 0; i--)  
	{  
		char digit = '0';  
		int mask = 1 << (i - 1);  
		if ((tileX & mask) != 0)  
		{  
			digit++;  
		}  
		if ((tileY & mask) != 0)  
		{  
			digit++;  
			digit++;  
		}  
		quadKey << digit;  
	}  
	return quadKey.str();  
  }
  
  std::tuple<int, int, int> quadkeyToLnglat(const std::string& quadKey) {
	int tileX = 0;
	int tileY = 0;
	int level = quadKey.length();  
	for (int i = level; i > 0; i--)  
	{  
		int mask = 1 << (i - 1);  
		switch (quadKey[level - i])  
		{  
			case '0':  
				break;  

			case '1':  
				tileX |= mask;  
				break;  

			case '2':  
				tileY |= mask;  
				break;  

			case '3':  
				tileX |= mask;  
				tileY |= mask;  
				break;  
		}  
	}  

    return std::tuple<int, int, int>{
      tileX,
      tileY,
      level
    };
  }
};