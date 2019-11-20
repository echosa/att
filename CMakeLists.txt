cmake_minimum_required(VERSION 3.15)
project(AllTheThings)

add_library(action src/action.c)
target_include_directories(action PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(action
  PRIVATE -Wall -Wextra -pedantic -Werror
)

add_library(commands src/commands.c)
target_include_directories(commands PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(commands
  PRIVATE -Wall -Wextra -pedantic -Werror
)

add_library(io src/io.c)
target_include_directories(io PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(io
  PRIVATE -Wall -Wextra -pedantic -Werror
)

add_library(apt src/managers/apt.c)
target_include_directories(apt PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(apt
  PRIVATE -Wall -Wextra -pedantic -Werror
)

add_library(brew src/managers/brew.c)
target_include_directories(brew PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(brew
  PRIVATE -Wall -Wextra -pedantic -Werror
)

add_library(flatpak src/managers/flatpak.c)
target_include_directories(flatpak PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(flatpak
  PRIVATE -Wall -Wextra -pedantic -Werror
)

add_library(guix src/managers/guix.c)
target_include_directories(guix PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(guix
  PRIVATE -Wall -Wextra -pedantic -Werror
)

add_library(snap src/managers/snap.c)
target_include_directories(snap PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(snap
  PRIVATE -Wall -Wextra -pedantic -Werror
)

add_library(managers src/managers.c)
target_include_directories(managers PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(managers
  PRIVATE -Wall -Wextra -pedantic -Werror
)

add_library(package_manager src/package_manager.c)
target_include_directories(package_manager PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(package_manager
  PRIVATE -Wall -Wextra -pedantic -Werror
)

add_library(requested_action src/requested_action.c)
target_include_directories(requested_action PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(requested_action
  action
)
target_compile_options(requested_action
  PRIVATE -Wall -Wextra -pedantic -Werror
)

add_library(run src/run.c)
target_include_directories(run PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(requested_action
  commands
  apt
  brew
  flatpak
  guix
  snap
)

add_library(supported_managers src/supported_managers.c)
target_include_directories(supported_managers PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(supported_managers
  PRIVATE -Wall -Wextra -pedantic -Werror
)

add_library(system src/system.c)
target_include_directories(system PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(system
  PRIVATE -Wall -Wextra -pedantic -Werror
)

add_executable(att src/main.c)
target_include_directories(att PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(att
  action
  commands
  io
  apt
  brew
  flatpak
  guix
  snap
  managers
  package_manager
  requested_action
  run
  supported_managers
  system
)
target_compile_options(att
  PRIVATE -Wall -Wextra -pedantic -Werror
)

add_executable(att-debug src/main.c)
target_include_directories(att-debug PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(att-debug
  action
  commands
  io
  apt
  brew
  flatpak
  guix
  snap
  managers
  package_manager
  requested_action
  run
  supported_managers
  system
)
target_compile_options(att-debug
  PRIVATE -Wall -Wextra -pedantic -Werror -g -O0
)

add_executable(att-tests test/tests.c)
target_link_libraries(att-tests
  cmocka
  action
  commands
  io
  apt
  brew
  flatpak
  guix
  snap
  managers
  package_manager
  requested_action
  supported_managers
  system
)
target_compile_options(att-tests
  PRIVATE -Wall -Wextra -pedantic
)
target_link_options(att-tests
  PRIVATE -Wl,--wrap=system
)

install(
  TARGETS att
  DESTINATION /usr/local/bin
)

add_custom_target(check
  cppcheck -i.ccls-cache ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/teste
)

add_custom_target(uninstall
  rm /usr/local/bin/att
)

add_custom_target(coverage
  COMMAND llvm-cov-9 gcov -f -b *.gcda
  COMMAND lcov --directory . --base-directory . --gcov-tool ../llvm-gcov.sh --capture -o cov.info
  COMMAND genhtml cov.info -o coverage
  COMMAND rm *.gcno *.gcda cov.info
)
