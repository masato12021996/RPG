#include "SceneManager.h"
#include "Application.h"
#include "Scene.h"

SceneManagerPtr SceneManager::GetTask( ){
	return std::dynamic_pointer_cast<SceneManager>(Application::GetInstance()->GetTask( GetTag( ) ) );
}

//�����ŏ����� ��ɃV�[���̒ǉ����s��
SceneManager::SceneManager( ) {
}

//�I������ ��{�I�Ƀ}�b�v�̃������J��
SceneManager::~SceneManager( ) {
}

void SceneManager::Update( ){
	_currentScene->Update( );
}

//�V�[�����J��
void SceneManager::SceneOpen( SCENE_ID id ) {
	
}