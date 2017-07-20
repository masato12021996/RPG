#include "Application.h"
#include "Define.h"
#include "DxLib.h"

ApplicationPtr Application::_instance;

Application::Application(){
	//�v�����C�}�����j�^�̕��A�����擾
	_screenHeight = GetSystemMetrics( SM_CYSCREEN );
	_screenWidth = GetSystemMetrics( SM_CXSCREEN );

//�t���X�N���[�����[�h�̐ݒ�
#if FULLSCREEN
	SetFullScreenResolutionMode( DX_FSRESOLUTIONMODE_DESKTOP );

//�E�B���h�E���[�h�̐ݒ�
#else
	//�t���X�N���[����3/4�̑傫���ɂ���
	_screenHeight = _screenHeight * 3/4;
	_screenWidth  = _screenWidth  * 3/4;
	//�E�B���h�E���[�h�ɂ���
	ChangeWindowMode( TRUE );
#endif

	//�A�C�R���̃Z�b�g
	//SetWindowIconID( );
	//�E�B���h�E�̖��O�ݒ�
	SetMainWindowText( WINDOW_NAME );
	// ��ʃ��[�h�̃Z�b�g
	SetGraphMode( _screenWidth, _screenHeight, COLOR_BIT_DEPTH, FPS );

	// �c�w���C�u��������������
	if( DxLib_Init( ) == -1 ) {
		_terminating = true;
		return;// �G���[���N�����璼���ɏI��
	}
	//3D�̐ݒ�
	SetUseLighting( FALSE );
	SetLightEnable( FALSE );
	SetUseZBuffer3D( TRUE );
	SetWriteZBuffer3D( TRUE );
	SetDrawScreen( DX_SCREEN_BACK );
	SetupCamera_Perspective( 12.0f * DX_PI_F / 180.0f );
	SetCameraNearFar( 10.0f, 10000.0f );
	SetAlwaysRunFlag( TRUE ) ;
	SetUseBackCulling( TRUE ) ;
    SetTextureAddressModeUV( DX_TEXADDRESS_WRAP, DX_TEXADDRESS_WRAP );
	
	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen( DX_SCREEN_BACK );

	//�ϐ��̏�����
	_terminating = false;
}

Application::~Application(){
	DxLib_End( );
}


void Application::Initialize() {
	//�C���X�^���X���Ȃ���΃C���X�^���X�쐬
	if ( !_instance ) {
		_instance = ApplicationPtr( new Application );
	}
}

void Application::Run() {
	TaskInitialize();//�^�X�N�̏�����
	//���C�����[�v
	while( true ) {

		if ( ProcessMessage() != 0 ) {
			break;
		}
		//�G�X�P�[�v�L�[�������ꂽ��I��
		if ( CheckHitKey( KEY_INPUT_ESCAPE ) != 0 ) {
			break;
		}
		//terminating��true�Ȃ�I������
		if ( _terminating ) {
			break;
		}
		TaskUpdate();//�^�X�N�̍X�V
		ScreenFlip();// ����ʂ̓��e��\��ʂɔ��f������
		ClearDrawScreen();// ��ʂ�����������
	}
	TaskFinalize();//�^�X�N�̏I������
}

void Application::Finalize() {
	//�C���X�^���X�̉��
	if ( _instance ) {
		_instance.reset();
	}
}

void Application::TaskInitialize() {
	std::map< std::string, TaskPtr >::iterator ite = _taskList.begin( );
	while ( ite != _taskList.end( ) ) {
		TaskPtr task = ite->second;
		task->Initialize( );
		ite++;
	}
}

void Application::TaskUpdate(){
	std::map< std::string, TaskPtr >::iterator ite = _taskList.begin( );
	while ( ite != _taskList.end( ) ) {
		TaskPtr task = ite->second;
		task->Update( );
		ite++;
	}
}

void Application::TaskFinalize(){
	std::map< std::string, TaskPtr >::iterator ite = _taskList.begin( );
	while ( ite != _taskList.end( ) ) {
		TaskPtr task = ite->second;
		task->Finalize( );
		ite++;
	}
}


void Application::AddTask( std::string tag, TaskPtr task ){
	if ( task ) {
		_taskList[tag] = task;
	}
}

TaskPtr Application::GetTask( std::string tag ) {
	return _taskList[tag];
}

//�C���X�^���X�̎擾
ApplicationPtr Application::GetInstance( ){
	return _instance;
}

//�X�N���[���̍����擾
int Application::GetScreenHeight() const {
	return _screenHeight;
}

//�X�N���[���̕��擾
int Application::GetScreenWidth() const {
	return _screenWidth;
}

//�A�v���P�[�V�������I��������
void Application::AppClose( ){
	_terminating = true;
}

