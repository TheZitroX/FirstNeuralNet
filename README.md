# FirstNeuralNet
This is my first attempt to create an Neural Net

The net could have been trained without the training file by simple randomly creating the values hardcoded, ive just wanted to try out how to read in the data.
After 1k runs, the net already made 98% correct predictions

## Inputfile-structure
The input file is named `trainingData.txt`

The first line gives the topology of the neuronal-net:
*topology: <input-Num> <hidden layer, hidden layer...> <output-layer>*
example with 2 input values, 1 hidden layer with 10 neurons, and 1 out put neuron:
**topology: 2 10 1**

The next lines will be in the following structure.
*in: <input-num>*
*out: <output-num>*
with the example:
*in: 0.0 1.0*
*out: 1.0*

The more training data there is, the better the neurons get.
