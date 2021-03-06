# makefile for Lua hierarchy
# see INSTALL for installation instructions
# see file "config" for customization instructions

LUA= .

include $(LUA)/config
include kos/$(KOS_ARCH).cnf


# primary targets (only "all" and "clean" are useful after distribution)
all: install-headers
	cd include; $(MAKE) $@
	cd src; $(MAKE) $@
#	cd src/luac; $(MAKE) $@
	cd src/lib; $(MAKE) $@
#	cd src/lua; $(MAKE) $@
	cp lib/*.a $(KOS_PATH)/lib/addons

clean co klean:
	cd include; $(MAKE) $@
	cd src; $(MAKE) $@
#	cd src/luac; $(MAKE) $@
	cd src/lib; $(MAKE) $@
#	cd src/lua; $(MAKE) $@
	rm -f $(KOS_PATH)/lib/addons/liblua.a
	rm -f $(KOS_PATH)/lib/addons/liblualib.a

# remove debug information from binaries
strip:
	strip bin/lua bin/luac

# official installation
install: all strip
	mkdir -p $(INSTALL_BIN) $(INSTALL_INC) $(INSTALL_LIB) $(INSTALL_MAN)
	$(INSTALL_EXEC) bin/* $(INSTALL_BIN)
	$(INSTALL_DATA) include/*.h $(INSTALL_INC)
	$(INSTALL_DATA) lib/lib* $(INSTALL_LIB)
	$(INSTALL_DATA) doc/*.1 $(INSTALL_MAN)

install-headers:
	install -d ${KOS_PATH}/include/addons/lua
	install -d ${KOS_PATH}/include/addons/lua/lua
	install -m 660 ../include/lua/*.h ${KOS_PATH}/include/addons/lua/
	install -m 660 ../include/lua/lua/*.h ${KOS_PATH}/include/addons/lua/lua/

# shared libraries (for Linux)
so:
	ld -o lib/liblua.so.$V -shared src/*.o
	ld -o lib/liblualib.so.$V -shared src/lib/*.o
	cd lib; ln -s liblua.so.$V liblua.so; ln -s liblualib.so.$V liblualib.so

# binaries using shared libraries
sobin:
	rm -f bin/lua bin/luac
	cd src/lua; $(MAKE)
	cd src/luac; $(MAKE)

# (end of Makefile)
