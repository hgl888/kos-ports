# KallistiOS ##version##
#
# libkmg Makefile
# Copyright (c)2003 Dan Potter
#   
# $Id: Makefile,v 1.1 2003/03/14 05:50:36 bardtx Exp $

TARGET = libkmg.a
OBJS = kmg.o

include ../Makefile.prefab

install-headers:
	install -d ${KOS_PATH}/include/addons/kmg
	install -m 660 ../include/kmg/*.h ${KOS_PATH}/include/addons/kmg/
