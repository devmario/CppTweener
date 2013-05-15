//
//  tween.h
//  CppTweener
//
//  Created by wonhee jang on 13. 5. 14..
//  Copyright (c) 2013년 vanillabreeze. All rights reserved.
//

#ifndef __CppTweener__tween__
#define __CppTweener__tween__

#include <iostream>
#include "CppTweener.h"
#include <list>
#include <time.h>

using namespace tween;

class tween_manager {
public:
	struct animation {
		std::string tag;
		Tweener tween;
		long tick;
		clock_t mkclock;
		animation() {
			tag = "";
			tick = 0;
			tween = Tweener();
			mkclock = clock();
		}
		
		~animation() {
		}
		
		bool operator == (const animation& _animation) {
			return (_animation.mkclock == mkclock);
		}
	};
	
	std::list<animation> list_animation;
	
	bool update_animation(std::list<animation>::iterator _it, long _milli_seconds);
	
private:
	tween_manager();
	
public:
	static tween_manager* share();
	
	void start(std::string _tag, long _time, float* _src, float _dst, short _equation = EASE_IN_OUT, short _transition = EXPO, TweenerListener* _listener = NULL, short _delay = 0);
	void stop(std::string _tag);
	
	void update(float _tick);
};

#endif /* defined(__CppTweener__tween__) */
