## FILES

NAME		=	server_zappy

SRC		=	main				\
			server/server			\
			server/server_monitor		\
			server/server_io		\
			server/server_process		\
			server/server_init		\
			client/client			\
			client/client_io		\
			client/client_player		\
			client/client_player_run_input	\
			client/client_graphic		\
			player/player			\
			player/player_command		\
			monitor/monitors		\
			monitor/monitor_command		\
			misc/parser			\
			misc/socketstream		\
			misc/socketstream_flush		\
			misc/socketstream_io		\
			misc/list			\
			gameplay/gameplay		\
			gameplay/gameplay_init		\
			gameplay/gameplay_move		\
			gameplay/gameplay_fork		\
			gameplay/gameplay_add_command	\
			gameplay/gameplay_broadcast	\
			gameplay/gameplay_voir		\
			gameplay/gameplay_incantation	\
			gameplay/gameplay_client	\
			gameplay/gameplay_food		\
			gameplay/gameplay_linemate	\
			gameplay/gameplay_deraumere	\
			gameplay/gameplay_sibur		\
			gameplay/gameplay_mendiane	\
			gameplay/gameplay_phiras	\
			gameplay/gameplay_thystame	\
			gameplay/gameplay_monitor	\
			gameplay/gameplay_player	\
			gameplay/gameplay_object	\
			gameplay/map			\
			gameplay/case			\
			gameplay/team

SRC_EXT		=	.c

## DIRECTORIES

DOBJ		=	obj
DSRC		=	src
DBIN		=	.

## COMPILATION

DINC		=	include		\

CFLAGS		=	-Wall		\
			-Wextra

MAKED		=	make --no-print-directory -C

## LINKAGE

LIB		=

DLIB		=

LDFLAGS		=

## RUNS

CC		=	gcc -fmax-errors=1
RM		=	rm -rf
MD		=	mkdir -p

####################
## INTERNAL RULES ##
####################

## CONSTANTS

DBGBOOL		=	yes

PROFILE		=	no

DBG		=	-g3		\
			-ggdb

WERROR		=	-Werror

## FILES

OBJ		=	$(addsuffix .o, $(SRC))
_SRC		=	$(addsuffix $(SRC_EXT), $(SRC))

## DIRECTORIES

DINC		:=	$(addsuffix /, $(DINC))
DOBJ		:=	$(addsuffix /, $(DOBJ))
DSRC		:=	$(addsuffix /, $(DSRC))
DBIN		:=	$(addsuffix /, $(DBIN))

## COMPILATION ARGS

CINC		=	$(addprefix -I, $(DINC))

COBJ		=	$(addprefix $(DOBJ), $(OBJ))
CSRC		=	$(addprefix $(DSRC), $(_SRC))
CNAME		=	$(addprefix $(DBIN), $(NAME))

## LINKAGE ARGS

LIB		:=	$(addprefix -l, $(LIB))
DLIB		:=	$(addsuffix /, $(DLIB))
DLIB		:=	$(addprefix -L, $(DLIB))

## FLAGS

ifeq ($(DBGBOOL), yes)
	CFLAGS  += $(DBG)
endif

ifeq ($(DBGBOOL), no)
	CFLAGS	+= $(WERROR)
endif

ifeq ($(PROFILE), yes)
	CFLAGS	+= -pg
	LDFLAGS += -pg
endif

CFLAGS		+=	$(CINC)
LDFLAGS		+=	$(DLIB)				\
			$(LIB)				\
			-Wl,-rpath=./gdl/libs:./lua/libs

## MISC RULES

MAKEOBJ		= $(addprefix $(DOBJ), %.o) : $(addprefix $(addprefix $(DSRC), %), $(SRC_EXT))

all:	$(CNAME)

dbg:	$(CNAME)

$(CNAME):	$(COBJ)
		@$(MD) $(DBIN)
		@echo "Linkage : $(CNAME)"
		@$(CC) $(COBJ) -o $(CNAME) $(LDFLAGS)

$(COBJ):	$(MAKEOBJ)
		@$(MD) $(DOBJ)
		@for dir in `cd $(DSRC); ls -d */ 2> /dev/null`; \
		do \
		if [ ! -d "$(DOBJ)$$dir" ];then \
			$(MD) $(DOBJ)$$dir; \
		fi \
		done
		@echo "Compilation : $<"
		@$(CC) -c $< -o $@ $(CFLAGS)

clean:
		@$(RM) $(COBJ)

fclean:		clean
		@$(RM) $(CNAME)

re:		fclean all
redbg:		fclean dbg

.PHONY:		fclean clean all dbg re
