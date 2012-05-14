/**
 * author : Administrator
 * date   : 2012-4-21
 * file   : StrategyTwo.java
 * prj    : GOF
 * usefor : 
 */
package scut.gof.strategy;

/**
 * @author Administrator 策略2几何平均数
 */
public class StrategyTwo implements CalcStrategy {

	@Override
	public double calcScore(double[] a) {
		double sum = 1;
		for (int i = 0; i < a.length; i++) {
			sum = sum * a[i];
		}
		//NOTE return Math.pow(sum, 1 / a.length); WRONG!!! int/int
		return Math.pow(sum, 1.0 / a.length);
		
	}

}
