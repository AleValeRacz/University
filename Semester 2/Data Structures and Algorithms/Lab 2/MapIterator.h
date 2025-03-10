#pragma once
#include "Map.h"
class MapIterator
{
	//DO NOT CHANGE THIS PART
	friend class Map;
private:
	 Map& map;
	Node* current;
	
	MapIterator( Map& m);
public:
	TElem remove();
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};


