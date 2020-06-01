NAME=btsp

SOURCE_FOLDER=srcs
HEADER_FOLDER=includes
OBJ_FOLDER=out

CFLAGS= -I $(HEADER_FOLDER)

SOURCES=main.c\
		generator_nation.c\
		ship_operations.c\
		map_operations.c\

SRCS=$(addprefix $(SOURCE_FOLDER)/, $(SOURCES))
OUT= $(addprefix $(OBJ_FOLDER)/,$(notdir $(SOURCES:.c=.o)))

.PHONY: all clean fclean re

all:  $(NAME)

$(NAME): $(OUT)
	gcc $(CFLAGS) -o $(NAME) $(OUT)

$(OBJ_FOLDER)/%.o: $(SOURCE_FOLDER)/%.c
	@mkdir -p $(OBJ_FOLDER)
	gcc $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ_FOLDER)

fclean: clean
	rm -rf $(NAME)

re:
	@make fclean
	@make all