set (SOURCE_FILES
    rule-nlp/Parser.cpp
)

add_library(rule-nlp ${SOURCE_FILES})
target_include_directories(rule-nlp PUBLIC ./)
#target_include_directories(rule-nlp.cpp PUBLIC ${CONAN_INCLUDE_DIRS})

#target_link_libraries(rule-nlp.cpp ${CONAN_LIBS})

# vim:ft=cmake
