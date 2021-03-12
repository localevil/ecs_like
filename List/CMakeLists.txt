cmake_minimum_required(VERSION 3.5)

project(list LANGUAGES C)

set(HDR
	list.h
	)

set (SRC
	list.c
	)

add_library(list SHARED ${HDR} ${SRC})
