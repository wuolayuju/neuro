CC = gcc  -g
CFLAGS = -Wall
EXE = backpropagationPart1 generateInput adapta-fichero-serie backpropagationPart2
LM = -lm

help :

help :
	@echo "---------------------------"
	@echo "USO : make <comando>"
	@echo "\nCOMANDOS\n"
	@echo "\thelp : Muestra esta ayuda."
	@echo "\tcompile : Compila y enlaza el programa 'perceptronapp'."
	@echo "\tclean : Borra los ficheros objeto y los ejecutables generados."
	
	@echo "\nPROGRAMA backpropagationPart1 & backpropagationPart2\n"
	@echo "\tUSO: ./backpropagationPart1 [-inputLearn <f_entrada>] [-inputExploit <f_entrada> -output <f_salida>] [-outputDebug <f_debug>] [-numNeurons <numero_neuronas>] [-part <porcentaje_aprendizaje>] [-learnrate <tasa_aprendizaje>]"
	@echo "\tUSO: ./backpropagationPart2 [-inputLearn <f_entrada>] [-inputExploit <f_entrada> -output <f_salida>] [-outputDebug <f_debug>] [-numNeurons <numero_neuronas>] [-part <porcentaje_aprendizaje>] [-learnrate <tasa_aprendizaje>]"

	@echo "\nENTRADA/SALIDA"

	@echo "\t-inputLearn FICHERO"
	@echo "\t\tFichero que se usará para el aprendizaje supervisado de la red."
	@echo "\t[-inputExploit FICHERO]"
	@echo "\t\tFichero de patrones no clasificados para la fase de explotación."
	@echo "\t-output FICHERO"
	@echo "\t\tFichero donde se escribirán los resultados de clasificación en la parte de exploit."
	@echo "\t-outputDebug FICHERO"
	@echo "\t\tFichero donde se escribirán los resultados de clasificación en la parte de test."

	@echo "\nPARÁMETROS"
	@echo "\t[-part NUM]"
	@echo "\t\tPorcentaje del fichero de entrada que se usará para aprendizaje. Comprendido entre [0,1]"
	@echo "\t[-learnrate NUM]"
	@echo "\t\tTasa de aprendizaje de la red. Debe ser mayor que 0."

	@echo "\nPROGRAMA generateInput\n"
	@echo "\tUSO: ./generateInput [-output <f_salida>] [-n <tamaño_rejilla>]"

	@echo "\nENTRADA/SALIDA"


	@echo "\t-output FICHERO"
	@echo "\t\tFichero donde se escribirán los diferentes patrones de líneas"

	@echo "\nPARÁMETROS"
	@echo "\t[-n <tamaño_rejilla>]"
	@echo "\t\tancho/alto de la rejilla cuadrada"

	@echo "\nPROGRAMA adapta-fichero-serie\n"
	@echo "\tUSO: ./adapta-fichero-serie [-input <f_entrada>] [-output <f_salida>] [-Np <n_puntos>]"

	@echo "\nENTRADA/SALIDA"

	@echo "\t-input FICHERO"
	@echo "\t\tFichero que se usará para generar los patrones de la serie temporal"
	@echo "\t-output FICHERO"
	@echo "\t\tFichero donde se escribirán los diferentes patrones de tiempo"

	@echo "\nPARÁMETROS"
	@echo "\t[-Np <n_puntos>]"
	@echo "\t\tNumero de puntos que tendrá cada patron"
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