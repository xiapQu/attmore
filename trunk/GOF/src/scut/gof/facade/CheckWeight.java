/**
 * author : Administrator
 * date   : 2012-4-27
 * file   : CheckWeight.java
 * prj    : GOF
 * usefor : SubSystem�ĵڶ��� ����
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
		System.out.println("============�ڶ��� ����==============");
		System.out.println("���" + goods);
		System.out.println("������" + weight);
		System.out.println("============���� ���==============");
	}
}
