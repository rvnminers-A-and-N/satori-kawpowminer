# A custom command and target to turn the CUDA kernel into a byte array header
# The normal build depends on it properly and if the kernel file is changed, then
# a rebuild of libethash-cuda should be triggered

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/CUDAMiner_kernel.h
	COMMAND ${CMAKE_COMMAND} ARGS
	-DTXT2STR_SOURCE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/CUDAMiner_kernel.cu"
	-DTXT2STR_VARIABLE_NAME=CUDAMiner_kernel
	-DTXT2STR_HEADER_FILE="${CMAKE_CURRENT_BINARY_DIR}/CUDAMiner_kernel.h"
	-P "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/txt2str.cmake"
	COMMENT "Generating CUDA Kernel"
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/CUDAMiner_kernel.cu
)
add_custom_target(cuda_kernel DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/CUDAMiner_kernel.h ${CMAKE_CURRENT_SOURCE_DIR}/CUDAMiner_kernel.cu)

find_package(CUDA REQUIRED)

set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};--ptxas-options=-v;-lineinfo;-use_fast_math)

if (NOT MSVC)
	list(APPEND CUDA_NVCC_FLAGS "--disable-warnings")
endif()

list(APPEND CUDA_NVCC_FLAGS_RELEASE -O3)
list(APPEND CUDA_NVCC_FLAGS_DEBUG -G)

message("")
message("----------------------------------------------------------------------------")
message("-- Detected CUDA Version: ${CUDA_VERSION}")
if(COMPUTE)
	message("-- Compute Version: ${COMPUTE}")
endif()
message("----------------------------------------------------------------------------")
message("")

if(COMPUTE AND (COMPUTE GREATER 0))
	list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_${COMPUTE},code=sm_${COMPUTE}")
else()
	# Complete architecture support matrix - 4 builds required for full coverage:
	# Ancient (CUDA 10.2): UNIQUE sm_30,32 | SHARED sm_35,50,52,53,60,61,62,70,72,75
	# Legacy (CUDA 11.8): UNIQUE sm_35,37 | SHARED sm_50,52,53,60,61,62,70,72,75,80,86,87,89,90
	# Standard (CUDA 12.9.1): UNIQUE sm_50-72,101 variants | SHARED sm_75,80,86,87,89,90,90a,100,103,120,121
	# Modern (CUDA 13.0): UNIQUE sm_88,110 variants | SHARED sm_75,80,86,87,89,90,90a,100,103,120,121
	# CRITICAL: sm_101 variants ONLY in 12.9.1, NOT in 13.0 | sm_110 variants ONLY in 13.0, NOT in 12.9.1!
	
	# ============================================================================
	# KEPLER ARCHITECTURE (Compute Capability 3.x)
	# ============================================================================
	
	# Kepler sm_30, sm_32 - ONLY in CUDA 10.x
	# GPUs: GTX 680, GTX 690, GT 640, GT 630, Quadro K5000
	if(CUDA_VERSION VERSION_LESS 11.0)
		list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_30,code=sm_30")
		list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_32,code=sm_32")
	endif()
	
	# Kepler sm_35, sm_37 - CUDA 10.x and 11.x (dropped in 12.0)
	# GPUs: GTX 780, GTX 780 Ti, GTX Titan, Tesla K20/K40, Quadro K6000
	if(CUDA_VERSION VERSION_LESS 12.0)
		list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_35,code=sm_35")
		if(CUDA_VERSION VERSION_GREATER_EQUAL 11.0)
			# sm_37 only exists in CUDA 11.x
			list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_37,code=sm_37")
		endif()
	endif()
	
	# ============================================================================
	# MAXWELL ARCHITECTURE (Compute Capability 5.x)
	# ============================================================================
	
	# Maxwell - Supported through CUDA 12.x, dropped in CUDA 13.0
	# sm_50: GTX 750, GTX 750 Ti (first-gen Maxwell)
	# sm_52: GTX 960, GTX 970, GTX 980, GTX Titan X, Quadro M6000
	# sm_53: Tegra TX1, Jetson Nano
	if(CUDA_VERSION VERSION_LESS 13.0 AND CUDA_VERSION VERSION_GREATER_EQUAL 10.0)
		list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_50,code=sm_50")
		list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_52,code=sm_52")
		list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_53,code=sm_53")
	endif()
	
	# ============================================================================
	# PASCAL ARCHITECTURE (Compute Capability 6.x)
	# ============================================================================
	
	# Pascal - Supported through CUDA 12.x, dropped in CUDA 13.0
	# sm_60: GP100 - Tesla P100
	# sm_61: GP102/GP104/GP106 - GTX 1080, GTX 1070, GTX 1060, Quadro P6000/P5000
	# sm_62: Tegra TX2
	if(CUDA_VERSION VERSION_LESS 13.0 AND CUDA_VERSION VERSION_GREATER_EQUAL 10.0)
		list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_60,code=sm_60")
		list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_61,code=sm_61")
		list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_62,code=sm_62")
	endif()
	
	# ============================================================================
	# VOLTA ARCHITECTURE (Compute Capability 7.x)
	# ============================================================================
	
	# Volta - Supported through CUDA 12.x, dropped in CUDA 13.0!
	# sm_70: GV100 - Tesla V100, Titan V, Quadro GV100
	# sm_72: Tegra Xavier
	if(CUDA_VERSION VERSION_LESS 13.0 AND CUDA_VERSION VERSION_GREATER_EQUAL 10.0)
		list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_70,code=sm_70")
		list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_72,code=sm_72")
	endif()
	
	# ============================================================================
	# TURING ARCHITECTURE (Compute Capability 7.5)
	# ============================================================================
	
	# Turing - Supported in all modern CUDA versions (10.0+)
	# sm_75: TU102/TU104/TU106 - RTX 2080 Ti, RTX 2080, RTX 2070, RTX 2060
	#        GTX 1660 Ti, GTX 1660, GTX 1650, Quadro RTX 8000/6000/5000
	if(CUDA_VERSION VERSION_GREATER_EQUAL 10.0)
		list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_75,code=sm_75")
	endif()
	
	# ============================================================================
	# AMPERE ARCHITECTURE (Compute Capability 8.x)
	# ============================================================================
	
	# Ampere - CUDA 11.0+ required
	if(CUDA_VERSION VERSION_GREATER_EQUAL 11.0)
		# sm_80: GA100 - A100, A30
		list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_80,code=sm_80")
		# sm_86: GA102/GA104 - RTX 3090, RTX 3080, RTX 3070, RTX 3060 Ti, RTX A6000
		list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_86,code=sm_86")
		
		if(CUDA_VERSION VERSION_GREATER_EQUAL 11.8)
			# sm_87: GA107 - RTX 3050, RTX 3060, mobile variants
			list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_87,code=sm_87")
		endif()
		
		if(CUDA_VERSION VERSION_GREATER_EQUAL 13.0)
			# sm_88: Ampere refresh (specific variants)
			list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_88,code=sm_88")
		endif()
	endif()
	
	# ============================================================================
	# ADA LOVELACE ARCHITECTURE (Compute Capability 8.9)
	# ============================================================================
	
	# Ada Lovelace - CUDA 11.8+ required
	# sm_89: AD102/AD103/AD104 - RTX 4090, RTX 4080, RTX 4070 Ti, RTX 4070
	#        RTX 4060 Ti, RTX 4060, L4, L40, RTX 6000 Ada
	if(CUDA_VERSION VERSION_GREATER_EQUAL 11.8)
		list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_89,code=sm_89")
	endif()
	
	# ============================================================================
	# HOPPER ARCHITECTURE (Compute Capability 9.x)
	# ============================================================================
	
	# Hopper - CUDA 11.8+ required
	if(CUDA_VERSION VERSION_GREATER_EQUAL 11.8)
		# sm_90: GH100 - H100, H200
		list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_90,code=sm_90")
		
		if(CUDA_VERSION VERSION_GREATER_EQUAL 12.0)
			# sm_90a: H100 specific optimizations (TMA support)
			list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_90,code=sm_90a")
		endif()
	endif()
	
	# ============================================================================
	# BLACKWELL ARCHITECTURE (Compute Capability 10.x, 12.x)
	# ============================================================================
	
	# Blackwell - Different levels of support across CUDA versions
	if(CUDA_VERSION VERSION_GREATER_EQUAL 12.5)
		# Base Blackwell support (12.5+)
		# sm_100: B100, B200 base models
		list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_100,code=sm_100")
		
		if(CUDA_VERSION VERSION_GREATER_EQUAL 12.9)
			# Extended Blackwell support (12.9+)
			# sm_100f, sm_100a: B100 variants with FP8/TMA features
			list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_100,code=sm_100f")
			list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_100,code=sm_100a")
			
			# sm_101: UNIQUE to CUDA 12.9.x - NOT in 13.0!
			# CRITICAL: Must check that version is LESS than 13.0
			if(CUDA_VERSION VERSION_LESS 13.0)
				list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_101,code=sm_101")
				list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_101,code=sm_101f")
				list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_101,code=sm_101a")
			endif()
			
			# sm_103: RTX 50 series consumer GPUs
			list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_103,code=sm_103")
			list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_103,code=sm_103f")
			list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_103,code=sm_103a")
			
			# sm_120, sm_121: GB200 superchip variants
			list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_120,code=sm_120")
			list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_120,code=sm_120f")
			list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_120,code=sm_120a")
			list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_121,code=sm_121")
			list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_121,code=sm_121f")
			list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_121,code=sm_121a")
		endif()
		
		if(CUDA_VERSION VERSION_GREATER_EQUAL 13.0)
			# sm_110: UNIQUE to CUDA 13.0 - NOT in 12.9!
			list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_110,code=sm_110")
			list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_110,code=sm_110f")
			list(APPEND CUDA_NVCC_FLAGS "-gencode arch=compute_110,code=sm_110a")
		endif()
	endif()
endif()

file(GLOB sources CUDAMiner.cpp CUDAMiner_cuda.cu)
file(GLOB headers CUDAMiner.h CUDAMiner_cuda.h ${CMAKE_CURRENT_BINARY_DIR}/CUDAMiner_kernel.h)

# Handle deprecated cuda_add_library for newer CMake versions
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.18")
	# Modern CUDA support for CMake 3.18+
	set_source_files_properties(CUDAMiner_cuda.cu PROPERTIES LANGUAGE CUDA)
	add_library(ethash-cuda STATIC ${sources} ${headers})
	set_target_properties(ethash-cuda PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
else()
	# Use legacy CUDA module for older CMake
	cuda_add_library(ethash-cuda STATIC ${sources} ${headers})
endif()
add_dependencies(ethash-cuda cuda_kernel)
# Cmake doesn't handle nvrtc automatically
find_library(CUDA_nvrtc_LIBRARY NAMES nvrtc PATHS ${CUDA_TOOLKIT_ROOT_DIR} PATH_SUFFIXES lib64 lib/x64 lib64/stubs lib/x64/stubs lib NO_DEFAULT_PATH)
find_library(CUDA_cuda_LIBRARY NAMES cuda PATHS ${CUDA_TOOLKIT_ROOT_DIR} PATH_SUFFIXES lib64 lib/x64 lib64/stubs lib/x64/stubs lib NO_DEFAULT_PATH)
target_link_libraries(ethash-cuda ethcore crypto Boost::thread)
target_link_libraries(ethash-cuda ${CUDA_nvrtc_LIBRARY} ${CUDA_cuda_LIBRARY})
target_include_directories(ethash-cuda PUBLIC ${CUDA_INCLUDE_DIRS})
target_include_directories(ethash-cuda PRIVATE .. ${CMAKE_CURRENT_BINARY_DIR})
