/**
 * author : Administrator
 * date   : 2012-4-21
 * file   : App.java
 * prj    : GOF
 * usefor : 策略模式
 * 
 * 策略模式将一个个的算法封装起来，并且使他们可以相互替换。策略模式使得算法可以独立于使用它的客户而变化。
 *  
 * 本例：计算分数有不同的方法，实现不同的方法，可以在不同的比赛中进行计分
 */
package scut.gof.strategy;

/**
 * @author Administrator
 * 
 */
public class App {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		double[] score = { 2.4, 2.8, 4.5, 5.6, 8.3, 4.5, 9.2, 1.9 };
		CalcContext _ctx = new CalcContext();
		_ctx.setStrategy(new StrategyOne());
		System.out.println("平均分数："+_ctx.getScore(score));
		_ctx.setStrategy(new StrategyTwo());
		System.out.println("几何平均分数："+_ctx.getScore(score));
		_ctx.setStrategy(new StrategyThree());
		System.out.println("去掉最低最高后的平均分数："+_ctx.getScore(score));

	}

}
