#pragma once
#include "Task.h"
#include <string>
#include <map>

PTR(Scene);
PTR(SceneManager);

class SceneManager : public Task {
public:
	enum SCENE_ID{
		TITLE,
	};
public:
	static SceneManagerPtr GetTask( );
	static std::string GetTag(){ return "SCENE_MANAGER"; };
public:
	SceneManager( );
	virtual ~SceneManager( );
public:
	void SceneOpen( SCENE_ID id );
	void Update( );
private:
	ScenePtr _currentScene;
};