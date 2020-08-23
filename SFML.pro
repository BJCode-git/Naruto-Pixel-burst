CONFIG += c++17 console
#CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.


# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += SFML_STATIC

SOURCES += \
        AnimatedSprite.cpp \
        animation.cpp \
        globales.cpp \
        main.cpp \
        personnage.cpp \
        settings.cpp

#TARGET=Naruto Pixel Burst

#DESTDIR = $$PWD

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



INCLUDEPATH += P:/SFML-Qt/include
DEPENDPATH += P:/SFML-Qt/include

LIBS += -L"P:/SFML-Qt/lib"
#Release Configuration
CONFIG(release, debug|release):
{
#Audio Related Libs
LIBS += -lsfml-audio-s          #SFML Static Module
LIBS += -lopenal32              #Dependency
LIBS += -lFLAC                  #Dependency
LIBS += -lvorbisenc             #Dependency
LIBS += -lvorbisfile            #Dependency
LIBS += -lvorbis                #Dependency
LIBS += -logg                   #Dependency

#SFML-Graphics Libs
LIBS += -lsfml-graphics-s       #SFML Static Module
LIBS += -lfreetype              #Dependency

#SFML-Network Libs
LIBS += -lsfml-network-s        #SFML Static Module
LIBS += -lws2_32                #Dependency

#SFML-Window Libs
LIBS += -lsfml-window-s         #SFML Static Module
LIBS += -lopengl32              #Dependency
LIBS += -lgdi32                 #Dependency

#SFML-System Libs
LIBS += -lsfml-system-s         #SFML Static Module
LIBS += -lwinmm                 #Dependency
}

#Debug Configuration
CONFIG(debug, debug|release):
{
#Audio Related Libs
LIBS += -lsfml-audio-s-d        #SFML Static Module
LIBS += -lopenal32              #Dependency
LIBS += -lFLAC                #Dependency
LIBS += -lvorbisenc          #Dependency
LIBS += -lvorbisfile         #Dependency
LIBS += -lvorbis         #Dependency
LIBS += -logg            #Dependency

#SFML-Graphics Libs
LIBS += -lsfml-graphics-s-d     #SFML Static Module
LIBS += -lfreetype               #Dependency

#SFML-Network Libs
LIBS += -lsfml-network-s-d      #SFML Static Module
LIBS += -lws2_32          #Dependency

#SFML-Window Libs
LIBS += -lsfml-window-s-d       #SFML Static Module
LIBS += -lopengl32            #Dependency
LIBS += -lgdi32         #Dependency

#SFML-System Libs
LIBS += -lsfml-system-s-d       #SFML Static Module
LIBS += -lwinmm            #Dependency
}

RESOURCES +=

HEADERS += \
    AnimatedSprite.h \
    animation.h \
    personnage.h \
    settings.h

RC_ICONS = naruto-sign-32.ico

#DISTFILES += \
#    assets/code/CODE Bold.otf \
#    assets/code/CODE Light.otf \
#    assets/code/nasalization/nasalization-rg.ttf \
#    assets/code/nasalization/read-this.html \
#    assets/code/nasalization/typodermic-eula-02-2014.pdf \
#    assets/code/roboto/NOTICE.txt \
#    assets/code/roboto/Roboto-Black.ttf \
#    assets/code/roboto/Roboto-BlackItalic.ttf \
#    assets/code/roboto/Roboto-Bold.ttf \
#    assets/code/roboto/Roboto-BoldCondensed.ttf \
#    assets/code/roboto/Roboto-BoldCondensedItalic.ttf \
#    assets/code/roboto/Roboto-BoldItalic.ttf \
#    assets/code/roboto/Roboto-Condensed.ttf \
#    assets/code/roboto/Roboto-CondensedItalic.ttf \
#    assets/code/roboto/Roboto-Italic.ttf \
#    assets/code/roboto/Roboto-Light.ttf \
#    assets/code/roboto/Roboto-LightItalic.ttf \
#    assets/code/roboto/Roboto-Medium.ttf \
#    assets/code/roboto/Roboto-MediumItalic.ttf \
#    assets/code/roboto/Roboto-Regular.ttf \
#    assets/code/roboto/Roboto-Thin.ttf \
#    assets/code/roboto/Roboto-ThinItalic.ttf \
#    assets/code/roboto/Roboto_Specimen_Book.pdf \
#    assets/musics/The_Offspring_All_I_Want_8_bit.flac

