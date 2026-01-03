#pragma once
#include <print>
#include <format>
#include <source_location>

enum class Severity
{
	Debug,
	Warning,
	Error
};

template <typename... Args>
void sabr_prv_log(const char* FILE, const char* FUNCTION, uint32_t LINE, Severity severity, const std::format_string<Args...> fmt, Args&&... args)
{
	if (severity == Severity::Debug) { auto msg = std::format(fmt, std::forward<Args>(args)...); std::println("Sabre :: {} :: File \"{}\" Function \"{}\" Line \"{}\"", msg, FILE, FUNCTION, LINE); }
	else if (severity == Severity::Warning) { auto msg = std::format(fmt, std::forward<Args>(args)...); std::println("\033[33mSabre :: {} :: File \"{}\" Function \"{}\" Line \"{}\" \033[0m", msg, FILE, FUNCTION, LINE); }
	else if (severity == Severity::Error) { auto msg = std::format(fmt, std::forward<Args>(args)...); std::println("\033[31mSabre :: {} :: File \"{}\" Function \"{}\" Line \"{}\" \033[0m", msg, FILE, FUNCTION, LINE); }
}

template <typename... Args>
void sabr_prv_assert(const char* FILE, const char* FUNCTION, uint32_t LINE, bool val, const std::format_string<Args...> fmt, Args&&... args)
{
	if (val)
		return;

#ifndef DIST
	sabr_prv_log(FILE, FUNCTION, LINE, Severity::Error, fmt, std::forward<Args>(args)...);
#endif

	std::exit(-1);
}

#ifndef DIST
#define SABRE_LOG(...) sabr_prv_log(__FILE__, __func__, __LINE__, __VA_ARGS__)
#endif 

#ifdef DIST

#define SABRE_LOG(...)

#endif 

#define SABRE_ASSERT(val, ...) sabr_prv_assert(__FILE__, __func__, __LINE__, val, __VA_ARGS__)