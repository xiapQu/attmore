/**
 * author : Administrator
 * date   : 2012-4-1
 * file   : JobHunterCenter.java
 * prj    : GOFObserver
 * usefor : 具体的主题 这里是求职中心
 */
package scut.gof.observer;

import java.util.ArrayList;

/**
 * @author Administrator
 * 
 */
public class JobHunterCenter implements Subject {
	private ArrayList<Observer> personList = null;
	private boolean flagNewJobs = false;
	private String newJobs = "";

	public JobHunterCenter() {
		personList = new ArrayList<Observer>();
	}

	public void postSomeNewJobs(String jobs) {
		if (newJobs.equals(jobs)) {
			flagNewJobs = false;
		} else {
			newJobs = jobs;
			flagNewJobs = true;
		}
	}

	@Override
	public void addObserver(Observer o) {
		if (!personList.contains(o)) {
			personList.add(o);
		}
	}

	@Override
	public void delObserver(Observer o) {
		// TODO Auto-generated method stub
		if (personList.contains(o)) {
			personList.remove(0);
		}
	}

	@Override
	public void notifyObserver() {
		if (flagNewJobs == true) {
			for (int i = 0; i < personList.size(); i++) {
				personList.get(i).update(newJobs);
			}
		}
		flagNewJobs = false;
	}

}
