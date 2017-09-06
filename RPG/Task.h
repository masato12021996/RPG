/**************************
タスク管理用の基底クラス
Update以外は任意に設定する
**************************/
#pragma once
#include "smart_ptr.h"

PTR( Task );

class Task {
public:
	Task(){};
	virtual ~Task(){};
public:
	virtual void Initialize(){ };
	virtual void Update() = 0;
	virtual void Finalize(){ };
};

