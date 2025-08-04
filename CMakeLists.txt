cmake_minimum_required( VERSION 3.25 )


project(TRMeshGD LANGUAGES CXX VERSION 0.1.0)
add_library(${PROJECT_NAME} SHARED)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
set(LIB_ARCH ${CMAKE_SYSTEM_PROCESSOR})
set(LIB_DIR "lib/${CMAKE_SYSTEM_NAME}-${LIB_ARCH}")
set(BUILD_OUTPUT_DIR "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/")

set_target_properties(
   ${PROJECT_NAME}
    PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN true
        RUNTIME_OUTPUT_DIRECTORY "${BUILD_OUTPUT_DIR}/${LIB_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${BUILD_OUTPUT_DIR}/${LIB_DIR}"
)

if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
    set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "-d")
endif()

# Copy over additional files from the support_files directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/res"
            ${BUILD_OUTPUT_DIR}
)

include(cmake/CompilerWarnings.cmake)

target_sources(
   ${PROJECT_NAME}
   PRIVATE
      src/RegisterExtension.cpp
)

# Configure dependencies
set(GODOTCPP_USE_HOT_RELOAD ON)
add_subdirectory(vendor/TRMesh)
add_subdirectory(vendor/godot-cpp SYSTEM)
set_target_properties(godot-cpp PROPERTIES CXX_VISIBILITY_PRESET hidden)
set_target_properties(TRMesh PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_link_libraries(
   ${PROJECT_NAME}
   PRIVATE
   godot-cpp
   TRMesh
)


# Install logic
message(STATUS "Installing to: ${CMAKE_INSTALL_PREFIX}")
install(
   TARGETS
      ${PROJECT_NAME}
   LIBRARY DESTINATION ${LIB_DIR}
   RUNTIME DESTINATION ${LIB_DIR}
)
install(
   FILES
      res/TRMesh.gdextension
   DESTINATION 
      ${CMAKE_INSTALL_PREFIX}
)
