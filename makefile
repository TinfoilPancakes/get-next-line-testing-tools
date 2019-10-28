# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppatil <ppatil@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/05 23:33:26 by ppatil            #+#    #+#              #
#    Updated: 2019/10/27 23:26:25 by cacharle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Hey this is what you need to edit!
# Use absolute path to get_next_line root project folder.
GNL_SOURCE_DIR = ../get_next_line
# Try not to edit past this line. (Unless something goes very wrong.)

NAME = gnl_tester
CC = clang
C_FLAGS = -Wall -Werror -Wextra
TEST_BUFFER_SIZE = 20
C_FILES = gnl_test.c
# This is required in the assignment if using libft.
MOULITEST_DIR = ./moulitest_files

INCLUDE_DIRS =	. $(GNL_SOURCE_DIR)

I_ARGS = $(patsubst %, -I%, $(INCLUDE_DIRS))
HEADER_CPY = gnl_header_cpy.h
SRC_CPY = gnl_src_cpy.c

default :
	@echo ""
	@echo "================== GET NEXT LINE TESTS =================="
	@echo "[ WARNING:                                              ]"
	@echo "[ - This test will copy and modify your get_next_line.h ]"
	@echo "[   file! Why? Because I need to recompile with several ]"
	@echo "[   BUFFER_SIZE amounts. So it removes the #define line   ]"
	@echo "[   in your source's copy.                              ]"
	@echo "[ - DON'T PANIC! Your original file is still in tact!   ]"
	@echo "[   Just watch out for any problems in the copy in this ]"
	@echo "[   test directory.                                     ]"
	@echo "[ - Please report any bugs because I'm very lazy :P     ]"
	@echo "[ PREREQUISITES:                                        ]"
	@echo "[ - Edit this makefile to point GNL_SOURCE_DIR to your  ]"
	@echo "[   project directory.                                  ]"
	@echo "[ USAGE:                                                ]"
	@echo "[ - make buff_1 : Runs test with BUFFER_SIZE set to 1     ]"
	@echo "[ - make buff_16 : Runs test with BUFFER_SIZE set to 16   ]"
	@echo "[ - make buff_32 : Runs test with BUFFER_SIZE set to 32   ]"
	@echo "[ - make buff_42 : You see the pattern here...          ]"
	@echo "[ - make buff_64 : Boop                                 ]"
	@echo "[ - make buff_128 : Beep                                ]"
	@echo "[ - make buff_2048 : Waffle                             ]"
	@echo "[ - make buff_4096 : Tea                                ]"
	@echo "[ - make buff_EXTREME : Whoa take it easy buddy...      ]"
	@echo "[ - make mtest_N : Runs the get_next_line Moulitest     ]"
	@echo "[                  where N is an above buffer size.     ]"
	@echo "[ NOTES:                                                ]"
	@echo "[ - If you get a linker error for libft make sure it is ]"
	@echo "[   in the libft/ directory in your project root. The   ]"
	@echo "[   assignment specifies it.                            ]"
	@echo "========================================================="
	@echo ""

mtest_1 :
	$(MAKE) mtest TEST_BUFFER_SIZE=1

mtest_16 :
	$(MAKE) mtest TEST_BUFFER_SIZE=16

mtest_32 :
	$(MAKE) mtest TEST_BUFFER_SIZE=32

mtest_42 :
	$(MAKE) mtest TEST_BUFFER_SIZE=42

mtest_64 :
	$(MAKE) mtest TEST_BUFFER_SIZE=64

mtest_128 :
	$(MAKE) mtest TEST_BUFFER_SIZE=128

mtest_2048 :
	$(MAKE) mtest TEST_BUFFER_SIZE=2048

mtest_4096 :
	$(MAKE) mtest TEST_BUFFER_SIZE=4096

mtest_EXTREME :
	$(MAKE) mtest TEST_BUFFER_SIZE=2

mtest : moulitest_config
	$(MAKE) -C $(MOULITEST_DIR) gnl PASSED_DEFINES="-DBUFFER_SIZE=\"$(TEST_BUFFER_SIZE)\""

moulitest_config : $(GNL_SOURCE_DIR)/get_next_line.c $(GNL_SOURCE_DIR)/get_next_line.h $(GNL_SOURCE_DIR)/get_next_line_utils.c
	-mkdir mtest_tmp
	cp $(GNL_SOURCE_DIR)/get_next_line.h ./mtest_tmp/
	sed -i.bkp -e 's/.*define BUFFER_SIZE.*//g' ./mtest_tmp/get_next_line.h
	cp $(GNL_SOURCE_DIR)/get_next_line.c ./mtest_tmp/
	sed -i.bkp -e 's/.*define BUFFER_SIZE.*//g' ./mtest_tmp/get_next_line.c
	cp $(GNL_SOURCE_DIR)/get_next_line_utils.c ./mtest_tmp/
	sed -i.bkp -e 's/.*define BUFFER_SIZE.*//g' ./mtest_tmp/get_next_line_utils.c
	echo "GET_NEXT_LINE_PATH = $(shell pwd)/mtest_tmp" > $(MOULITEST_DIR)/config.ini

buff_1 :
	$(MAKE) $(NAME) TEST_BUFFER_SIZE=1
	./$(NAME)

buff_16 :
	$(MAKE) $(NAME) TEST_BUFFER_SIZE=16
	./$(NAME)

buff_32 :
	$(MAKE) $(NAME) TEST_BUFFER_SIZE=32
	./$(NAME)

buff_42 :
	$(MAKE) $(NAME) TEST_BUFFER_SIZE=42
	./$(NAME)

buff_64 :
	$(MAKE) $(NAME) TEST_BUFFER_SIZE=64
	./$(NAME)

buff_128 :
	$(MAKE) $(NAME) TEST_BUFFER_SIZE=128
	./$(NAME)

buff_2048 :
	$(MAKE) $(NAME) TEST_BUFFER_SIZE=2048
	./$(NAME)

buff_4096 :
	$(MAKE) $(NAME) TEST_BUFFER_SIZE=4096
	./$(NAME)

buff_EXTREME :
	$(MAKE) $(NAME) TEST_BUFFER_SIZE=2
	./$(NAME)

$(NAME) : $(C_FILES) $(HEADER_CPY) $(SRC_CPY)
	$(CC) $(C_FILES) $(GNL_SOURCE_DIR)/get_next_line_utils.c $(SRC_CPY) $(C_FLAGS) \
	-DBUFFER_SIZE=$(TEST_BUFFER_SIZE) \
	-DGNL_HEADER_CPY=\"$(HEADER_CPY)\" \
	-DGNL_SRC_CPY=\"$(SRC_CPY)\" \
	$(I_ARGS) -o $(NAME)

$(HEADER_CPY) : $(GNL_SOURCE_DIR)/get_next_line.h
	$(shell cp $(GNL_SOURCE_DIR)/get_next_line.h ./$(HEADER_CPY))
	$(shell sed -i.bkp -e 's/.*define BUFFER_SIZE.*//g' ./$(HEADER_CPY))

$(SRC_CPY) : $(GNL_SOURCE_DIR)/get_next_line.c
	$(shell cp $(GNL_SOURCE_DIR)/get_next_line.c ./$(SRC_CPY))
	$(shell sed -i.bkp -e 's/.*include \"get_next_line.h\".*/#include GNL_HEADER_CPY/g' ./$(SRC_CPY))

clean :
	rm -f $(NAME)
	rm -f *.bkp
	rm -f $(HEADER_CPY) $(SRC_CPY)
	-$(MAKE) -C $(MOULITEST_DIR)/get_next_line_tests fclean
	rm -rf mtest_tmp

.PHONY :	clean re buff_1 buff_16 buff_32 buff_42 buff_64 \
			buff_128 buff_2048 buff_4096 buff_EXTREME \
			$(NAME) $(SRC_CPY) $(HEADER_CPY) mtest
