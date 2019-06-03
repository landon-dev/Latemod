#include "latemod.h"

using namespace lm;

latemod::latemod()
{

	auto jvm = GetModuleHandleA(xorstr("jvm.dll").crypt_get());

	if (jvm == nullptr)
		return;

	auto createdvms_fn = GetProcAddress(jvm, xorstr("JNI_GetCreatedJavaVMs").crypt_get());

	auto get_created_vms = reinterpret_cast<createdvms_t>(createdvms_fn);

	jsize result;

	get_created_vms(&this->vm, 1, &result);
	if (result != JNI_OK)
		return;

	if (this->vm->AttachCurrentThread(reinterpret_cast<void**>(&this->env), nullptr) != JNI_OK)
		return;

	if (this->vm->GetEnv(reinterpret_cast<void**>(&this->jvmti), JVMTI_VERSION_1_2) != JNI_OK)
		return;

	auto opengl = GetModuleHandleA(xorstr("opengl32.dll").crypt_get());
	if (opengl == nullptr)
		return;

	this->wgl_swap_buffers = GetProcAddress(opengl, xorstr("wglSwapBuffers").crypt_get());

	/* initialize hooks */

	this->targetWindow = FindWindowA(nullptr, xorstr("Minecraft 1.7.10").crypt_get());

	/* initialize window hook */

	while (this->b_running)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		/* do latemod stuff */
	}
}

latemod::~latemod()
{
	jvmti->DisposeEnvironment();
	vm->DetachCurrentThread();
}
