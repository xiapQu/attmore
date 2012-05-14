/**
 * author : Administrator
 * date   : 2012-4-1
 * file   : RadioButtomEx.java
 * prj    : CustomComponents
 * usefor : ¿©’πRadioButton£¨ µœ÷Key-Value¥Ê¥¢
 */
package scut.attmore.ui.view;

import scut.attmore.ui.R;
import android.content.Context;
import android.content.res.TypedArray;
import android.util.AttributeSet;
import android.widget.RadioButton;

/**
 * @author Administrator
 * 
 */
public class RadioButtonEx extends RadioButton {
	public String mValues;

	public RadioButtonEx(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		TypedArray ta = context.obtainStyledAttributes(attrs,
				R.styleable.RadioButtonEx);
		this.mValues = ta.getString(R.styleable.RadioButtonEx_value);
		ta.recycle();
	}

	public RadioButtonEx(Context context, AttributeSet attrs) {
		super(context, attrs);
		TypedArray ta = context.obtainStyledAttributes(attrs,
				R.styleable.RadioButtonEx);
		this.mValues = ta.getString(R.styleable.RadioButtonEx_value);
		ta.recycle();
	}

	public RadioButtonEx(Context context) {
		super(context);
	}

	public String getValues() {
		return mValues;
	}

	public void setValues(String mValues) {
		this.mValues = mValues;
	}

}
