cmake_minimum_required(VERSION 3.21 FATAL_ERROR)


project("stick::lib"
        VERSION 0.0.2.10
        DESCRIPTION "Full and cross-platform implementation of many libraries without any dependencies."
        HOMEPAGE_URL "https://github.com/stickM4N/stick-lib"
        LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


find_package(Doxygen 1.9.3)


option(std_exception_base "Use std::exception as error engine base." ON)


add_library("lib" STATIC
        #   defines
        "include/stick/defines/arch.hpp"
        "include/stick/defines/compiler.hpp"
        "include/stick/defines/endian.hpp"
        "include/stick/defines/os.hpp"
        "include/stick/defines/predef.hpp"
        "include/stick/defines/types.hpp"
        #   memory
        "include/stick/memory/storage.hpp"
        "include/stick/memory/management.hpp"
        "include/stick/memory/management_impl.hpp"
        "include/stick/memory/scoped_pointer.hpp"
        "include/stick/memory/scoped_pointer_impl.hpp"
        #   error
        "include/stick/error/base_error.hpp"
        "source/stick/error/base_error.cpp"
        "include/stick/error/generic_error.hpp"
        "source/stick/error/generic_error.cpp"
        "include/stick/error/memory_error.hpp"
        "source/stick/error/memory_error.cpp"
        "include/stick/error/cast_error.hpp"
        "source/stick/error/cast_error.cpp"
        #   string
        "include/stick/string/casting.hpp"
        "include/stick/string/casting_impl.hpp"
        "source/stick/string/casting.cpp"
        "include/stick/string/cstring.hpp"
        "source/stick/string/cstring.cpp"
        "include/stick/string/string.hpp"
        "source/stick/string/string.cpp"
        "include/stick/string/wcasting.hpp"
        "include/stick/string/wcasting_impl.hpp"
        "source/stick/string/wcasting.cpp"
        "include/stick/string/wcstring.hpp"
        "source/stick/string/wcstring.cpp"
        "include/stick/string/wstring.hpp"
        "source/stick/string/wstring.cpp"
        #   templates
        "include/stick/templates/reference.hpp"
        "include/stick/templates/reference_impl.hpp")

target_include_directories("lib" PUBLIC
        $<INSTALL_INTERFACE:include/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>)

if (std_exception_base)
    target_compile_definitions("lib" PUBLIC stick_USE_STD_EXCEPTION_BASE)
endif ()


configure_file("cmake/stick_lib.in" "${CMAKE_SOURCE_DIR}/include/stick_lib")


if (DOXYGEN_FOUND)
    set(DOXYGEN_PROJECT_LOGO "stick-lib_logo.png")
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "README.md")

    set(DOXYGEN_SOURCE_BROWSER "YES")
    set(DOXYGEN_INLINE_SOURCES "YES")

    set(DOXYGEN_FILE_PATTERNS "*")
    set(DOXYGEN_EXTENSION_MAPPING "no_extension=C++")
    set(DOXYGEN_EXTRACT_ALL "YES")
    set(DOXYGEN_MACRO_EXPANSION "YES")

    set(DOXYGEN_OUTPUT_DIRECTORY "export/doc")

    set(DOXYGEN_GENERATE_TREEVIEW "YES")
    set(DOXYGEN_CREATE_SUBDIRS "YES")
    set(DOXYGEN_HTML_HEADER "doc/theme/doxygen_header.html")
    set(DOXYGEN_HTML_FOOTER "doc/theme/doxygen_footer.html")
    set(DOXYGEN_HTML_EXTRA_STYLESHEET "doc/theme/doxygen-awesome.css")
    set(DOXYGEN_HTML_EXTRA_FILES "doc/theme/doxygen-awesome-darkmode-toggle.js")

    doxygen_add_docs("lib-doc"
            "include/"
            "source/"
            "LICENSE.md"
            "README.md"
            COMMENT "stick::lib HTML docs.")
endif ()


install(TARGETS "lib"
        EXPORT "stick-export" ARCHIVE)

install(EXPORT "stick-export"
        DESTINATION "lib/cmake/stick/"
        NAMESPACE "stick::"
        FILE "stick-targets.cmake")

install(FILES "cmake/stick-config.cmake"
        DESTINATION "lib/cmake/stick/")

install(FILES "${CMAKE_SOURCE_DIR}/include/stick_lib"
        DESTINATION "include/")

install(DIRECTORY "include/"
        DESTINATION "include")

if (DOXYGEN_FOUND)
    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/export/doc/"
            DESTINATION "doc/stick")
endif ()
