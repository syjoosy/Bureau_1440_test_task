# Имя компилятора
CC = gcc

# Флаги компиляции
CFLAGS = -Wall -Wextra -O2

# Исходные файлы
SRCS = task2.c md5/md5c.c md5/driver.c

# Имя исполняемого файла
TARGET = firmware_checker

# Правило по умолчанию
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Очистка скомпилированных файлов
clean:
	rm -f $(TARGET)

# Фиктивные цели
.PHONY: all clean
