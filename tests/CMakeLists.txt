add_executable(rnlptests src/TestRunner.cpp
    src/ParserTest.cpp
    src/ScoreTest.cpp
)

# Catch2 {{{
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.0.0-preview4)

FetchContent_MakeAvailable(Catch2)

target_link_libraries(rnlptests Catch2::Catch2)
# }}}

target_link_libraries(rnlptests rule-nlp)
