add_library(ext_namedtype INTERFACE)
target_include_directories(ext_namedtype INTERFACE namedtype)

add_library(ext_type_safe INTERFACE)
target_include_directories(ext_type_safe INTERFACE type_safe/include)

add_library(ext_strong_type INTERFACE)
target_include_directories(ext_strong_type INTERFACE strong_type/include)

add_library(ext_stype INTERFACE)
target_include_directories(ext_stype INTERFACE stype/include)
