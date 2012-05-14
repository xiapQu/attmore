package scut.gof.observer;
/**
 * author : Administrator
 * date   : 2012-4-1
 * file   : Subject.java
 * prj    : GOFObserver
 * usefor : �۲������ģʽ�е�Subject
 */

/**
 * @author Administrator
 *
 */
public interface Subject {
	public void addObserver(Observer o);
	public void delObserver(Observer o);
	public void notifyObserver();
}
