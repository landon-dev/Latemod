#pragma once

#include "util/includes.h"

using createdvms_t = jint(JNICALL*)(JavaVM**, jsize, jsize*);

namespace lm {
	class latemod {
	private:
		jvmtiEnv* jvmti;
		JNIEnv* env;
		JavaVM* vm;

		void* wgl_swap_buffers;
	public:
		bool b_running = true;
		HWND targetWindow;

		latemod();
		~latemod();
	};

}

extern std::shared_ptr<lm::latemod> cheat;
