/**
 * author : Administrator
 * date   : 2012-4-3
 * file   : App.java
 * prj    : GOF
 * usefor : 
 */
package scut.gof.wrapper;

/**
 * @author Administrator
 *
 */
public class App {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Component comp=new ConcreteComponent();
		System.out.println("û��װ��֮ǰ��comp��ֵ��"+comp.function());
		Component compDecorator=new ConcreteDecorator(comp);
		System.out.println("װ��֮��comp��ֵ��"+compDecorator.function());
		Component compDecorator2=new ConcreteDecorator(compDecorator);
		System.out.println("װ��֮��compDecorator��ֵ��"+compDecorator2.function());
	}

}
