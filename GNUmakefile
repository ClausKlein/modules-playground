# Copyright Claus Klein, 2025-2026
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

# Standard stuff

.SUFFIXES:

MAKEFLAGS+= --no-builtin-rules  # Disable the built-in implicit rules.
MAKEFLAGS+= --warn-undefined-variables        # Warn when an undefined variable is referenced.

# TODO: export CMAKE_CXX_COMPILER_LAUNCHER=ccache
# TODO: export CMAKE_C_COMPILER_LAUNCHER=ccache
export CMAKE_CONFIG_TYPE=Release
export CMAKE_CONFIGURATION_TYPES="Release;Debug"
export CMAKE_EXPORT_COMPILE_COMMANDS=YES
export CMAKE_GENERATOR=Ninja
# XXX export CMAKE_INSTALL_PREFIX="${HOME}/.local"
# XXX export CMAKE_PREFIX_PATH="${HOME}/.local"

# NOTE: only to use experimental cmake versions:
# TODO: export PATH="${HOME}/.local/bin:${PATH}"

export hostSystemName:=$(shell uname)

ifeq (${hostSystemName},Darwin)

  ### NOTE: to test clang++-22:
  ifeq (${CXX},clang++)
    SYSROOT:=$(shell xcrun --show-sdk-path)
    export LLVM_PREFIX:=$(shell brew --prefix llvm)
    export LLVM_DIR:=$(shell realpath ${LLVM_PREFIX})
    export PATH:=${LLVM_DIR}/bin:${PATH}
    export CMAKE_CXX_STDLIB_MODULES_JSON:=${LLVM_DIR}/lib/c++/libc++.modules.json
    export CXXFLAGS:=-stdlib=libc++ --sysroot=$(SYSROOT)
    export LDFLAGS:=-L$(LLVM_DIR)/lib/c++ # XXX -lc++abi
    # XXX export CXX:=clang++
    # XXX export GCOV:="llvm-cov gcov"
  endif

  ### NOTE: to test g++-15:
  ifeq (${CXX},g++-15)
    export GCC_PREFIX:=$(shell brew --prefix gcc)
    export GCC_DIR:=$(shell realpath ${GCC_PREFIX})
    export CMAKE_CXX_STDLIB_MODULES_JSON:=${GCC_DIR}/lib/gcc/current/libstdc++.modules.json
    export CXXFLAGS:=-stdlib=libstdc++
    # XXX export CXX:=g++-15
    # XXX export GCOV:="gcov"
  endif

else ifeq (${hostSystemName},Linux)
  ifeq (${CXX},clang++)
    export LLVM_DIR:=/usr/lib/llvm-23
    export PATH:=${LLVM_DIR}/bin:${PATH}
    export CXX:=clang++-23
  endif
endif

.PHONY: all install tests distclean format

all: __build/compile_commands.json
	ln -sf $< .
	ninja -C __build # XXX -j 1 -k 1

__build/compile_commands.json: CMakeLists.txt GNUmakefile
	cmake --version
	cmake -S . -B __build -G Ninja \
  -D CMAKE_CXX_STDLIB_MODULES_JSON=${CMAKE_CXX_STDLIB_MODULES_JSON} \
  -D CMAKE_CXX_STANDARD=23 -D CMAKE_CXX_EXTENSIONS=YES -D CMAKE_CXX_STANDARD_REQUIRED=YES \
  -D CMAKE_BUILD_TYPE=Release \
  --log-level=VERBOSE -Wdev --fresh \
  # --trace-expand --trace-source=use-fetch-content.cmake \
  # XXX --debug-find-pkg=boost_headers

install: __build/cmake_install.cmake
	cmake --install __build

tests: tests/CMakeLists.txt
	cmake --version
	cmake -S tests -B __build/find-tests -G Ninja \
  -D CMAKE_EXPERIMENTAL_CXX_IMPORT_STD="451f2fe2-a8a2-47c3-bc32-94786d8fc91b" \
  -D CMAKE_CXX_STDLIB_MODULES_JSON=${CMAKE_CXX_STDLIB_MODULES_JSON} \
  -D CMAKE_CXX_STANDARD=23 -D CMAKE_CXX_EXTENSIONS=YES -D CMAKE_CXX_STANDARD_REQUIRED=YES \
  -D CMAKE_BUILD_TYPE=Release \
  --log-level=VERBOSE -Wdev --fresh \
  # XXX --debug-find-pkg=modules_playground
	ln -sf __build/find-tests/compile_commands.json .
	ninja -C __build/find-tests
	ninja -C __build/find-tests test

distclean: # XXX clean
	rm -rf .cache __build stagedir compile_commands.json
	find . -name '*~' -delete

format: # XXX distclean
	git ls-files ::*.cmake ::*CMakeLists.txt | xargs gersemi -i --line-length 102 \
  --no-warn-about-unknown-commands
	git ls-files ::*.cpp ::*.cppm ::*.hpp | xargs clang-format -i

# Anything we don't know how to __build will use this rule.
% ::
	ninja -C __build $(@)
