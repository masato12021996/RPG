#include "Application.h"
#include "Define.h"
#include "DxLib.h"

ApplicationPtr Application::_instance;

Application::Application(){
	//プレライマリモニタの幅、高さ取得
	_screenHeight = GetSystemMetrics( SM_CYSCREEN );
	_screenWidth = GetSystemMetrics( SM_CXSCREEN );

//フルスクリーンモードの設定
#if FULLSCREEN
	SetFullScreenResolutionMode( DX_FSRESOLUTIONMODE_DESKTOP );

//ウィンドウモードの設定
#else
	//フルスクリーンの3/4の大きさにする
	_screenHeight = _screenHeight * 3/4;
	_screenWidth  = _screenWidth  * 3/4;
	//ウィンドウモードにする
	ChangeWindowMode( TRUE );
#endif

	//アイコンのセット
	//SetWindowIconID( );
	//ウィンドウの名前設定
	SetMainWindowText( WINDOW_NAME );
	// 画面モードのセット
	SetGraphMode( _screenWidth, _screenHeight, COLOR_BIT_DEPTH, FPS );

	// ＤＸライブラリ初期化処理
	if( DxLib_Init( ) == -1 ) {
		_terminating = true;
		return;// エラーが起きたら直ちに終了
	}
	//3Dの設定
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
	
	// 描画先画面を裏画面にセット
	SetDrawScreen( DX_SCREEN_BACK );

	//変数の初期化
	_terminating = false;
}

Application::~Application(){
	DxLib_End( );
}


void Application::Initialize() {
	//インスタンスがなければインスタンス作成
	if ( !_instance ) {
		_instance = ApplicationPtr( new Application );
	}
}

void Application::Run() {
	TaskInitialize();//タスクの初期化
	//メインループ
	while( true ) {

		if ( ProcessMessage() != 0 ) {
			break;
		}
		//エスケープキーが押されたら終了
		if ( CheckHitKey( KEY_INPUT_ESCAPE ) != 0 ) {
			break;
		}
		//terminatingがtrueなら終了する
		if ( _terminating ) {
			break;
		}
		TaskUpdate();//タスクの更新
		ScreenFlip();// 裏画面の内容を表画面に反映させる
		ClearDrawScreen();// 画面を初期化する
	}
	TaskFinalize();//タスクの終了処理
}

void Application::Finalize() {
	//インスタンスの解放
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

//インスタンスの取得
ApplicationPtr Application::GetInstance( ){
	return _instance;
}

//スクリーンの高さ取得
int Application::GetScreenHeight() const {
	return _screenHeight;
}

//スクリーンの幅取得
int Application::GetScreenWidth() const {
	return _screenWidth;
}

//アプリケーションを終了させる
void Application::AppClose( ){
	_terminating = true;
}

