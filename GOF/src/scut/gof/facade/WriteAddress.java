/**
 * author : Administrator
 * date   : 2012-4-27
 * file   : WriteAddress.java
 * prj    : GOF
 * usefor : Subsystem�ĵ�һ�� д��ַ
 */
package scut.gof.facade;

/**
 * @author Administrator
 * 
 */
public class WriteAddress {
	private String goods;
	private String addr;

	public WriteAddress(String goods, String addr) {
		this.goods = goods;
		this.addr = addr;
	}

	public void WritingAddress() {
		System.out.println("============��һ�� д��ַ==============");
		System.out.println("���"+goods);
		System.out.println("Ŀ�ĵأ�"+addr);
		System.out.println("============ д��ַ��� ==============");
	}
}
