set(LIB_SRCS
    bsearchtree.h
    btreenode.h
    linkedlist.h
    linkedlistelement.h
    rbtree.h
    rbtreenode.h
    prettyprintrbtree.h
)
add_library(mystd SHARED ${LIB_SRCS})
set_target_properties(mystd PROPERTIES LINKER_LANGUAGE CXX)
