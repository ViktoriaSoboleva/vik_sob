target_sources(${LIBRARY}
	PRIVATE
		long_number.cpp
)

target_include_directories(${LIBRARY} PUBLIC
	"${PROJECT_SOURCE_DIR}"
)