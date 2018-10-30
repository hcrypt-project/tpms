package test.tpm;

import java.util.Vector;

public class Tpm 
{
	Vector<Perceptron> p=new Vector<Perceptron>();

	
	public Tpm()
	{	
		
		for(int i=0;i<Main.K;i++)
		{
			p.add(new Perceptron());
		}
	}
	
	public int run(int[][] in)
	{
		int o=1;
		
		for(int i=0;i<Main.K;i++)
		{
			int t=p.elementAt(i).run(in[i]);
			o=o*t;
		}
		
//		System.out.println("--return tpm1 == "+o);
		return o;
	}
	
	public void learn(int[][] in,int tau)
	{
		for(int i=0;i<Main.K;i++)
		{
			p.elementAt(i).learn(in[i],tau);
		}
	}
	
	public int[] getW()
	{
		int[] r=new int[Main.K*Main.N];
		
		int idx=0;
		
		for(int i=0;i<Main.K;i++)
		{
			Perceptron per=p.elementAt(i);
			for(int j=0;j<Main.N;j++)
			{
				r[idx++]=per.w[j];
			}
		}
		
		return r;
	}
	

}
