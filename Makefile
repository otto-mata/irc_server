NAME:=ircserv
CXX:=c++
DEPS:=-MMD -MP
DEBUGF:=-g -O0
FSANF:=-fsanitize=address
CXXFLAGS:=-Wall -Wextra -std=c++98 -Iincludes/ $(DEPS)

BUILD_DIR = $(shell realpath ./build)
BASE_PATH = $(shell pwd)

LIBS_NAMES = core commandparser socketserver logger
LIBS_FILES = $(addprefix $(BUILD_DIR)/, $(addsuffix .a, $(addprefix lib, $(LIBS_NAMES))))
LIBS_FLAGS = $(addprefix -l, $(LIBS_NAMES))

export BUILD_DIR


SRC=main.cpp

OBJDIR=./build
OBJ=$(addprefix $(OBJDIR)/,$(SRC:.cpp=.o))

ifeq ($(DEBUG), 1)
CXXFLAGS += $(DEBUGF)
BUILDDIR := $(subst)
endif

ifeq ($(FSAN), 1)
CXXFLAGS += $(FSANF)
endif

ifeq ($(STRICT), 1)
CXXFLAGS += -Werror -pedantic
endif

all:
	$(shell mkdir -p $(BUILD_DIR)) 
	$(MAKE) -C ./commandparser libcommandparser.a
	$(MAKE) -C ./socketserver libsocketserver.a
	$(MAKE) -C ./core libcore.a
	$(MAKE) -C ./logger liblogger.a
	$(MAKE) $(NAME)


$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -L$(BUILD_DIR) $(LIBS_FLAGS) 
	@printf "\t'$@' compiled ($(CXX), $(CXXFLAGS), [$^])\n"


$(OBJDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<
	@printf "\t'$@' compiled ($(CXX), $(CXXFLAGS), $<)\n"

clean:
	@rm -rf $(OBJDIR)
	@printf " > Removed '$(OBJDIR)'\n"

fclean: clean
	@rm -f $(NAME)
	@printf " > Removed '$(NAME)'\n"

re: fclean all

.PHONY: all clean fclean re top bottom

-include $(OBJ:.o=.d)
