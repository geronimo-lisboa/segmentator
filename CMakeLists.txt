cmake_minimum_required(VERSION 2.8)
#nome do projeto
project(Segmentator)
#Seta os paths das coisas necessárias
set(ITK_DIR "C:/libs/itk/ITK_bin")#itk
set(VTK_DIR "C:/libs/VTK-8.0.0_bin")#vtk
set(D3D_LIBRARY "d3d9.lib")#necessário pra pegar o tamanho da memória da GPU.
set(WBEM_LIBRARY "wbemuuid.lib")#necessário pra pegar o tamanho da memória da GPU.

# Find ITK.
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
# Find VTK
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})


#pega os arquivos
file(GLOB my_source_files "*.h" "*.cpp")
#Define um executável
add_executable(segmentator ${my_source_files} )
#Liga as bibliotecas ao executável definido
target_link_libraries(segmentator ${ITK_LIBRARIES} ${VTK_LIBRARIES})
target_link_libraries(segmentator ${D3D_LIBRARY} ${WBEM_LIBRARY})