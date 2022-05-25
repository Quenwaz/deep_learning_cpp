


macro(get_current_filename result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*.cpp)
    set(dirlist "")
    foreach(child ${children})
        if(NOT IS_DIRECTORY ${curdir}/${child})
            STRING(REGEX REPLACE "(.*)\.cpp" "\\1" FILE_NAME ${child})
            list(APPEND dirlist ${FILE_NAME})
        endif()
    endforeach(child ${children})
    set(${result} ${dirlist})
endmacro(get_current_filename result curdir)