# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/09 17:09:36 by rbeaufre          #+#    #+#              #
#    Updated: 2019/11/23 18:23:26 by rbeaufre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

MAKEFILE = Makefile

BIN_DIR = .
INCLUDES_DIR = .
SRC_DIR = .
OBJ_DIR = obj
INCLUDES_DIR = .

SRC_RAW = ft_strlen.c ft_memcpy.c ft_memccpy.c ft_strcpy.c ft_strncpy.c \
		ft_strcat.c ft_strncat.c ft_strlcat.c ft_strcmp.c ft_strncmp.c \
		ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
		ft_strstr.c ft_strnstr.c ft_strdup.c ft_bzero.c ft_memset.c \
		ft_memmove.c ft_memchr.c ft_memcmp.c ft_memalloc.c ft_memdel.c \
		ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
		ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
		ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c \
		ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c \
		ft_lstadd.c ft_lstdelone.c ft_lstdel.c ft_lstiter.c \
		ft_lstmap.c ft_issp.c ft_foreach.c ft_itoa_base.c ft_clamp.c \
		ft_lstpushback.c ft_sizeof_nbr.c ft_abs.c\
		ft_cs.c ft_data.c ft_di.c ft_flags_to_data.c \
		ft_o.c ft_p_percent.c ft_padding.c ft_parse_flags.c \
		ft_printf.c ft_xx.c ft_u.c ft_padding2.c \
		ft_padding_u.c ft_float.c ft_padding_float.c \
		ft_padding_float2.c ft_float_2.c ft_puttab.c ft_putbits.c \
		ft_xx_2.c ft_parse_colour.c ft_printf_err.c \
		ft_is_plus_minus.c get_next_line.c ft_split_whitespaces.c ft_count_words.c ft_ln_w.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_RAW))

OBJ_RAW = $(subst .c,.o,$(SRC_RAW))
OBJ = $(addprefix $(OBJ_DIR)/, $(OBJ_RAW))

HEADERS = libft.h
INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(HEADERS))

CCC = gcc
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES)

RED := "\033[0;31m"
GREEN := "\033[0;32m"
CYAN := "\033[0;36m"
RESET :="\033[0m"

all: 	$(BIN_DIR)/$(NAME)

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES) $(MAKEFILE)
		@$(CCC) -c $< -o $@ $(CFLAGS)

$(BIN_DIR)/$(NAME): $(OBJ_DIR) $(OBJ)
		@ar rc $(NAME) $(OBJ)
		@ranlib $(NAME)
		@echo ${GREEN}"Compiled '$(NAME)' with success"${RESET}

clean:
		@rm -f $(OBJ)
		@echo ${CYAN}"Cleaned objects with success"${RESET}
		@rm -rf $(OBJ_DIR)
		@echo ${CYAN}"Cleaned '$(NAME)' objects with success"${RESET}

fclean: clean
		@rm -f $(NAME) ./a.out
		@echo ${CYAN}"Removed '$(NAME)' with success"${RESET}

re: fclean all

.PHONY: clean fclean
