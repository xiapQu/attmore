/**
 * author : Administrator
 * date   : 2012-4-27
 * file   : App.java
 * prj    : GOF
 * usefor : ���ģʽ
 * 
 * ���ģʽΪϵͳ�е�һ��ӿ��ṩһ��ͳһ�Ľ��棬Facadeģʽ������һ���߲�ӿڣ�����ӿ�ʹ����һ��ϵͳ��������ʹ�á�
 * 
 * ���ģʽ�Ǽ��û�����ϵͳ���н����ĳ���ģʽ��
 * ���ģʽ�������ֽ�ɫ����ϵͳSubSystem�����Facade
 */
package scut.gof.facade;

/**
 * @author Administrator
 *
 */
public class App {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		PostFacade agent=new PostFacade("ƻ������12̨", "����");
		agent.doPost();

	}

}
