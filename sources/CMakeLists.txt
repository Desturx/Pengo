#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Map.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Player.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/tinyxml2.cpp"
    
)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}/headers"
)

