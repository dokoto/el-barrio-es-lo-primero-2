#!/bin/bash

function checkForderExist() {
	echo "Checking if" $1$2 "exist.."
	if [ ! -d "$1$2" ]; then
    echo $2 ", no found" ;
    exit 1 ;
	else
    echo "Checking OK, folder" $1$2"exist"
	fi
}

function rsyncFolder() {
	echo "Coping with rsync" $1 "to" $2 ;
	echo "-------------------------------------------------------------" ;
	if rsync -av --delete "$1" "$2";  then
    echo "Folder" $1 "copied ok to " $2;
	else
    echo "Copy of " $1 "to " $2 ", has Failed";
    exit 1 ;
	fi
	echo "-------------------------------------------------------------" ;
}

IMG_FOLDER="img" ;
AUDIO_FOLDER="audio" ;
TTF_FOLDER="ttf" ;

LEN_SRCROOT=${#SRCROOT} ;
OSX_PROJECT_BASE_DIR=${SRCROOT:0:LEN_SRCROOT-3};
echo "Project Base Folder:" $OSX_PROJECT_BASE_DIR;

checkForderExist $OSX_PROJECT_BASE_DIR $IMG_FOLDER ;
checkForderExist $OSX_PROJECT_BASE_DIR $AUDIO_FOLDER ;
checkForderExist $OSX_PROJECT_BASE_DIR $TTF_FOLDER ;

rsyncFolder $OSX_PROJECT_BASE_DIR$IMG_FOLDER $TARGET_BUILD_DIR;
rsyncFolder $OSX_PROJECT_BASE_DIR$AUDIO_FOLDER $TARGET_BUILD_DIR;
rsyncFolder $OSX_PROJECT_BASE_DIR$TTF_FOLDER $TARGET_BUILD_DIR;

exit 0;