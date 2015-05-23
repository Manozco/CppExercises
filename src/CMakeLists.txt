set(LIB_SRCS
    bsearchtree.h
    btreenode.h
    linkedlist.h
    linkedlistelement.h
)
add_library(mystd SHARED ${LIB_SRCS})
set_target_properties(mystd PROPERTIES LINKER_LANGUAGE CXX)
