package scut.attmore.shengbo.util;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;

public class Act{
	static List<Activity> activities;
	
	public static void init() {
		if (activities == null) {
			activities = new ArrayList<Activity>();
		}	
	}
	
	public static void add(Activity activity) {
		activities.add(activity);
	}
	
	public static List<Activity> get(){
		return activities;
	}
	
	public static void delete(){
		for (int i = 0; i < activities.size(); i++) {
			 try {
				 activities.get(i).finish();
			} catch (Exception e) {
				// TODO: handle exception
			}
		}
	}
}
