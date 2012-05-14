/**
 * author : Administrator
 * date   : 2012-4-1
 * file   : SomeEmployer.java
 * prj    : GOFObserver
 * usefor : 具体的观察者 这里指的是应聘者
 */
package scut.gof.observer;

/**
 * @author Administrator
 * 
 */
public class SomeEmployer implements Observer {
	private Subject subject = null;
	private String employerName = null;

	public SomeEmployer(String name, Subject sub) {
		if (!name.equals("") && name != null) {
			this.employerName = name;
		}
		this.subject = sub;
		this.subject.addObserver(this);
	}

	@Override
	public void update(String str) {
		System.out.println(employerName+"::"+str);
	}
	
	public void removeMyself(){
		subject.delObserver(this);
	}

}
