# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 11:05:02 by yliu              #+#    #+#              #
#    Updated: 2024/11/23 13:18:53 by yliu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= philo
WARNING			:= -Wall -Wextra -Werror -pedantic
RM				:= rm -rf
ECHO			:= printf
MMD_MP			:= -MMD -MP
SANITIZE		:= -g -fsanitize=integer,undefined,thread
CFLAGS			:= $(WARNING) $(SANITIZE)

# color and line
DEF_COLOR		:=	\033[0;39m
ORANGE			:=	\033[0;33m
GRAY			:=	\033[0;90m
RED				:=	\033[0;91m
GREEN			:=	\033[1;92m
YELLOW			:=	\033[1;93m
BLUE			:=	\033[0;94m
MAGENTA			:=	\033[0;95m
CYAN			:=	\033[0;96m
WHITE			:=	\033[0;97m
-				:=	─
BAR_LEN			:= 42
LINE			:= $(shell yes $- | head -n $(BAR_LEN) | tr -d '\n'; echo)
FILE_NUM		= $(words $(SRCS))
DIFF_LINE		= $(shell yes $- | head -n $(DIFF) | tr -d '\n'; echo)

##########################################
# mandatory directory
SRCS_DIR		:= ./src
OBJS_DIR		:= ./obj
INCS_DIR		:= ./inc

##########################################
# base files
INCS_DIR		:=	$(INCS_DIR)/								\
					$(SRCS_DIR)/libftsubset/libftsubset.h		\
					$(SRCS_DIR)/validate_args/validate_args.h	\
					$(SRCS_DIR)/init/init.h						\
					$(SRCS_DIR)/simulation/simulation.h			\
					$(SRCS_DIR)/mutexes/mutexes.h				\
					$(SRCS_DIR)/channel/channel.h				\
					$(SRCS_DIR)/time/time.h						\
					$(SRCS_DIR)/utils/utils.h					\

INCLUDES		:= $(addprefix -I,$(dir $(INCS_DIR)))

SRCS 			:=	$(SRCS_DIR)/main.c							\
					$(SRCS_DIR)/libftsubset/ft_strlen.c			\
					$(SRCS_DIR)/libftsubset/ft_atoi.c			\
					$(SRCS_DIR)/libftsubset/ft_memcpy.c			\
					$(SRCS_DIR)/validate_args/validate_args.c	\
					$(SRCS_DIR)/init/init.c						\
					$(SRCS_DIR)/simulation/simulation.c			\
					$(SRCS_DIR)/simulation/philosopher.c		\
					$(SRCS_DIR)/simulation/manager.c			\
					$(SRCS_DIR)/simulation/eat.c				\
					$(SRCS_DIR)/mutexes/init.c					\
					$(SRCS_DIR)/mutexes/destroy.c				\
					$(SRCS_DIR)/mutexes/eam.c					\
					$(SRCS_DIR)/mutexes/unsafe_function.c		\
					$(SRCS_DIR)/mutexes/safe_function.c			\
					$(SRCS_DIR)/channel/channel.c				\
					$(SRCS_DIR)/time/time.c						\
				

# mandatory files
OBJS			:= $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.o))
DEP				:= $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.d))

##########################################

.PHONY:			all
all:			$(NAME)

$(NAME):		$(SRCS) Makefile
				@make  -s step_0

.PHONY:			debug
debug:		    
				@make WITH_DEBUG=1 all

.PHONY:			step_0
step_0:
				@make  -s step_1

.PHONY:			step_1
step_1:
				@$(ECHO) "$(DEF_COLOR)$(BLUE)[$(NAME)]\t./$(NAME) \t$(WHITE)checking...$(DEF_COLOR)\n"
				@$(ECHO) "\e$(GRAY)$(LINE)\r$(DEF_COLOR)"
				@make -s step_2

.PHONY:			step_2
step_2:			$(OBJS)
				@$(CC) $(CFLAGS) $^ -o $(NAME)
				@$(ECHO) "\r\e$(GREEN)$(LINE)$(DEF_COLOR)"
				@$(ECHO) "$(GREEN) ‣ 100%% $(DEF_COLOR)\n"
				@$(ECHO) "$(DEF_COLOR)$(BLUE)[$(NAME)]\t./$(NAME) \t$(GREEN)compiled ✓$(DEF_COLOR)\n"

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c $(INCS_DIR)
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) $(MMD_MP) $(INCLUDES) -c $< -o $@
				@make -s output_diff

ITER			= 0
DIFF			= 0
PREV			= 0
.PHONY:			output_diff
output_diff:
				$(eval ITER=$(shell echo $$(($(ITER) + 1))))
				$(eval NEW=$(shell echo $$(($(ITER) * $(BAR_LEN) / $(FILE_NUM)))))
				$(eval DIFF=$(shell echo $$(($(NEW) - $(PREV)))))
				$(eval PREV=$(shell echo $$(($(NEW)))))
				i=1; \
				while [ $$i -le $(DIFF) ]; do \
					$(ECHO) "$(RED)$-$(DEF_COLOR)"; \
					i=$$((i + 1)); \
				done

-include $(DEP)
##########################################
# other cmds
.PHONY:			clean
clean:
				@$(RM) $(OBJS_DIR)
				@$(ECHO) "$(DEF_COLOR)$(BLUE)[$(NAME)]\tobject files \t$(GREEN)deleted ✓$(DEF_COLOR)\n"

.PHONY:			fclean
fclean:			clean
				@$(RM) $(NAME)
				@$(ECHO) "$(DEF_COLOR)$(BLUE)[$(NAME)]\t./$(NAME) \t$(GREEN)deleted ✓$(DEF_COLOR)\n"

.PHONY:			re
re:				fclean all

.PHONY:			norm
norm:
				@norminette $(SRCS) $(INCS_DIR) | grep -v 'OK'; norminette -v

.PHONY:			format_norm
format_norm:
				@c_formatter_42 $(SRCS) $(INCS)
				@make -s norm

.PHONEY:		test
test:			all
				@./$(NAME) 2 200 200 200 5

.PHONEY:		test1
test1:			all
				@./$(NAME) 1 200 200 200 20

.PHONEY:		test2
test2:			all
				@./$(NAME) 10 200 200 200 20

.PHONEY:
testx:			all
				make test
				-make test1
				make test2
