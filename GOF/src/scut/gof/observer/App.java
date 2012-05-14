/**
 * author : Administrator
 * date   : 2012-4-1
 * file   : App.java
 * prj    : GOFObserver
 * usefor : 
 */
package scut.gof.observer;

/**
 * @author Administrator
 *
 */
public class App {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		JobHunterCenter center=new JobHunterCenter();
		SomeEmployer stu=new SomeEmployer("ʵϰ��", center);
		SomeEmployer haigui=new SomeEmployer("������", center);
		
		center.postSomeNewJobs("��Ѷ��Ƹ3��");
		center.notifyObserver();
		center.postSomeNewJobs("SCUT��Ƹ120��");
		center.notifyObserver();
		center.postSomeNewJobs("�ٺ�����Ƹ3��");
		center.notifyObserver();
		center.postSomeNewJobs("�ٺ�����Ƹ3��");
		center.notifyObserver();
		stu.removeMyself();
		center.postSomeNewJobs("��н10000W��Ƹ��ְ");
		center.notifyObserver();
	}

}
