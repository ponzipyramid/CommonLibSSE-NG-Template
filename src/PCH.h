#pragma once

#include <new>
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags,
	unsigned debugFlags, const char* file, int line);

#pragma warning(push)
#if defined(FALLOUT4)
#	include "F4SE/F4SE.h"
#	include "RE/Fallout.h"
#	define SKSE F4SE
#	define SKSEAPI F4SEAPI
#	define SKSEPlugin_Load F4SEPlugin_Load
#	define SKSEPlugin_Query F4SEPlugin_Query
#else
#	define SKSE_SUPPORT_XBYAK
#	include "RE/Skyrim.h"
#	include "SKSE/SKSE.h"
#	include <xbyak/xbyak.h>
#endif

#ifdef NDEBUG
#	include <spdlog/sinks/basic_file_sink.h>
#else
#	include <spdlog/sinks/msvc_sink.h>
#endif

#pragma warning(pop)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using namespace std::literals;

namespace stl
{
	using namespace SKSE::stl;

	template <class T>
	void write_thunk_call(std::uintptr_t a_src)
	{
		SKSE::AllocTrampoline(14);
		auto& trampoline = SKSE::GetTrampoline();
		T::func = trampoline.write_call<5>(a_src, T::thunk);
	}

	template <class T>
	void write_thunk_call_6(std::uintptr_t a_src)
	{
		SKSE::AllocTrampoline(14);
		auto& trampoline = SKSE::GetTrampoline();
		T::func = *(uintptr_t*)trampoline.write_call<6>(a_src, T::thunk);
	}

	template <class F, size_t index, class T>
	void write_vfunc()
	{
		REL::Relocation<std::uintptr_t> vtbl{ F::VTABLE[index] };
		T::func = vtbl.write_vfunc(T::size, T::thunk);
	}

	template <std::size_t idx, class T>
	void write_vfunc(REL::VariantID id)
	{
		REL::Relocation<std::uintptr_t> vtbl{ id };
		T::func = vtbl.write_vfunc(idx, T::thunk);
	}

	template <class T>
	void write_thunk_jmp(std::uintptr_t a_src)
	{
		SKSE::AllocTrampoline(14);
		auto& trampoline = SKSE::GetTrampoline();
		T::func = trampoline.write_branch<5>(a_src, T::thunk);
	}

	template <class F, class T>
	void write_vfunc()
	{
		write_vfunc<F, 0, T>();
	}
}

namespace logger = SKSE::log;
namespace WinAPI = SKSE::WinAPI;

namespace util
{
	using SKSE::stl::report_and_fail;
}

#include "Plugin.h"

#include <ClibUtil/distribution.hpp>
#include <ClibUtil/editorID.hpp>
#include <ClibUtil/numeric.hpp>
#include <ClibUtil/rng.hpp>
#include <ClibUtil/simpleINI.hpp>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <magic_enum.hpp>

#include "SimpleMath.h"

using uint = uint32_t;