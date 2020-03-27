#if 0
How to compiel this code?
user@SAMJ-PC:~/KMEANS/C++$ g++ kmeans_algorithm_impl.cpp
user@SAMJ-PC:~/KMEANS/C++$ ./a.out
Usage: kmeans_app <k_value> <input_file_name>
user@SAMJ-PC:~/KMEANS/C++$ ./a.out 3 input0.txt
0) 344.554 : 338.1 338.7 339.8 340 340.2 344.1 344.2 344.8 347.3 348.5 350.4 351.3 351.8
1) 78.0385 : 70.9 71.9 72.3 73.2 73.9 77.2 77.2 79.4 79.8 82.3 83.3 85.8 87.3
2) 177.443 : 152.3 169.6 170.7 176.3 176.9 177.2 179.4 180.1 181.2 181.9 182 182.6 185.5 188.5
Mean variance = 1674.46

user@SAMJ-PC:~/KMEANS/C++$
#endif


#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <bits/stdc++.h> 

using namespace std;

class Kmeans
{
   private:
      vector<double> items;
      int k;
      vector<double> centroids;
      vector<double> *clusters;  

   public:
      Kmeans(int kval)
      {
         k = kval;
         
         clusters = new vector<double>[k]; // create 'k' num of clusters
      }

      void read_from_file_and_populate(string fname, string mode)
      {
         FILE *fptr = fopen(fname.c_str(), mode.c_str());
         if (fptr == NULL)
         {
            cout<<"Cannot open file name = "<<fname<<endl;
            exit(0);
         }
         
         char byte;
         char token[512];
         int count = 0;
         int index = 0;
         memset(token, 512, 0);
         while(1)
         {
            byte = fgetc(fptr);
            if (byte == ',')
            {
               token[index] = '\0';
               count++;
               index = 0;
               double dtoken = atof(token);
               items.push_back(dtoken);
               memset(token, 512, 0);
            }
            else if (byte == feof(fptr) || byte == '\n')
            {
               token[index] = '\0';
               count++;
               index = 0; 

               double dtoken = atof(token);
               items.push_back(dtoken);
               memset(token, 512, 0);

               fclose(fptr);
               break;
            }
            else
            {
               token[index] = byte;
               index++;
            }
         }
      }

      double calculate_euclidean_distance(double a, double b)
      {
         double dist = a - b;
         double A = pow(dist, 2);
         double B = sqrt(A);
         return B;
      }
 
      vector<double> pick_k_random_centroids()    
      {
         int tot = items.size();
         vector<double> mrandom;
         mrandom.reserve(k);
         // init
         for(int i=0; i<k; i++)
            mrandom[i] = 0;

         // pick k num of random centroids and initialize
         double item = 0;
         for(int i=0; i<k; i++)
         {
            item = items[rand() % tot];
            vector<double>::iterator p = std::find(mrandom.begin(), mrandom.end(), item);

            // ensure we dont insert the same centroid twice
            if (p != mrandom.end())
            {
               //cout<<"random centroild = "<<item<<" already inserted ... searching again"<<endl;
               i--;
            }
            else
            {
               //cout<<"random centroild = "<<item<<" inserted successfully"<<endl;
               mrandom.push_back(item);
            }
         }
 
         return mrandom;
      }

      void init_centroids(vector<double> random)
      {
         vector<double>::iterator it;
         int index = 0;
         for(it = random.begin(); it != random.end(); ++it)
            centroids.push_back(*it);
      }

      void print_centroids()
      {
         vector<double>::iterator it;
         for(it = centroids.begin(); it != centroids.end(); ++it)
            cout<<"Centroid = "<<*it<<endl;
      }
      
      void init_clusters()
      {
         vector<double>::iterator iit; // items iterator
         vector<double>::iterator cit; // centroid iterator
         int dist_small = -1;               
         for(iit = items.begin(); iit != items.end(); ++iit)
         {
            dist_small = -1; // we must reset everytime before entering loop
            int cluster_index = 0;
            int cluster_ctr = 0;
            for(cit = centroids.begin(); cit != centroids.end(); ++cit)
            {
               // calculate distance between a centroid and an item
               double dist_calculated = calculate_euclidean_distance(*cit, *iit);
        
               // perform k number of iterations and find an item
               // that has a min distance from the given centroid
               if (dist_small == -1 || dist_calculated < dist_small)
               {
                  dist_small = dist_calculated;
                  cluster_index = cluster_ctr;
               }

               cluster_ctr++;
            }

            clusters[cluster_index].push_back(*iit);
         }
      }

      void print_clusters()
      {
         vector<double>::iterator it;
         for(int cluster_index = 0; cluster_index < k; ++cluster_index)
         {
            cout<<cluster_index<<") "<<centroids[cluster_index]<<" : ";
            for(it = clusters[cluster_index].begin(); it != clusters[cluster_index].end(); ++it)
               cout<<*it<<" ";
            cout<<endl;
         }
      }
      
      void print_mean_variance()
      {
         double mean_var = calculate_mean_variance();
         cout<<"Mean variance = "<<mean_var<<endl;;
      }

      double calculate_total_squared_error(int which_cluster)
      {
         double mean = calculate_mean(which_cluster);

         vector<double>::iterator it;
         double diff = 0;
         double tot = 0;
         double tot_squared_error = 0;
         for(it = clusters[which_cluster].begin(); it != clusters[which_cluster].end(); ++it)
         {
            diff = *it - mean;
            tot  = pow(diff, 2);
            tot_squared_error += tot;
         }

         return tot_squared_error;
      }

      double calculate_mean_variance() // for all clusters
      {
         vector<double>::iterator it;
         double mean_variance = 0;
         double tot = 0;
         for(int cluster_index = 0; cluster_index < k; ++cluster_index)
            mean_variance += calculate_total_squared_error(cluster_index);
 
         return mean_variance;
      }

      double calculate_mean(int which_cluster)
      {
         vector<double>::iterator it;
         double tot = 0;
         for(it = clusters[which_cluster].begin(); it != clusters[which_cluster].end(); ++it)
            tot += *it;

         double mean = tot/clusters[which_cluster].size();
         return mean;
      }

      void update_centroids()
      {
         // ensure you empty the prev centroids before updating 
         // with the new values
         centroids.clear();

         vector<double>::iterator it;
         for(int cluster_index = 0; cluster_index < k; ++cluster_index)
         {
            double mean = calculate_mean(cluster_index);
            centroids.push_back(mean);
         }
      }

      void update_clusters()
      {
         vector<double>::iterator it;
         for(int cluster_index = 0; cluster_index < k; ++cluster_index)
         {
            // ensure you empty the prev centroids before updating  
            // it  with the new values
            clusters[cluster_index].clear();
         }

         // re-assign items based on the newly calculated mean
         init_clusters();
      }

      void repeat()
      {
         vector<double> centroids_prev;
         while(1)
         {
            centroids_prev = centroids; // backup the current centroids
            update_centroids(); // generate new centroids
            update_clusters();
            // compare old centroids with the newly generated centroids      
            if (centroids_prev == centroids)
            {
               print_clusters();
               print_mean_variance();
               cout<<endl;
               break;
            }
         }
      }
};

int main(int argc, char *argv[])
{
   if (argc != 3)
   {
      cout<<"Usage: kmeans_app <k_value> <input_file_name>"<<endl;
      exit(0);
   }

   int k_value = atoi(argv[1]);

   Kmeans km(k_value);
 
   string fname = argv[2];
   string mode = "r";
   km.read_from_file_and_populate(fname, mode);
   vector<double> random_centroids = km.pick_k_random_centroids();
   km.init_centroids(random_centroids);
   //km.print_centroids();
   km.init_clusters();
   km.repeat();
}
