# Just include ANS_INCLUDE_DIRS.

if(Ans_DIR)
    set(ANS_INSTALL_DIR "${Ans_DIR}/include")
else()
    message(FATAL_ERROR "Can't find a ANS installation.")
endif()

set(ANS_INCLUDE_DIRS "${ANS_INSTALL_DIR}")
