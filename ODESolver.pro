#Author Caleb Amoa Buahin
#Email caleb.buahin@gmail.com
#Date 2014-2018
#License GNU Lesser General Public License (see <http: //www.gnu.org/licenses/> for details).
#Copyright 2014-2018, Caleb Buahin, All rights reserved.

TEMPLATE = lib
TARGET = ODESolver
VERSION = 1.0.0
QT += core testlib

CONFIG += c++11
CONFIG += debug_and_release
CONFIG += optimize_full

#DEFINES += ODESOLVER_LIBRARY
DEFINES += USE_CHPC
DEFINES += USE_OPENMP
DEFINES += USE_MPI
DEFINES += USE_CVODE 
#DEFINES += USE_CVODE_OPENMP


#Compile as library or executable
contains(DEFINES,ODESOLVER_LIBRARY){
  TEMPLATE = lib
  message("Compiling ODESolver as library")
} else {
  TEMPLATE = app
  CONFIG-=app_bundle
  message("Compiling ODESolver as application")
}

PRECOMPILED_HEADER = ./include/stdafx.h

INCLUDEPATH += .\
               ./include 

HEADERS += ./include/stdafx.h \
           ./include/odesolver_global.h \
           ./include/odesolver.h \
           ./include/test/odesolvertest.h

SOURCES +=./src/stdafx.cpp \
          ./src/odesolver.cpp \
          ./src/main.cpp \
          ./src/test/odesolvertest.cpp 

macx{

    INCLUDEPATH += /usr/local \
                   /usr/local/include

    contains(DEFINES, USE_CVODE){
        message("CVODE enabled")
        LIBS += -L/usr/local/lib -lsundials_cvode
    }

    contains(DEFINES,USE_OPENMP){

        QMAKE_CC = /usr/local/opt/llvm/bin/clang
        QMAKE_CXX = /usr/local/opt/llvm/bin/clang++
        QMAKE_LINK = /usr/local/opt/llvm/bin/clang++

        QMAKE_CFLAGS+= -fopenmp
        QMAKE_LFLAGS+= -fopenmp
        QMAKE_CXXFLAGS+= -fopenmp

        INCLUDEPATH += /usr/local/opt/llvm/lib/clang/5.0.0/include
        LIBS += -L /usr/local/opt/llvm/lib -lomp

        message("OpenMP enabled")

       } else {

        message("OpenMP disabled")
    }

    contains(DEFINES,USE_MPI){

        QMAKE_CC = /usr/local/bin/mpicc
        QMAKE_CXX = /usr/local/bin/mpicxx
        QMAKE_LINK = /usr/local/bin/mpicxx

        LIBS += -L/usr/local/lib -lmpi

        message("MPI enabled")

    } else {

      message("MPI disabled")

    }
}


linux{

    INCLUDEPATH += /usr/include

    contains(DEFINES,USE_CHPC){

        contains(DEFINES,USE_CVODE){

            message("CVODE enabled")

            INCLUDEPATH += ../sundials-3.1.1/instdir/include
            LIBS += -L../sundials-3.1.1/instdir/lib -lsundials_cvode
        }
        message("Compiling on CHPC")
    }

    contains(DEFINES,USE_OPENMP){

      QMAKE_CFLAGS += -fopenmp
      QMAKE_LFLAGS += -fopenmp
      QMAKE_CXXFLAGS += -fopenmp

      message("OpenMP enabled")

    } else {

      message("OpenMP disabled")

    }

    contains(DEFINES,USE_MPI){

        QMAKE_CC = mpicc
        QMAKE_CXX = mpic++
        QMAKE_LINK = mpic++

        LIBS += -L/usr/local/lib/ -lmpi

        message("MPI enabled")

        } else {

        message("MPI disabled")

    }
}

win32{

    #Windows vspkg package manager installation path if environment variable is not set
    VCPKGDIR = C:/vcpkg/installed/x64-windows

    INCLUDEPATH += $${VCPKGDIR}/include \
                   $${VCPKGDIR}/include/gdal

    contains(DEFINES, USE_CVODE){

       message("CVODE enabled")

       CONFIG(debug, debug|release) {
            message("CVODE debug")
            LIBS += -L$${VCPKGDIR}/debug/lib -lsundials_cvode

        } else {
            LIBS += -L$${VCPKGDIR}/lib -lsundials_cvode
        }
    }

    contains(DEFINES,USE_OPENMP){

        QMAKE_CFLAGS += /openmp
        QMAKE_CXXFLAGS += /openmp

        message("OpenMP enabled")

     } else {

       message("OpenMP disabled")

     }

    contains(DEFINES,USE_MPI){

        message("MPI enabled")

        CONFIG(debug, debug|release) {
            LIBS += -L$${VCPKGDIR}/debug/lib -lmsmpi
          } else {
            LIBS += -L$${VCPKGDIR}/lib -lmsmpi
        }

    } else {
      message("MPI disabled")
    }

    QMAKE_CXXFLAGS += /MP
    QMAKE_LFLAGS += /incremental /debug:fastlink

}

CONFIG(debug, debug|release) {

    win32 {
       QMAKE_CXXFLAGS += /MDd /O2
    }

    macx {
       QMAKE_CXXFLAGS += -O3
    }

    linux {
       QMAKE_CXXFLAGS += -O3
    }

   DESTDIR = ./build/debug
   OBJECTS_DIR = $$DESTDIR/.obj
   MOC_DIR = $$DESTDIR/.moc
   RCC_DIR = $$DESTDIR/.qrc
   UI_DIR = $$DESTDIR/.ui
}

CONFIG(release, debug|release) {

   win32 {
    QMAKE_CXXFLAGS += /MD
   }

    RELEASE_EXTRAS = ./build/release
    OBJECTS_DIR = $$RELEASE_EXTRAS/.obj
    MOC_DIR = $$RELEASE_EXTRAS/.moc
    RCC_DIR = $$RELEASE_EXTRAS/.qrc
    UI_DIR = $$RELEASE_EXTRAS/.ui
}
