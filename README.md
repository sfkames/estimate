# oneshot_learning
"One shot" learning algorithm that uses historical data to predict house prices based on particular attributes

CS211 PA 2

Samantha Ames

You will write a program estimate that uses a training data set to learn weights for a set of house
attributes, and then applies those weights to a set of input data to calculate prices for those houses.
estimate takes two arguments, which are the paths to files containing the training data and input
data.
Training data format The first line will be the word “train”. The second line will contain an
integer k, giving the number of attributes. The third line will contain an integer n, giving the
number of houses. The next n lines will contain k + 1 floating-point numbers, separated by spaces.
Each line gives data for a house. The first k numbers give the values x1 · · · xk for that house, and
the last number gives its price y.
For example, a file train.txt might contain:
train
4
7
3.000000 1.000000 1180.000000 1955.000000 221900.000000
3.000000 2.250000 2570.000000 1951.000000 538000.000000
2.000000 1.000000 770.000000 1933.000000 180000.000000
4.000000 3.000000 1960.000000 1965.000000 604000.000000
3.000000 2.000000 1680.000000 1987.000000 510000.000000
4.000000 4.500000 5420.000000 2001.000000 1230000.000000
3.000000 2.250000 1715.000000 1995.000000 257500.000000
This file contains data for 7 houses, with 4 attributes and a price for each house. The corresponding
matrix X will be 7 × 5 and Y will be 7 × 1. (Recall that column 0 of X is all ones.)
Input data format The first line will be the word “data”. The second line will be an integer k,
giving the number of attributes. The third line will be an ineteger m, giving the number of houses.
The next m lines will contain k floating-point numbers, separated by spaces. Each line gives data
for a house, not including its price.
For example, a file data.txt might contain:
5
data
4
2
3.000000 2.500000 3560.000000 1965.000000
2.000000 1.000000 1160.000000 1942.000000
This contains data for 2 houses, with 4 attributes for each house. The corresponding matrix X
will be 2 × 5.
Output format Your program should output the prices computed for each house in the input
data using the weights derived from the training data. Each house price will be printed on a line,
rounded to the nearest integer.
To print a floating-point number rounded to the nearest integer, use the formatting code %.0f,
as in:
printf("%.0f\n", price);
Usage Assuming the files train.txt and data.txt exist in the same directory as estimate:
$ ./estimate train.txt data.txt
737861
203060
