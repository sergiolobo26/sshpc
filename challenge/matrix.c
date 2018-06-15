#include "defs.h"
#include "arrays.h"
#include "timer.h"
#include "randn.h"

#define seed 7

void SetMatrixZero(my_prec **A,unsigned int rows, unsigned int cols){
	int j,k;
	for( j = 0; j < rows; j++ )
		for( k = 0; k < cols; k++ )
			A[j][k] = 0;
};

void SetMatrixRandom(my_prec **A,unsigned int rows, unsigned int cols){
	int j,k;
	for( j = 0; j < rows; j++ )
		for( k = 0; k < cols; k++ )
			A[j][k] = normal_rand();
};

// Matrix Transpose Code

my_prec ComputeError_i(my_prec *restrict w, my_prec *restrict x_i, my_prec y_i){

    my_prec error;

    my_prec dot_product = 0;

    for (int i = 0; i < 128; ++i)
    {
    	dot_product += w[i]*x_i[i];
    }

    error = dot_product - y_i;
    return error;
}

void GradientDescent(my_prec **data, my_prec *restrict w, my_prec *restrict y){

	//output = array with all the w for the 9000 iteration
    
    const int size = 512;
    my_prec *dw;
    const float learning_rate = 0.1;
    const unsigned int a = 128;
    dw = CREATE_ARRAY(a);

    int l;
    int i;
    my_prec e_i;
    

        float derivative;


        for (l = 0; l < a; ++l)
        {
    	    dw[l] = 0;
        }
        while(derivative > 10){
            
            derivative = 0;
            
        	for (int j = 0; j < size; ++j)
        	{
        		 
        		e_i = ComputeError_i(w, data[j], y[j]);

        		for (int k = 0; k < a; ++k)
        		{
        			//dw = 2/N * sum(e(w)*x_i)
        			dw[k] += 0.00390625*e_i*data[j][k];

        		}
            }
        
            for (int g = 0; g < 128; ++g)
            {
            	w[g] -= dw[g]*learning_rate;
            	derivative += pow(dw[g], 2);
            }
            derivative = sqrt(derivative);
        }

	



}



// Matrix Multiply Code
// Matrix Inversion Code


// Perform Linear Regression or find the optimizatino problem


// Collect R^2
// Compute p values
// Compute T test and F test

/*

	Python Friendly functions

*/
my_prec **treatMatrix(unsigned int samples, unsigned int size_X, unsigned int size_data){
	static int iter = 0;
	static SimpleTimer_t t;
	static my_prec **m;
	if(iter == 0)
	    srand(seed);
	if(iter % 2 == 0){
		m = CREATE_MATRIX(size_data,size_X);
		SimpleTimer_start( &t );
		SetMatrixRandom(m,size_data,size_X);
		// Collect stop time
		SimpleTimer_stop( &t );
		// Print duration
		printf("Create Matrix for Sample: %d -> ",iter/2+1);
		SimpleTimer_print( &t );

		iter++;
		return m;
	}
	printf("Destroying Matrix of Sample: %d\n",iter/2+1);
	iter++;
	free(m[0]);
	free(m), m = NULL;
	return NULL;
};
/*

	End of Python Friendly functions

*/
