#
# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2020-2021, Intel Corporation
# Copyright 2021, Fujitsu
#

cmake_minimum_required(VERSION 3.3)
project(exampleR C)

set(LIBPMEM_REQUIRED_VERSION 1.6)

# append -Wall and -Werror to CMAKE_C_FLAGS
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(PkgConfig QUIET)

if(PKG_CONFIG_FOUND)
	pkg_check_modules(LIBRPMA librpma)
	pkg_check_modules(LIBIBVERBS libibverbs)
	pkg_check_modules(LIBPMEM libpmem>=${LIBPMEM_REQUIRED_VERSION})
endif()
if(NOT LIBRPMA_FOUND)
	find_package(LIBRPMA REQUIRED librpma)
endif()
if(NOT LIBIBVERBS_FOUND)
	find_package(LIBIBVERBS REQUIRED libibverbs)
endif()
if(NOT LIBPMEM_FOUND)
	find_package(LIBPMEM ${LIBPMEM_REQUIRED_VERSION} REQUIRED libpmem)
endif()

link_directories(${LIBRPMA_LIBRARY_DIRS})

function(add_example name)
	set(srcs ${ARGN})
	add_executable(${name} ${srcs})
	target_include_directories(${name} PRIVATE ${LIBRPMA_INCLUDE_DIRS} ${LIBPMEM_INCLUDE_DIRS})
	target_link_libraries(${name} rpma ${LIBIBVERBS_LIBRARIES} ${LIBRT_LIBRARIES} ${LIBPMEM_LIBRARIES})
endfunction()

add_example(server server.c common.c)
add_example(client client.c common.c)
add_example(simple_server simple_server.c common.c)
add_example(simple_client simple_client.c common.c)

add_custom_target(config_softroce
	COMMAND ${CMAKE_SOURCE_DIR}/tools/config_softroce.sh)
