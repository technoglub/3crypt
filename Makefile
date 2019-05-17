CC = g++
CXXFLAGS = -std=c++17 -pipe -fPIC -fno-exceptions
DEBUGFLAGS = -Og
OPTFLAGS   = -O3 -march=native
LINKFLAGS  = -lncurses
prefix     = /usr/

debug:
	$(CC) $(CXXFLAGS) $(LINKFLAGS) $(DEBUGFLAGS)\
		-o 3crypt\
		main.cc \
		3crypt.cc \
		include/files/files.cc \
		include/general/print.cc \
		include/general/arg_mapping.cc \
		include/crypto/sspkdf.cc \
		include/crypto/operations.cc \
		include/interface/terminal.cc
3crypt:
	$(CC) $(CXXFLAGS) $(LINKFLAGS) $(OPTFLAGS)\
		-o 3crypt\
		main.cc \
		3crypt.cc \
		include/files/files.cc \
		include/general/print.cc \
		include/general/arg_mapping.cc \
		include/crypto/sspkdf.cc \
		include/crypto/operations.cc \
		include/interface/terminal.cc
install: 3crypt
	install -s -m 0755 3crypt $(prefix)/bin
clean:
	$(RM) 3crypt 
