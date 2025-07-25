find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable (ZuziGame "ZuziGame.cpp"  "ZuziGame.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ZuziGame PROPERTY CXX_STANDARD 20)
endif()

# tests and install targets if needed.
target_link_libraries(ZuziGame PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)
