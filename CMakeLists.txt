if(${CMAKE_VERSION} VERSION_LESS "3.9.0")
 cmake_minimum_required(VERSION 3.7)
 message("Please upgrade to cmake 3.9 to get more fancy stuff")
else()
 cmake_minimum_required(VERSION 3.9)
endif()

set (CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

project(AdvancedGenieEditor3)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)

if(MSVC)
    # Otherwise we get thousands of warnings from wxwidgets
    # Why on earth people use wxwidgets is beyond me
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(/wd4018)
endif()

# Find wxWidgets
# In case you didn't know, it (wxWidgets) is crap, so we need this hack
if(MSVC AND _VCPKG_INSTALLED_DIR)

    add_definitions(/DwxUSE_UNICODE)
    set(wxWidgets_USE_STATIC TRUE)
    include(${CMAKE_SOURCE_DIR}/cmake/vcpkg-wxwidgets.cmake)
    message(STATUS "argh: ${wxWidgets_LIBRARIES}")
    message(STATUS "VCPKG available, this should be empty: ${wxWidgets_DEFINITIONS}")
    include("${wxWidgets_USE_FILE}")
else()
    # wxwidgets is a burning, flying shitshow
    if(NOT DEFINED ENV{WX_CONFIG})
        set(ENV{WX_CONFIG} wx-config-gtk3)
        message(STATUS "Defaulting to wx-config name $ENV{WX_CONFIG}")
    endif()

    find_package(wxWidgets REQUIRED adv core base)

    # Needed to fix GTK's spam shit
    if ("${wxWidgets_LIBRARIES}" MATCHES "gtk")
        message(WARNING 
            "################################################################################################################\n"
            "   wxGTK is _very_ slow and laggy (especially GTK3). It will build and work, but don't file any bugs about this.\n"
            "################################################################################################################\n"
        )
        find_package(PkgConfig REQUIRED)
        pkg_search_module(GLIB REQUIRED glib-2.0)
        include_directories(${GLIB_INCLUDE_DIRS})
        set(wxWidgets_LIBRARIES ${wxWidgets_LIBRARIES} ${GLIB_LDFLAGS})

    endif()

    include("${wxWidgets_USE_FILE}")
endif()


find_package(SFML 2.4 REQUIRED system audio)

set(GUTILS_TOOLS FALSE)
set(GUTILS_TEST FALSE)

option(ENABLE_SANITIZERS "Enable runtime sanitizing (for development)")
if (ENABLE_SANITIZERS)
    message("Enabling asan and ubsan")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=undefined")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")
endif()

if (ENABLE_IPO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT IPO_AVAILABLE OUTPUT IPO_ERROR)
    if (IPO_AVAILABLE)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION True)

        if (CMAKE_COMPILER_IS_GNUCXX)
            message(STATUS "Enabling all link time optimizations")
            add_definitions(-fuse-linker-plugin)
        else()
            message(STATUS "Using IPO for optimizing binary size")
        endif()
    else()
        message(STATUS "IPO/LTO not supported: <${IPO_ERROR}>")
    endif()
else()
    message(STATUS "Not enabling IPO/LTO")
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/extern/genieutils/include/genie/Types.h)
    message(STATUS "Using bundled genieutils")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extern/genieutils/include/)

    set(GUTILS_STATIC True)
    add_subdirectory(extern/genieutils)
endif()

include_directories(
    ${SFML_INCLUDE_DIR}
)

set(AGE_SRC Main.cpp
    AGE_TextControls.cpp
    AGE_CheckBoxes.cpp
    AGE_ComboBoxes.cpp
    AGE_AboutDialog.cpp
    AGE_OpenSave.cpp
    AGE_OpenDialog.cpp
    AGE_SaveDialog.cpp
    SharedComboPopup.cpp

    AGE_Frame/Constructor.cpp
    AGE_Frame/Other.cpp
    AGE_Frame/Civs.cpp
    AGE_Frame/General.cpp
    AGE_Frame/Graphics.cpp
    AGE_Frame/PlayerColors.cpp
    AGE_Frame/Research.cpp
    AGE_Frame/Sounds.cpp
    AGE_Frame/Techs.cpp
    AGE_Frame/TechTrees.cpp
    AGE_Frame/TerrainBorders.cpp
    AGE_Frame/TerrainRestrictions.cpp
    AGE_Frame/Terrains.cpp
    AGE_Frame/UnitLine.cpp
    AGE_Frame/Units.cpp

    wintendo/Resources.rc
    )

add_executable(AdvancedGenieEditor3 ${AGE_SRC})

set(ALL_LIBRARIES
    genieutils sfml-system sfml-audio
    )

if(WIN32)
    # WinMain dumbness
    set_property(TARGET AdvancedGenieEditor3 PROPERTY WIN32_EXECUTABLE true)

    include_directories(extern/genieutils/extern/win-iconv/)

    target_link_libraries(AdvancedGenieEditor3 ${wxWidgets_LIBRARIES} ${ALL_LIBRARIES} genieutils psapi)
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wno-sign-compare")
    target_link_libraries(AdvancedGenieEditor3 ${wxWidgets_LIBRARIES} ${ALL_LIBRARIES} stdc++fs)
endif()

install(TARGETS AdvancedGenieEditor3 DESTINATION bin)
