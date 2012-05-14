/**
 * author : Administrator
 * date   : 2012-4-2
 * file   : PanelSwitcher.java
 * prj    : CustomComponents
 * usefor : 
 */
package scut.attmore.ui.view;

import android.content.Context;
import android.util.AttributeSet;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.view.animation.TranslateAnimation;
import android.widget.FrameLayout;

/**
 * @author Administrator
 * 
 */
public class PanelSwitcher extends FrameLayout {
	private final int THRESHOLD = 100; // ���һ����ķ�ֵ
	private final int ANIM_DURATION = 200; // ��������ʱ��
	private GestureDetector mGestureDetector; // ����ʶ��
	private View mChildren[] = new View[0]; // �ӿؼ�

	private int mCurrentView = 0;

	private TranslateAnimation inLeft, outLeft, inRight, outRight;// ����

	public PanelSwitcher(Context context) {
		super(context);
	}

	public PanelSwitcher(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
	}

	public PanelSwitcher(Context context, AttributeSet attrs) {
		super(context, attrs);
		mGestureDetector = new GestureDetector(context,
				new GestureDetector.SimpleOnGestureListener() {

					@Override
					public boolean onFling(MotionEvent e1, MotionEvent e2,
							float velocityX, float velocityY) {
						int dx = (int) (e1.getX() - e2.getX());
						if (Math.abs(dx) > THRESHOLD // �ƶ��ľ�����ڷ�ֵ
														// ����X���ϵ��ƶ��ٶȴ���Y����ƶ��ٶ�
								&& Math.abs(velocityX) > Math.abs(velocityY)) {
							if (velocityX > 0) {
								panelMoveRight();
							} else {
								panelMoveLeft();
							}
							return true;
						} else {
							return false;
						}
					}
				});
	}

	@Override
	protected void onFinishInflate() {
		super.onFinishInflate();
		int count = getChildCount();
		mChildren = new View[count];
		for (int i = 0; i < count; ++i) {
			mChildren[i] = getChildAt(i);
		}
		updateCurrentView();

	}

	private void updateCurrentView() {
		for (int i = mChildren.length - 1; i >= 0; --i) {
			mChildren[i].setVisibility(i == mCurrentView ? View.VISIBLE
					: View.GONE);
		}
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		mGestureDetector.onTouchEvent(event);
		return true;
	}

	@Override
	public boolean onInterceptTouchEvent(MotionEvent event) {
		return mGestureDetector.onTouchEvent(event);
	}

	@Override
	protected void onSizeChanged(int w, int h, int oldw, int oldh) {
		inLeft = new TranslateAnimation(w, 0, 0, 0);
		outLeft = new TranslateAnimation(0, -w, 0, 0);
		inRight = new TranslateAnimation(-w, 0, 0, 0);
		outRight = new TranslateAnimation(0, w, 0, 0);

		inLeft.setDuration(ANIM_DURATION);
		outLeft.setDuration(ANIM_DURATION);
		inRight.setDuration(ANIM_DURATION);
		outRight.setDuration(ANIM_DURATION);
	}

	/**
	 * ������󻬶�
	 */
	private void panelMoveLeft() {
		if (mCurrentView < mChildren.length - 1) {// �ұ߻���View
			mChildren[mCurrentView + 1].setVisibility(View.VISIBLE);
			mChildren[mCurrentView + 1].startAnimation(inLeft);
			mChildren[mCurrentView].startAnimation(outLeft);
			mChildren[mCurrentView].setVisibility(View.GONE);
			mCurrentView++;
		}

	}

	/**
	 * ������һ���
	 */
	private void panelMoveRight() {
		if (mCurrentView > 0) {// ��߻���View
			mChildren[mCurrentView - 1].setVisibility(View.VISIBLE);
			mChildren[mCurrentView - 1].setAnimation(inRight);
			mChildren[mCurrentView].startAnimation(outRight);
			mChildren[mCurrentView].setVisibility(View.GONE);
			mCurrentView--;
		}

	}
	
	
}
