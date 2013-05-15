//
//  tween.cpp
//  CppTweener
//
//  Created by wonhee jang on 13. 5. 14..
//  Copyright (c) 2013년 vanillabreeze. All rights reserved.
//

#include "tween.h"

bool tween_manager::update_animation(std::list<animation>::iterator _it, long _milli_seconds) {
	(*_it).tick += _milli_seconds;
	(*_it).tween.step((*_it).tick);
	
	if((*_it).tween.tweens.size() == 0) {
		return false;
	} else {
		return true;
	}
}

tween_manager::tween_manager() {
}

tween_manager* _local_tween_manager = NULL;

tween_manager* tween_manager::share() {
	if(!_local_tween_manager)
		_local_tween_manager = new tween_manager();
	return _local_tween_manager;
}

void tween_manager::start(std::string _tag, long _time, float* _src, float _dst, short _equation, short _transition, TweenerListener* _listener, short _delay) {
	animation _animation = animation();
	_animation.tag = _tag;
	TweenerParam _param = TweenerParam(_time, _transition, _equation, _delay);
	_param.tag = _tag;
	if(_src)
		_param.addProperty(_src, _dst);
	_animation.tween.addTween(_param);
	if(_listener)
		_animation.tween.addListener(_listener);
	
	list_animation.push_back(_animation);
}

void tween_manager::update(float _tick) {
	long _milli_seconds = _tick * 1000;
	std::list<animation>::iterator _it = list_animation.begin();
	while (_it != list_animation.end()) {
		if(!update_animation(_it, _milli_seconds)) {
			list_animation.remove(*_it);
		}
		_it++;
	}
}

void tween_manager::stop(std::string _tag) {
	std::list<animation>::iterator _it = list_animation.begin();
	while (_it != list_animation.end()) {
		if((*_it).tag == _tag) {
			list_animation.remove(*_it);
		}
		_it++;
	}
}