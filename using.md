---
layout: default
title: Using Luna with your project
---

# Using Luna with your project

At the moment, Luna only supports CMake, and can only be integrated into projects using CMake.

At the moment, there are three ways to incorporate Luna into your project: Build as a stand-alone library (not at the moment supported, and not discussed in great depth here, but totally possible), added as a Git submodule (not the worst thing ever), or added as a [CPM](http://www.cpm.rocks) module (A++ recommended, would add again).

# Adding Luna with CPM 😃

Somewhere near the top of your `CMakeLists.txt` file, add the following:

    #------------------------------------------------------------------------------
    # Required CPM Setup - no need to modify - See: https://github.com/iauns/cpm
    #------------------------------------------------------------------------------
    set(CPM_DIR "${CMAKE_CURRENT_BINARY_DIR}/cpm_packages" CACHE TYPE STRING)
    find_package(Git)
    if(NOT GIT_FOUND)
        message(FATAL_ERROR "CPM requires Git.")
    endif()
    if (NOT EXISTS ${CPM_DIR}/CPM.cmake)
        message(STATUS "Cloning repo (https://github.com/iauns/cpm)")
        execute_process(
                COMMAND "${GIT_EXECUTABLE}" clone https://github.com/iauns/cpm ${CPM_DIR}
                RESULT_VARIABLE error_code
                OUTPUT_QUIET ERROR_QUIET)
        if(error_code)
            message(FATAL_ERROR "CPM failed to get the hash for HEAD")
        endif()
    endif()
    include(${CPM_DIR}/CPM.cmake)

    #------------------------------------------------------------------------------
    # CPM Modules
    #------------------------------------------------------------------------------

    # ++ MODULE: luna
    CPM_AddModule("luna"
            GIT_REPOSITORY "https://github.com/DEGoodmanWilson/luna"
            GIT_TAG "v1.0.0-beta1")

    CPM_Finish()

And then when you defining the link step, make sure you link against Luna as such

    target_link_libraries(my_cool_app ${CPM_LIBRARIES})

Then, in your program, just include `luna/luna.h`

    #include <luna/luna.h>


A working example project that uses CPM is available in the (https://github.com/DEGoodmanWilson/luna/tree/worked_example)[`worked_example` branch of Luna.].

# Adding Luna as a Git submodule 🙂

# Building Luna as a stand-alone library 😐

