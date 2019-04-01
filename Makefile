##
## EPITECH PROJECT, 2019
## PSU_strace_2018
## File description:
## Makefile
##

NAME =		ftrace

CFLAGS +=	-I$(INC_DIR) -W -Wall -Wextra

SRC =		$(SRC_DIR)/main.c \
			$(SRC_DIR)/ftrace.c \
			$(SRC_DIR)/syscalls.c \
			$(SRC_DIR)/print.c \
			$(SRC_DIR)/elf.c \
			$(SRC_DIR)/signals.c \
			$(SRC_DIR)/utils.c \
			$(SRC_DIR)/stack.c \
			$(SRC_DIR)/path.c \
			$(SRC_DIR)/strtab.c \
			$(SRC_DIR)/strutils.c


TEST =		$(TEST_DIR)/tests.c

SRC_DIR =	$(realpath src)

INC_DIR =	$(realpath include)

TEST_DIR =	$(realpath tests)

OBJ =		$(SRC:.c=.o)

OBJ_TEST =	$(TEST:.c=.o)

RM =		@rm -rf

ECHO =		/bin/echo -e

DEFAULT =	"\033[00m"

GREEN =		"\033[1;32m"

TEAL =		"\033[1;37m"

RED =		"\033[1;33m"

SANG =		"\033[1;31m"

all:		titre $(NAME)

titre:
			@$(ECHO) $(RED)¶ Building $(NAME)$(TEAL):$(DEFAULT)

unit-tests:
			@$(ECHO) $(RED)¶ Building tests$(TEAL):$(DEFAULT)

$(NAME):	$(OBJ)
			@gcc -o $(NAME) $(OBJ) -lelf && $(ECHO) $(GREEN)✓$(TEAL)" BUILD SUCCESS !"$(TEAL) $(DEFAULT) || $(ECHO) $(SANG)✗$(TEAL)" BUILD FAILED !"$(TEAL) $(DEFAULT)

clean:
			@$(ECHO) $(RED)¶ Cleaning$(TEAL):$(DEFAULT)
			@$(ECHO) $(GREEN)  " [OK]" $(TEAL)"Clean obj"$(TEAL)
			$(RM) $(OBJ) $(OBJ_TEST)
			@($(ECHO) $(GREEN)✓$(TEAL)" CLEAN SUCCESS !"$(TEAL))

fclean:		clean
			$(RM) $(NAME)
			@find . -name "*.gcda" -delete > /dev/null
			@find . -name "*.gcno" -delete > /dev/null
			@find . -name "*.gcov" -delete > /dev/null
			$(RM) unit-tests

re:			fclean all

tests_run: 	titre $(NAME) unit-tests  $(OBJ_TEST)
			@gcc -o unit-tests $(OBJ_TEST) -lcriterion -coverage && $(ECHO) $(GREEN)✓$(TEAL)" BUILD SUCCESS !"$(TEAL) $(DEFAULT) || $(ECHO) $(SANG)✗$(TEAL)" BUILD FAILED !"$(TEAL) $(DEFAULT)
			@(./unit-tests)

%.o : %.c
			@gcc -c -o $@ $^ $(CFLAGS) -lelf && $(ECHO) -n $(GREEN)"  [OK] "$(TEAL) || $(ECHO) -n $(SANG)"  [NO] "$(TEAL) && $(ECHO) $< | rev | cut -d'/' -f 1 | rev

.PHONY:		all fclean re clean
