<?php
/**
 * PHP飞信发送类
 * @author quanhengzhuang <blog.quanhz.com>
 * @author modify by Attmore<Attmore@163.com>
 * @version 1.2.1
 */
class PHPFetion {
	
	/**
	 * 发送者手机号
	 * @var string
	 */
	protected $_mobile;
	
	/**
	 * 飞信密码
	 * @param string
	 */
	protected $_password;
	
	/**
	 * Cookie字符串
	 * @param string
	 */
	protected $_cookie = '';
	
	/**
	 * 构造函数
	 * @param string $mobile 手机号(登录者)
	 * @param string $password 飞信密码
	 */
	public function __construct($mobile, $password) {
		if($mobile === '' || $password === '') {
			return false;
		}
		
		$this->_mobile = $mobile;
		$this->_password = $password;
		
		$this->_login();
	}
	
	/**
	 * 析构函数
	 */
	public function __destruct() {
		$this->_logout();
	}
	
	/**
	 * 登录
	 * @return string
	 */
	protected function _login() {
		$uri = '/im/login/inputpasssubmit1.action';
		$data = 'm='.$this->_mobile.'&pass='.urlencode($this->_password).'&loginstatus=1';
		
		$result = $this->_postWithCookie($uri, $data);
		
		// 解析Cookie
		preg_match_all('/.*?\r\nSet-Cookie: (.*?);.*?/si', $result, $matches);
		if(isset($matches[1])) {
			$this->_cookie = implode('; ', $matches[1]);
		}

		return $result;
	}
	/**
	 * 添加新用户到默认分组
	 * @param string $tel 用户电话
	 * @param string $nickname 发送邀请时显示的昵称
	 * 
	 */
	public function AddFriends($tel,$nickname){
		$uri='/im/user/insertfriendsubmit.action';
		$data='number='.$tel.'&buddylist=0&type=0&nickname='.$nickname;
		
		$result=$this->_postWithCookie($uri,$data);
		return $result;
	}

	/**
	 * 向指定的手机号发送飞信
	 * @param string $mobile 手机号(接收者)
	 * @param string $message 短信内容
	 * @return string
	 */
	public function send($mobile, $message) {
		if($message === '') {
			return '';
		}

		// 判断是给自己发还是给好友发
		// 如果接收的号码和登录时的号码相同，则调用发送给自己的方法。
		if($mobile == $this->_mobile) {
			return $this->_toMyself($message);
		} else {
		//获得用户的uid
			$uid = $this->_getUid($mobile);
			return $uid === '' ? '' : $this->_toUid($uid, $message);
		}
	}
	
	public function GetUserInfoByTel($tel){
		$uid=$this->_getUid($tel);
		$uri='/im/user/userinfoByuserid.action';
		$data='touserid='.$uid;
		
		$result=$this->_postWithCookie($uri,$data);
		return $result;
		//$uri='/im/index/onlinesuserinfo.action';
		//$data='gender=2&tp=info&touserid='.$uid;
		
		//$result=$this->_postWithCookie($uri,$data);
		
		//return $result;
	}
	/**
	 * 获取飞信ID
	 * @param string $mobile 手机号
	 * @return string
	 */
	protected function _getUid($mobile) {
		$uri = '/im/index/searchOtherInfoList.action';
		$data = 'searchText='.$mobile;
		
		$result = $this->_postWithCookie($uri, $data);
		
		// 匹配
		preg_match('/toinputMsg\.action\?touserid=(\d+)/si', $result, $matches);
		
		return isset($matches[1]) ? $matches[1] : '';
	}
	
	/**
	 * 向好友发送飞信
	 * @param string $uid 飞信ID
	 * @param string $message 短信内容
	 * @return string
	 */
	protected function _toUid($uid, $message) {
		$uri = '/im/chat/sendMsg.action?touserid='.$uid;
		$data = 'msg='.urlencode($message);
		
		$result = $this->_postWithCookie($uri, $data);
		
		return $result;
	}
	
	/**
	 * 给自己发飞信
	 * @param string $message
	 * @return string
	 */
	protected function _toMyself($message) {
		$uri = '/im/user/sendMsgToMyselfs.action';
		$result = $this->_postWithCookie($uri, 'msg='.urlencode($message));
		
		return $result;
	}
	
	/**
	 * 退出飞信
	 * @return string
	 */
	protected function _logout() {
		$uri = '/im/index/logoutsubmit.action';
		$result = $this->_postWithCookie($uri, '');
		
		return $result;
	}
	
	/**
	 * 携带Cookie向f.10086.cn发送POST请求
	 * @param string $uri
	 * @param string $data
	 */
	protected function _postWithCookie($uri, $data) {
		$fp = fsockopen('f.10086.cn', 80);
		fputs($fp, "POST $uri HTTP/1.1\r\n");
		fputs($fp, "Host: f.10086.cn\r\n");
		fputs($fp, "Cookie: {$this->_cookie}\r\n");
		fputs($fp, "Content-Type: application/x-www-form-urlencoded\r\n");
		fputs($fp, "Content-Length: ".strlen($data)."\r\n");
		fputs($fp, "Connection: close\r\n\r\n");
		fputs($fp, $data);

		$result = '';
		while(!feof($fp)) {
			$result .= fgets($fp);
		}

		fclose($fp);

		return $result;
	}
	
	
	protected function _getWithCookie($uri,$data){
		$fp = fsockopen('f.10086.cn', 80);
		fputs($fp, "GET $uri HTTP/1.1\r\n");
		fputs($fp, "Host: f.10086.cn\r\n");
		fputs($fp, "Cookie: {$this->_cookie}\r\n");
		fputs($fp, "Content-Type: application/x-www-form-urlencoded\r\n");
		fputs($fp, "Content-Length: ".strlen($data)."\r\n");
		fputs($fp, "Connection: close\r\n\r\n");
		fputs($fp, $data);

		$result = '';
		while(!feof($fp)) {
			$result .= fgets($fp);
		}

		fclose($fp);

		return $result;
	}

}
