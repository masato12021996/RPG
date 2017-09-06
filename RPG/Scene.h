#pragma once
#include <string>
#include "smart_ptr.h"

PTR( Scene );

class Scene {
public:
	Scene( int id ){ _id = id; };
	virtual ~Scene( ){ };
public:
	virtual void Initialize( )= 0;
	virtual void Update( ) = 0;
	virtual void Finalize( ) = 0;
	int GetID()const { return _id; }
private:
	 int _id;
};