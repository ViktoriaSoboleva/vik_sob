set(SOURCES 
	long_number_test.cpp
)

add_executable(long_number_test ${SOURCES})
target_link_libraries(long_number_test
	${LIBRARY}
	gtest
	gmock_main 
)

add_test(NAME long_number_test COMMAND long_number_test)