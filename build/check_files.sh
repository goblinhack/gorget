#!/bin/bash

# https://stackoverflow.com/questions/51655657/tar-ignoring-unknown-extended-header-keyword-libarchive-xattr-security-selinux
untar() {
  set -x
    TAR_FLAGS="--no-same-owner --no-same-permissions --warning=no-unknown-keyword --warning=no-timestamp --delay-directory-restore"
    tar $TAR_FLAGS zxvf $*

    TAR_FLAGS="--no-same-owner --no-same-permissions --warning=no-unknown-keyword "
    tar $TAR_FLAGS zxvf $*

    TAR_FLAGS="--warning=no-unknown-keyword"
    tar $TAR_FLAGS zxvf $*
  set +x
    if [[ $? -eq 0 ]]; then
        return
    fi
    tar zxvf $*
}

if [[ ! -d data/gfx ]]; then
    echo $0: Need to extract graphics archive
    untar data/gfx.tgz
    if [[ $? -ne 0 ]];
    then
        echo $0: Failed to extract data/gfx.tgz
        exit 1
    fi
    DONE=1
fi

if [[ ! -d data/sounds ]]; then
    echo $0: Need to extract sounds archive
    untar data/sounds.tgz
    if [[ $? -ne 0 ]];
    then
        echo $0: Failed to extract data/sounds.tgz
        exit 1
    fi
    DONE=1
fi

if [[ $DONE -eq 1 ]]; then
    exit 0
fi

#
# Remove mac dot underscore files
#
find . -type f -name '._*' -delete

COUNT=$(find data/gfx -newer data/gfx.tgz -type f | wc -l)
if [[ $COUNT -gt 0 ]];
then
    echo $0: Need to retar graphics tarball due to updates
    (
        tar zcvf data/gfx.tgz data/gfx
        if [[ $? -ne 0 ]];
        then
            echo $0: Failed to zip data/gfx.tgz
            exit 1
        fi
    )
fi

COUNT=$(find data/sounds -newer data/sounds.tgz -type f | wc -l)
if [[ $COUNT -gt 0 ]];
then
    echo $0: Need to retar sounds tarball due to updates
    (
        tar zcvf data/sounds.tgz data/sounds
        if [[ $? -ne 0 ]];
        then
            echo $0: Failed to zip data/sonuds.tgz
            exit 1
        fi
    )
fi

if [[ ! -d data/gfx ]];
then
    echo $0: Unzip graphics
    tar zxf data/gfx.tgz
    if [[ $? -ne 0 ]];
    then
        echo $0: Failed to unzip data/gfx.tgz
        exit 1
    fi
fi

if [[ ! -d data/sounds ]];
then
    echo $0: Unzip sounds
    tar zxf data/sounds.tgz
    if [[ $? -ne 0 ]];
    then
        echo $0: Failed to unzip data/sounds.tgz
        exit 1
    fi
fi

#
# Remove mac dot underscore files
#
find . -type f -name '._*' -delete
