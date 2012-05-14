/**
 * author : Administrator
 * date   : 2012-4-27
 * file   : PostFacade.java
 * prj    : GOF
 * usefor : 邮寄包裹的外观类
 */
package scut.gof.facade;

/**
 * @author Administrator
 * 
 */
public class PostFacade {
	private WriteAddress write;
	private CheckWeight check;
	private Pack pack;

	public PostFacade(String goods,String addr) {
		write=new WriteAddress(goods, addr);
		check=new CheckWeight(goods);
		pack=new Pack();
	}
	
	public void doPost(){
		write.WritingAddress();
		check.CheckingWeight();
		pack.Packing();
	}
}
