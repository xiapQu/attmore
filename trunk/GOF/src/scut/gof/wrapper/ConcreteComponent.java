/**
 * author : Administrator
 * date   : 2012-4-3
 * file   : ConcreteComponent.java
 * prj    : GOF
 * usefor : 具体组件
 */
package scut.gof.wrapper;

/**
 * @author Administrator
 *
 */
public class ConcreteComponent extends Component {

	/* (non-Javadoc)
	 * @see scut.gof.wrapper.Component#function()
	 */
	@Override
	public int function() {
		return 10;
	}

}
