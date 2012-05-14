/**
 * author : Administrator
 * date   : 2012-4-27
 * file   : App.java
 * prj    : GOF
 * usefor : 外观模式
 * 
 * 外观模式为系统中的一组接口提供一个统一的界面，Facade模式定义了一个高层接口，这个接口使得这一子系统更加容易使用。
 * 
 * 外观模式是简化用户和子系统进行交互的成熟模式。
 * 外观模式中有两种角色，子系统SubSystem和外观Facade
 */
package scut.gof.facade;

/**
 * @author Administrator
 *
 */
public class App {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		PostFacade agent=new PostFacade("苹果电脑12台", "美国");
		agent.doPost();

	}

}
