/**
 * author : Administrator
 * date   : 2012-4-3
 * file   : Decorator.java
 * prj    : GOF
 * usefor : 
 */
package scut.gof.wrapper;

/**
 * @author Administrator
 * 
 */
public abstract class Decorator extends Component {
	protected Component component;

	public Decorator(Component _com) {
		this.component = _com;
	}
}
