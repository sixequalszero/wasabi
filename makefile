.SUFFIXES:
.SUFFIXES: .cpp .h

NAME			= wasabi
VERSION 		= 
PACKAGES		= exceptions
SOURCE			= $(PACKAGES:%=%.cpp)
LIBRARY			= $(NAME:%=%.a)

HEADERS			= $(PACKAGES:%=%.h)
OBJECTS			= $(PACKAGES:%=%.o) 

DEBUG			= -Og -Wall -Wextra -Werror -Wold-style-cast \
					-pedantic-errors -g -DVERBOSE -fmax-errors=2 #-Wfatal-errors 

RELEASE			= -O3 -DNDEBUG -flto

LINK_DIRS		=  
LIBRARIES		= 
LINKS			= $(LINK_DIRS:%=-L%) $(LIBRARIES:%=-l%) 

STD				= -std=c++20
CFLAGS			= -march=native -mtune=native -pipe -fexec-charset=UTF-8 \
					-fconcepts -fcoroutines #-fmodules-ts

DEFINE			= 
DEFINITIONS		= $(DEFINE:%=-D%)

INCLUDE_DIRS	= 
INCLUDE			= $(INCLUDE_DIRS:%=-I%)

OPTIONS			= $(STD) ${CFLAGS} $(DEFINITIONS) $(INCLUDE)

$(LIBRARY): clean $(SOURCE) $(HEADERS)
	@echo -e "\e[1;34mReleasing exceptions.o\e[0m"
	g++ $(OPTIONS) $(RELEASE) -c exceptions.cpp

	@echo -e "\e[1;34mPackaging $(LIBRARY)\e[0m"
	ar -rcs $(LIBRARY) $(OBJECTS)

	@echo -e "\e[1;34mReleasing test-cli\e[0m"
	g++ $(OPTIONS) $(RELEASE) -o test-cli test-cli.cpp $(LIBRARY)

debug: $(SOURCE) $(HEADERS)
	@echo -e "\e[1;34mDebugging exceptions.o\e[0m"
	g++ $(OPTIONS) $(DEBUG)	-c exceptions.cpp

	@echo -e "\e[1;34mPackaging $(LIBRARY)\e[0m"
	ar -rcs $(LIBRARY) $(OBJECTS)

	@echo -e "\e[1;34mDebugging test-cli\e[0m"
	g++ $(OPTIONS) $(DEBUG)	-o test-cli test-cli.cpp $(LIBRARY)

run: test-cli
	@echo -e "\e[1;34mRunning test-cli -h\e[0m"
	./test-cli -h

clean:
	@echo -e "\e[1;34mCleaning\e[0m"
	rm -fv $(LIBRARY) $(OBJECTS)

all: clean debug

.DELETE_ON_ERROR:
.PHONY:  run clean all release debug
.SILENT: