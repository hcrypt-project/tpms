package test.tpm;

import java.util.Random;

public class Perceptron 
{
	public int[] w=null;
	
	public Perceptron()
	{
		w=new int[Main.N];
		
		
		
		for(int i=0;i<Main.N;i++)
		{
			w[i]=Main.rnd.nextInt(2*Main.L)-Main.L;
		}
	}
	
	public int run(int[] in)
	{
		int o=1;
		for(int i=0;i<Main.N;i++)
		{
			int t=this.w[i]*in[i];
			o=o+t;
		}
		
		int r=Integer.signum(o);
		if(r==0) r=-1;
		
		return r;
	}
	
	public void learn(int[] in,int tau)
	{
		int o=run(in);
		
		if(o==tau)
		for(int i=0;i<Main.N;i++)
		{
			this.w[i]=this.w[i]+(in[i])*tau;
			
			if(this.w[i]>Main.L)
				this.w[i]=Main.L;
			
			if(this.w[i]<(-Main.L))
				this.w[i]=(-Main.L);
		}
	}
}
