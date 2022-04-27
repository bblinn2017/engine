QT += core gui opengl widgets

TARGET = cs195u_engine
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++14
CONFIG += c++14

unix:!macx {
    LIBS += -lGLU
}
macx {
    QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.7
    QMAKE_CXXFLAGS_X86_64 = $$QMAKE_CFLAGS_X86_64
    CONFIG += c++11
}
win32 {
    DEFINES += GLEW_STATIC
    LIBS += -lopengl32 -lglu32
}

SOURCES += \
    libs/glew-1.10.0/src/glew.c \
    src/app/behaviortrees/tagtree/tagtree.cpp \
    src/app/components/tagcomponent.cpp \
    src/app/screens/mainscreen.cpp \
    src/app/gameobjects/menu.cpp \
    src/app/myapp.cpp \
    src/app/gameobjects/other.cpp \
    src/app/screens/playscreen.cpp \
    src/common/player.cpp \
    src/residentevil/gameobjects/part.cpp \
    src/residentevil/re_app.cpp \
    src/residentevil/screens/gamescreen.cpp \
    src/spatialstructures/gameobjectbvh.cpp \
    src/app/gameobjects/world.cpp \
    src/objects/complex.cpp \
    src/objects/cylinder.cpp \
    src/spatialstructures/tribvh.cpp \
    src/common/component.cpp \
    src/common/application.cpp \
    src/common/gameobject.cpp \
    src/common/gameworld.cpp \
    src/common/input.cpp \
    src/common/system.cpp \
    src/components/cameracomponent.cpp \
    src/components/drawcomponent.cpp \
    src/components/enemyresponsecomponent.cpp \
    src/components/movementcomponent.cpp \
    src/components/navigationcomponent.cpp \
    src/components/navmeshcomponent.cpp \
    src/components/objcollisioncomponent.cpp \
    src/components/objectcomponent.cpp \
    src/components/playercontrolcomponent.cpp \
    src/components/transformcomponent.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/common/screen.cpp \
    src/systems/drawsystem.cpp \
    src/systems/navigationsystem.cpp \
    src/systems/ticksystem.cpp \
    src/view.cpp \
    src/viewformat.cpp \
    src/engine/graphics/ResourceLoader.cpp \
    src/engine/graphics/FBO.cpp \
    src/engine/graphics/IBO.cpp \
    src/engine/graphics/Texture.cpp \
    src/engine/graphics/Texture1D.cpp \
    src/engine/graphics/Texture2D.cpp \
    src/engine/graphics/Texture3D.cpp \
    src/engine/graphics/VAO.cpp \
    src/engine/graphics/VBO.cpp \
    src/engine/graphics/VBOAttribMarker.cpp \
    src/engine/graphics/Font.cpp \
    src/engine/graphics/DepthBuffer.cpp \
    src/engine/graphics/RenderBuffer.cpp \
    src/engine/graphics/GraphicsDebug.cpp \
    src/engine/graphics/Shader.cpp \
    src/engine/graphics/Camera.cpp \
    src/engine/graphics/Shape.cpp \
    src/engine/graphics/Graphics.cpp \
    src/engine/graphics/Material.cpp \
    src/engine/graphics/Light.cpp \
    src/engine/graphics/OBJLoader.cpp

HEADERS += \
    libs/glew-1.10.0/include/GL/glew.h \
    libs/stb/stb_rect_pack.h \
    libs/stb/stb_truetype.h \
    src/app/behaviortrees/tagtree/chase.h \
    src/app/behaviortrees/tagtree/chase_hide.h \
    src/app/behaviortrees/tagtree/hide.h \
    src/app/behaviortrees/tagtree/isChasing.h \
    src/app/behaviortrees/tagtree/pickTarget.h \
    src/app/behaviortrees/tagtree/tagtree.h \
    src/app/behaviortrees/tagtree/wait.h \
    src/app/components/appcomponents.h \
    src/app/components/tagcomponent.h \
    src/app/gameobjects/appgameobjects.h \
    src/app/screens/mainscreen.h \
    src/app/gameobjects/menu.h \
    src/app/myapp.h \
    src/app/gameobjects/other.h \
    src/app/screens/playscreen.h \
    src/behaviortree/behaviortree.h \
    src/behaviortree/nodemap.h \
    src/common/player.h \
    src/residentevil/gameobjects/part.h \
    src/residentevil/gameobjects/regameobjects.h \
    src/residentevil/re_app.h \
    src/residentevil/screens/gamescreen.h \
    src/spatialstructures/gameobjectbvh.h \
    src/app/gameobjects/world.h \
    src/behaviortree/action.h \
    src/behaviortree/basicsbehaviortree.h \
    src/behaviortree/btreenode.h \
    src/behaviortree/composite.h \
    src/behaviortree/condition.h \
    src/behaviortree/leaf.h \
    src/behaviortree/nodecaster.h \
    src/behaviortree/selector.h \
    src/behaviortree/sequence.h \
    src/objects/basicobjects.h \
    src/objects/complex.h \
    src/objects/cylinder.h \
    src/spatialstructures/bvh.h \
    src/objects/objects.h \
    src/spatialstructures/spatialstructures.h \
    src/spatialstructures/tribvh.h \
    src/common/component.h \
    src/common/gameobject.h \
    src/common/application.h \
    src/common/input.h \
    src/common/system.h \
    src/common/triangle.h \
    src/components/basiccomponents.h \
    src/components/cameracomponent.h \
    src/components/drawcomponent.h \
    src/components/enemyresponsecomponent.h \
    src/components/movementcomponent.h \
    src/components/navigationcomponent.h \
    src/components/navmeshcomponent.h \
    src/components/objcollisioncomponent.h \
    src/components/objectcomponent.h \
    src/components/playercontrolcomponent.h \
    src/components/transformcomponent.h \
    src/engine/util/TypeMap.h \
    src/common/gameworld.h \
    src/mainwindow.h \
    src/common/screen.h \
    src/systems/basicsystems.h \
    src/systems/bvhcollisionsystem.h \
    src/systems/collisionsystem.h \
    src/systems/drawsystem.h \
    src/systems/navigationsystem.h \
    src/systems/ticksystem.h \
    src/view.h \
    src/viewformat.h \
    src/engine/util/CommonIncludes.h \
    src/engine/graphics/ResourceLoader.h \
    src/engine/graphics/CylinderData.h \
    src/engine/graphics/SphereData.h \
    src/engine/graphics/FBO.h \
    src/engine/graphics/IBO.h \
    src/engine/graphics/Texture.h \
    src/engine/graphics/Texture1D.h \
    src/engine/graphics/Texture2D.h \
    src/engine/graphics/Texture3D.h \
    src/engine/graphics/VAO.h \
    src/engine/graphics/VBO.h \
    src/engine/graphics/VBOAttribMarker.h \
    src/engine/graphics/CubeData.h \
    src/engine/graphics/Font.h \
    src/engine/graphics/DepthBuffer.h \
    src/engine/graphics/RenderBuffer.h \
    src/engine/graphics/GraphicsDebug.h \
    src/engine/graphics/Shader.h \
    src/engine/graphics/ShaderAttribLocations.h \
    src/engine/graphics/Camera.h \
    src/engine/graphics/Graphics.h \
    src/engine/graphics/Shape.h \
    src/engine/graphics/Material.h \
    src/engine/graphics/Light.h \
    src/engine/graphics/Constants.h \
    src/engine/graphics/OBJLoader.h

FORMS += src/mainwindow.ui

RESOURCES += \
    res/platformer/meshes.qrc \
    res/shaders/shaders.qrc \
    res/fonts/fonts.qrc \
    res/images/images.qrc

OTHER_FILES += \
    res/images/grass.png \
    res/platformer/large_environment.obj \
    res/platformer/level_easy.obj \
    res/platformer/level_easy.png \
    res/platformer/level_easy_channels.png \
    res/platformer/level_easy_navmesh.obj \
    res/platformer/level_hard.obj \
    res/platformer/level_hard_channels.png \
    res/platformer/level_island.obj \
    res/platformer/level_island.png \
    res/platformer/level_island_channels.png \
    res/platformer/level_island_navmesh.obj \
    res/platformer/level_island_navemesh_eroded.obj

DISTFILES += \
    res/shaders/shader.vert \
    res/shaders/shader.frag

INCLUDEPATH += src libs glm libs/glew-1.10.0/include
DEPENDPATH += src libs glm libs/glew-1.10.0/include

# Don't add the -pg flag unless you know what you are doing. It makes QThreadPool freeze on Mac OS X
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_WARN_ON -= -Wall
QMAKE_CXXFLAGS_WARN_ON += -Waddress -Warray-bounds -Wc++0x-compat -Wchar-subscripts -Wformat\
                          -Wmain -Wmissing-braces -Wparentheses -Wreorder -Wreturn-type \
                          -Wsequence-point -Wsign-compare -Wstrict-overflow=1 -Wswitch \
                          -Wtrigraphs -Wuninitialized -Wunused-label -Wunused-variable \
                          -Wvolatile-register-var -Wno-extra

QMAKE_CXXFLAGS += -g
