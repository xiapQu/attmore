/**
 * 
 */
package scut.attmore.shengbo.util;

import java.util.Random;

/**
 * @author Administrator
 * 
 */
public class RandomUtil {
	private static Random rm=new Random();
	private static String chartable[] = { "a", "A", "b", "B", "c", "C", "D", "d", "E",
			"e", "F", "f", "G", "g", "H", "h", "J", "j", "K", "k", "L", "M",
			"m", "N", "n", "P", "p", "Q", "R", "T", "t", "Z", "1", "2", "3",
			"4", "5", "6", "7", "8", "9" };
	/**
	 * ����6λ����������
	 * 
	 * @return
	 */
	public static String getRandomPwd() {
		StringBuilder sb=new StringBuilder();
		for(int i=0;i<6;i++){
			sb.append(getRandomIntNum(9));
		}
		return sb.toString();
	}

	/**
	 * ���ش�Сд���ŵ�6λid
	 * 
	 * @return
	 */
	public static String getRandomId() {
		StringBuilder sb=new StringBuilder();
		for(int i=0;i<6;i++){
			sb.append(chartable[getRandomIntNum(chartable.length)]);
		}
		return sb.toString();
	}

	private static int getRandomIntNum(int limit){	
		return rm.nextInt(limit);
	}
}
