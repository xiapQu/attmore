/**
 * author : Administrator
 * date   : 2012-4-21
 * file   : App.java
 * prj    : GOF
 * usefor : ����ģʽ
 * 
 * ����ģʽ��һ�������㷨��װ����������ʹ���ǿ����໥�滻������ģʽʹ���㷨���Զ�����ʹ�����Ŀͻ����仯��
 *  
 * ��������������в�ͬ�ķ�����ʵ�ֲ�ͬ�ķ����������ڲ�ͬ�ı����н��мƷ�
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
		System.out.println("ƽ��������"+_ctx.getScore(score));
		_ctx.setStrategy(new StrategyTwo());
		System.out.println("����ƽ��������"+_ctx.getScore(score));
		_ctx.setStrategy(new StrategyThree());
		System.out.println("ȥ�������ߺ��ƽ��������"+_ctx.getScore(score));

	}

}
