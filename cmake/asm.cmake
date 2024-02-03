if (WITH_ASM AND NOT CPURIG_ARM AND CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(CPURIG_ASM_LIBRARY "cpurig-asm")

    if (CMAKE_C_COMPILER_ID MATCHES MSVC)
        enable_language(ASM_MASM)

        if (MSVC_TOOLSET_VERSION GREATER_EQUAL 141)
            set(CPURIG_ASM_FILES
                "src/crypto/cn/asm/cn_main_loop.asm"
                "src/crypto/cn/asm/CryptonightR_template.asm"
            )
        else()
            set(CPURIG_ASM_FILES
                "src/crypto/cn/asm/win64/cn_main_loop.asm"
                "src/crypto/cn/asm/win64/CryptonightR_template.asm"
            )
        endif()

        set_property(SOURCE ${CPURIG_ASM_FILES} PROPERTY ASM_MASM)
    else()
        enable_language(ASM)

        if (WIN32 AND CMAKE_C_COMPILER_ID MATCHES GNU)
            set(CPURIG_ASM_FILES
                "src/crypto/cn/asm/win64/cn_main_loop.S"
                "src/crypto/cn/asm/CryptonightR_template.S"
            )
        else()
            set(CPURIG_ASM_FILES
                "src/crypto/cn/asm/cn_main_loop.S"
                "src/crypto/cn/asm/CryptonightR_template.S"
            )
        endif()

        set_property(SOURCE ${CPURIG_ASM_FILES} PROPERTY C)
    endif()

    add_library(${CPURIG_ASM_LIBRARY} STATIC ${CPURIG_ASM_FILES})
    set(CPURIG_ASM_SOURCES
        src/crypto/common/Assembly.h
        src/crypto/common/Assembly.cpp
        src/crypto/cn/r/CryptonightR_gen.cpp
        )
    set_property(TARGET ${CPURIG_ASM_LIBRARY} PROPERTY LINKER_LANGUAGE C)

    add_definitions(/DCPURIG_FEATURE_ASM)
else()
    set(CPURIG_ASM_SOURCES "")
    set(CPURIG_ASM_LIBRARY "")

    remove_definitions(/DCPURIG_FEATURE_ASM)
endif()
