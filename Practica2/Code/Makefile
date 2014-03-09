CC = gcc  -g 
CFLAGS = -Wall
LDFLAGS = -lm
EXE = backpropagationapp

help :

	@echo "---------------------------"	

compile : $(EXE)
	   
.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o perceptron.o backpropagation.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o perceptron.o backpropagation.o $(LDFLAGS)

%.o : %.c perceptron.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<