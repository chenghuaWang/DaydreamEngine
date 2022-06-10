/*!
 * @author	chenghua.wang
 * @brief	define of file system.
 * @detail	File system is one of the most important part
 * in this lib. It provides the methdologies below:
 * 1. Write and read from XML/Json file. (Not sure use xml or json).
 * 2. Using boost serialization package to write binary data to files.
 * 3. Write and read data from pure text data encoding with utf-8.
 * 
 * @note	This file system just for files read and write. It not manage
 * what the data like or how data organized in different files. You should
 * manage all data and prepare them before using this lib to write into or
 * read from some files.
 * 
 * There r just file files need this file_sys.hpp. Such as load_model/scene-
 * manage/app-state-record/user-state-record. So, it isn't necessary to put
 * this file into a precompiled head.
 */
#ifndef H_FILE_SYS
#define H_FILE_SYS

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../pch.hpp"

namespace daydream {
namespace io {

	class pure_text {
		pure_text() = default;
		~pure_text() {

		}
	}; 

	class json {

	};

	class xml {

	};

	class binary {

	};

} // !namespace io
} // !namespace daydream

#endif // !H_FILE_SYS
