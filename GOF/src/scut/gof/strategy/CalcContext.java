/**
 * author : Administrator
 * date   : 2012-4-21
 * file   : CalcContext.java
 * prj    : GOF
 * usefor : 
 */
package scut.gof.strategy;

/**
 * @author Administrator иообнд
 */
public class CalcContext {
	CalcStrategy strategy;

	public void setStrategy(CalcStrategy strategy) {
		this.strategy = strategy;
	}

	public double getScore(double a[]) {
		if (strategy != null) {
			return strategy.calcScore(a);
		} else {
			return 0.0;
		}
	}
}
