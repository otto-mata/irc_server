NAME=ircserv
CXX=c++
DEPS=-MMD -MP
DEBUGF=-g -O0
FSANF=-fsanitize=address
CXXFLAGS=-Wall -Wextra -std=c++98 -Iincludes/ $(DEPS)
CMDPARSERLIB=libcommandparser.a
CMDPARSERDIR=./command-parser
SCKTSERVLIB=libsocketserver.a
SCKTSERVDIR=./socket-server

LIBS=-L$(CMDPARSERDIR) -L$(SCKTSERVDIR) -lcommandparser -lsocketserver

SRC=IRCServer.cpp\
	IRCClient.cpp\
	main.cpp
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


all: libcommandparser libsocketserver $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)
	@printf "\t'$@' compiled ($(CXX), $(CXXFLAGS), [$^])\n"


$(CMDPARSERDIR)/$(CMDPARSERLIB):
	make -C $(CMDPARSERDIR)

$(SCKTSERVDIR)/$(SCKTSERVLIB):
	make -C $(SCKTSERVDIR)

libcommandparser: $(CMDPARSERDIR)/$(CMDPARSERLIB)
libsocketserver: $(SCKTSERVDIR)/$(SCKTSERVLIB)

-include $(OBJ:.o=.d)

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


re-cmdprsr:
	make re -C $(CMDPARSERDIR)
re-scktserv:
	make re -C $(SCKTSERVDIR)
re-all: re-cmdprsr re-scktserv re

default: $(NAME)

.PHONY: all clean fclean re top bottom
