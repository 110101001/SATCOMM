aux_source_directory(. DIR_SRCS)
include_directories("../include/")
include_directories("..")
add_library(src ${DIR_SRCS})
