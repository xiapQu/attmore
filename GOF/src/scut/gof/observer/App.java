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
		SomeEmployer stu=new SomeEmployer("实习生", center);
		SomeEmployer haigui=new SomeEmployer("海归派", center);
		
		center.postSomeNewJobs("腾讯招聘3人");
		center.notifyObserver();
		center.postSomeNewJobs("SCUT招聘120人");
		center.notifyObserver();
		center.postSomeNewJobs("百合网招聘3人");
		center.notifyObserver();
		center.postSomeNewJobs("百合网招聘3人");
		center.notifyObserver();
		stu.removeMyself();
		center.postSomeNewJobs("年薪10000W招聘兼职");
		center.notifyObserver();
	}

}
