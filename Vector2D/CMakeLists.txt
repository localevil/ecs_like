cmake_minimum_required(VERSION 3.5)

project(vector2f LANGUAGES C)

set(HDR
	vector2f.h
	)

set (SRC
	vector2f.c
	)

add_library(vector2f SHARED ${HDR} ${SRC})
