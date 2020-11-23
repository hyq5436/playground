if(USE_GCOV)
    include(CMakePrintHelpers)
    find_package(PythonInterp REQUIRED)
 
    SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
    SET(GCC_COVERAGE_LINK_FLAGS "-lgcov")
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )               
 
    add_custom_command(OUTPUT _run_gcovr_parser
        POST_BUILD

	# Create folder
	COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/coverage

	COMMAND "${PYTHON_EXECUTABLE}" -m gcovr
	    -r ${CMAKE_SOURCE_DIR}
	    -f ${CMAKE_SOURCE_DIR}/test -f ${CMAKE_SOURCE_DIR}/src 
	    --object-dir=${CMAKE_BINARY_DIR}
	    --exclude-throw-branches
	    --exclude-unreachable-branches
	    --branches  -e test_*
	    --html --html-details
	    -o coverage/index.html
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

    add_custom_target (coverage DEPENDS _run_gcovr_parser)
endif(USE_GCOV)
