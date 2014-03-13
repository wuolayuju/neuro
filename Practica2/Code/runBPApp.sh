
#incrementos Neuronas

inicio=4
final=12
incr=1


for i in $(seq $inicio $incr $final)
do
	./backpropagationapp -inputLearn nand.txt -numNeurons $i -part 1 -learnrate 0.05  -outputDebug outputs/neuron_nand$i.out>  outputs/hits_neuron_nand$i.out
	./backpropagationapp -inputLearn nor.txt -numNeurons $i -part 1 -learnrate 0.05  -outputDebug outputs/neuron_nor$i.out>  outputs/hits_neuron_nor$i.out

done

