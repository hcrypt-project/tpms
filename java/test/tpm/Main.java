package test.tpm;

import java.util.Random;

public class Main 
{
	static int L=3;	//weight domain
	
	static int N=12;	//input neurons per hidden neuron
	static int K=10;	//hidden neurons
	
	static Random rnd=new Random(1);
	
	public static void main(String[] args)
	{
	
		
		
		Tpm tpm1=new Tpm();
		Tpm tpm2=new Tpm();
		
		System.out.println("w1: "+arrayToString(tpm1.getW()));
		System.out.println("w2: "+arrayToString(tpm2.getW()));
		
		diff(tpm1.getW(),tpm2.getW());
		
		for(int i=0;i<10000;i++)
		{
			int dif=1;
			
			int[][] input=genInput(true);
			
			int tau1=tpm1.run(input);
			int tau2=tpm2.run(input);
			
			System.out.println("w1: "+arrayToString(tpm1.getW()));
			System.out.println("w2: "+arrayToString(tpm2.getW()));
			
			if(tau1==tau2)
			{
				tpm1.learn(input,tau1);
				tpm2.learn(input,tau1);
				dif=diff(tpm1.getW(),tpm2.getW());
			}
			System.out.println("---");
			if(dif==0)
			{
				System.out.println(i+" iterations");
				System.out.println("w1: "+arrayToString(tpm1.getW()));
				System.out.println("w2: "+arrayToString(tpm2.getW()));
				break;
			}
		}
			
	}
	
	public static int[][] genInput(boolean print)	
	{
		int[][] input=new int[Main.K][Main.N];
		
		if(print)
			System.out.print("input: ");
		for(int i=0;i<Main.K;i++)
			for(int j=0;j<Main.N;j++)
			{
				input[i][j]=rnd.nextBoolean()?1:-1;
				if(print)
					System.out.print(input[i][j]+" ");
			}
		
		if(print)
			System.out.println();
		
		return input;
	}
	
	public static int diff(int[]a, int[]b)
	{
		int dif=0;
		
		System.out.print("diff: ");
		
		for(int i=0;i<Main.K*Main.N;i++)
		{
			dif+=Math.abs(a[i]-b[i]);
			System.out.print(Math.abs(a[i]-b[i])+" ");
		}
		
		System.out.println();
		return dif;
	}
	
	public static String arrayToString(int[] a)
	{
		String r="";
		
		for(int i=0;i<a.length;i++)
			r=r+(a[i]<0?"":"+")+a[i]+" ";
		
		return r;
	}
}
