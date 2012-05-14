/**
 * author : Administrator
 * date   : 2012-4-3
 * file   : ConcreteDecorator.java
 * prj    : GOF
 * usefor : 具体装饰者
 */
package scut.gof.wrapper;

/**
 * @author Administrator
 *
 */
public class ConcreteDecorator extends Decorator {

	public ConcreteDecorator(Component _com) {
		super(_com);
		
	}

	/* (non-Javadoc)
	 * @see scut.gof.wrapper.Component#function()
	 */
	@Override
	public int function() {
		return component.function()+wrapFunction();
	}
	
	private int wrapFunction(){
		return 5;
	}

}
