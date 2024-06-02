set(CMAKE_FOLDER "Scripts")

set(CPPS
  $<$<PLATFORM_ID:Darwin,Linux>:
    linux_lib.cpp
  >
)

set(SCRIPTS
  aigame2
  AIGame3
  aigame4
  AIGame
  barney
  BatteriesIncluded
  BossCamera
  CanyonsCTF
  CellTestLevel
  ChrisTest
  clutter
  generic
  Geodomes
  HalfPipe
  InfernalBolt
  Inversion
  LEVEL0
  level10
  level11
  Level12
  level13
  level14
  LEVEL15
  Level16
  level17
  level1
  level2
  level3
  level4
  level5
  Level6
  level7
  level8
  Level9
  LevelS1
  levelS2
  Merc02
  Merc1
  Merc3
  Merc4
  merc5
  Merc6
  Merc7
  myPowerHouse
  Mysterious_Isle
  orbital
  Paranoia
  PiccuStation
  Polaris
  Quadsomniac
  RudeAwakening
  SewerRat
  testscript
  TrainingMission
  Y2K)

#add_custom_target(HogDemo-copy
#	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/scripts/data/demohog ${CMAKE_BINARY_DIR}/scripts/data/demohog/
#	COMMENT "Copy script/data/demohog directory"
#)

foreach(SCRIPT ${SCRIPTS})
  add_library(${SCRIPT} MODULE ${CPPS} "${SCRIPT}.cpp")
  target_link_libraries(${SCRIPT} PRIVATE
    fix
    module
    physics
    manage)
  set_target_properties(${SCRIPT} PROPERTIES PREFIX "")
  set_target_properties(${SCRIPT} PROPERTIES CXX_VISIBILITY_PRESET "hidden")

  if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set_target_properties(${SCRIPT} PROPERTIES SUFFIX ".dylib")
  endif()
endforeach()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(HOG_NAME "linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  set(HOG_NAME "osx")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(HOG_NAME "win")
endif()

add_custom_target(HogFull
  COMMAND $<TARGET_FILE:HogMaker>
    "$<TARGET_FILE_DIR:Descent3>/d3-${HOG_NAME}.hog"
    "${CMAKE_SOURCE_DIR}/scripts/data/fullhog/d3-${HOG_NAME}-fullhog.txt"
    "$<TARGET_FILE_DIR:AIGame>"
  DEPENDS ${SCRIPTS} HogMaker data/fullhog/d3-${HOG_NAME}-fullhog.txt
  COMMENT "Generate fullhog/d3-${HOG_NAME}.hog"
)

# Place file next to Descent3 executable on installation
install(FILES "$<TARGET_FILE_DIR:Descent3>/d3-${HOG_NAME}.hog" DESTINATION ${CMAKE_INSTALL_DATADIR})

# FIXME: there may be only one d3-linux.hog, need deal with demo somehow.
#	add_custom_target(HogLinuxDemo
#		COMMAND $<TARGET_FILE:HogMaker>
#     "${CMAKE_BINARY_DIR}/scripts/data/demohog/d3-${HOG_NAME}.hog"
#     "${CMAKE_BINARY_DIR}/scripts/data/demohog/d3-${HOG_NAME}-demohog.txt"
#     "${CMAKE_BINARY_DIR}/scripts/"
#		DEPENDS ${SCRIPTS} HogMaker data/fullhog/d3-${HOG_NAME}-demohog.txt
#		COMMENT "Generate linuxdemohog/d3-${HOG_NAME}.hog"
#	)
