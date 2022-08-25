INCLUDES_DIR = ./includes/
LIBFT_DIR = ./lib/libft/
MLX_DIR = ./lib/mlx/
SOURCE_DIR = ./src
PARSE_DIR = $(SOURCE_DIR)/parse/
UTILS_DIR = $(SOURCE_DIR)/utils/
VECTOR_DIR = $(SOURCE_DIR)/vector/
DISCRIMINANT_DIR = $(SOURCE_DIR)/discriminant/
RAY_DIR = $(SOURCE_DIR)/ray/
TRANSFORM_DIR = $(SOURCE_DIR)/transform/
LIGHT_DIR = $(SOURCE_DIR)/light/
SHADOW_DIR = $(SOURCE_DIR)/shadow/
OBJECT_DIR = ./object_files
FILES = \
		main \

PARSE_FILE = read_rt_file set_objects set_view
UTILS_FILE = ft_stof utils_mlx utils_common utils_parse utils_parse_bool
VECTOR_FILE = vector vector2 vector3
RAY_FILE = ray shoot_ray
DISCRIMINANT_FILE = discriminant discriminant_cylinder hit
TRANSFORM_FILE = world_to_camera transformation 
LIGHT_FILE = ambient diffuse
SHADOW_FILE = shadow

#vpath %.c $(SOURCE_DIR)
VPATH := $(shell find $(SOURCE_DIR) -type d -print | tr '\012' ':' | sed 's/:$$//')

SOURCES = $(addsuffix .c, $(FILES)) \
		  $(addprefix $(PARSE_DIR), $(addsuffix .c, $(PARSE_FILE))) \
		  $(addprefix $(UTILS_DIR), $(addsuffix .c, $(UTILS_FILE))) \
		  $(addprefix $(VECTOR_DIR), $(addsuffix .c, $(VECTOR_FILE))) \
		  $(addprefix $(DISCRIMINANT_DIR), $(addsuffix .c, $(DISCRIMINANT_FILE))) \
		  $(addprefix $(RAY_DIR), $(addsuffix .c, $(RAY_FILE))) \
		  $(addprefix $(TRANSFORM_DIR), $(addsuffix .c, $(TRANSFORM_FILE))) \
		  $(addprefix $(LIGHT_DIR), $(addsuffix .c, $(LIGHT_FILE))) \
		  $(addprefix $(SHADOW_DIR), $(addsuffix .c, $(SHADOW_FILE))) \

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
	@echo "make objects folder"
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
	@make -C $(MLX_DIR) fclean
	@make -C $(LIBFT_DIR) fclean

re :
	rm -rf $(OBJECT_DIR)
	rm -f $(NAME) $(LIBFT) $(MLX)
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) fclean
	@make all

.PHONY: all clean fclean re

-include $(OBJECTS:.o=.d)
