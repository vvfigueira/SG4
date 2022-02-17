
#----------------------------------------------------------------------------
# Definição do Projeto
#

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(SG4)

#----------------------------------------------------------------------------
# Encontra a instalação do Geant4 e ativa todos seus drives gráficos
# Pode definir-se WITH_GEANT4_UIVIS como OFF para executar apenas em batch
#

option(WITH_GEANT4_UIVIS "Constrói o projeto com Geant4 UI e drives de visualização" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Carrega bibliotecas do Geant4 e seus compiladores
# 


include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Bibliotecas e códigos fonte do projeto
# 

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB sources ${PROJECT_SOURCE_DIR}/source/*.cc )
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh )

#----------------------------------------------------------------------------
# Constrói o executável 'build'
#

add_executable(build main.cc ${sources} ${headers})
target_link_libraries(build ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
# Copia arquivos para a pasta onde ~$ cmake foi executado
# 

set(SG4_scripts
  run.mac
  vis.mac
  )

foreach(_script ${SG4_scripts})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Para uso interno do Geant4
# 

add_custom_target(SG4 DEPENDS build)

#----------------------------------------------------------------------------
# Instala o executável no 'bin' da definição de CMAKE_INSTALL_PREFIX
#

install(TARGETS build DESTINATION bin)