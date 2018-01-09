
# Put the ini files in the build directory next to the scope
# .so file so that the test tools can find them.
intltool_merge_translations(
  "data/less.ini.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${SCOPE_NAME}.ini"
  ALL
  UTF8
)
intltool_merge_translations(
  "data/less-settings.ini.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${SCOPE_NAME}-settings.ini"
  ALL
  UTF8
)

# Install the scope ini files
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${SCOPE_NAME}.ini"
    "${CMAKE_CURRENT_BINARY_DIR}/${SCOPE_NAME}-settings.ini"
  DESTINATION
    ${SCOPE_INSTALL_DIR}
)

configure_file(
  "data/data.json"
  "${CMAKE_CURRENT_BINARY_DIR}/data.json"
  @ONLY
  COPYONLY
)

configure_file(
  "data/yoda.svg"
  "${CMAKE_CURRENT_BINARY_DIR}/yoda.svg"
  @ONLY
  COPYONLY
)

configure_file(
  "data/earth.svg"
  "${CMAKE_CURRENT_BINARY_DIR}/earth.svg"
  @ONLY
  COPYONLY
)

configure_file(
  "data/sun.svg"
  "${CMAKE_CURRENT_BINARY_DIR}/sun.svg"
  @ONLY
  COPYONLY
)

configure_file(
  "data/water.svg"
  "${CMAKE_CURRENT_BINARY_DIR}/water.svg"
  @ONLY
  COPYONLY
)

configure_file(
  "data/yellow.svg"
  "${CMAKE_CURRENT_BINARY_DIR}/yellow.svg"
  @ONLY
  COPYONLY
)

configure_file(
  "data/blue.svg"
  "${CMAKE_CURRENT_BINARY_DIR}/blue.svg"
  @ONLY
  COPYONLY
)

configure_file(
  "data/empty.svg"
  "${CMAKE_CURRENT_BINARY_DIR}/empty.svg"
  @ONLY
  COPYONLY
)
# Install the scope images
install(
  FILES
	  "data/data.json"
	  "data/yoda.svg"
	  "data/empty.svg"
	  "data/earth.svg"
	  "data/sun.svg"
	  "data/water.svg"
	  "data/blue.svg"
	  "data/yellow.svg"
    "data/icon.png"
    "data/screenshot.png"
  DESTINATION
    ${SCOPE_INSTALL_DIR}
)

# Find all the sources
file(GLOB_RECURSE
  SCOPE_SOURCES
  "*.cpp"
  "*.h"
)

# Build a shared library containing our scope code.
add_library(
  scope SHARED
  ${SCOPE_SOURCES}
)

# Link against the object library and our external library dependencies
target_link_libraries(
  scope
  ${SCOPE_LDFLAGS}
)

qt5_use_modules(
  scope
  Core
)

# Set the correct library output name to conform to the securiry policy 
set_target_properties(
  scope
  PROPERTIES
    OUTPUT_NAME "${SCOPE_NAME}"
)

# Install the scope shared library
install(
  TARGETS scope
  LIBRARY DESTINATION ${SCOPE_INSTALL_DIR}
)
