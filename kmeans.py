import sys
import csv
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
import warnings
warnings.simplefilter(action='ignore', category=FutureWarning)

import pandas
import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf

import numpy as np

# it seems ROS has been installed on my laptop sometimes ago.
# I need to make sure this path is removed otherwise, script fails
ros_path = '/opt/ros/kinetic/lib/python2.7/dist-packages'

if ros_path in sys.path:
    sys.path.remove(ros_path)
import cv2
sys.path.append('/opt/ros/kinetic/lib/python2.7/dist-packages')

def syntax_error(script_name):
   print("\n")
   print("Usage: %s <input.txt>" % (script_name))
   print("\n")

def file_exist(fname):
   flag = os.path.isfile(fname)
   return flag

def count_entries(fname):
   count = 0
   with open(fname, 'r') as f:
      count = f.read().count(',')
   return (count+1)  #fix_me

# two dimensional polar coordinate expects to have an angle and distance.
# But at present, we are igoring the distance.
# the input file is exected to contain only the angle
def kmeans(fname):
   polar_coordinate_list = []

   # convert the file from "list of strings" to "list of floats"
   with open(fname, newline='') as csvfile:
      temp_list = list(csv.reader(csvfile))
      polar_coordinate_list = np.array(temp_list).astype(np.float)
      total_num_of_polar_coordinates = len(temp_list)

   # get the total number entries
   total_num_of_polar_coordinates = count_entries(fname)
   #print(total_num_of_polar_coordinates)

   # convert to array
   x = np.asarray(polar_coordinate_list)

   # we can use this if we have multile entries
   z = np.hstack((x))

   # i am reshaping to column vector
   z = z.reshape((total_num_of_polar_coordinates,1))    
   z = np.float32(z)

   # let me Define criteria = ( type, max_iter = 10 , epsilon = 1.0 )
   criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 10, 1.0)

   # let me Set flags
   flags = cv2.KMEANS_RANDOM_CENTERS

   # Apply KMeans
   compactness,labels,centers = cv2.kmeans(z,3,None,criteria,10,flags)

   # because i am interested only in centroids
   return centers

# I am hard-coding the output file. That means,
# the result is always written into output.txt in the current directory
def Write_file(list_result):
   with open('./output.txt', 'w') as textfile:
      for item in list_result:
         textfile.write("%s\n" % item)

# main
# thisis my driver code
if __name__ == '__main__':
   argc = len(sys.argv)
   script_name = sys.argv[0]

   if (argc < 2):
      syntax_error(script_name)
      sys.exit(1)

   fname = sys.argv[1]
   if (file_exist(fname) == False):
      print("File %s does not exist" % str(fname))
      sys.exit(1)

   #ReadFile(fname)
   result = kmeans(fname)
   #print (result)

   Write_file(result)
