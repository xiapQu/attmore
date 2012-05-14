/**
 * author : Administrator
 * date   : 2012-4-27
 * file   : CheckWeight.java
 * prj    : GOF
 * usefor : SubSystem的第二步 称重
 */
package scut.gof.facade;

/**
 * @author Administrator
 * 
 */
public class CheckWeight {
	private String goods;
	private String weight;

	public CheckWeight(String goods) {
		this.goods = goods;
		this.weight = "15kg";
	}

	public void CheckingWeight() {
		System.out.println("============第二步 称重==============");
		System.out.println("货物：" + goods);
		System.out.println("重量：" + weight);
		System.out.println("============称重 完毕==============");
	}
}
