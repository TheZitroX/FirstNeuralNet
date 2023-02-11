# FirstNeuralNet
This is my first attempt to create an Neural Net

The net could have been trained without the training file by simple randomly creating the values hardcoded, ive just wanted to try out how to read in the data.
After 1k runs, the net already made 98% correct predictions

## Inputfile-structure
The input file is named `trainingData.txt`

The first line gives the topology of the neuronal-net: <br>
*topology: \<input-Num\> \<hidden layer, hidden layer...\> \<output-layer\>* <br>
example with 2 input values, 1 hidden layer with 10 neurons, and 1 out put neuron: <br>
**topology: 2 10 1** <br>

The next lines will be in the following structure. <br>
*in: \<input-num\>* <br>
*out: \<output-num\>* <br>
with the example: <br>
**in: 0.0 1.0** <br>
**out: 1.0** <br>

The more training data there is, the better the neurons get. <br>
