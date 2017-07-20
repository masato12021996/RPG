/*******************************
Application管理クラス
アプリケーションの初期化
タスクの管理を行う
*******************************/
#pragma once
#include "smart_ptr.h"
#include "Task.h"
#include <map>
#include <string>

PTR(Application);

class Application {
public:
	Application();
	virtual ~Application();
public:
	static void Initialize();
	static void Finalize();
	static ApplicationPtr GetInstance( );
public:
	void Run();
	void AppClose( );
	void AddTask( std::string tag, TaskPtr task );
	TaskPtr GetTask( std::string tag ); 
	int GetScreenWidth() const;
	int GetScreenHeight() const;
private:
	void TaskInitialize();
	void TaskUpdate();
	void TaskFinalize();
private:
	static ApplicationPtr _instance;
	int _screenWidth;
	int _screenHeight;
	bool _terminating;
	std::map<std::string, TaskPtr> _taskList;
};