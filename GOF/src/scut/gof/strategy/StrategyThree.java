/**
 * author : Administrator
 * date   : 2012-4-21
 * file   : StrategyThree.java
 * prj    : GOF
 * usefor : 
 */
package scut.gof.strategy;

import java.util.Arrays;

/**
 * @author Administrator 策略3 去掉最大最小之后求平均数
 */
public class StrategyThree implements CalcStrategy {

	/*
	 * (non-Javadoc)
	 * 
	 * @see scut.gof.strategy.CalcStrategy#calcScore(double[])
	 */
	@Override
	public double calcScore(double[] a) {
		Arrays.sort(a);
		double sum = 0;
		for (int i = 1; i < a.length - 1; i++) {
			sum = sum + a[i];
		}
		return sum / (a.length - 2);
	}

}
