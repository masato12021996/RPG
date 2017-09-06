#include "SceneManager.h"
#include "Application.h"
#include "Scene.h"

SceneManagerPtr SceneManager::GetTask( ){
	return std::dynamic_pointer_cast<SceneManager>(Application::GetInstance()->GetTask( GetTag( ) ) );
}

//ここで初期化 主にシーンの追加を行う
SceneManager::SceneManager( ) {
}

//終了処理 基本的にマップのメモリ開放
SceneManager::~SceneManager( ) {
}

void SceneManager::Update( ){
	_currentScene->Update( );
}

//シーンを開く
void SceneManager::SceneOpen( SCENE_ID id ) {
	
}