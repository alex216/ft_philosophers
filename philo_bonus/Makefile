# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 11:05:02 by yliu              #+#    #+#              #
#    Updated: 2024/12/21 21:27:58 by yliu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= philo_bonus
WARNING			:= -Wall -Wextra -Werror -pedantic
RM				:= rm -rf
ECHO			:= printf
INCLUDES		= $(addprefix -I,$(dir $(INCS)))
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
# directory
SRCS_DIR		:= src
BULD_DIR		:= build
INCS_DIR		:= inc

##########################################
# base files
INCS			:=	$(INCS_DIR)/philo_bonus.h							\
					$(SRCS_DIR)/libftsubset/libftsubset_bonus.h			\
					$(SRCS_DIR)/validate_args/validate_args_bonus.h		\
					$(SRCS_DIR)/init/init_bonus.h						\
					$(SRCS_DIR)/simulation/simulation_bonus.h			\
					$(SRCS_DIR)/semaphores/semaphores_bonus.h			\
					$(SRCS_DIR)/channel/channel_bonus.h					\
					$(SRCS_DIR)/time/time_bonus.h						\
					$(SRCS_DIR)/utils/utils_bonus.h						\

SRCS 			:=	$(SRCS_DIR)/main_bonus.c									\
					$(SRCS_DIR)/libftsubset/ft_strlen_bonus.c			\
					$(SRCS_DIR)/libftsubset/ft_atoi_bonus.c				\
					$(SRCS_DIR)/libftsubset/ft_itoa_bonus.c				\
					$(SRCS_DIR)/libftsubset/ft_strcmp_bonus.c			\
					$(SRCS_DIR)/libftsubset/ft_memcpy_bonus.c			\
					$(SRCS_DIR)/libftsubset/ft_strdup_bonus.c			\
					$(SRCS_DIR)/libftsubset/ft_strjoin_bonus.c			\
					$(SRCS_DIR)/validate_args/validate_args_bonus.c		\
					$(SRCS_DIR)/init/init_bonus.c						\
					$(SRCS_DIR)/simulation/simulation_bonus.c			\
					$(SRCS_DIR)/simulation/philosopher_bonus.c			\
					$(SRCS_DIR)/simulation/manager_bonus.c				\
					$(SRCS_DIR)/simulation/eat_bonus.c					\
					$(SRCS_DIR)/semaphores/init_bonus.c					\
					$(SRCS_DIR)/semaphores/destroy_bonus.c				\
					$(SRCS_DIR)/semaphores/safe_function_bonus.c		\
					$(SRCS_DIR)/channel/channel_bonus.c					\
					$(SRCS_DIR)/time/time_bonus.c						\
					$(SRCS_DIR)/utils/utils_bonus.c						\
					$(SRCS_DIR)/utils/math_bonus.c
				

# other files
BUILDS			:= $(subst $(SRCS_DIR), $(BULD_DIR), $(SRCS:.c=.o))
DEP				:= $(subst $(SRCS_DIR), $(BULD_DIR), $(SRCS:.c=.d))

##########################################

.PHONY:			all
all:			$(NAME)

.PHONY:			bonus
bonus:			all

$(NAME): 	 	$(BUILDS)
				@make  -s step_1

.PHONY:			debug
debug:
				@make WITH_DEBUG=1 all

.PHONY:			step_0
step_0:
				@make  -s step_1

.PHONY:			step_1
step_1:			$(BUILDS)
				@$(CC) $(CFLAGS) $(BUILDS) -o $(NAME)

				@$(ECHO) "\r\e$(GREEN)$(LINE)$(DEF_COLOR)"
				@$(ECHO) "$(GREEN) ‣ 100%% $(DEF_COLOR)\n"
				@$(ECHO) "$(DEF_COLOR)$(BLUE)[$(NAME)]\t./$(NAME) \t$(GREEN)compiled ✓$(DEF_COLOR)\n"

IS_FIRST_BUILD := 1

$(BULD_DIR)/%.o:$(SRCS_DIR)/%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) $(INCLUDES) $(MMD_MP) -c $< -o $@

				$(eval TMP := $(IS_FIRST_BUILD))
				$(eval IS_FIRST_BUILD := 0) 
				@if [ $(TMP) -eq 1 ]; then \
					$(ECHO) "$(DEF_COLOR)$(BLUE)[$(NAME)]\t./$(NAME) \t$(WHITE)checking...$(DEF_COLOR)\n" && \
					$(ECHO) "\e$(GRAY)$(LINE)\r$(DEF_COLOR)"; \
				fi
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
				@$(RM) $(BULD_DIR)
				@$(ECHO) "$(DEF_COLOR)$(BLUE)[$(NAME)]\tbuild files \t$(GREEN)deleted ✓$(DEF_COLOR)\n"

.PHONY:			fclean
fclean:			clean
				@$(RM) $(NAME)
				@$(ECHO) "$(DEF_COLOR)$(BLUE)[$(NAME)]\t./$(NAME) \t$(GREEN)deleted ✓$(DEF_COLOR)\n"

.PHONY:			re
re:				fclean all

.PHONY:			norm
norm:
				@norminette $(SRCS) $(INCS) | grep -v 'OK'; norminette -v

.PHONY:			format_norm
format_norm:
				@c_formatter_42 $(SRCS) $(INCS)
				@make -s norm

.PHONEY:		test
test:			all
				@./$(NAME) 2 401 200 200 3

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
