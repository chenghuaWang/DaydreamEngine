/*!
 * @author	chenghua.wang
 * @brief	A pch head for all files in Daydream modules
 * 
 * @details	This pch head only contains libs provided by
 * compiler and systems. Also some basic define will be 
 * include in.
 */
#if _MSC_VER > 1000
#pragma once
#pragma warning(disable:4251)
#endif // _MSC_VER > 1000

// include STL
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cmath>
#include <memory>
#include <utility>
#include <set>

// For shared lib
#ifdef _WIN32
#define D_PLATFORM_WINDOWS
#define D_DYNAMIC_LINK true
#endif // !_WIN32

#ifdef D_PLATFORM_WINDOWS
#if D_DYNAMIC_LINK
#define D_API_EXPORT __declspec(dllexport)
#define D_API_IMPORT __declspec(dllimport)
#else
#define D_API
#endif // !D_DYNAMIC_LINK
#else
#error Daydream engine only support Windows for now!
#endif // !D_PLATFORM_WINDOWS

// include self-defined head files.
#include "./include/log_sys.hpp"

// macros for smart ptr.
#define REF(x) std::shared_ptr<x>
#define CREATE_REF(x) std::make_shared<x>

// macros for absolute paths
#define ROOT_PATH(s) P_STR(s) 
#define P_STR(s) #s
