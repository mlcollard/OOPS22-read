# @file CMakeLists.txt
# 
# CMake files for read experiments

cmake_minimum_required(VERSION 3.10)

# project info
project(Read)

# Force release build since used for timing
set(CMAKE_BUILD_TYPE Release)

# C++17
set(CMAKE_CXX_STANDARD 17)

# Turn on warnings
if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # standard warnings
    add_compile_options(-Wall)
endif()

# Assume each .cpp file is a separate application
file(GLOB APPLICATIONS "*.cpp")

# Generate executable for each .cpp file
foreach(APP ${APPLICATIONS})

    # Use basename (no path, no extension) of .cpp file for application name
    get_filename_component(APPBASENAME "${APP}" NAME_WLE)

    # Application is based on .cpp file only
    add_executable(${APPBASENAME} ${APPBASENAME}.cpp)

endforeach()

# Extract the large example data file
execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_SOURCE_DIR}/large.dat.zip
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Collect list of applications
set(PROGRAM_LIST)
foreach(APP ${APPLICATIONS})
    get_filename_component(APPBASENAME "${APP}" NAME_WLE)
    list(APPEND PROGRAM_LIST "${APPBASENAME}")
endforeach()
list(JOIN PROGRAM_LIST "," PROGRAMS)

# Benchmark of all applications
find_program(HYPERFINE_EXE name hyperfine REQUIRED)
add_custom_target(benchmark
    COMMAND ${HYPERFINE_EXE} --warmup 1 -L program ${PROGRAMS} './{program} large.dat < large.dat'
    DEPENDS ${PROGRAM_LIST})

# Benchmark of all applications output markdown
find_program(HYPERFINE_EXE name hyperfine REQUIRED)
add_custom_target(benchmark-markdown
    COMMAND ${HYPERFINE_EXE} --warmup 1 --export-markdown benchmark.md -L program ${PROGRAMS} './{program} large.dat < large.dat'
    DEPENDS ${PROGRAM_LIST})

# Benchmark for each application, i.e., make benchmark-readcin
foreach(APP ${APPLICATIONS})
    get_filename_component(APPBASENAME "${APP}" NAME_WLE)
    add_custom_target(benchmark-${APPBASENAME}
        COMMAND ${HYPERFINE_EXE} --warmup 1 './${APPBASENAME} large.dat < large.dat'
        DEPENDS ${APPBASENAME}
    )
endforeach()
