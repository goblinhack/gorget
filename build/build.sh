#!/bin/bash
#
# Copyright (C) goblinhack@gmail.com
#
# This game is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This game is distributed in the hope that it will be fun,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this game; if not, write to the Free
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

. ./build/common.sh

TARGET=gorget

# The default MINGW32 and MINGW64 environments build binaries using the older
#  MSVCRT library that should be present on all Windows systems.
MINGW_TYPE=mingw64
MINGW_PKG_TYPE=mingw-w64

# The MINGW UCRT environments build binaries using the newer UCRT library that
# is only known to be present on Windows 10. It should produce binaries more
# compatible with MSVC-compiled binaries, but not with the MSVCRT environment.
MINGW_TYPE=ucrt64
MINGW_PKG_TYPE=mingw-w64-ucrt

# Determine OS platform
# https://askubuntu.com/questions/459402/how-to-know-if-the-running-platform-is-ubuntu-or-centos-with-help-of-a-bash-scri
UNAME=$(uname | tr "[:upper:]" "[:lower:]")
# If Linux, try to determine specific distribution
if [ "$UNAME" == "linux" ]; then
    # If available, use LSB to identify distribution
    if [ -f /etc/lsb-release -o -d /etc/lsb-release.d ]; then
        export DISTRO=$(lsb_release -i | cut -d: -f2 | sed s/'^\t'//)
    # Otherwise, use release info file
    else
        export DISTRO=$(ls -d /etc/[A-Za-z]*[_-][rv]e[lr]* | grep -v "lsb" | cut -d'/' -f3 | cut -d'-' -f1 | cut -d'_' -f1)
    fi
fi

# For everything else (or if above failed), just use generic identifier
[ "$DISTRO" == "" ] && export DISTRO=$UNAME
unset UNAME

# Prefer gnu over freebsd coreutils
PATH=/opt/local/libexec/gnubin:$PATH

export PATH
log_info "Distro                     : $DISTRO"

help_full()
{
    case $(uname) in
    Linux)
      log_warn "For Fedora, you may need to install:"
      log_warn "  dnf install -y findutils"
      log_warn "  dnf install -y SDL2_mixer-devel SDL2_mixer"
      log_warn "  dnf install -y SDL2 SDL2-devel"
      log_warn "  dnf install -y SDL2_image SDL2_image-devel"
      log_warn "  dnf install -y git"
      log_warn "  dnf install -y make automake gcc-c++"
      log_warn "  dnf install -y vim"
      log_warn "  dnf install -y libmikmod-devel"
      log_warn "  dnf install -y libfishsound-devel"
      log_warn " "
      log_warn "Install the following for Ubuntu?"
      set -x
      sudo apt-get install -y build-essential \
                      g++ \
                      git \
                      libegl1 \
                      libfishsound1-dev \
                      libflac-dev \
                      libfluidsynth-dev \
                      libfreetype6-dev \
                      libgl1 \
                      libglvnd0 \
                      libglx0 \
                      libmikmod-dev \
                      liboggz2-dev \
                      libsdl2-2.0-0 \
                      libsdl2-dev \
                      libsdl2-mixer-2.0-0 \
                      libsdl2-mixer-dev \
                      libsmpeg-dev \
                      libx11-6 \
                      libxext6 \
                      ssh \
                      vim \
                      clang \
                      clang-format \
                      xutils-dev
      set +x
      echo "Now re-run RUNME"
      exit 0
      ;;
    *MING*|*MSYS*)
      log_warn "Install the following?"
      set -x
      pacman -S git \
        make vim base-devel --needed \
        ${MINGW_PKG_TYPE}-x86_64-SDL \
        ${MINGW_PKG_TYPE}-x86_64-SDL2 \
        ${MINGW_PKG_TYPE}-x86_64-SDL2_gfx \
        ${MINGW_PKG_TYPE}-x86_64-SDL2_image \
        ${MINGW_PKG_TYPE}-x86_64-SDL2_mixer \
        ${MINGW_PKG_TYPE}-x86_64-SDL2_net \
        ${MINGW_PKG_TYPE}-x86_64-SDL2_ttf \
        ${MINGW_PKG_TYPE}-x86_64-ag \
        ${MINGW_PKG_TYPE}-x86_64-binutils \
        ${MINGW_PKG_TYPE}-x86_64-bzip2 \
        ${MINGW_PKG_TYPE}-x86_64-clang \
        ${MINGW_PKG_TYPE}-x86_64-clang-tools-extra \
        ${MINGW_PKG_TYPE}-x86_64-crt-git \
        ${MINGW_PKG_TYPE}-x86_64-expat \
        ${MINGW_PKG_TYPE}-x86_64-flac \
        ${MINGW_PKG_TYPE}-x86_64-fluidsynth \
        ${MINGW_PKG_TYPE}-x86_64-gcc \
        ${MINGW_PKG_TYPE}-x86_64-gcc-libs \
        ${MINGW_PKG_TYPE}-x86_64-gdb \
        ${MINGW_PKG_TYPE}-x86_64-gdbm \
        ${MINGW_PKG_TYPE}-x86_64-gettext \
        ${MINGW_PKG_TYPE}-x86_64-giflib \
        ${MINGW_PKG_TYPE}-x86_64-glib2 \
        ${MINGW_PKG_TYPE}-x86_64-gmp \
        ${MINGW_PKG_TYPE}-x86_64-headers-git \
        ${MINGW_PKG_TYPE}-x86_64-isl \
        ${MINGW_PKG_TYPE}-x86_64-libffi \
        ${MINGW_PKG_TYPE}-x86_64-libiconv \
        ${MINGW_PKG_TYPE}-x86_64-libjpeg-turbo \
        ${MINGW_PKG_TYPE}-x86_64-libmad \
        ${MINGW_PKG_TYPE}-x86_64-libmodplug \
        ${MINGW_PKG_TYPE}-x86_64-libogg \
        ${MINGW_PKG_TYPE}-x86_64-libpng \
        ${MINGW_PKG_TYPE}-x86_64-libsndfile \
        ${MINGW_PKG_TYPE}-x86_64-libsystre \
        ${MINGW_PKG_TYPE}-x86_64-libtiff \
        ${MINGW_PKG_TYPE}-x86_64-libtre-git \
        ${MINGW_PKG_TYPE}-x86_64-libunwind \
        ${MINGW_PKG_TYPE}-x86_64-libvorbis \
        ${MINGW_PKG_TYPE}-x86_64-libwebp \
        ${MINGW_PKG_TYPE}-x86_64-libwinpthread-git \
        ${MINGW_PKG_TYPE}-x86_64-lld \
        ${MINGW_PKG_TYPE}-x86_64-mpc \
        ${MINGW_PKG_TYPE}-x86_64-mpfr \
        ${MINGW_PKG_TYPE}-x86_64-ncurses \
        ${MINGW_PKG_TYPE}-x86_64-openssl \
        ${MINGW_PKG_TYPE}-x86_64-portaudio \
        ${MINGW_PKG_TYPE}-x86_64-readline \
        ${MINGW_PKG_TYPE}-x86_64-smpeg2 \
        ${MINGW_PKG_TYPE}-x86_64-speex \
        ${MINGW_PKG_TYPE}-x86_64-speexdsp \
        ${MINGW_PKG_TYPE}-x86_64-termcap \
        ${MINGW_PKG_TYPE}-x86_64-windows-default-manifest \
        ${MINGW_PKG_TYPE}-x86_64-winpthreads-git \
        ${MINGW_PKG_TYPE}-x86_64-xz \
        ${MINGW_PKG_TYPE}-x86_64-zlib
      set +x
      echo "Now re-run RUNME"
      exit 0
      ;;
    *Darwin*)
      log_warn "Install MAC ports then install:"
      log_warn "  sudo port install libsdl2"
      log_warn "  sudo port install libsdl2_mixer"
      ;;
  esac
}

MY_OS_NAME=$(uname)
case "$MY_OS_NAME" in
    *MING*|*MSYS*)
        for i in \
            $(which sdl2-config) \
            /${MINGW_TYPE}/bin/sdl2-config
        do
            if [ -x "$i" ]; then
                SDL2_CONFIG=$i
                break
            fi
        done
    ;;
    *)
        for i in \
            $(which sdl2-config) \
            /opt/local/bin/sdl2-config \
            /usr/bin/sdl2-config
        do
            if [ -x "$i" ]; then
                SDL2_CONFIG=$i
                break
            fi
        done
    ;;
esac

sdl_help()
{
    log_err "I need SDL2 and SDL2 mixer installed"
    help_full
    exit 1
}

gcc_help()
{
    log_err "No g++ or clang compiler found"
    help_full
    exit 1
}

SDL2_SCORE=0

if [ "$SDL2_CONFIG" != "" ]; then
    SDL2_INC_PATH=$($SDL2_CONFIG --cflags | sed -e 's/.*-I\([a-zA-Z\/@_0-9:\.]*\) .*/\1/g' -e 's/\-.*//g')

    if [[ "$SDL2_INC_PATH" != "" ]]; then
        find "$SDL2_INC_PATH" | grep -q SDL_mixer.h
        if [ $? -eq 0 ]; then
            SDL2_SCORE=$((SDL2_SCORE + 1))
            SDL2_MIXER=$(find "$SDL2_INC_PATH" -name SDL_mixer.h)
        fi
    fi
fi

log_info "SDL2 config                : $SDL2_CONFIG"
log_info "SDL2 version               : "$($SDL2_CONFIG --version 2>/dev/null)
log_info "SDL2 libs                  : "$($SDL2_CONFIG --libs 2>/dev/null)
log_info "SDL2 static libs           : "$($SDL2_CONFIG --static-libs 2>/dev/null)
log_info "SDL2 cflags                : "$($SDL2_CONFIG --cflags 2>/dev/null)
log_info "SDL2 prefix                : "$($SDL2_CONFIG --prefix 2>/dev/null)
log_info "SDL2 exec-prefix           : "$($SDL2_CONFIG --exec-prefix 2>/dev/null)
log_info "SDL2 include path          : $SDL2_INC_PATH"
log_info "SDL2 mixer.h               : $SDL2_MIXER"
#log_info "SDL2 found                 : $SDL2_SCORE"

if [[ $SDL2_SCORE != "1" ]]; then
    sdl_help
    exit 1
fi

#
# Gives warnings at runtime on MACOS
#
SDL_LIBS=$($SDL2_CONFIG --libs)
if [ $? -ne 0 ]
then
    sdl_help
    exit 1
fi

C_FLAGS=$($SDL2_CONFIG --cflags | sed 's/ \-D_REENTRANT//g')
if [ $? -ne 0 ]
then
    sdl_help
    exit 1
fi

#
# -funwind-tables and -rdynamic for backtrace info on linux.
# But it seemed to help little.
#
LDLIBS="$SDL_LIBS"
LDLIBS="$LDLIBS -lSDL2_mixer"

/bin/rm -f data/gorget-hiscore.txt data/gorget-config.txt

#
# Common config file
#
CONFIG_H=src/cfg.hpp
echo "#include \"my_cfg.hpp\"" > $CONFIG_H
C_FLAGS+=" -include cfg.hpp"
rm -f src/precompiled.hpp.gch

#
# for backtraces, but it doesn't help much
#
case "$MY_OS_NAME" in
    *MSYS*)
        log_err "Please compile for ming64, not msys"
        exit 1
        ;;
    *MING*|*MSYS*)
        PATH=/${MINGW_TYPE}/bin:$PATH
        EXE=".exe"
        C_FLAGS+=" -I/${MINGW_TYPE}/ginclude "
        LDLIBS+=" -L/${MINGW_TYPE}/glib/"
        LDLIBS=$(echo $LDLIBS | sed -e 's/-lmingw32 //g')
        LDLIBS+=" -funwind-tables"
        LDLIBS+=" -lstdc++"
        LDLIBS+=" -lopengl32"
        LDLIBS+=" -lpthread"
        LDLIBS+=" /${MINGW_TYPE}/lib/libSDL2_mixer.a"
        LDLIBS+=" -L/${MINGW_TYPE}/lib/binutils -lbfd -lintl -ldbghelp -liberty -lz"

        if [ -f /${MINGW_TYPE}/lib/libunwind.a ]; then
          echo "#define HAVE_LIBUNWIND" >> $CONFIG_H
          LDLIBS+=" -lunwind"
          log_info "Have libunwind             : Yes"
        else
          log_info "Have libunwind             : No"
        fi

        #
        # Clang supports PDB debug file creation, but you need to do
        # the following to enable it.
        #
        C_FLAGS+=" -g -gcodeview"

        #
        # Needed to create PDB files
        #
        if [ -x /${MINGW_TYPE}/bin/lld ]; then
          LDFLAGS+=" -fuse-ld=lld "
        fi

        #
        # The space after pdb= is intentional to use the executable name for PDB file generation.
        #
        LDFLAGS+=" -g -Wl,--pdb= "
        ;;
    *Darwin*)
        EXE=""
        LDLIBS+=" -funwind-tables"
        LDLIBS+=" -rdynamic"
        LDLIBS+=" -Wl,-framework,Opengl"
        DSYM="dsymutil ../${TARGET}"

        if [[ $OPT_DEV2 != "" ]]; then
            C_FLAGS+=" -fsanitize=address -fno-omit-frame-pointer"
            LDFLAGS+=" -fsanitize=address"
        fi
        ;;
    *inux*)
        EXE=""
        LDFLAGS+=' -rdynamic'
        LDLIBS+=" -lGL "

        if [[ $OPT_DEV2 != "" ]]; then
            C_FLAGS+=" -fsanitize=address -fno-omit-frame-pointer -fno-common"
            LDFLAGS+=" -fsanitize=address"
        fi

        pkg-config --print-provides libunwind >/dev/null 2>/dev/null
        if [[ $? -eq 0 ]]; then
          echo "#define HAVE_LIBUNWIND" >> $CONFIG_H
          LDLIBS+=" -lunwind"
          log_info "Have libunwind             : Yes"
        else
          log_info "Have libunwind             : No"
        fi
        ;;
    *)
        EXE=""
        ;;
esac

#
# Better to leave off for production
#
# Windows builds also fail due to missing headers
#
WERROR=""
if [[ $OPT_DEV1 != "" ]]; then
    WERROR="-Werror"
fi

#
# Hard code on for me
#
if [[ $(grep -q goblinhack ~/.gitconfig 2>/dev/null) ]]; then
  WERROR="-Werror"
fi

echo "#define MYVER \"$MYVER\"" >> $CONFIG_H

log_info "VERSION (game)             : $MYVER"

cd src || exit

if [[ $OPT_PROF != "" ]]; then
    C_FLAGS+=" -pg"
    LDFLAGS+=" -pg"
fi

MAKEFILE=../build/Makefile.template

if [[ $OPT_REL != "" ]]; then
    echo "COMPILER_FLAGS=$WERROR $C_FLAGS -O3 -g" > $MAKEFILE
else
    echo "COMPILER_FLAGS=$WERROR $C_FLAGS -O0 -g" > $MAKEFILE
fi

if [[ $OPT_DEV2 != "" ]]; then
    GCC_STACK_CHECK="-fstack-protector-all -D_FORTIFY_SOURCE=2"
    GCC_STACK_CHECK="-fstack-protector-all"
else
    GCC_STACK_CHECK=
fi

#
# LLD is faster
#
which -s lld 2>/dev/null
if [ $? -eq 0 ]; then
  LDFLAGS+=" -fuse-ld=lld"
fi

cat >>$MAKEFILE <<%%
WARNING_FLAGS=-Wall -Wextra -Wpedantic
#
# When compiling C, give string constants the type const char[length] so that copying the address of
# one into a non-const char * pointer produces a warning. These warnings help you find at compile time
# code that can try to write into a string constant, but only if you have been very careful about using
# const in declarations and prototypes.
#
WARNING_FLAGS+=-Wwrite-strings
#
# Warn whenever a local variable or type declaration shadows another variable, parameter.
#
WARNING_FLAGS+=-Wshadow
#
# Warn whenever a function parameter is unused aside from its declaration. This option is not enabled by
# -Wunused unless -Wextra is also specified.
#
WARNING_FLAGS+=-Wno-unused-parameter
#
# Warn if anything is declared more than once in the same scope, even in cases where multiple declaration is valid and changes nothing.
#
WARNING_FLAGS+=-Wredundant-decls
#
# Enable -Wformat plus additional format checks. Currently equivalent to -Wformat -Wformat-nonliteral -Wformat-security -Wformat-y2k.
#
WARNING_FLAGS+=-Wformat=2
#
# If -Wformat is specified, also warn if the format string is not a string literal and so cannot be checked, unless the format
# function takes its format arguments as a va_list.
#
WARNING_FLAGS+=-Wno-format-nonliteral
#
# To silence Xcode warning: "variable length arrays are a C99 feature [-Wvla-extension]"?
#
WARNING_FLAGS+=-Wno-vla-extension
#
# A warning is generated if the precision of a value may change.
#
WARNING_FLAGS+=-Wfloat-conversion

CLANG_COMPILER_WARNINGS=\${WARNING_FLAGS} -std=c++2a
GCC_COMPILER_WARNINGS=\${WARNING_FLAGS} -std=c++2a $GCC_STACK_CHECK
LDFLAGS=$LDFLAGS
%%

GOT_CC=

g++ --version > /dev/null 2>/dev/null
if [ $? -eq 0 ]
then
    echo "COMPILER_WARNINGS=\$(GCC_COMPILER_WARNINGS)" >> $MAKEFILE
    echo "CC=g++" >> $MAKEFILE
    GOT_CC=1
fi

#
# Prefer clang as its faster
#
if [[ $OPT_GCC = "" ]]; then
  clang++ --version > /dev/null 2>/dev/null
  if [ $? -eq 0 ]; then
      echo "COMPILER_WARNINGS=\$(CLANG_COMPILER_WARNINGS)" >> $MAKEFILE
      echo "CC=clang++" >> $MAKEFILE
      GOT_CC=1
  fi
fi

if [[ $GOT_CC = "" ]]; then
    gcc_help
    exit 1
fi

case "$MY_OS_NAME" in
    *MING*|*MSYS*)
        echo "CC=/${MINGW_TYPE}/bin/clang++.exe" >> $MAKEFILE
        #
        # To resolve WinMain, add these at the end again
        #
        LDLIBS="$LDLIBS -lmingw32 -mwindows /${MINGW_TYPE}/lib/libSDL2main.a -L/${MINGW_TYPE}/lib -lSDL2main -lSDL2"
    ;;
esac

#
# Create the makefile
#
cat >>$MAKEFILE <<%%
EXE=$EXE
DSYM=$DSYM
LDLIBS=$LDLIBS
%%

#
# Cleanup pre-build
#
log_info "Cleaning"
make clobber | sed 's/^/  /g'

#
# How many cores?
#
CORES=""

case "$MY_OS_NAME" in
    *Darwin*)
      CORES=$(/usr/sbin/system_profiler -detailLevel full SPHardwareDataType  | grep Cores | sed 's/.*: //g' | awk '{print $1}')
    ;;
    *inux*)
      CORES=$(grep -E -c "cpu cores|processor" /proc/cpuinfo)
    ;;
    *MING*|*MSYS*)
      CORES=$(grep -E -c "cpu cores|processor" /proc/cpuinfo)
    ;;
esac

if [ "$CORES" != "" ]
then
    log_info "Compiling ($CORES cpus)"

    CORES="-j $CORES"
else
    log_info "Compiling"
fi

cd ..

echo USE_PRECOMPILED=yep make -f build/Makefile $CORES "$@" all
USE_PRECOMPILED=yep make -f build/Makefile $CORES "$@" all

if [ $? -eq 0 ]
then
    case "$MY_OS_NAME" in
        *MING*|*MSYS*)
            log_info "Run:"

            cat >${TARGET}-create-release.sh <<%%
#!/bin/sh
###############################################################################
# Execute the following to build the release
###############################################################################
#
# Clean up the old installs
#
rm ${TARGET}.*installer.exe

#
# Update the version
#
echo \$0: updating the version to $MYVER
sed -i "s/<version>.*/<version>$MYVER<\/version>/g" build/windows/windows.xml
(cd build/windows/ ; ./windows.sh)


#
# All commits since last tag
#
echo \$0: all commits since last tag
git log \$(git describe --tags --abbrev=0)..HEAD --oneline | grep -E "feat:|bug:" | sort +1 -r

#
# Lay a tag
#
echo \$0: laying a tag
git tag -m "tag: $MYVER" -a v$MYVER
git push origin --tags

echo \$0: all done
%%
            chmod +x ${TARGET}-create-release.sh

            cat >${TARGET}.sh <<%%

#!/bin/sh
###############################################################################
# Execute the following, or run ./${TARGET}.sh
###############################################################################
./${TARGET}.exe \$*
%%

            cat ${TARGET}.sh
            chmod +x ${TARGET}.sh
            ;;
        Linux)
            log_info "Run:"
            echo "  ./${TARGET}"
            ;;
        *)
            log_info "Run:"
            echo "  ./${TARGET}"
            ;;
    esac

    rm -f Makefile.bak
else
    log_die "Build failed"
    exit 1
fi

#
# Execute unit tests?
#
if [[ $OPT_GITHUB != "" ]]; then
    ./${TARGET} --tests
    if [[ $? -ne 0 ]]; then
        exit 1
    fi
fi

exit 0
