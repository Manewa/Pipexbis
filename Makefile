# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namalier <namalier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/11 16:29:28 by namalier          #+#    #+#              #
#    Updated: 2024/09/25 23:41:40 by natgomali        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PARSING			= srcs/Parsing
EXEC			= srcs/Exec
OBJDIR 			= obj
LIBA			= includes/Libft/libft.a

SRCS 			=	srcs/pipex.c ${PARSING}/ft_error.c ${PARSING}/access_cmd2.c\
					${PARSING}/access_files.c ${PARSING}/lst.c \
					${EXEC}/forking.c ${EXEC}/try_access.c \

OBJS 			=	$(patsubst %.c,${OBJDIR}/%.o,$(notdir ${SRCS}))

NAME			=	pipex

CFLAGS			=	-Wall -Werror -Wextra -g3

${NAME}			:	${OBJDIR} ${OBJS} ${LIBA}
					cc ${OBJS} ${LIBA} ${CFLAGS} -o ${NAME}

$(OBJDIR)		:
				@mkdir -p $@

%.o: srcs/%.c
	cc ${CFLAGS} -c $< -o $@

${OBJDIR}/%.o	:	${PARSING}/%.c
				cc ${CFLAGS} -c $< -o $@

${OBJDIR}/pipex.o	: srcs/pipex.c
				cc ${CFLAGS} -c $< -o $@

${OBJDIR}/%.o	: ${EXEC}/%.c
				cc ${CFLAGS} -c $< -o $@

${LIBA}			:
				make -C includes/Libft

clean			:
				rm -rf ${OBJDIR} includes/Libft/objs

fclean			:	clean
				rm -rf ${NAME} includes/Libft/libft.a

re				: fclean all

all				: 	${NAME}

.PHONY			: all clean fclean re
