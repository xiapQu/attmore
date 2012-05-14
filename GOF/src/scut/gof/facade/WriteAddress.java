/**
 * author : Administrator
 * date   : 2012-4-27
 * file   : WriteAddress.java
 * prj    : GOF
 * usefor : Subsystem的第一步 写地址
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
		System.out.println("============第一步 写地址==============");
		System.out.println("货物："+goods);
		System.out.println("目的地："+addr);
		System.out.println("============ 写地址完毕 ==============");
	}
}
