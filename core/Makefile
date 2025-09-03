NAME=libcore.a
BUILD_DIR ?= ../build
TARGET:=$(BUILD_DIR)/$(NAME)
CXX=c++
DEPS=-MMD -MP
DEBUGF=-g -O0
FSANF=-fsanitize=address
AR=ar rcs
CXXFLAGS=-Wall -Wextra -std=c++98 -Iincludes/ $(DEPS)

SRC=IRCClient.cpp IRCServer.cpp
OBJDIR=./build
OBJ=$(addprefix $(OBJDIR)/,$(SRC:.cpp=.o))

ifeq ($(DEBUG), 1)
CXXFLAGS += $(DEBUGF)
endif

ifeq ($(FSAN), 1)
CXXFLAGS += $(FSANF)
endif

ifeq ($(STRICT), 1)
CXXFLAGS += -Werror -pedantic
endif

all: $(NAME)

$(NAME): $(TARGET)

$(TARGET): $(OBJ)
	@$(AR) $@ $^
	@printf "\tArchive '$@' created ($(AR), [$^])\n"


$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<
	@printf "\t'$@' compiled ($(CXX), $(CXXFLAGS), $<)\n"

clean:
	@rm -rf $(OBJDIR)
	@printf " > Removed '$(OBJDIR)'\n"

fclean: clean
	@rm -f $(NAME)
	@printf " > Removed '$(NAME)'\n"

re: fclean all

default: $(NAME)

.PHONY: all clean fclean re top bottom

-include $(OBJ:.o=.d)
