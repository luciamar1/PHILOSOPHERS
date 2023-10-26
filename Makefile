# Nombre del ejecutable
NAME := philo

# Archivos fuente principales
SRCS := src/main/main.c		\
		src/utils/utils.c	\
		src/utils/utils2.c	\
		src/utils/utils_circle_2link_list.c \
		src/threads/threads_control.c	\
		src/threads/threads_create.c	\
		src/threads/threads_utils.c	\

# Archivos objeto
OBJS := $(SRCS:src/%.c=objs/%.o)

# Ruta de compilación
CFLAGS = -Wall -Wextra -Werror -I libraries
LDFLAGS = -pthread # Si estás usando pthread

RM = /bin/rm -rf

# Reglas para construir el ejecutable y otros objetivos
all: $(NAME)

# Crear la carpeta objs
objs:
	@mkdir -p	objs/main \
				objs/utils \
				objs/threads \


# Compilar src
objs/%.o: src/%.c | objs
	cc $(CFLAGS) -c $< -o $@

# Enlazar objetos a OBJS
$(NAME): $(OBJS)
	cc $(LDFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) objs

# Reglas de limpieza
fclean: clean
	$(RM) $(NAME)

re: fclean all

#malloc debug flags#
fclean_nolib:
	$(RM) objs
	$(RM) $(NAME)
re_nolib: fclean_nolib all

malloc_debug:: CFLAGS += -D MALLOC_DEBUG
malloc_debug:: CFLAGS += -D MALLOC_FAIL=$(when)
malloc_debug: $(OBJS) objs/debug/malloc_debug.o
	cc $(CFLAGS) -c src/debug/malloc_debug.c -o objs/debug/malloc_debug.o
	cc $(LDFLAGS) $(OBJS) objs/debug/malloc_debug.o -o $(NAME)

malloc_debug_sanitize:: CFLAGS += -fsanitize=thread -lpthread
malloc_debug_sanitize:: LDFLAGS += -fsanitize=thread -lpthread
malloc_debug_sanitize:: CFLAGS += -D MALLOC_DEBUG
malloc_debug_sanitize:: CFLAGS += -D MALLOC_FAIL=$(when)
malloc_debug_sanitize: fclean_nolib $(OBJS) objs/debug/malloc_debug.o
	cc $(LDFLAGS) $(OBJS) objs/debug/malloc_debug.o -o $(NAME)

#leaks flags#
leaks:: CFLAGS += -D LEAKS
leaks: $(OBJS) objs/debug/malloc_debug.o
	cc $(CFLAGS) -c src/main.c -o objs/main.o
	cc $(LDFLAGS) $(OBJS) objs/debug/malloc_debug.o -o $(NAME)

#sanitizer flags#
sanitize:: CFLAGS += -fsanitize=thread -g3 
sanitize:: LDFLAGS += -fsanitize=thread 
sanitize:: re_nolib

.PHONY: all clean fclean re fclean_nolib re_nolib malloc_debug sanitize lucia re_lucia leaks