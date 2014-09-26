# Find the kernel release
execute_process(
  COMMAND uname -r
  OUTPUT_VARIABLE KERNEL_RELEASE
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Find the headers
find_path(KERNELHEADERS_DIR
  NAMES include/linux/list.h
  PATHS /usr/src/kernels/${KERNEL_RELEASE}
)

if (KERNELHEADERS_DIR)
  set(KERNELHEADERS_INCLUDE_DIRS
    ${KERNELHEADERS_DIR}/include
# Only needed on 2.x kernels
#    ${KERNELHEADERS_DIR}/arch/x86/include/asm
    ${KERNELHEADERS_DIR}/include/arch/x86/include
    ${KERNELHEADERS_DIR}/include/arch/x86/include/generated
    CACHE PATH "Kernel headers include dirs" FORCE
  )
  set(KERNELHEADERS_FOUND 1 CACHE STRING "Set to 1 if kernel headers were found")
else (KERNELHEADERS_DIR)
  set(KERNELHEADERS_FOUND 0 CACHE STRING "Set to 1 if kernel headers were found")
endif (KERNELHEADERS_DIR)

message(STATUS "Kernel release: ${KERNEL_RELEASE}")
message(STATUS "Kernel headers: ${KERNELHEADERS_DIR}")
message(STATUS "Kernel include dirs: ${KERNELHEADERS_INCLUDE_DIRS}")

mark_as_advanced(KERNELHEADERS_FOUND)
