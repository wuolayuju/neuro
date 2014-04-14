CC = gcc  -g
CFLAGS = -Wall
EXE = backpropagationPart1 generateInput adapta-fichero-serie backpropagationPart2
LM = -lm

help :

	@echo "---------------------------"	

compile : $(EXE)
	   
.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o perceptron.o backpropagation.o autoencoder.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o autoencoder.o perceptron.o backpropagation.o $(LM)

%.o : %.c perceptron.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $< 