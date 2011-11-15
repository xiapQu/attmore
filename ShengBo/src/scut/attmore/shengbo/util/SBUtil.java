package scut.attmore.shengbo.util;

import java.io.File;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;

import android.os.Environment;

public class SBUtil {
	
	public static String getFileName() 
    {
    	SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd_HH-mm-ss_SS");
    	String fileName = format.format( new Timestamp( System.currentTimeMillis()) );
    	return fileName;
    }
	
	public static String getCamerePath()
    {
    	return getSDPath()+"/shengbo/";
    }
	
	//获取SD卡路径
	public static String getSDPath() {
        // 获取SdCard状态
        String state = Environment.getExternalStorageState();
        // 判断SdCard是否存在并且是可用的
        if (Environment.MEDIA_MOUNTED.equals(state)) {
             if (Environment.getExternalStorageDirectory().canWrite()) {
                  return Environment.getExternalStorageDirectory().getPath();
             }
        }
        return null;
	}
}
