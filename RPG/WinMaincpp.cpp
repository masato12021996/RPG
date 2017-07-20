#include "Application.h"
#include "DxLib.h"

void main();

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	//初期化
	Application::Initialize( );
	//タスクの追加
	main( );
	//タスクの実行
	Application::GetInstance()->Run( );
	//終了処理
	Application::Finalize( );
	return 0;
}
