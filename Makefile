# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/27 17:30:37 by jopedro-          #+#    #+#              #
#    Updated: 2025/03/13 11:40:27 by jopedro-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#==============================================================================#
#                                     NAMES                                    #
#==============================================================================#

NAME = pipex
NAME_BONUS = pipex_bonus

### Message Vars
_SUCCESS 		= [$(GRN)SUCCESS$(D)]
_INFO 			= [$(BLU)INFO$(D)]
_NORM 			= [$(MAG)Norminette$(D)]
_NORM_SUCCESS 	= $(GRN)=== OK:$(D)
_NORM_INFO 		= $(BLU)File no:$(D)
_NORM_ERR 		= $(RED)=== KO:$(D)
_SEP 			= =====================

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

SRC_PATH 		= src
SRC_BONUS_PATH	= src_bonus
LIBS_PATH		= lib
BUILD_PATH		= .build
BUILDB_PATH 	= .build_bonus
TEMP_PATH		= .temp

SRC				= $(addprefix $(SRC_PATH)/, main.c exit.c init_struct.c utils.c parsing.c free.c)

SRC_BONUS		= $(addprefix $(SRC_BONUS_PATH)/, main.c exit.c init_struct.c utils.c parsing.c free.c)

OBJS			= $(SRC:$(SRC_PATH)/%.c=$(BUILD_PATH)/%.o)
OBJS_BONUS		= $(SRC_BONUS:$(SRC_BONUS_PATH)/%.c=$(BUILDB_PATH)/%.o)

LIBFT_PATH		= $(LIBS_PATH)/42_libft
LIBFT_ARC		= $(LIBFT_PATH)/libft.a

#==============================================================================#
#                              COMPILER & FLAGS                                #
#==============================================================================#

CC		= cc

CFLAGS		= -Wall -Werror -Wextra
DFLAGS		= -g

INC			= -I

#==============================================================================#
#                                COMMANDS                                      #
#==============================================================================#

AR			= ar rcs
RM			= rm -rf
MKDIR_P		= mkdir -p

MAKE		= make -C

#==============================================================================#
#                                  RULES                                       #
#==============================================================================#

all: deps $(NAME)

bonus: deps $(NAME_BONUS)

other: $(BUILD_PATH) $(OBJS)
	@echo "[$(YEL)Compiling pipex$(D)]"
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) -o $(NAME)
	@echo "[$(_SUCCESS) compiling $(MAG)pipex!$(D) $(YEL)🖔$(D)]"

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	@echo -n "$(MAG)█$(D)"
	$(CC) $(CFLAGS) $(DFLAGS) -MMD -MP -c $< -o $@

$(BUILDB_PATH)/%.o: $(SRC_BONUS_PATH)/%.c
	@echo -n "$(MAG)█$(D)"
	$(CC) $(CFLAGS) $(DFLAGS) -MMD -MP -c $< -o $@

$(BUILD_PATH):
	$(MKDIR_P) $(BUILD_PATH)
	@echo "* $(YEL)Creating $(BUILD_PATH) folder:$(D) $(_SUCCESS)"

$(BUILDB_PATH):
	$(MKDIR_P) $(BUILDB_PATH)
	@echo "* $(YEL)Creating $(BUILDB_PATH) folder:$(D) $(_SUCCESS)"

$(TEMP_PATH):
	$(MKDIR_P) $(TEMP_PATH)
	@echo "* $(YEL)Creating $(TEMP_PATH) folder:$(D) $(_SUCCESS)"

$(NAME): $(BUILD_PATH) $(LIBFT_ARC) $(OBJS) 
	@echo "[$(YEL)Compiling pipex$(D)]"
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) $(LIBFT_ARC) $(MLXFLAGS) -o $(NAME)
	@echo "[$(_SUCCESS) compiling $(MAG)pipex!$(D) $(YEL)🖔$(D)]"

$(NAME_BONUS): $(BUILDB_PATH) $(LIBFT_ARC) $(OBJS_BONUS)
	@echo "[$(YEL)Compiling pipex bonus$(D)]"
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS_BONUS) $(LIBFT_ARC) $(MLXFLAGS) -o $(NAME_BONUS)
	@echo "[$(_SUCCESS) compiling $(MAG)pipex bonus!$(D) $(YEL)🖔$(D)]"


$(LIBFT_ARC):
	$(MAKE) $(LIBFT_PATH) extra

deps: 			## Download/Update libft
	@if test ! -d "$(LIBFT_PATH)"; then make get_libft; \
		else echo "$(YEL)[libft]$(D) folder found 🖔"; fi
	@echo " $(RED)$(D) [$(GRN)Nothing to be done!$(D)]"

-include $(BUILD_PATH)/*.d

update_modules:
	@echo "* $(CYA)Updating submodules$(D)]"
	git submodule init
	git submodule update --recursive --remote
	@echo "* $(GRN)Submodules update$(D): $(_SUCCESS)"

get_libft:
	@echo "* $(CYA)Getting Libft submodule$(D)]"
	git clone git@github.com:4Rr0x/42_libft.git $(LIBFT_PATH)
	@echo "* $(GRN)Libft submodule download$(D): $(_SUCCESS)"

##@ Norm, Debug & Leak Check Rules 

norm: $(TEMP_PATH)		## Run norminette test on push_swap files
	@printf "${_NORM}: $(YEL)$(SRC_PATH)$(D)\n"
	@ls $(SRC_PATH) | wc -l > $(TEMP_PATH)/norm_ls.txt
	@printf "$(_NORM_INFO) $$(cat $(TEMP_PATH)/norm_ls.txt)\n"
	@printf "$(_NORM_SUCCESS) "
	@norminette $(SRC_PATH) | grep -wc "OK" > $(TEMP_PATH)/norm.txt; \
	if [ $$? -eq 1 ]; then \
		echo "0" > $(TEMP_PATH)/norm.txt; \
	fi
	@printf "$$(cat $(TEMP_PATH)/norm.txt)\n"
	@if ! diff -q $(TEMP_PATH)/norm_ls.txt $(TEMP_PATH)/norm.txt > /dev/null; then \
		printf "$(_NORM_ERR) "; \
		norminette $(SRC_PATH) | grep -v "OK"> $(TEMP_PATH)/norm_err.txt; \
		cat $(TEMP_PATH)/norm_err.txt | grep -wc "Error:" > $(TEMP_PATH)/norm_errn.txt; \
		printf "$$(cat $(TEMP_PATH)/norm_errn.txt)\n"; \
		printf "$$(cat $(TEMP_PATH)/norm_err.txt)\n"; \
	else \
		printf "[$(YEL)Everything is OK$(D)]\n"; \
	fi
	@echo "$(CYA)$(_SEP)$(D)"

check_ext_func:## Check for external functions
	@echo "[$(YEL)Checking for external functions$(D)]"
	@echo "$(YEL)$(_SEP)$(D)"
	@echo "$(CYA)Reading binary$(D): $(MAG)pipex$(D)"
	nm ./pipex | grep "U" | tee $(TEMP_PATH)/ext_func.txt
	@echo "$(YEL)$(_SEP)$(D)"

gdb:				## Run with GDB w/ custom arg=""
	gdb --tui --args ./$(NAME) $(arg)

##@ Clean-up Rules 󰃢

clean: 				## Remove object files
	@echo "* $(YEL)Removing $(MAG)$(NAME)$(D) and deps $(YEL)object files$(D)"
	@if [ -d "$(LIBFT_PATH)/$(BUILD_PATH)" ] || [ -d "$(BUILD_PATH)" ] || [ -d "$(TEMP_PATH)" ]; then \
		if [ -d "$(LIBFT_PATH)/$(BUILD_PATH)" ]; then \
			$(MAKE) $(LIBFT_PATH) clean; \
			echo "* $(YEL)Removing $(CYA)libft$(D) object files$(D): $(_SUCCESS)"; \
		fi; \
		if [ -d "$(BUILD_PATH)" ]; then \
			$(RM) $(BUILD_PATH); \
			echo "* $(YEL)Removing $(CYA)$(BUILD_PATH)$(D) folder & files$(D): $(_SUCCESS)"; \
		fi; \
		if [ -d "$(TEMP_PATH)" ]; then \
			$(RM) $(TEMP_PATH); \
			echo "* $(YEL)Removing $(CYA)$(TEMP_PATH)$(D) folder & files:$(D) $(_SUCCESS)"; \
		fi; \
	else \
		echo " $(RED)$(D) [$(GRN)Nothing to clean!$(D)]"; \
	fi

fclean: clean	## Remove archives & executables
	$(RM) $(NAME) $(NAME_BONUS)
	@echo "* $(YEL)Cleaning executable$(D): $(_SUCCESS)"
	$(MAKE) $(LIBFT_PATH) fclean
	@echo "* $(YEL)Removing libft archive$(D): $(_SUCCESS)"

libclean: fclean	## Remove libs
	$(RM) $(LIBS_PATH)
	@echo "* $(YEL)Removing lib folder & files!$(D) : $(_SUCCESS)"

re: fclean all	## Purge and Recompile

##@ Help 󰛵

.PHONY: help
help: 			## Display this help page
	@awk 'BEGIN {FS = ":.*##"; \
			printf "\n=> Usage:\n\tmake $(GRN)<target>$(D)\n"} \
		/^[a-zA-Z_0-9-]+:.*?##/ { \
			printf "\t$(GRN)%-15s$(D) %s\n", $$1, $$2 } \
		/^##@/ { \
			printf "\n=> %s\n", substr($$0, 5) } ' Makefile
## Tweaked from source:
### https://www.padok.fr/en/blog/beautiful-makefile-awk

.PHONY: deps get_libft update_modules clean fclean libclean re \
		norm
	

#==============================================================================#
#                                  UTILS                                       #
#==============================================================================#

# Colors
#
# Run the following command to get list of available colors
# bash -c 'for c in {0..255}; do tput setaf $c; tput setaf $c | cat -v; echo =$c; done'
#
B  		= $(shell tput bold)
BLA		= $(shell tput setaf 0)
RED		= $(shell tput setaf 1)
GRN		= $(shell tput setaf 2)
YEL		= $(shell tput setaf 3)
BLU		= $(shell tput setaf 4)
MAG		= $(shell tput setaf 5)
CYA		= $(shell tput setaf 6)
WHI		= $(shell tput setaf 7)
GRE		= $(shell tput setaf 8)
BRED 	= $(shell tput setaf 9)
BGRN	= $(shell tput setaf 10)
BYEL	= $(shell tput setaf 11)
BBLU	= $(shell tput setaf 12)
BMAG	= $(shell tput setaf 13)
BCYA	= $(shell tput setaf 14)
BWHI	= $(shell tput setaf 15)
D 		= $(shell tput sgr0)
BEL 	= $(shell tput bel)
CLR 	= $(shell tput el 1)
