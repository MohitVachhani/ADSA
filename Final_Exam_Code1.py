#csv is imported to take the input for a data file
import csv
#For generating random numbers
import random
import math
import operator
import numpy
#the following function will find out the covariance of the matrix 
def cov(x)
	n,k=x.shape 
	xc=x-tile(mean(x),(n,1))#it will generate a matrix of size n x 1 and all the values in that will be equal to mean(x)
	c=xc*xc/n
	return c

#it is the distance algorithm(Here it is mahalanobis algorithm)
def Distance(i1, i2, l):
	#the next two line uses the function shape which returns the row and coloumn of the matrix
	n1,k1=i1.shape 
	n2,k2=i2.shape
	n=n1+n2
	#it calulates the difference between mean of the two matrix
	xdiff=np.mean(i1)-np.mean(i2)
	#the next two line uses the function covariance which I have made above	
	ca=cov(i1)
	cb=cov(i2)
	#formula of finding the mahalanobis distance between two data set
	pc=n1/n*ca+n2/n*cb
	d=sqrt(xdiff*pc.I*xdiff)
	return d


#This is the function which is used to get the neighbours of the data set which helps in voting of the data set
def get_n(Train_Set,t_i,k):
	d = []
	l = len(t_i)-1
	for x in range(len(Train_Set)):
		dist = Distance(t_i, Train_Set[x], l)
		d.append((Train_Set[x], dist))
	d.sort(key=operator.itemgetter(1))
	neigh = []
	for x in range(k):
		neigh.append(d[x][0])
	return neigh

#This is the function which is used to count the votes and decide in which cluster it will get in 
def get_r(neigh):
	cv = {}
	for x in range(len(neigh)):
		r = neigh[x][-1]
		if r in cv:
			cv[r] += 1
		else:
			cv[r] = 1
	sort_V = sorted(cv.iteritems(), key=operator.itemgetter(1), reverse=True)
	return sort_V[0][0]

#This is a function which is used for generating the accuray of the code which I have implemented 
def get_Accuracy(Test_Set, pre):
	correct = 0
	for x in range(len(Test_Set)):
		if Test_Set[x][-1] == pre[x]:
			correct += 1
	return (correct/float(len(Test_Set))) * 100.0
	

# this is basic function which takes input from the csv file(for the data analysis)
def load(filename, split, Train_Set=[] , Test_Set=[]):
	with open(filename, 'rb') as csvfile:
	    lines = csv.reader(csvfile)
	    Data_Set = list(lines)
	    for x in range(len(Data_Set)-1):
	        for y in range(4):
	            Data_Set[x][y] = float(Data_Set[x][y])
	        if random.random() < split:
	            Train_Set.append(Data_Set[x])
	        else:
	            Test_Set.append(Data_Set[x])

#the main function in which the above functions are used and called in a particular order to run it as a KNN algorithm
def main():
	# Data is been prepared
	Train_Set=[]
	Test_Set=[]
	split = 0.67
	#Loading the data
	load('iris.data', split, Train_Set, Test_Set)
	print 'Test_set: ' + repr(len(Test_Set))
	print 'Train_Set: ' + repr(len(Train_Set))
	# generate pre
	pre=[]
	#Value of K is defined here as we change the value of K there will be different answer of the accuracy
	# some analysis
	# k=1 then accuracy is 94.4%
	# k=3 then accuracy is 98.019%
	# k=5 then accuracy is 97.75%	
	k = 5
	for x in range(len(Test_Set)):
		neigh = get_n(Train_Set, Test_Set[x], k)
		result = get_r(neigh)
		pre.append(result)
		print('predicted=' + repr(result) + ', actual=' + repr(Test_Set[x][-1]))
	accuracy = get_Accuracy(Test_Set, pre)
	print('Accuracy: ' + repr(accuracy) + '%')
#the main function is called here 
main()
