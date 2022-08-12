# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/03 09:57:48 by sohan             #+#    #+#              #
#    Updated: 2022/08/06 18:27:49 by sohan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES_DIR = ./includes/
LIBFT_DIR = ./lib/libft/
MLX_DIR = ./lib/mlx/
SOURCE_DIR = ./src
PARSE_DIR = $(SOURCE_DIR)/parse/
STRING_DIR = $(SOURCE_DIR)/string/
VECTOR_DIR = $(SOURCE_DIR)/vector/
DISCRIMINANT_DIR = $(SOURCE_DIR)/discriminant/
OBJECT_DIR = ./objects
FILES = \
		main \

PARSE_FILE = parse
STRING_FILE = ft_stof
VECTOR_FILE = vector
DISCRIMINANT_FILE = viewport

#vpath %.c $(SOURCE_DIR)
VPATH := $(shell find src -type d -print | tr '\012' ':' | sed 's/:$$//')

SOURCES = $(addsuffix .c, $(FILES)) \
		  $(addprefix $(PARSE_DIR), $(addsuffix .c, $(PARSE_FILE))) \
		  $(addprefix $(STRING_DIR), $(addsuffix .c, $(STRING_FILE))) \
		  $(addprefix $(VECTOR_DIR), $(addsuffix .c, $(VECTOR_FILE))) \
		  $(addprefix $(DISCRIMINANT_DIR), $(addsuffix .c, $(DISCRIMINANT_FILE))) \

OBJECTS = $(addprefix $(OBJECT_DIR)/, $(notdir $(SOURCES:.c=.o)))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -MD
DLIBS = -framework Metal -framework AppKit
LDFLAGS = -lmlx -L$(MLX_DIR) -lft -L$(LIBFT_DIR)

NAME = miniRT
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
MLX	= libmlx.dylib

all: $(NAME) 

$(NAME): $(LIBFT) $(MLX) $(OBJECT_DIR) $(OBJECTS)
	$(CC) $(CFLAGS) $(DLIBS) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJECT_DIR):
	@mkdir -p $(OBJECT_DIR)

$(OBJECT_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	@echo "make libft"
	@make -C $(LIBFT_DIR)

$(MLX):
	@echo "make mlx"
	@make -C $(MLX_DIR)
	@cp $(MLX_DIR)$@ .

clean:
	rm -rf $(OBJECT_DIR)
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) clean

fclean:
	rm -rf $(OBJECT_DIR)
	rm -f $(NAME) $(LIBFT) $(MLX)
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) fclean

re :
	rm -rf $(OBJECT_DIR)
	rm -f $(NAME) $(LIBFT) $(MLX)
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) fclean
	@make all

.PHONY: all clean fclean re

-include $(OBJECTS:.o=.d)
