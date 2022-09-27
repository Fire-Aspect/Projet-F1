#include <stdio.h>
#include <stdlib.h>

int sortArray(int arr[]);

int main()    
{    
    //Initialiser l'array   
    int result, arr[] = {5, 2, 8, 7, 1};
    
     
    result = sortArray(arr);
   // printf("%d ", result);
    
    return 0;    
}  

int sortArray(int arr[]) {
    int temp = 0; 
//
    //calcul de la longueur de l'array arr    
 
    int length = sizeof(arr);
    
    //affichage des éléments de l'array   
    printf("éléments de l'array: \n");    
    for (int i = 0; i < length; i++) {     
        printf("%d ", arr[i]);     
    }      

    //trier l'array   
    for (int i = 0; i < length; i++) {     
        for (int j = i+1; j < length; j++) {     
           if(arr[i] > arr[j]) {    
               temp = arr[i];    
               arr[i] = arr[j];    
               arr[j] = temp;    
           }     
        }     
    }    
    
    printf("\n");       

    //Displaying elements of array after sorting    
    printf("éléments de l'array triés en ordre ascendant: \n");    
    for (int i = 0; i < length; i++) { 
       
        printf("%d ", arr[i]);  
        //temp = arr[i]; 
        
    }
    printf("the length of the array registered is : %d", length);      
}   
