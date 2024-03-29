if (WIN32)
    set(CPURIG_OS_WIN ON)
elseif (APPLE)
    set(CPURIG_OS_APPLE ON)

    if (IOS OR CMAKE_SYSTEM_NAME STREQUAL iOS)
        set(CPURIG_OS_IOS ON)
    else()
        set(CPURIG_OS_MACOS ON)
    endif()
else()
    set(CPURIG_OS_UNIX ON)

    if (ANDROID OR CMAKE_SYSTEM_NAME MATCHES "Android")
        set(CPURIG_OS_ANDROID ON)
    elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
        set(CPURIG_OS_LINUX ON)
    elseif(CMAKE_SYSTEM_NAME STREQUAL FreeBSD OR CMAKE_SYSTEM_NAME STREQUAL DragonFly)
        set(CPURIG_OS_FREEBSD ON)
    endif()
endif()


if (CPURIG_OS_WIN)
    add_definitions(-DWIN32 -DCPURIG_OS_WIN)
elseif(CPURIG_OS_APPLE)
    add_definitions(-DCPURIG_OS_APPLE)

    if (CPURIG_OS_IOS)
        add_definitions(-DCPURIG_OS_IOS)
    else()
        add_definitions(-DCPURIG_OS_MACOS)
    endif()

    if (CPURIG_ARM)
        set(WITH_SECURE_JIT ON)
    endif()
elseif(CPURIG_OS_UNIX)
    add_definitions(-DCPURIG_OS_UNIX)

    if (CPURIG_OS_ANDROID)
        add_definitions(-DCPURIG_OS_ANDROID)
    elseif (CPURIG_OS_LINUX)
        add_definitions(-DCPURIG_OS_LINUX)
    elseif (CPURIG_OS_FREEBSD)
        add_definitions(-DCPURIG_OS_FREEBSD)
    endif()
endif()

if (WITH_SECURE_JIT)
    add_definitions(-DCPURIG_SECURE_JIT)
endif()
