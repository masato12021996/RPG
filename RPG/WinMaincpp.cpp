#include "Application.h"
#include "DxLib.h"

void main();

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	//������
	Application::Initialize( );
	//�^�X�N�̒ǉ�
	main( );
	//�^�X�N�̎��s
	Application::GetInstance()->Run( );
	//�I������
	Application::Finalize( );
	return 0;
}
