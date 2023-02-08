import java.util.Date;
import java.util.Random;

public class main 
{
	public static int[][] generate_array(int N)
	{
		int[][] arr = new int[N][N];
		Random rand = new Random();
		
		for(int i = 0 ; i < N ; i++)
		{
			for (int j = 0 ; j < N ; j++)
			{
				arr[i][j] = rand.nextInt(100);
//				Correct the value of random....
			}
		}
		
		return arr;
	}
	
	public static void print_array(int[][] arr)
	{
		for(int i = 0 ; i < arr.length ; i++)
		{
			for(int j = 0 ; j < arr.length ; j++)
			{
				System.out.printf("%d   ", arr[i][j]);
			}
			System.out.println();
		}
		System.out.println();
	}
	
	public static int[][] seq_matrix_mult(int[][] A , int[][] B)
	{
		int[][] C = new int[A.length][A.length];
		
		for(int i = 0 ; i < A.length ; i++)
		{
			for (int j = 0 ; j < A.length ; j++)
			{
				C[i][j] = 0;
				
				for(int k = 0 ; k < A.length ; k++)
				{
					C[i][j] += A[i][k]*B[k][j];
				}
			}
		}
		
		return C;
	}
	
	public static void comparison_using_constant_threads() throws InterruptedException
	{
		
		int N = 5;
		
		for ( ; N < 1000 ; N += 50)
		{
			int[][] A = generate_array(N);
			int[][] B = generate_array(N);
			
//			print_array(A);
//			print_array(B);
//			print_array(seq_matrix_mult(A,B));
			Date s1 = new Date();
			int[][] C = seq_matrix_mult(A,B);
			Date s2 = new Date();
			
			Threaded_matrix_mult result_obj = new Threaded_matrix_mult(A,B);
			threads t0 = new threads(result_obj);
			threads t1 = new threads(result_obj);
			threads t2 = new threads(result_obj);
			threads t3 = new threads(result_obj);
			
			Date s3 = new Date();
			t0.start();
			t1.start();
			t2.start();
			t3.start();

			t0.join();
			t1.join();
			t2.join();
			t3.join();
			
			int[][] D = Threaded_matrix_mult.result;
			Date s4 = new Date();
			
			System.out.println("Matrix Size:" + N + " ,Sequential MatMult Time:" + (s2.getTime()-s1.getTime()) + " ,Threaded MatMult Time:" + (s4.getTime() - s3.getTime()));
//			print_array(D);
		}
		
		return;
		
	
	}
	
	public static void comparison_using_constant_matrixSize() throws InterruptedException
	{
		int N = 1500;
		System.out.println("Matrix Size:" + N);

		for(int i = 0 ; i < 10 ; i++)
		{
			
			int[][] A = generate_array(N);
			int[][] B = generate_array(N);
			Threaded_matrix_mult result_obj = new Threaded_matrix_mult(A,B);
			Date start = new Date();
						
			threads t0 = new threads(result_obj);
			threads t1 = new threads(result_obj);
			t0.start();
			t1.start();
			
			if (i >= 1)
			{
				threads t2 = new threads(result_obj);
				threads t3 = new threads(result_obj);
				t2.start();
				t3.start();
			}
			if (i >= 2)
			{
				threads t4 = new threads(result_obj);
				threads t5 = new threads(result_obj);
				t4.start();
				t5.start();
			}
			if (i >= 3)
			{
				threads t6 = new threads(result_obj);
				threads t7 = new threads(result_obj);
				t6.start();
				t7.start();
			}
			if (i >= 4)
			{
				threads t8 = new threads(result_obj);
				threads t9 = new threads(result_obj);
				t8.start();
				t9.start();
			}
			if (i >= 5)
			{
				threads t10 = new threads(result_obj);
				threads t11 = new threads(result_obj);
				t10.start();
				t11.start();
			}
			if (i >= 6)
			{
				threads t12 = new threads(result_obj);
				threads t13 = new threads(result_obj);
				t12.start();
				t13.start();
			}
			if (i >= 7)
			{
				threads t14 = new threads(result_obj);
				threads t15 = new threads(result_obj);
				t14.start();
				t15.start();
			}
			if (i >= 8)
			{
				threads t16 = new threads(result_obj);
				threads t17 = new threads(result_obj);
				t16.start();
				t17.start();
			}
			if (i >= 9)
			{
				threads t18 = new threads(result_obj);
				threads t19 = new threads(result_obj);
				t18.start();
				t19.start();
			}
			
			t0.join();
			t1.join();
			Date end = new Date();
			System.out.println("Number of Threads:" +(i*2+2) + " , Time Taken: " + (end.getTime()-start.getTime()) );
		}
		
	}
	
	public static void main (String args[]) throws InterruptedException
	{
		
		System.out.println("-----------Constant threads and increasing matrix size--------\n");
		
		comparison_using_constant_threads();
		
		System.out.println("-----------Constant matrix Size and increasing Threads---------\n");
		
		comparison_using_constant_matrixSize();
	}

}

class Threaded_matrix_mult
{
	
//	Shared Object
	
	int[][] A;
	int[][] B;
	
	int max_working_row = 0;
	int max_working_column = 0;
	int N;
	boolean start = true;
	static int[][] result;
	
	public Threaded_matrix_mult (int[][] a , int[][] b)
	{
		A = a;
		B = b;
		N = A.length;
		result = new int[N][N];
	}
	
	synchronized void update_row_col() throws InterruptedException
	{
		if(max_working_column == N-1)
		{
			max_working_row++;
			max_working_column = 0;
			return;
		}
		
		max_working_column++ ;

	}
	
	void row_col_mult(int i , int j) throws InterruptedException
	{
		start = false;
		if(max_working_row == N)
			return;
		
		result[i][j] = 0;
		for(int k = 0 ; k < N ; k++)
		{
			result[i][j] += A[i][k]*B[k][j];
		}
//		System.out.println(threads.currentThread().getName() + "\nrow :: " + i + "\tcolumn :: " + j);

	}
}

class threads extends Thread
{
	Threaded_matrix_mult mult;
	
	public threads(Threaded_matrix_mult m)
	{
		mult = m;
	}
	
	public void run()
	{
		while(mult.max_working_row < mult.N)
		{
			try 
			{
				if(mult.start == false)
					mult.update_row_col();
				mult.row_col_mult(mult.max_working_row, mult.max_working_column);
			}
			catch(Exception e) {e.printStackTrace();}
		}
		
	}

}
