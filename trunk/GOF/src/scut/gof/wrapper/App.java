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
		System.out.println("没有装饰之前，comp的值是"+comp.function());
		Component compDecorator=new ConcreteDecorator(comp);
		System.out.println("装饰之后comp的值是"+compDecorator.function());
		Component compDecorator2=new ConcreteDecorator(compDecorator);
		System.out.println("装饰之后compDecorator的值是"+compDecorator2.function());
	}

}
