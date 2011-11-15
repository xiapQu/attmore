package scut.attmore.shengbo.ui;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import scut.attmore.shengbo.R;
import scut.attmore.shengbo.util.Act;
import scut.attmore.shengbo.util.ReferenceListAdapter;
import scut.attmore.shengbo.util.ReferenceManager;
import scut.attmore.shengbo.util.SBUtil;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.Toast;

public class ReferenceUI extends BaseActivity {

	public static int position = 1;
	private int pattern = 2;
	private List<String> itemsList = null; //存放文件全称
	private List<String> pathsList = null; //存放路径
	private List<String> wavnameList = null; //存放名称
	private List<Boolean> judgementList = null; //存放名称
	private String rootPath = ""; //根目录
	private String des = "";
	private ListView listView;	
	private Builder chooseBuilder; //发送类型选择对话框
	private Builder askBuilder; //是否再次发送对话框
	private SharedPreferences setting = null;
		
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		
		setContentView(R.layout.reference_ui);
		
		Act.add(ReferenceUI.this);
		
		Toast.makeText(getApplicationContext(), "点击文件名可播放录音哦~", Toast.LENGTH_SHORT).show();
		
		setting = ReferenceManager.getInstance(
				this).getSetting();
		
		rootPath = SBUtil.getSDPath() + "/shengbo/";
		
		listView = (ListView) findViewById(R.id.wavList);
		
		ChooseDialogBuild();
		AskDialogBuild();
	}
	
	private void getFileDir(String filePath) {

		itemsList = new ArrayList<String>();
		pathsList = new ArrayList<String>();
		wavnameList = new ArrayList<String>();
		judgementList = new ArrayList<Boolean>();
		
		File f = new File(filePath);
		File[] files = f.listFiles();
		
		for( int i = 0; i < files.length; i++ )
		{
			File fileTemp = files[i];
			if (fileTemp.getName().endsWith(".wav")) {
				itemsList.add(fileTemp.getName());
				pathsList.add(fileTemp.getPath());
				wavnameList.add(fileTemp.getName().substring(0, fileTemp.getName().length()-4));
				judgementList.add(setting.getBoolean(fileTemp.getName(), false));
			}
		}
		
		ReferenceListAdapter referenceListAdapter = new ReferenceListAdapter(getApplicationContext(), 
				itemsList, pathsList, chooseBuilder, askBuilder, judgementList);
		
		listView.setAdapter(referenceListAdapter);
	}
	
	private void ChooseDialogBuild(){
		chooseBuilder = new AlertDialog.Builder(this);
		chooseBuilder.setTitle("请选择发送类型");
		chooseBuilder.setSingleChoiceItems(new String[]{ "雷锋的约定", "我要报料" ,"微博留声机" }, 1,
				new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface arg0, int arg1) {
				switch (arg1) {
				case 0:
					pattern = 1;
					break;
					
				case 1:
					pattern = 2;
					break;
					
				case 2:
					pattern = 3;
					break;

				default:
					break;
				}
				
			}
		});
		chooseBuilder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface arg0, int arg1) {
				Intent intent = new Intent( ReferenceUI.this, SendBroadcastMessage.class);
				des = setting.getString(wavnameList.get(position), "");
				intent.putExtra("des",des);
				intent.putExtra("filename", itemsList.get(position));
				intent.putExtra("filepath", pathsList.get(position));
				intent.putExtra("wavname", wavnameList.get(position));
				intent.putExtra("pattern", pattern);
				startActivity(intent);
			}
		});
		chooseBuilder.create();
	}
	
	private void AskDialogBuild(){
		askBuilder = new AlertDialog.Builder(this);
		askBuilder.setTitle("再次发送?");
		askBuilder.setMessage("这则声博已曾经发送.确认再次发送?");
		askBuilder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface arg0, int arg1) {
				 chooseBuilder.show();
			}
		});
		askBuilder.setNegativeButton("取消", new DialogInterface.OnClickListener(){

			@Override
			public void onClick(DialogInterface arg0, int arg1) {
				
			}			
		});
		askBuilder.create();
	}
	
	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
		getFileDir(rootPath);
	}
}
