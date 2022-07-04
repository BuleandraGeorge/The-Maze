cmake_minimum_required(VERSION "3.14.0")

project("Polymorphism")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
add_executable("${PROJECT_NAME}" "Main.cpp" "Bullet.cpp" "Bullet.h" "GameObject.cpp" "GameObject.h" "NPC.cpp" "NPC.h" "Portal.h" "Trigger.h" "Screen" "Highscores.h" "ObjectManipulator.cpp" "ObjectManipulator.h" "PatternTurret.cpp" "PatternTurret.h" "Player.cpp" "Player.h" "TriggerTurret.cpp" "TriggerTurret.h" "Wall.cpp" "Wall.h" "Portal.cpp" "Trigger.cpp" "Screen.cpp" "Highscores.cpp" "Message.h" "Message.cpp")

set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

#look for SFML and add it
find_package (SFML 2.5.1 REQUIRED system window graphics network audio)

target_link_libraries(Polymorphism PRIVATE sfml-audio sfml-graphics sfml-network sfml-system)


#include_directories(${SFML_INCLUDE_DIR})

install(TARGETS "${PROJECT_NAME}" DESTINATION bin) #${CMAKE_INSTALL_PREFIX}/bin
#install(FILES "Main.cpp " "Bullet.cpp" "GameObject.cpp" "NPC.cpp" "ObjectManipulator.cpp" "PatternTurret.cpp" "Player.cpp" "TriggerTurret.cpp" "Wall.cpp"  "Portal.cpp" "Trigger.cpp" "Screen.cpp" "Highscores.cpp" "Message.cpp" DESTINATION src)
install(FILES "Main.cpp " DESTINATION src)
# Group into "Source Files" and "Header Files"
    if ("${FILE}" MATCHES ".*\\.cpp")
      set(GROUP "src${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
      set(GROUP "include${GROUP}")
    endif()

	
set(CMAKE_SUPPRESS_REGENERATION true)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
