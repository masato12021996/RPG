/**************************
�^�X�N�Ǘ��p�̊��N���X
Update�ȊO�͔C�ӂɐݒ肷��
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

