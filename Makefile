# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 13:06:52 by adlecler          #+#    #+#              #
#    Updated: 2022/05/06 19:09:07 by adlecler         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

END = \033[0m
RED = \033[31m
ORANGE = \033[93m
GREEN = \033[32m
PURPLE = \033[0;95m
BLUE = \033[34m
BOLD = \033[1m
CYAN = \x1b[36m

SRCS_CLIENT			=	srcs/client.c\
						srcs/utils.c\
						srcs/utils2.c

SRCS_SERVER			=	srcs/server.c\
						srcs/utils.c\
						srcs/utils2.c

SRCS_CLIENT_BONUS	=	srcs/client_bonus.c\
						srcs/utils_bonus.c\
						srcs/utils2_bonus.c

SRCS_SERVER_BONUS	=	srcs/server_bonus.c\
						srcs/utils_bonus.c\
						srcs/utils2_bonus.c

DIR_HEAD			=	includes/

INCLUDES			=	${DIR_HEAD}minitalk.h

OBJS_CLIENT			=	${SRCS_CLIENT:.c=.o}
OBJS_SERVER			=	${SRCS_SERVER:.c=.o}
OBJS_CLIENT_BONUS	=	${SRCS_CLIENT_BONUS:.c=.o}
OBJS_SERVER_BONUS	=	${SRCS_SERVER_BONUS:.c=.o}

NAME_CLIENT			=	client
NAME_SERVER			=	server
NAME_CLIENT_BONUS	=	client_bonus
NAME_SERVER_BONUS	=	server_bonus

CC					=	gcc
RM					=	rm -rf
FLAGS				=	-Wall -Werror -Wextra -I

.c.o:
			@${CC} ${FLAGS} ${DIR_HEAD} -c $< -o ${<:.c=.o}
			@echo "${BOLD}${BLUE}[ ${GREEN}OK${END}${BLUE}${BOLD} ] ${<:.s=.o}${END}"

all:		${NAME_CLIENT}

bonus:		${NAME_CLIENT_BONUS} ${NAME_SERVER_BONUS}

${NAME_CLIENT_BONUS}:	${OBJS_CLIENT_BONUS}
			@${CC} ${FLAGS} -I${DIR_HEAD} -o ${NAME_CLIENT_BONUS} ${OBJS_CLIENT_BONUS}
			@echo "\n\t\t${BOLD}${GREEN} client_bonus and files.o has been created !${END}${END}\n"

${NAME_SERVER_BONUS}:	${OBJS_SERVER_BONUS}
			@${CC} ${FLAGS} -I${DIR_HEAD} -o ${NAME_SERVER_BONUS} ${OBJS_SERVER_BONUS}
			@echo "\n\t\t${BOLD}${GREEN} server_bonus and files.o has been created !${END}${END}\n"

${NAME_CLIENT}:			${NAME_SERVER} ${OBJS_CLIENT}
			@${CC} ${FLAGS} -I${DIR_HEAD} -o ${NAME_CLIENT} ${OBJS_CLIENT}
			@echo "\n\t\t${BOLD}${GREEN} client and files.o has been created !${END}\n"

${NAME_SERVER}:			${OBJS_SERVER}
			@${CC} ${FLAGS} -I${DIR_HEAD} -o ${NAME_SERVER} ${OBJS_SERVER}
			@echo "\n\t\t${BOLD}${GREEN} server and files.o has been created !${END}\n"

clean:		
			@${RM} ${OBJS_CLIENT} ${OBJS_SERVER} ${OBJS_CLIENT_BONUS} ${OBJS_SERVER_BONUS}

fclean:		clean
			@${RM} ${NAME_CLIENT} ${NAME_CLIENT_BONUS} ${NAME_SERVER} ${NAME_SERVER_BONUS}
			@echo "\t\t${BOLD}${RED} client, server and files.o has been deleted !${END}"

re:			fclean all

.PHONY:		all clean fclean re bonus