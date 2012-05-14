/**
 * author : Administrator
 * date   : 2012-4-21
 * file   : StrategyOne.java
 * prj    : GOF
 * usefor : 
 */
package scut.gof.strategy;

/**
 * @author Administrator ¾ßÌå²ßÂÔ1£º
 */
public class StrategyOne implements CalcStrategy {

	/*
	 * (non-Javadoc)
	 * 
	 * @see scut.gof.strategy.CalcStrategy#calcScore(double[])
	 */
	@Override
	public double calcScore(double[] a) {
		double sum = 0;
		for (int i = 0; i < a.length; i++) {
			sum = sum + a[i];
		}

		return sum / a.length;
	}

}
